// Exercise 1
//
// Try to read and understand the following commented code
// Run it and try to break it and extend it with new features, I want you to
// explore it. Try to point the features that you identified in the categories
// of things in the education plan:
// https://link.excalidraw.com/l/hxPegpAmTX/7Dd2cuSCIQY

#include <iostream>
#include <optional>
#include <variant>
#include <vector>

// templates allow to create several copies of a class with different type
// parameters replaced inside for everything that we need replaced
template <typename NodeData, typename EdgeData> 
struct Graph {
private:
  // It is possible to nest type declarations, this is useful when types depend
  // on other types, or when you want to hide a type
  struct Node {
    // https://en.cppreference.com/w/cpp/language/attributes
    [[no_unique_address]] NodeData value;
    std::vector<std::pair<size_t, EdgeData>> edges;
  };

  // https://www.foonathan.net/2020/03/iterator-sentinel/
  struct EndNodeRef;
  struct NodeRef {
    NodeRef &operator++() {
      ++idx;
      // "this" is a pointer to the current object, it should have been a
      // reference, but they didn't exist when "this" was added to C++
      return *this;
    }

    NodeRef operator+(size_t n) {
      // this implements "some_node_ref + number", it however doesn't implement
      // "number + some_node_ref"
      auto cpy = *this;
      cpy.idx += n;
      return cpy;
    }

    bool operator==(const EndNodeRef &) const {
      // Compare with sentinel means check if we are out of bounds
      return idx >= owner.m.data.size();
    }


    // https://www.cppstories.com/2023/monadic-optional-ops-cpp23/
    std::optional<NodeData *> operator*() {
      return index().transform(
          [](auto *v) -> NodeData * { return &(v->value); });
    }

    // "using" is used to define type aliases. This aliases
    // "std::vector<std::pair<size_t, EdgeData>>" into the name "edge_list"
    using edge_list = std::vector<std::pair<size_t, EdgeData>>;

    std::optional<const edge_list> edges() {
      if (owner.m.data.size() > idx) {
        return owner.m.data[idx].edges;
      }
      return std::nullopt;
    }

    bool link_edge(const NodeRef &link_to, const EdgeData &data) {
      // In C++, you can define a function that will "capture" the local scope.
      // Called a lambda, those functions
      //     are actually internally a struct with an operator() and the
      //     captured members are its contents.
      // [capture](arguments){code...} is the basic syntax.
      // if capture is = "[=](arguments){code...}" then everything that is
      // captured is copied in the lambda if capture is &
      // "[&](arguments){code...}" then everything that is captured as a
      // reference to the original
      //     value in the lambda
      // if capture is empty "[](arguments){code...}" then nothing is captured
      auto v = index().transform([&](Node *node) -> bool {
        // We need to verify if both nodes are in the same graph, for that we
        // use the "addressof" function that returns where in memory the data is
        // sitting
        if (link_to.idx >= owner.size() or
            std::addressof(link_to.owner) != std::addressof(owner)) {
          return false;
        }
        // -> is used when the left side is a pointer or smart pointer
        // . is used when the left side is a value or a reference
        node->edges.push_back({link_to.idx, data});
        return true;
      });
      return v.value_or(false);
    }

    // Everything in the scope that follows "private:" is hidden from the
    // outside, except to friends who can still access it
  private:
    // https://en.cppreference.com/w/cpp/language/constructor
    NodeRef(Graph &graph, size_t in_idx) : owner{graph}, idx{in_idx} {}

    std::optional<Node *> index() {
      // Thanks to optional, all the unsafe things you can do are contained in
      // this function
      if (owner.size() > idx) {
        return std::addressof(owner.m.data[idx]);
      }
      return std::nullopt;
    }

    // References MUST be initialized, so the constructor is REQUIRED to
    // initialize it
    Graph &owner;
    size_t idx;

    // https://en.cppreference.com/w/cpp/language/friend
    friend Graph;
  };

  struct EndNodeRef {
    bool operator==(const NodeRef &value) const {
      // implementing the flipped operator, by using the other one
      return value == *this;
    }
  };

  // Everything in the scope that follows "public:" is visible from the outside
public:
  NodeRef begin() {
    // the first index is 0
    return NodeRef{*this, 0};
  }

  EndNodeRef end() {
    // the "last" index is the sentinel
    return EndNodeRef{};
  }

  size_t size() { return m.data.size(); }

  NodeRef insert(const NodeData &data) {
    m.data.push_back(Node{.value = data, .edges = {}});
    // reference to the last thing (that we just inserted) is the one at the
    // position size() - 1 (because we index from 0
    return NodeRef{*this, size() - 1};
  }

private:
  // https://www.youtube.com/watch?v=KWB-gDVuy_I
  struct internals {
    std::vector<Node> data;
  };
  internals m;
};

int main() {
  // std::monostate is just an empty type (hence, there is only one state it can
  // be in, hence "monostate")
  Graph<std::string, std::monostate> graph;
  auto one = graph.insert("one");
  auto two = graph.insert("two");
  auto three = graph.insert("three");
  auto four = graph.insert("four");
  one.link_edge(two, {});
  one.link_edge(three, {});
  one.link_edge(four, {});
  two.link_edge(four, {});
  three.link_edge(four, {});

  // Before range-for loops, this is how we iterated over things, since the
  // class above doesn't have a good interface for range-for loops, we need to
  // do it the old way
  for (auto it = graph.begin(); it != graph.end(); ++it) {
    // decltype(A) gives you the type of the variable A, for example here, it
    // returns the correct type of NodeRef
    auto edge_list = it.edges().value_or(decltype(it)::edge_list{});
    std::cout
        << (*it).transform([](auto *v) { return *v; }).value_or("[UNKNOWN]")
        << " links to " << edge_list.size() << " node(s):\n";
    for (const auto &edge : edge_list) {
      std::cout << "\t"
                << (*(graph.begin() + edge.first))
                       .transform([](auto *v) { return *v; })
                       .value_or("[UNKNOWN]")
                << "\n";
    }
  }
  return 0;
}

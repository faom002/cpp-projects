// From the provided diagram and code, try to implement the other diagram into
// code https://link.excalidraw.com/l/hxPegpAmTX/2XTbnG16BYY

#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

struct Product {

  int price;
  std::string name;

public:
  Product(std::string name, int price) : name(name), price(price) {}
};

struct InvoiceLine {

  std::shared_ptr<Product> products =
      std::make_shared<Product>("balenciaga", 200);

  std::optional<int> line_price() {

    if (products->price > 0) {
      return products->price * quantity;
    }
    return {};
  }

  int quantity = 0;
};

struct Invoice {

  std::vector<InvoiceLine> invoices;

  int total_price() {
    int price = 0;
    for (auto &inv : invoices) {

      price = inv.line_price().value_or(0);
    
    }

    return price;
  }
};

int main() {
  Invoice inv;
  InvoiceLine line;

  line.quantity = 3;
  inv.invoices.emplace_back(line);
  
  std::cout << inv.total_price() << "\n";
}

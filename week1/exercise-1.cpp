#include <algorithm>
#include <cctype>
#include <vector>
#include <string>
#include <iostream>
int main() {
std::vector<std::string> numbers {"zero", "one", "two",
"three"};


// cpp reference for solution

// We can use 'auto' to omit giving the type explicitly
for(auto number : numbers) {
    std::transform(number.begin(), number.end(), number.begin(), ::toupper);
    std::cout << number << "\n";
}
}

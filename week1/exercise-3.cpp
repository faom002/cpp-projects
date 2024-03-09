#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

void sum_of_both_vectors(std::vector<int> sales_london,
                         std::vector<int> sales_paris);

int main() {

  std::vector<int> sales_london{12, 32, 54, 87};

  std::vector<int> sales_paris{54, 56, 85, 10};

  sum_of_both_vectors(sales_london, sales_paris);
}

void sum_of_both_vectors(std::vector<int> sales_london,
                         std::vector<int> sales_paris) {

    // solution i made

  //
  // for (size_t i = 0; i < sales_london.size(); i++) {
  //
  //     for (size_t j = 0; j < sales_paris.size(); j++) {
  //
  //        std::cout << sales_paris[j] + sales_london[i] << "\n";
  //
  //
  //     }
  //
  // }
  

    //solution i found on stackoverflow

  std::transform(sales_london.begin(), sales_london.end(), sales_paris.begin(),
                 sales_london.begin(), std::plus<int>());

  for (size_t i = 0; i < sales_london.size(); i++) {

    std::cout << sales_london[i] << "\n";
  }
}

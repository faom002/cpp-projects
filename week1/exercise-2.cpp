#include <cstddef>
#include <iostream>
#include <vector>

void convert_fahrenheit_to_celsius(std::vector<float> fahrenheit,
                                   std::vector<float> celsius);

int main() {
  std::vector<float> temperatures_fahrenheit{-3.0, 120.0, 27.0, 68.0};
  std::vector<float> temperatures_celcius;

  convert_fahrenheit_to_celsius(temperatures_fahrenheit,
                                temperatures_fahrenheit);
}

void convert_fahrenheit_to_celsius(std::vector<float> fahrenheit,
                                   std::vector<float> celsius) {

  float fahrenheit_freezing_point = 32.0;
  float celsius_value = 0;
  for (size_t i = 0; i < fahrenheit.size(); i++) {

    celsius_value = (fahrenheit[i] - fahrenheit_freezing_point) * 5 / 9;

    celsius.push_back(celsius_value);
  }

  for (size_t i = 0; i < celsius.size(); i++) {
    std::cout << celsius[i] << "\n";
  }
}

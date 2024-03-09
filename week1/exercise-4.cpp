#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>
int main() {
  std::string text = "Two roads diverged in a yellow wood,And sorry I could not travel both And be one traveler, long I stood And looked down one as far as I could To where it bent in the undergrowth ";

  for (size_t i = 0; i < text.length(); i++) {
  
    if (i == 0 || text[i - 1] == ' ')
        {
            text[i] = toupper(text[i]); 
        }
  }


  std::cout << text << "\n";


}


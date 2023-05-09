#include <iostream>

#include "bstring.hpp"

extern "C" {
// Forward declare from rust
void get_bstring1(char* bstrData);
}


int main() {
    BString bstr;
    get_bstring1(bstr.data);

    std::cout << bstr.to_cpp() << std::endl;
}

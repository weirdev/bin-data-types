#include <iostream>

#include "bstring.hpp"
#include "blist.hpp"

extern "C" {
// Forward declare from rust
void get_bstring1(char* bstrData);

void get_blist_string1(char* blistData);
}

// Macro and combine with decl?
template<typename T, typename F>
T binTFromWire(F wireFn) {
    T binT{};
    wireFn(binT.data);
    return binT;
}

void string1Test() {
    auto bstr = binTFromWire<BString>(get_bstring1);
    std::cout << bstr.to_cpp() << std::endl;
}

void listString1Test() {
    auto blist = binTFromWire<BList<BString>>(get_blist_string1);

    auto bIt = blist.to_cpp();

    for (size_t i = 0; i < bIt.size; ++i) {
        std::cout << bIt.ptr->to_cpp() << std::endl;
        ++bIt.ptr;
    }
}

int main() {
    string1Test();
    listString1Test();
}

#include <iostream>

#include "bint32.hpp"
#include "bstring.hpp"
#include "blist.hpp"
#include "bmap.hpp"

extern "C" {
// Forward declare from rust
void get_bstring1(char* bstrData);

void get_blist_string1(char* blistData);

void get_bmap_string_int1(char* bmapData);
}

// Macro and combine with decl?
template<typename T, typename F>
T binTFromWire(F wireFn) {
    T binT{};
    wireFn((char *)&binT);
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

void mapStringInt1Test() {
    auto bmap = binTFromWire<BMap<BString, BInt32>>(get_bmap_string_int1);

    auto bIt = bmap.to_cpp();

    for (size_t i = 0; i < bIt.size; ++i) {
        auto kvPair = bIt.ptr->to_cpp();
        std::cout << std::get<0>(kvPair).to_cpp() << ":" << std::get<1>(kvPair).to_cpp() << std::endl;
        ++bIt.ptr;
    }
}

int main() {
    string1Test();
    listString1Test();
    mapStringInt1Test();
}

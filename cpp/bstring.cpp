#include "bstring.hpp"

BString::BString() {
    *(char**)&data[0] = nullptr;
    *(size_t*)(&data[8]) = 0;
}

BString::BString(std::string_view str) {
    auto dataPtr = (char*)malloc(str.size());
    memcpy(dataPtr, str.data(), str.size());

    *(char**)&data[0] = dataPtr;
    *(size_t*)(&data[8]) = str.size();
}

BString::BString(BString&& other) {
    *(char**)&data[0] = *(char**)&other.data[0];
    *(size_t*)(&data[8]) = *(size_t*)(&other.data[8]);

    *(char**)&other.data[0] = nullptr;
    *(size_t*)(&other.data[8]) = 0;
}

BString& BString::operator=(BString&& other) {
    freeData();

    *(char**)&data[0] = *(char**)&other.data[0];
    *(size_t*)(&data[8]) = *(size_t*)(&other.data[8]);

    *(char**)&other.data[0] = nullptr;
    *(size_t*)(&other.data[8]) = 0;

    return *this;
}

std::string_view BString::to_cpp() {
    auto dataPtr = *(char**)&data[0];
    auto count = *(size_t*)(&data[8]);

    return std::string_view(dataPtr, count);
}

void BString::freeData() {
    auto dataPtr = *(char**)&data[0];
    if (dataPtr != nullptr) free(dataPtr);
}

#include <iostream>
#include <string_view>
#include <cstring>

struct BString {
    char data[16];

    public:
        BString() {
            *(char**)&data[0] = nullptr;
            *(size_t*)(&data[8]) = 0;
        }

        BString(std::string_view str) {
            auto dataPtr = (char*)malloc(str.size());
            memcpy(dataPtr, str.data(), str.size());

            *(char**)&data[0] = dataPtr;
            *(size_t*)(&data[8]) = str.size();
        }

        BString(const BString& other) = delete;

        BString(BString&& other) {
            *(char**)&data[0] = *(char**)&other.data[0];
            *(size_t*)(&data[8]) = *(size_t*)(&other.data[8]);

            *(char**)&other.data[0] = nullptr;
            *(size_t*)(&other.data[8]) = 0;
        }

        BString& operator=(const BString& other) = delete;

        BString& operator=(BString&& other) {
            freeData();

            *(char**)&data[0] = *(char**)&other.data[0];
            *(size_t*)(&data[8]) = *(size_t*)(&other.data[8]);
            
            *(char**)&other.data[0] = nullptr;
            *(size_t*)(&other.data[8]) = 0;

            return *this;
        }

        ~BString() {
            freeData();
        }

        std::string_view to_cpp() {
            auto dataPtr = *(char**)&data[0];
            auto count = *(size_t*)(&data[8]);

            return std::string_view(dataPtr, count);
        }
    
    private:
        void freeData() {
            auto dataPtr = *(char**)&data[0];
            if (dataPtr != nullptr) free(dataPtr);
        }
};

extern "C" {
// Forward declare from rust
void get_bstring1(char* bstrData);
}


int main() {
    BString bstr;
    get_bstring1(bstr.data);

    std::cout << bstr.to_cpp() << std::endl;
}
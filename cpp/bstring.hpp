#include <string_view>

struct BString {
    char data[16];

    public:
        BString();

        BString(std::string_view str);

        BString(const BString& other) = delete;

        BString(BString&& other);

        BString& operator=(const BString& other) = delete;

        BString& operator=(BString&& other);

        ~BString() {
            freeData();
        }

        std::string_view to_cpp();

    private:
        void freeData();
};

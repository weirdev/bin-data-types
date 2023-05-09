#include <utility>

template<typename T>
struct BListIt {
    T* ptr;
    size_t size;
};

template<typename T>
struct BList {
    char data[16];

    public:
        BList() {
            *(T**)&data[0] = nullptr;
            *(size_t*)(&data[8]) = 0;
        }

        BList(const T* start, size_t size) {
            auto dataPtr = new T[size];
            for (size_t i = 0; i < size; ++i) {
                dataPtr[i] = T(*start);
                ++start;
            }

            *(T**)&data[0] = dataPtr;
            *(size_t*)(&data[8]) = size;
        }

        BList(T* start, size_t size) {
            auto dataPtr = new T[size];
            for (size_t i = 0; i < size; ++i) {
                dataPtr[i] = std::move(*start);
                ++start;
            }

            *(T**)&data[0] = dataPtr;
            *(size_t*)(&data[8]) = size;
        }

        BList(const BList<T>& other) = delete;

        BList(BList<T>&& other) {
            *(T**)&data[0] = *(T**)&other.data[0];
            *(size_t*)(&data[8]) = *(size_t*)(&other.data[8]);

            *(T**)&other.data[0] = nullptr;
            *(size_t*)(&other.data[8]) = 0;
        }

        BList<T>& operator=(const BList<T>& other) = delete;

        BList<T>& operator=(BList<T>&& other) {
            freeData();

            *(T**)&data[0] = *(T**)&other.data[0];
            *(size_t*)(&data[8]) = *(size_t*)(&other.data[8]);

            *(T**)&other.data[0] = nullptr;
            *(size_t*)(&other.data[8]) = 0;

            return *this;
        }

        ~BList() {
            freeData();
        }

        BListIt<T> to_cpp() {
            return BListIt<T>{*(T**)(&data[0]), *(size_t*)(&data[8])};
        }

    private:
        void freeData() {
            auto dataPtr = *(T**)&data[0];
            if (dataPtr != nullptr) delete dataPtr;
        }
};

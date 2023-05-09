#include <utility>
#include <tuple>

template <typename K, typename V>
struct KVPair {
    char data[sizeof(K) + sizeof(V)];

    public:
        KVPair() {
            *(K*)&data[0] = K{};
            *(V*)&data[sizeof(K)] = V{};
        }

        KVPair(K key, V value) {
            *(K*)&data[0] = std::move(key);
            *(V*)&data[sizeof(K)] = std::move(value);
        }

        KVPair(const KVPair<K, V>&) = delete;

        KVPair(KVPair<K, V>&& other) {
            memcpy(data, other.data, sizeof(K) + sizeof(V));

            *(K*)&other[0] = K{};
            *(V*)&other[sizeof(K)] = V{};
        }

        KVPair& operator=(const KVPair&) = delete;

        KVPair& operator=(KVPair&& other) {
            freeData();

            memcpy(data, other.data, sizeof(K) + sizeof(V));

            *(K*)&other[0] = K{};
            *(V*)&other[sizeof(K)] = V{};
        }

        ~KVPair() {
            freeData();
        }

        std::tuple<const K&, const V&> to_cpp() const {
            return {*(K*)&data[0], *(V*)&data[sizeof(K)]};
        }

        std::tuple<K&, V&> to_cpp() {
            return {*(K*)&data[0], *(V*)&data[sizeof(K)]};
        }

    private:
        void freeData() {
            auto& key = *(K*)&data[0];
            key.~K();
            auto& value = *(V*)&data[sizeof(K)];
            value.~V();
        }
};

template<typename K, typename V>
struct BMapIt {
    KVPair<K, V>* ptr;
    size_t size;
};

template<typename K, typename V>
struct BMap {
    char data[16];

    public:
        BMap() {
            *(KVPair<K, V>**)&data[0] = nullptr;
            *(size_t*)(&data[8]) = 0;
        }

        BMap(const KVPair<K, V>* start, size_t size) {
            auto dataPtr = new KVPair<K, V>[size];
            for (size_t i = 0; i < size; ++i) {
                dataPtr[i] = KVPair<K, V>(*start);
                ++start;
            }

            *(KVPair<K, V>**)&data[0] = dataPtr;
            *(size_t*)(&data[8]) = size;
        }

        BMap(KVPair<K, V>* start, size_t size) {
            auto dataPtr = new KVPair<K, V>[size];
            for (size_t i = 0; i < size; ++i) {
                dataPtr[i] = std::move(*start);
                ++start;
            }

            *(KVPair<K, V>**)&data[0] = dataPtr;
            *(size_t*)(&data[8]) = size;
        }

        BMap(const BMap<K, V>& other) = delete;

        BMap(BMap<K, V>&& other) {
            *(KVPair<K, V>**)&data[0] = *(KVPair<K, V>**)&other.data[0];
            *(size_t*)(&data[8]) = *(size_t*)(&other.data[8]);

            *(KVPair<K, V>**)&other.data[0] = nullptr;
            *(size_t*)(&other.data[8]) = 0;
        }

        BMap<K, V>& operator=(const BMap<K, V>& other) = delete;

        BMap<K, V>& operator=(BMap<K, V>&& other) {
            freeData();

            *(KVPair<K, V>**)&data[0] = *(KVPair<K, V>**)&other.data[0];
            *(size_t*)(&data[8]) = *(size_t*)(&other.data[8]);

            *(KVPair<K, V>**)&other.data[0] = nullptr;
            *(size_t*)(&other.data[8]) = 0;

            return *this;
        }

        ~BMap() {
            freeData();
        }

        BMapIt<const K, const V> to_cpp() const {
            return BMapIt<const K, const V>{*(KVPair<K, V>**)(&data[0]), *(size_t*)(&data[8])};
        }

        BMapIt<K, V> to_cpp() {
            return BMapIt<K, V>{*(KVPair<K, V>**)(&data[0]), *(size_t*)(&data[8])};
        }

    private:
        void freeData() {
            auto dataPtr = *(KVPair<K, V>**)&data[0];
            if (dataPtr != nullptr) delete dataPtr;
        }
};

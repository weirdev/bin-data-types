struct BInt32 {
    char data[4];

    public:
        explicit BInt32(int value) {
            *(int*)(&data[0]) = value;
        }

        int to_cpp() const {
            return *(int*)(&data[0]);
        }
};

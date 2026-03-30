#pragma once
#include <cstdint>

class bitset
{
private:
    uint64_t * data;
    size_t capacity_bits;

    size_t units_count() const ;
    void resize(size_t new_bits_count);


public:
    bitset();
    ~bitset();
    explicit bitset(size_t initial_capacity);
    bitset(const bitset& other);
    bitset(bitset&& other) noexcept;

    bitset& operator=(bitset other);
    bitset operator*(bitset other) const;
    bitset operator+(bitset other) const;

    bool test(int index);
    void set(int index, bool val);
    bool empty();
    int size() const;
    bitset union_with(const bitset& set) const;
    bitset intersection(const bitset& set) const;
    bool is_subnet(const bitset& set) const;
    void clear();
};



#include "bitset.h"
#include <algorithm>
#include <cstring>

size_t bitset::units_count() const
{
    return (capacity_bits + 63) / 64;
}

void bitset::resize(size_t new_bits_count)
{
    size_t old_units = units_count();
    capacity_bits = std::max(new_bits_count, capacity_bits * 2);
    if (capacity_bits < 64)
    {
        capacity_bits = 64;
    }
    size_t new_units = units_count();
    uint64_t *new_data = new uint64_t[new_units]();

    if (data)
    {
        std::memcpy(new_data, data, old_units * sizeof(uint64_t));
        delete[] data;
    }
    data = new_data;
}

bitset::bitset() : data(nullptr), capacity_bits(0)
{

}

bitset::bitset(size_t initial_capacity) : capacity_bits(initial_capacity)
{
    size_t units = units_count();
    if (units > 0)
    {
        data = new uint64_t[units]();
    }
    else
    {
        data = nullptr;
    }
}

bitset::~bitset()
{
    delete[] data;
}

bitset::bitset(const bitset &other) : capacity_bits(other.capacity_bits)
{
    size_t units = units_count();
    if (units > 0)
    {
        data = new uint64_t[units]();
    }
    else
    {
        data = nullptr;
    }
    if (data)
    {
        std::memcpy(data, other.data, units * sizeof(uint64_t));
    }
}

bitset::bitset(bitset &&other) noexcept : data(other.data), capacity_bits(other.capacity_bits)
{
    other.data = nullptr;
    other.capacity_bits = 0;
}

bitset &bitset::operator=(bitset other)
{
    std::swap(capacity_bits, other.capacity_bits);
    std::swap(data, other.data);
    return *this;
}

void bitset::set(int index, bool val)
{
    if (val)
    {
        if (index >= capacity_bits)
        {
            resize(index + 1);
        }
        data[index / 64] |= (1ULL << (index % 64));
    }
    else
    {
        if (index < capacity_bits)
        {
            data[index / 64] &= ~(1ULL << (index % 64));
        }
    }
}

bool bitset::test(int index)
{
    if (index >= capacity_bits)
    {
        return false;
    }
    else
    {
        return (data[index / 64] & (1ULL << (index % 64))) != 0;
    }
}

bool bitset::empty()
{
    for (size_t i = 0; i < units_count(); i++)
    {
        if (data[i] != 0)
        {
            return false;
        }
    }
    return true;
}

int bitset::size() const
{
    return capacity_bits;
}

bitset bitset::union_with(const bitset& set) const
{
    size_t max_bits = std::max(capacity_bits, set.capacity_bits);
    bitset result(max_bits);
    size_t max_units=result.units_count();
    for(size_t i=0; i<max_units; i++)
    {
        uint64_t a;
        if(i<units_count())
        {
            a=data[i];
        }
        else
        {
            a=0;
        }
        uint64_t b;
        if(i<units_count())
        {
            b=set.data[i];
        }
        else
        {
            b=0;
        }
        result.data[i]=a | b;
    }
    return result;
}

bitset bitset::intersection(const bitset& set) const
{
    size_t min_bits=std::min(capacity_bits,set.capacity_bits);
    bitset result(min_bits);
    size_t units=result.units_count();
    for(size_t i=0; i<units; i++)
    {
        result.data[i]=data[i] & set.data[i];
    }
    return result;
}

bool bitset::is_subnet(const bitset& set) const {
    for (size_t i = 0; i < units_count(); i++)
    {
        uint64_t current=data[i];
        uint64_t target;
        if(i<set.units_count())
        {
            target=set.data[i];
        }
        else
        {
            target=0;
        }
        if((current & target)!=current )
        {
            return false;
        }
    }
    return true;

}

void bitset::clear()
{
    if(data)
    {
        std::memset(data,0,units_count()*sizeof(uint64_t));
    }
}

bitset bitset::operator*(bitset other) const
{
    return intersection(other);
}

bitset bitset::operator+(bitset other) const
{
    return union_with(other);
}
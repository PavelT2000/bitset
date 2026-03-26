class bitset
{
private:
    /* data */
public:
    bitset(/* args */);
    ~bitset();
    bool test(int index);
    bool set(int index, bool val);
    bool empty();
    int size();
    bitset union_with(bitset set);
    bitset intersection(bitset set);
};

bitset::bitset(/* args */)
{
}

bitset::~bitset()
{
}

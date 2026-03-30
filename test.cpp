#include "bitset.h"
#include <iostream>
#include <cassert>
#include <vector>


// Простой макрос для тестов
#define ASSERT_TRUE(cond) if (!(cond)) { std::cerr << "Test failed: " << #cond << " at line " << __LINE__ << std::endl; exit(1); }
#define ASSERT_FALSE(cond) ASSERT_TRUE(!(cond))

void test_basic_ops() {
    bitset bs;
    ASSERT_FALSE(bs.test(10));

    bs.set(10, true);
    ASSERT_TRUE(bs.test(10));
    ASSERT_TRUE(bs.size() >= 11);

    bs.set(10, false);
    ASSERT_FALSE(bs.test(10));
    ASSERT_TRUE(bs.empty());
}

void test_copy_move() {
    bitset bs1;
    bs1.set(100, true);

    // Тест копирования
    bitset bs2 = bs1;
    ASSERT_TRUE(bs2.test(100));
    bs1.set(100, false);
    ASSERT_TRUE(bs2.test(100)); // Глубокое копирование: bs2 не изменился

    // Тест перемещения
    bitset bs3 = std::move(bs2);
    ASSERT_TRUE(bs3.test(100));
    ASSERT_TRUE(bs2.empty()); // Источник в пустом состоянии
}

void test_set_logic() {
    bitset a, b;
    a.set(1, true); a.set(3, true);
    b.set(3, true); b.set(5, true);

    // bitset res_union = a.union_with(b);
    bitset res_union = a+b;
    ASSERT_TRUE(res_union.test(1) && res_union.test(3) && res_union.test(5));

    // bitset res_inter = a.intersection(b);
    bitset res_inter = a*b;
    ASSERT_TRUE(res_inter.test(3));
    ASSERT_FALSE(res_inter.test(1));

}

void test_subnet() {
    bitset a, b;
    a.set(1, true); a.set(3, true); a.set(5, true);  a.set(6, true); a.set(9, true);
    b.set(3, true); b.set(6, true);

    ASSERT_TRUE(b.is_subnet(a));


    b.set(7,true);

    ASSERT_FALSE(b.is_subnet(a));


}

int main() {
    try {
        test_basic_ops();
        test_copy_move();
        test_set_logic();
        std::cout << "All tests passed successfully!" << std::endl;
    } catch (...) {
        std::cerr << "Unknown error during testing" << std::endl;
    }
    return 0;
}
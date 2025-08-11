#include <iostream>
#include <array>
struct A {
    std::array<int, 4> arr;
    constexpr A() : arr() {
        arr = arr_init();
    }
    constexpr std::array<int, 4> arr_init() {
        std::array<int, 4> tal = {};
        for(int i=0;i<4;i++) {
            tal[i] = i;
        }
        return tal;
    }
};

int main() {
    constexpr A a;
    for (int x : a.arr)
        std::cout << x << '\n';
}
#include <iostream>
#include <vector>

template<typename T>
using FoldCallback = T(*)(T, T);

template<typename T>
constexpr T fold__(const std::vector<T>& vec, FoldCallback<T> callback, size_t index) {
    if (index == vec.size() - 1)
        return vec[index];

    return callback(vec[index], fold__(vec, callback, index + 1));
}

template<typename T>
constexpr T fold(const std::vector<T>& vec, FoldCallback<T> callback) {
    if (vec.empty())
        throw std::invalid_argument("Attempt to call fold() with an empty vector");

    return fold__(vec, callback, 0);
}

namespace ops {

constexpr int add(int a, int b) {
    return a + b;
}

constexpr int mul(int a, int b) {
    return a * b;
}

constexpr int sub(int a, int b) {
    return a - b;
}

} // namespace ops


consteval bool tests() {
    std::vector<int> vec = { 1, 2, 3, 4 };
    std::vector<int> vec2 = { 10, 5, 2 };

    int folded = fold(vec, ops::add);

    if (fold(vec, ops::add) != 10)
        throw "fold error for add";

    if (fold(vec, ops::mul) != 24)
        throw "fold error for mul";

    if (fold(vec2, ops::sub) != 7)
        throw "fold error for sub";

    return true;
}

int main()
{
    static_assert(tests(), "Tests failed");

    std::vector<int> lol = { 1, 2, 3, 4 };

    std::cout << "fold [add] of (1,2,3,4): " << fold(lol, ops::add) << "\n";

    int greatest = fold<int>(lol, [](int a, int b) {
        if (a > b) {
            return a;
        }
        else {
            return b;
        }
    });

    std::cout << "greatest of (1,2,3,4): " << greatest << "\n";
}
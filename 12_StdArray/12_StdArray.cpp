#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>

// Compiled with C++20!!!!
int main()
{
    // Construction uses aggregate initialization
    std::array<int, 3> a1{ {1, 2, 3} }; // Double-braces required in C++11 prior to
    // the CWG 1270 revision (not needed in C++11 after the revision and in C++14 and beyond)
    std::array<int, 3> a2 = { 1, 2, 3 }; // Double braces never required after =

    // Container operations are supported
    std::sort(a1.begin(), a1.end());
    for (const auto& s : a2)
        std::cout << s << ' ';
    std::cout << std::endl;

    std::ranges::reverse_copy(a2, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // Ranged for loop is supported
    std::array<std::wstring, 2> a3{ L"E", L"\u018E" };
    for (const auto& s : a3)
        std::wcout << s << ' ';
    std::cout << '\n';

    // Deduction guide for array creation (since C++17)
    [[maybe_unused]] std::array a4{ 3.0, 1.0, 4.0 }; // std::array<double, 3>

    // Behavior of unspecified elements is the same as with built-in arrays
    [[maybe_unused]] std::array<int, 2> a5; // No list init, a5[0] and a5[1]
    // are default initialized
    [[maybe_unused]] std::array<int, 2> a6{}; // List init, both elements are value
    // initialized, a6[0] = a6[1] = 0
    [[maybe_unused]] std::array<int, 2> a7{ 1 }; // List init, unspecified element is value
    // initialized, a7[0] = 1, a7[1] = 0
}
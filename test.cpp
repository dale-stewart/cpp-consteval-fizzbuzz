#include <string>
#include <string_view>
#include <iostream>
#include <variant>
#include <ranges>
#include <array>

typedef std::variant<std::string_view, int> FizzBuzzResult;

consteval FizzBuzzResult fizzbuzz(int value)
{
    if (value % 15 == 0)
        return std::string_view{"FizzBuzz"};
    if (value % 3 == 0)
        return std::string_view{"Fizz"};
    if (value % 5 == 0)
        return std::string_view{"Buzz"};
    return value;
}

// Verify compile-time evaluation
static_assert(std::get<std::string_view>(fizzbuzz(3)) == "Fizz", "3 should be Fizz");
static_assert(std::get<std::string_view>(fizzbuzz(5)) == "Buzz", "5 should be Buzz");
static_assert(std::get<std::string_view>(fizzbuzz(15)) == "FizzBuzz", "15 should be FizzBuzz");
static_assert(std::get<int>(fizzbuzz(1)) == 1, "1 should be number 1");

// Create a compile-time array of FizzBuzz results
consteval auto make_fizzbuzz_array()
{
    const int size = 100;
    std::array<FizzBuzzResult, size> results{};
    for (int i = 0; i < size; ++i) {
        results[i] = fizzbuzz(i + 1);
    }
    return results;
}

constexpr auto fizzbuzz_results = make_fizzbuzz_array();

int main()
{
    auto print = [](const auto& val) {
        std::cout << val << '\n';
    };
    
    for (const auto& result : fizzbuzz_results) {
        std::visit(print, result);
    }

    return 0;
}

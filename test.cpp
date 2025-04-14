#include <string_view>
#include <variant>
#include <ranges>
#include <array>
#include <print>

using FizzBuzzResult = std::variant<std::string_view, int>;

consteval FizzBuzzResult fizzbuzz(int value)
{
    constexpr auto fizz = std::string_view{"Fizz"};
    constexpr auto buzz = std::string_view{"Buzz"};
    constexpr auto fizzbuzz = std::string_view{"FizzBuzz"};

    const bool fizz_value = value % 3 == 0;
    const bool buzz_value = value % 5 == 0;

    if (fizz_value && buzz_value)
        return fizzbuzz;
    if (fizz_value)
        return fizz;
    if (buzz_value)
        return buzz;

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
    constexpr int size = 100;
    std::array<FizzBuzzResult, size> results{};
    for (int i = 0; i < size; ++i) {
        results[i] = fizzbuzz(i + 1);
    }
    return results;
}

constexpr auto fizzbuzz_results = make_fizzbuzz_array();

int main()
{
    for (auto [_, result] : std::views::enumerate(fizzbuzz_results)) {
        std::visit(
            [](const auto& v) {
                std::println("{}", v);
            },
            result
        );
    }
    return 0;
}

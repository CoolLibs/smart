#pragma once

#include <cmath>
#include <numeric>
#include <valarray>

namespace smart {
template<typename T>
T keep_above(T x, T min_value)
{
    return std::max(x, min_value);
}

template<typename T>
T keep_below(T x, T max_value)
{
    return std::min(x, max_value);
}

template<typename T>
T lerp(T a, T b, float t)
{
    return std::lerp(a, b, t);
}

template<typename T>
T midpoint(T a, T b)
{
    return std::midpoint(a, b);
}

/**
 * @brief Returns +1, -1 or 0 depending on the sign of val
 */
template<typename T>
int sign_or_0(T val)
{
    return (T{0} < val) - (val < T{0});
}

/**
 * @brief Returns T{+1} or T{-1} depending on the sign of val.
 * It will never return T{0}. If val is T{0}, it returns T{+1}.
 */
template<typename T>
T sign(T val)
{
    return val < T{0} ? T{-1} : T{1};
}

struct Fraction {
    int numerator{};
    int denominator{};

    friend auto operator==(Fraction a, Fraction b) -> bool
    {
        return a.numerator == b.numerator && a.denominator == b.denominator;
    }
};

inline std::ostream& operator<<(std::ostream& os, smart::Fraction fraction)
{
    os << fraction.numerator << "/" << fraction.denominator;
    return os;
}

template<typename Float>
auto as_fraction(Float x, int max_number = 99, Float precision = 1e-4) -> Fraction
{
    const int sign     = x > 0 ? 1 : -1;
    x                  = std::abs(x);
    Float decimal_part = x - std::floor(x);

    std::valarray<int> fraction{static_cast<int>(std::floor(x)), 1};
    std::valarray<int> previous_fraction{1, 0};
    while (fraction[0] < max_number
           && fraction[1] < max_number
           && decimal_part > precision)
    {
        const Float new_x      = 1 / decimal_part;
        const int   whole_part = static_cast<int>(std::floor(new_x));

        const auto temporary = fraction;
        fraction             = whole_part * fraction + previous_fraction;
        previous_fraction    = temporary;

        decimal_part = new_x - whole_part;
    }

    if (decimal_part > precision)     // We broke out of the loop because the numerator or denominator exceeded the allowed number
        fraction = previous_fraction; // so we have to go back to the previous fraction

    return {sign * fraction[0], fraction[1]};
}

} // namespace smart

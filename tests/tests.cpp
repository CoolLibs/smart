#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif
#include <doctest/doctest.h>
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#include <complex>
#include <smart/smart.hpp>

#define EQUALITY_COMPARABLE_TYPES int32_t, uint32_t, float, double, std::complex<float>, std::complex<double>
#define TOTALLY_ORDERED_TYPES     int32_t, uint32_t, float, double
#define SIGNED_TYPES              int32_t, float, double

TEST_CASE_TEMPLATE("keep_above", T, TOTALLY_ORDERED_TYPES)
{
    constexpr auto keep_above_5 = [](auto x) {
        return smart::keep_above(T{5}, x);
    };
    CHECK(keep_above_5(T{7}) == T{7});
    CHECK(keep_above_5(T{6}) == T{6});
    CHECK(keep_above_5(T{5}) == T{5});
    CHECK(keep_above_5(T{4}) == T{5});
    CHECK(keep_above_5(T{3}) == T{5});
}

TEST_CASE_TEMPLATE("keep_below", T, TOTALLY_ORDERED_TYPES)
{
    constexpr auto keep_below_5 = [](auto x) {
        return smart::keep_below(T{5}, x);
    };
    CHECK(keep_below_5(T{3}) == T{3});
    CHECK(keep_below_5(T{4}) == T{4});
    CHECK(keep_below_5(T{5}) == T{5});
    CHECK(keep_below_5(T{6}) == T{5});
    CHECK(keep_below_5(T{7}) == T{5});
}

TEST_CASE_TEMPLATE("sign", T, SIGNED_TYPES)
{
    CHECK(smart::sign(+T{0}) == T{+1});
    CHECK(smart::sign(-T{0}) == T{+1});
    CHECK(smart::sign(T{+3}) == T{+1});
    CHECK(smart::sign(T{-2}) == T{-1});
}

TEST_CASE_TEMPLATE("sign_or_0", T, SIGNED_TYPES)
{
    CHECK(smart::sign_or_0(+T{0}) == T{0});
    CHECK(smart::sign_or_0(-T{0}) == T{0});
    CHECK(smart::sign_or_0(T{+3}) == T{+1});
    CHECK(smart::sign_or_0(T{-2}) == T{-1});
}

TEST_CASE("as_fraction")
{
    CHECK(smart::as_fraction(0.5f) == smart::Fraction{1, 2});
    CHECK(smart::as_fraction(1.f) == smart::Fraction{1, 1});
    CHECK(smart::as_fraction(1.77777778) == smart::Fraction{16, 9});
}
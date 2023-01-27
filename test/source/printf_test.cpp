#include <cstdlib>

#include "printf/printf.hpp"

using namespace std::string_view_literals;

auto main() -> int
{
  auto result =
      dolf::print("Test\n"sv) && dolf::print("Test %"sv)
      && dolf::print("\nTest %%\n"sv) && dolf::print("Test %f\n"sv) &&

      dolf::print("Test %d\n"sv, -1) && dolf::print("Test %hd\n"sv, 32768)
      && dolf::print("Test %hhd\n"sv, -129) && dolf::print("Test %ld\n"sv, -1)
      && dolf::print(
          "Test %lld\n"sv,
          static_cast<long long>(static_cast<unsigned long long>(-1) / 2 - 1))
      &&

      dolf::print("Test %u\n"sv, -1) && dolf::print("Test %hu\n"sv, 32768)
      && dolf::print("Test %hhu\n"sv, -129) && dolf::print("Test %lu\n"sv, -1L)
      && dolf::print("Test %llu\n"sv, -1LL) &&

      dolf::print("Test %d%hd%hhd%ld%lld%u%hu%hhu%lu%llu\n"sv,
                  0,
                  1,
                  2,
                  3L,
                  4LL,
                  5,
                  6,
                  7,
                  8L,
                  9LL);

  return result ? EXIT_SUCCESS : EXIT_FAILURE;
}

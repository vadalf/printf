#include <algorithm>
#include <array>
#include <climits>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <limits>

#include "printf/printf.hpp"

using namespace std::string_view_literals;

namespace dolf
{

namespace
{

class printer
{
public:
  explicit printer(long long value)
      : m_value(value)
  {
  }

  auto print() -> bool
  {
    auto begin = m_buffer.begin();
    if (m_value < 0) {
      *begin++ = '-';
    }

    auto const start = begin;
    do {
      auto const number = static_cast<int>(m_value % 10);
      m_value /= 10;
      *begin++ = static_cast<char>('0' + (number < 0 ? -number : number));
    } while (m_value != 0);
    std::reverse(start, begin);

    auto const count =
        static_cast<std::size_t>(std::distance(m_buffer.begin(), begin));
    return std::fwrite(m_buffer.data(), 1, count, stdout) == count;
  }

private:
  long long m_value;

  static constexpr std::size_t max_digits_of_long_long =
      static_cast<std::size_t>(std::numeric_limits<long long>::digits10)
      + (std::numeric_limits<long long>::is_signed ? 1 : 0) + 1;
  std::array<char, max_digits_of_long_long> m_buffer {};

  static_assert(CHAR_BIT == 8 && sizeof(long long) == 8);
};

template<typename It>
auto print_it(It begin, It end) -> bool
{
  auto const count = static_cast<std::size_t>(std::distance(begin, end));
  return std::fwrite(&*begin, 1, count, stdout) == count;
}

}  // namespace

// NOLINTBEGIN(readability-function-cognitive-complexity)
// NOLINTBEGIN(readability-non-const-parameter)
auto vprint(std::string_view string, std::va_list args) -> bool
{
  auto begin = string.begin();
  auto const end = string.end();

  while (true) {
    auto pos = std::find(begin, end, '%');
    if (pos == end) {
      goto end;
    }

    auto const orig_pos = pos;
    ++pos;
    if (pos == end) {
      goto end;
    }

    if (!print_it(begin, orig_pos)) {
      return false;
    }
    begin = orig_pos;

    switch (*pos) {
      case '%':  // %%
        if (std::fputc('%', stdout) != '%') {
          return false;
        }
        begin = ++pos;
        continue;

      case 'd':  // %d
        if (!printer(static_cast<long long>(va_arg(args, int))).print()) {
          return false;
        }
        begin = ++pos;
        continue;

      case 'l':  // %l?
        ++pos;
        if (pos == end) {
          goto end;
        }

        switch (*pos) {
          case 'l':  // %ll?
            ++pos;
            if (pos == end) {
              goto end;
            }

            if (*pos == 'd') {  // %lld
              if (!printer(va_arg(args, long long)).print()) {
                return false;
              }
              begin = ++pos;
              continue;
            }
            goto out;

          case 'd':  // %ld
            if (!printer(static_cast<long long>(va_arg(args, long))).print()) {
              return false;
            }
            begin = ++pos;
            continue;
        }

        goto out;

      case 'h':  // %h?
        ++pos;
        if (pos == end) {
          goto end;
        }

        switch (*pos) {
          case 'h':  // %hh?
            ++pos;
            if (pos == end) {
              goto end;
            }

            if (*pos == 'd') {  // %hhd
              if (!printer(static_cast<long long>(
                               static_cast<signed char>(va_arg(args, int))))
                       .print())
              {
                return false;
              }
              begin = ++pos;
              continue;
            }

            goto out;

          case 'd':  // %hd
            if (!printer(static_cast<long long>(
                             static_cast<short>(va_arg(args, int))))
                     .print())
            {
              return false;
            }
            begin = ++pos;
            continue;
        }

        goto out;
    }

  out:
    if (!print_it(begin, pos)) {
      return false;
    }
    begin = pos;
  }

end:
  return print_it(begin, end);
}
// NOLINTEND(readability-non-const-parameter)
// NOLINTEND(readability-function-cognitive-complexity)

// NOLINTNEXTLINE(cert-dcl50-cpp)
auto print(std::string_view string, ...) -> bool
{
  // NOLINTNEXTLINE
  std::va_list args;
  // NOLINTBEGIN(*-array*-decay)
  va_start(args, string);
  auto const result = vprint(string, args);
  va_end(args);
  // NOLINTEND(*-array*-decay)
  return result;
}

}  // namespace dolf

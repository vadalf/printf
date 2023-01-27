#pragma once

#include <cstdarg>
#include <string_view>

#include "printf/printf_export.hpp"

namespace dolf
{

PRINTF_EXPORT auto vprint(std::string_view string, std::va_list args) -> bool;

PRINTF_EXPORT auto print(std::string_view string, ...) -> bool;

}  // namespace dolf

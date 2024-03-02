#pragma once

#ifndef FADED_PUBLIC__PUBLIC_HEADER_H__
#define FADED_PUBLIC__PUBLIC_HEADER_H__

#include <cstdint>
#include <string>

namespace Faded {
namespace Public {
using name_t = const std::string;
using numeric_t = int32_t;
using percentage_t = float;
using id_t = uint64_t;
}  // namespace Public
}  // namespace Faded

#endif  // !FADED_PUBLIC__PUBLIC_HEADER_H__

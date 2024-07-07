#ifndef _BOARD_H_
#define _BOARD_H_

#include <array>
#include <cstddef>
template <typename T, std::size_t X, std::size_t Y>
using board_t = std::array<std::array<T, X>, Y>;

#endif

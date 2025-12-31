// -*-c++-*-
/**
 * TuningsConcepts.h
 * Copyright Paul Walker, 2019-2020
 * Released under the MIT License. See LICENSE.md
 */

#ifndef __INCLUDE_TUNINGS_CONCEPTS_H
#define __INCLUDE_TUNINGS_CONCEPTS_H

#pragma once
#include <concepts>
#include <type_traits>
#include <fstream>

#ifdef _WIN32
#include <filesystem>
#endif

namespace Tunings
{
template <typename P>
concept StreamablePath = requires(P p) { std::ifstream(std::decay_t<P>(p)); };

template <typename P>
concept WidePath = std::same_as<P, const wchar_t *> || requires(const P &p) {
    { p.c_str() } -> std::same_as<const wchar_t *>;
};

template <typename P>
concept NarrowPath = std::same_as<P, const char *> || requires(const P &p) {
    { p.c_str() } -> std::same_as<const char *>;
};

#ifdef _WIN32
template <typename P>
concept U8PathConstructible = requires(const P &p) {
    { std::filesystem::u8path(p) } -> std::same_as<std::filesystem::path>;
};
#endif

template <typename P>
concept PathWithU8 = requires(const P &p) {
    { p.u8string() } -> std::convertible_to<std::string>;
};

template <typename P>
concept PathWithStemU8 = requires(const P &p) {
    { p.filename().stem().u8string() } -> std::convertible_to<std::string>;
};
} // namespace Tunings

#endif

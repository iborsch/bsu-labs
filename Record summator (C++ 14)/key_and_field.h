#pragma once

template <int ... ints>
class key {};

template <int i, int ... ints>
class key<i, ints...> : public key<ints...> {};

template <int ... ints>
class field {};

template <int i, int ... ints>
class field<i, ints...> : public field<ints...> {};
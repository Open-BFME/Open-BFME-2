// TU-scoped STLport comparison shared by W3DShroud and its erase donor.
// Keep the established inline body without emitting a flags-dependent COMDAT.
#pragma once
#include <functional>

namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

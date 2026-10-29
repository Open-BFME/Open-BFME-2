#ifndef BFME2_APT_OPTIONS_CONSTRUCTOR_LESS_H
#define BFME2_APT_OPTIONS_CONSTRUCTOR_LESS_H

// The AsciiString comparator the options screen's preference maps instantiate.
// Kept beside its TU so a split can carve a body out of
// AptOptionsConstructor.cpp (tools/tu_skeleton.py --split refuses a file whose
// namespace block defines something).

#include "ascii_string.h"

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

#endif

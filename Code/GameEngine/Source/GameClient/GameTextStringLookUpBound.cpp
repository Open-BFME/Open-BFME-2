// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// ?Rva002E5C15LowerBound@@YAPAUStringLookUp@@PAU1@0ABQBDURva002E5C15Comp@@H@Z 0x002E5C15 76B
// Evidence: chain from 0x002E56B3 Less; binary lower_bound over 8B StringLookUp array; callers 0x002E609E.
// The family is STLport's lower_bound/upper_bound/__equal_range over the
// GameText lookup array (GameText.cpp); /O1 /arch:SSE /G7 is that region's
// setting and the only one under which __equal_range keeps its EBP frame.

// The stdcall helpers take the same two stack arguments and ignore ECX; use
// alternates so the thiscall functor call sites retain retail's ECX setup.
#pragma comment(linker, "/alternatename:??RRva002E5C15Comp@@QBE_NPBUStringLookUp@@PBD@Z=?Rva002E56B3Less@@YG_NPBUStringLookUp@@PBD@Z")
#pragma comment(linker, "/alternatename:??RRva002E5C61Comp@@QBE_NPBDPBUStringLookUp@@@Z=?Rva002E56E2Greater@@YG_NPBDPBUStringLookUp@@@Z")

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct StringLookUp
{
	AsciiString *label;
	void *info;
};

struct Rva002E5C15Comp
{
	bool operator()(const StringLookUp *left, const char *right) const;
};

struct Rva002E5C61Comp
{
	bool operator()(const char *left, const StringLookUp *right) const;
};

StringLookUp *__cdecl Rva002E5C15LowerBound(StringLookUp *first, StringLookUp *last, const char *const &val, Rva002E5C15Comp comp, int d2)
{
	int count = int(last - first);
	while (count > 0) {
		int half = count >> 1;
		StringLookUp *mid = first + half;
		if (comp(mid, val)) {
			first = mid + 1;
			count = count - half - 1;
		} else {
			count = half;
		}
	}
	return first;
}

StringLookUp *__cdecl Rva002E5C61UpperBound(StringLookUp *first, StringLookUp *last, const char *const &val, Rva002E5C61Comp comp, int d2)
{
	int count = int(last - first);
	while (count > 0) {
		int half = count >> 1;
		StringLookUp *mid = first + half;
		if (comp(val, mid)) {
			count = half;
		} else {
			first = mid + 1;
			count = count - half - 1;
		}
	}
	return first;
}

StringLookUp *__cdecl Rva002E608CLowerBound(StringLookUp *first, StringLookUp *last, const char *const &val, Rva002E5C15Comp comp)
{
	return Rva002E5C15LowerBound(first, last, val, comp, 0);
}

StringLookUp *__cdecl Rva002E60A7UpperBound(StringLookUp *first, StringLookUp *last, const char *const &val, Rva002E5C61Comp comp)
{
	return Rva002E5C61UpperBound(first, last, val, comp, 0);
}

struct Rva002E6184Pair
{
	StringLookUp *first;
	StringLookUp *second;
	Rva002E6184Pair(StringLookUp *a, StringLookUp *b) : first(a), second(b) {}
};

// ?Rva002E6184EqualRange@@YA?AURva002E6184Pair@@PAUStringLookUp@@0ABQBDURva002E5C15Comp@@PAH@Z
// 0x002E6184 151B: STLport __equal_range, reached through the equal_range
// forwarder 0x002E6329 (which pushes the null distance_type pointer). One
// comparator object serves both orders, so the upper half reuses it.
Rva002E6184Pair __cdecl Rva002E6184EqualRange(StringLookUp *first, StringLookUp *last, const char *const &val, Rva002E5C15Comp comp, int *)
{
	int len = int(last - first);
	int half;
	StringLookUp *middle, *left, *right;
	while (len > 0) {
		half = len >> 1;
		middle = first;
		middle += half;
		if (comp(middle, val)) {
			first = middle;
			++first;
			len = len - half - 1;
		} else if (reinterpret_cast<Rva002E5C61Comp &>(comp)(val, middle)) {
			len = half;
		} else {
			left = Rva002E608CLowerBound(first, middle, val, comp);
			first += len;
			right = Rva002E60A7UpperBound(++middle, first, val, reinterpret_cast<Rva002E5C61Comp &>(comp));
			return Rva002E6184Pair(left, right);
		}
	}
	return Rva002E6184Pair(first, first);
}

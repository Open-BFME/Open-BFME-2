// Character-classification members use STLport's two 256-byte case maps and a
// 256-entry classification-mask table. Each table base is established by a
// matched BFME2 DIR32 reference; the element widths and byte-range checks
// establish the spans. All initialized table bytes match BFME2 retail.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/T2CtypeTableFacets.cpp); trimmed to the seven
// bodies the sweep places. The donor's remaining sibling defs (under 16B or
// ambiguous) are omitted: only declared here, never defined, so the
// find_declared_unmatched gate stays green. The donor declares t2_block_copy
// but retail reaches memmove, so the declaration is renamed to the real
// import (Import-ref verify refuses it otherwise; no pin can fix this).
typedef unsigned short T2WChar;

// The case maps at BFME2 VA 0x00BBC1E0 and 0x00BBC2E0 are STLport's
// ctype<char>::_S_upper and _S_lower, defined (with retail's bytes) in
// stlport_ctype_wchar_scan_not.cpp. STLport's ctype<char> befriends
// ctype<wchar_t> for exactly these reads; this view keeps that friendship.
struct T2WideCtype;
namespace _STL
{
template <class _CharT> class ctype;
template <> class ctype<char>
{
	friend struct ::T2WideCtype;
	static const unsigned char _S_upper[256];
	static const unsigned char _S_lower[256];
};
}

// BFME2 VA 0x00BBBDDC; all 1024 table bytes match retail.
extern const unsigned int g_ctypeClassificationMasks[256] = {
    0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u,
    0x00000020u, 0x00000028u, 0x00000028u, 0x00000028u, 0x00000028u, 0x00000028u, 0x00000020u, 0x00000020u,
    0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u,
    0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u,
    0x00000048u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u,
    0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u,
    0x000000C4u, 0x000000C4u, 0x000000C4u, 0x000000C4u, 0x000000C4u, 0x000000C4u, 0x000000C4u, 0x000000C4u,
    0x000000C4u, 0x000000C4u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u,
    0x00000050u, 0x000001C1u, 0x000001C1u, 0x000001C1u, 0x000001C1u, 0x000001C1u, 0x000001C1u, 0x00000141u,
    0x00000141u, 0x00000141u, 0x00000141u, 0x00000141u, 0x00000141u, 0x00000141u, 0x00000141u, 0x00000141u,
    0x00000141u, 0x00000141u, 0x00000141u, 0x00000141u, 0x00000141u, 0x00000141u, 0x00000141u, 0x00000141u,
    0x00000141u, 0x00000141u, 0x00000141u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u,
    0x00000050u, 0x000001C2u, 0x000001C2u, 0x000001C2u, 0x000001C2u, 0x000001C2u, 0x000001C2u, 0x00000142u,
    0x00000142u, 0x00000142u, 0x00000142u, 0x00000142u, 0x00000142u, 0x00000142u, 0x00000142u, 0x00000142u,
    0x00000142u, 0x00000142u, 0x00000142u, 0x00000142u, 0x00000142u, 0x00000142u, 0x00000142u, 0x00000142u,
    0x00000142u, 0x00000142u, 0x00000142u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000020u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u
};

extern "C" __declspec(dllimport) void *__cdecl memmove(void *dst, const void *src, unsigned int n);

struct T2NarrowCtype
{
	char toUpper(char c) const;
	const char *toLowerRange(char *low, char *high) const;
	const char *widenRange(const char *low, const char *high, char *to) const;
	const char *narrowRange(const char *low, const char *high, char dflt, char *to) const;
};

struct T2WideCtype
{
	const T2WChar *isRange(const T2WChar *low, const T2WChar *high, unsigned int *vec) const;
	T2WChar toUpper(unsigned int c) const;
	const T2WChar *toUpperRange(T2WChar *low, T2WChar *high) const;
	T2WChar toLower(unsigned int c) const;
	const T2WChar *toLowerRange(T2WChar *low, T2WChar *high) const;
	T2WChar widen(char c) const;
	const char *widenRange(const char *low, const char *high, T2WChar *to) const;
	int narrow(T2WChar c, char dflt) const;
	const T2WChar *narrowRange(const T2WChar *low, const T2WChar *high, char dflt, char *to) const;
};

const T2WChar *T2WideCtype::isRange(const T2WChar *low, const T2WChar *high,
                                    unsigned int *vec) const
{
	while (low < high)
	{
		*vec = (*low < 0x100) ? g_ctypeClassificationMasks[*low] : 0;
		++low;
		++vec;
	}
	return high;
}

const char *T2WideCtype::widenRange(const char *low, const char *high, T2WChar *to) const
{
	while (low != high)
	{
		*to = (T2WChar)(signed char)*low;
		++to;
		++low;
	}
	return high;
}

const T2WChar *T2WideCtype::narrowRange(const T2WChar *low, const T2WChar *high,
                                        char dflt, char *to) const
{
	while (low != high)
	{
		T2WChar c = *low;
		++low;
		int v = ((int)(char)c == (int)c) ? (int)c : (int)dflt;
		*to = (char)v;
		++to;
	}
	return high;
}

const T2WChar *T2WideCtype::toUpperRange(T2WChar *low, T2WChar *high) const
{
	while (low < high)
	{
		T2WChar c = *low;
		*low = (c < 0x100) ? (T2WChar)_STL::ctype<char>::_S_upper[c] : c;
		++low;
	}
	return high;
}

const T2WChar *T2WideCtype::toLowerRange(T2WChar *low, T2WChar *high) const
{
	while (low < high)
	{
		T2WChar c = *low;
		*low = (c < 0x100) ? (T2WChar)_STL::ctype<char>::_S_lower[c] : c;
		++low;
	}
	return high;
}

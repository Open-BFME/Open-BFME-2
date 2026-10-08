// ?Rva002E6184@@YAPAURva002E6184Pair@@PAU1@PAUStringLookUp@@1ABQBDURva002E5C15Comp@@@Z
// partial score=0.85 date=2026-10-08
// Stash 0x002E6184 (151 B): equal_range-shaped helper; see re_log partial.
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

#pragma comment(linker, "/alternatename:??RRva002E5C15Comp@@QBE_NPBUStringLookUp@@PBD@Z=?Rva002E56B3Less@@YG_NPBUStringLookUp@@PBD@Z")
#pragma comment(linker, "/alternatename:??RRva002E5C61Comp@@QBE_NPBDPBUStringLookUp@@@Z=?Rva002E56E2Greater@@YG_NPBDPBUStringLookUp@@@Z")

StringLookUp *__cdecl Rva002E608CLowerBound(StringLookUp *first, StringLookUp *last, const char *const &val, Rva002E5C15Comp comp);
StringLookUp *__cdecl Rva002E60A7UpperBound(StringLookUp *first, StringLookUp *last, const char *const &val, Rva002E5C61Comp comp);

struct Rva002E6184Pair
{
	StringLookUp *first;
	StringLookUp *second;
};

Rva002E6184Pair *__cdecl Rva002E6184(Rva002E6184Pair *result, StringLookUp *first, StringLookUp *last, const char *const &val, Rva002E5C15Comp comp)
{
	int count = int(last - first);
	while (count > 0)
	{
		int half = count >> 1;
		StringLookUp *mid = first + half;
		if (comp(mid, val))
		{
			first = mid + 1;
			count = count - half - 1;
		}
		else if (reinterpret_cast<Rva002E5C61Comp &>(comp)(val, mid))
		{
			count = half;
		}
		else
		{
			result->first = Rva002E608CLowerBound(first, mid, val, comp);
			result->second = Rva002E60A7UpperBound(mid + 1, first + count, val, reinterpret_cast<Rva002E5C61Comp &>(comp));
			return result;
		}
	}
	result->first = first;
	result->second = first;
	return result;
}

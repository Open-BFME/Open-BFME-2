// cl: /GX- /MD /Ireference/shims/bfme2_ascii
// stlport
// The StringLookUp sort family in stlport_sort_stringlookup.cpp calls this
// thiscall comparator at 0x002E5678. Its fields and ordering expression are
// independently evidenced by GameTextStringLookUpLess.cpp's rowed comparator.
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *left, const char *right);
#include "ascii_string.h"

struct StringLookUp
{
	AsciiString *label;
	void *info;
};

struct Rva002E5678Cmp
{
	bool operator()(const StringLookUp &a, const StringLookUp &b) const;
};

// ??RRva002E5678Cmp@@QBE_NABUStringLookUp@@0@Z @0x002E5678 59B
bool Rva002E5678Cmp::operator()(const StringLookUp &a, const StringLookUp &b) const
{
	return _strcmpi(a.label->str(), b.label->str()) < 0;
}

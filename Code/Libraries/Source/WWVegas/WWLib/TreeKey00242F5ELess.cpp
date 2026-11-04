// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?Rva000A78A3Less@@YG_NABUTreeKey00242F5E@@0@Z, retail 0x000A78A3, 46 bytes.
// TreeKey00242F5E set comparator (unsigned id at +0 then AsciiString at +4 via
// rowed 0x5598C) proving stdcall bool (ret 8) free-function shape. Callers
// 0xA78D1/0xA7909/0xA7AA7/0xA7C50 are rb_tree set operations for the same key
// (prev 0xA7876 _Construct and next 0xA799B _M_create_node). Donor is the
// rowed 0x240CE0 operator< for the same key in
// stlport_rb_tree_hint_00242f5e.cpp (signed int version with cdecl ret);
// retail here uses unsigned id compare (jae/jbe) and stdcall cleanup.

typedef bool Bool;

#include "ascii_string.h"

Bool __cdecl operator<(const AsciiString &left, const AsciiString &right);

#include "TreeKey00242F5E.h"

Bool __stdcall Rva000A78A3Less(const TreeKey00242F5E &lhs, const TreeKey00242F5E &rhs)
{
	if (lhs.field00 < rhs.field00)
		return true;
	if (lhs.field00 > rhs.field00)
		return false;
	return lhs.field04 < rhs.field04;
}

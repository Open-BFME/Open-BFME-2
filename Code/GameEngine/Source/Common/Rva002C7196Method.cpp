// cl: /Ireference/shims/bfme2_ascii /O1 /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva002C7196@Rva002A8AB1Record@@QAEHABVAsciiString@@@Z @0x002C7196 (52B):
// get-or-default int field off the +0x17C map. Contains check through the
// rowed ?rva002C6EA4@Rva002C6EA4@@QAE_NABVAsciiString@@@Z (same +0x17C map
// layout, key-only traversal so the value-type spelling does not change the
// bytes); hit path reads the mapped int through the rowed map
// <AsciiString,AsciiString> _M_find worker at 0x001F8437 (node+0x14 is the
// second slot; the live values are ints per 717E stores and tactic callers,
// the find body only touches keys so the ICF-identical rowed spelling is
// used); miss path inserts via the pinned
// ?rva002C717E@Rva002A8AB1Record@@QAEXABVAsciiString@@H@Z with 0 and returns
// 0. Evidence: 14 tactic callers (appliesTo/v6), sibling Rva002C6EA4Method,
// _M_find row, 717E pin.
#include <map>
#include "ascii_string.h"

class Rva002C6EA4
{
public:
	bool rva002C6EA4(const AsciiString &key);
};

class Rva002A8AB1Record
{
public:
	void rva002C717E(const AsciiString &key, int value);
	int rva002C7196(const AsciiString &key);
private:
	char m_pad[0x17C];
	_STL::map<AsciiString, AsciiString> m_map; // +0x17C
};

// ?rva002C7196@Rva002A8AB1Record@@QAEHABVAsciiString@@@Z
int Rva002A8AB1Record::rva002C7196(const AsciiString &key)
{
	if (((Rva002C6EA4 *)this)->rva002C6EA4(key))
		return *(const int *)&m_map.find(key)->second;
	rva002C717E(key, 0);
	return 0;
}

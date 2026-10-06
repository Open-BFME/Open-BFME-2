// ?rva002120A4@Rva002120A4@@QAEHW4NameKeyType@@@Z
// partial score=0.97 date=2026-09-27
// ?rva002120A4@Rva002120A4@@QAEHW4NameKeyType@@@Z
// partial score=0.97 date=2026-09-27
// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva002120A4@Rva002120A4@@QAEHW4NameKeyType@@@Z, retail 0x002120A4 30B.
// NameKeyType map value lookup at this+0x218 via the public twin of Armor
// _M_find 0x002888D4 (same key-only body; private made public here to call
// it legally). Returns the dword at node+8 and 0 on miss. Unblocks
// 0x004FBDB0 and 0x003F409F. Callers at 0x003F40A8 and 0x004FBDB9.
// Evidence: ret-4 thiscall; lea arg plus add ecx-0x218 plus call shape.
#define private public
#include <hash_map>

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

namespace rts
{
template <class T> struct hash
{
	size_t operator()(const T &value) const;
};
}

typedef _STL::hash_map<NameKeyType, int, rts::hash<NameKeyType>, _STL::equal_to<NameKeyType> > NameKeyIntMap;

class Rva002120A4
{
public:
	int rva002120A4(NameKeyType key);

private:
	unsigned char m_pad[0x218];
	NameKeyIntMap m_map;
};

int Rva002120A4::rva002120A4(NameKeyType key)
{
	void *node = (void *)m_map._M_ht._M_find(key);
	return node != 0 ? *(int *)((char *)node + 8) : 0;
}

// cl: /DNDEBUG /MD
//
// ?rva0039DDC2@Team@@QAE_NURva0039DDC2Filter@@_N@Z @0x0039DDC2 (132B).
// Team member scan returning true when a live member passes the 0x10E gate
// plus the flag-gated 0x108/b3/b4 block then rowed Thing::isKindOfMulti on
// the modified first filter plus default storage. Retail reads dead bit at
// Object+0x438 bit0 status byte at Object+0x94 bit0 template byte at +0x10E
// bit 0x80 then flag at [ebp+0x24] gating template dword at +0x108 bit 0x80
// plus Object dword at +0x114 bits 3 and 4 via two shr+test idioms then ORs
// byte at [ebp+8] with 0x80 before the call. Walk uses rowed
// iterate_TeamMemberList 0x263864 and DLINK advance via pin at 0x263526.
// Same flags and sibling model as TeamRva0039DD4B and TeamRva0039DF1C.
// Caller at 0x0039EE4C.

typedef unsigned int UnsignedInt;

class Object;

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];

public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

struct Rva0039DDC2Filter
{
	unsigned int w[7];
};

template<int N>
class BitFlags
{
public:
	unsigned int m_bits[(N + 31) / 32];
};

struct ThingTemplate
{
	unsigned char m_pad[0x108];
	UnsignedInt m_kind0;
	unsigned char m_pad2[0x10E - 0x10C];
	unsigned char m_kindByte10e;
};

class Thing
{
public:
	bool isKindOfMulti(const BitFlags<116> &mustBeSet, const BitFlags<116> &mustBeClear) const;
};

class BfmeFixedStorage0004543D;
extern const BfmeFixedStorage0004543D g_defaultStorage009FEFA4;

class Object
{
public:
	unsigned char m_pad0[4];
	ThingTemplate *m_template;
	unsigned char m_pad1[0x94 - 0x08];
	unsigned char m_status94;
	unsigned char m_pad95[0x114 - 0x95];
	UnsignedInt m_status114;
	unsigned char m_pad118[0x438 - 0x118];
	unsigned char m_dead;
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	bool rva0039DDC2(Rva0039DDC2Filter f1, bool flag);
};

bool Team::rva0039DDC2(Rva0039DDC2Filter f1, bool flag)
{
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *cur = iter.cur();
		if ((cur->m_dead & 1) != 0)
			continue;
		if ((cur->m_status94 & 1) != 0)
			continue;
		ThingTemplate *tmpl = cur->m_template;
		if ((tmpl->m_kindByte10e & 0x80) != 0)
			continue;
		if (flag) {
			if ((tmpl->m_kind0 & 0x80) != 0) {
				UnsignedInt s = cur->m_status114;
				bool b3 = ((s >> 3) & 1) != 0;
				bool b4 = ((s >> 4) & 1) != 0;
				if (b3)
					continue;
				if (b4)
					continue;
			}
		}
		((unsigned char *)&f1)[0] |= 0x80;
		const BitFlags<116> &mustBeSet = *(const BitFlags<116> *)(const void *)&f1;
		const BitFlags<116> &mustBeClear = *(const BitFlags<116> *)(const void *)&g_defaultStorage009FEFA4;
		if (((const Thing *)cur)->isKindOfMulti(mustBeSet, mustBeClear))
			return true;
	}
	return false;
}

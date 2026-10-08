// cl: /Ireference/shims/bfme2_ascii /MD
// stlport
//
// ?rva004EE79E@Rva004EE79E@@QAEXPAURva004EE79ESub@@@Z @0x004EE79E 79B.
// Counted selection: unless the rowed 0x004E06FB key on the argument matches
// +0xEC, or the argument's +0x28 link is null, take the link's +0x2C tag;
// when the tag is 1, push the world's +0xFC selection into the +0x44
// ModuleData vector through rowed push_back 0x004DFCB0. Always bumps the
// +0x78 counter indexed by the tag.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include <vector>

class ModuleData;

class Rva002BA8F1Logic;

struct Rva004EE79EWorld
{
	char m_pad[0xFC];
	const ModuleData *m_FC;
};

struct Rva004EE79ESub
{
	char m_pad[0x2C];
	int m_2C;
};

class Rva004E06FBPtrChase32Field
{
public:
	int get() const;
	char m_pad[0x28];
	Rva004EE79ESub *m_28;
};

class Rva004EE79E
{
public:
	void rva004EE79E(Rva004E06FBPtrChase32Field *a);
private:
	char m_pad[0x44];
	_STL::vector<const ModuleData *> m_44;
	char m_pad50[0x78 - 0x50];
	int m_count[8];
	char m_pad98[0xEC - 0x98];
	int m_EC;
};

void Rva004EE79E::rva004EE79E(Rva004E06FBPtrChase32Field *a)
{
	if (a->get() != m_EC)
		return;
	Rva004EE79ESub *s = a->m_28;
	if (!s)
		return;
	if (s->m_2C == 1) {
		const ModuleData *sel = ((Rva004EE79EWorld *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))->m_FC;
		m_44.push_back(sel);
	}
	++m_count[s->m_2C];
}

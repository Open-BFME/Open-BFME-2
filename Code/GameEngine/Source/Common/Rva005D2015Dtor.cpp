// cl: /MD /EHsc
// ??1Rva005D2015@@UAE@XZ retail 0x005D2015 58B
// Own vptr C75778; under EH state 0 the body unregisters this from the +4
// subobject of the object at +8 through the rowed
// ?rva002B7250@Rva002B7250 0x002B7250; the inline base dtor restores
// C6E350. Caller: rowed ??_G 0x005D204F. Names address-derived.

class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *who);
};

struct Rva005D2015Owner
{
	int m_00;
	Rva002B7250 m_list; // +0x04
};

struct Rva002BA8F1Listener;

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
};

namespace StrategicInGameUI
{
class HeroArmySelectionHandler
{
public:
	bool rva005D1F22();
};
}

class Rva005D2015Base
{
public:
	virtual ~Rva005D2015Base() {}
};

class Rva005D2015 : public Rva005D2015Base
{
public:
	Rva005D2015(int a, int owner, int c);
	virtual ~Rva005D2015();

private:
	int m_04; // +0x04
	Rva005D2015Owner *m_owner; // +0x08
	int m_0C;
	bool m_10;
};

// ??0Rva005D2015@@QAE@HHH@Z, retail 0x005D206B..0x005D20C1 (86 bytes, EH,
// RET 12; the spelling its caller 0x005CDD32 pinned): after the base (EH state
// 0) the three arguments go to +0x04/+0x08/+0x0C, +0x10 takes the pinned
// HeroArmySelectionHandler 0x005D1F22 query on this, and this registers in
// the owner's +0x04 list (rowed append 0x005A0B4C) -- the list the
// destructor below leaves.
Rva005D2015::Rva005D2015(int a, int owner, int c)
	: m_04(a), m_owner((Rva005D2015Owner *)owner), m_0C(c), m_10(false)
{
	m_10 = reinterpret_cast<StrategicInGameUI::HeroArmySelectionHandler *>(this)->rva005D1F22();
	reinterpret_cast<Rva005A0B4CList *>(&m_owner->m_list)->append((Rva002BA8F1Listener *)this);
}

Rva005D2015::~Rva005D2015()
{
	m_owner->m_list.rva002B7250((CreateAHeroData *)this);
}

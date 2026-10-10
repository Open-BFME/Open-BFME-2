// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??1AptConnectionScreen@@UAE@XZ, retail 0x005DB681..0x005DB6DA (89 bytes,
// EH); pinned until now as the opaque ??1Rva005DB681@@UAE@XZ. The online
// connection grid's destructor (class of AptConnectionScreenConstructor.cpp:
// the Apt window half and the 4-byte listener at +0x58): it restores the
// vftables 0x00C76798 / 0x00C7678C, unregisters the listener from the list
// at +0x2C of the object at 0x00E063F8 (rowed 0x002B7250), puts the listener
// base's own vftable back and runs the Apt window half's destructor.
#include "ascii_string.h"

class Rva005248D0
{
public:
	virtual ~Rva005248D0();

private:
	char m_pad[0x58 - 4];
};

class Rva0059EB41
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual ~Rva0059EB41() {}
};

class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};

class Rva005A6D47
{
public:
	char m_pad[0x2C];
	Rva002B7250 m_2C; // +0x2C
};

struct NAT;
extern NAT *TheNAT;

class AptConnectionScreen : public Rva005248D0, public Rva0059EB41
{
public:
	virtual ~AptConnectionScreen();

private:
	void *m_level; // +0x5C
};

AptConnectionScreen::~AptConnectionScreen()
{
	if (TheNAT)
		((Rva005A6D47 *)TheNAT)->m_2C.rva002B7250((CreateAHeroData *)static_cast<Rva0059EB41 *>(this));
}

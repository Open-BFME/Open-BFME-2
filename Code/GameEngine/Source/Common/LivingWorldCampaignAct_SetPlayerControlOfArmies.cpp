// cl: /Ireference/shims/bfme2_ascii /MD
// ?SetPlayerControlOfArmies@LivingWorldCampaignAct@@QAEXXZ @0x00564C08 56B.
// Applies the singleton finder to a 12-byte record range: for each record
// from +0xA8 to +0xAC, looks up the AsciiString at +0x4 through the rowed
// find 0x002B48E1 on the Rva00DFEF10 singleton, and on a hit stores the
// record byte at +0x8 through the rowed byte-slot set 0x00318D14.
// Caller at 0x005669AA; unblocks 0x0056696F.
// TU-local honest-address views; offsets prove operations not type names.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "ascii_string.h"

struct Rva002E1948Entry;

class Rva002B48E1
{
public:
	Rva002E1948Entry *rva002B48E1(const AsciiString &name);
};

class Rva00318D14ByteSlot
{
public:
	void set(unsigned char value);
};

struct Rec00564C08
{
	char m_pad0[4];
	AsciiString m_name4;
	unsigned char m_flag8;
	char m_pad9[3];
};

typedef unsigned int UnsignedInt;

class LivingWorldCampaignActEntry;

template <class T> class ActVectorView
{
public:
	UnsignedInt size() const { return UnsignedInt(m_finish - m_start); }
	T &operator[](UnsignedInt i) { T *base=m_start; return *(base+i); }
private:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};


struct Rva00565085Record
{
    int unknown;
    AsciiString ownerName;
    AsciiString regionName;
};

struct Rva00565085Vector
{
    // ?Rva00565085Vector::size absent-from-retail
    unsigned size() const { return end - begin; }
    // ?Rva00565085Vector::operator[] absent-from-retail
    Rva00565085Record &operator[](unsigned index) const { return begin[index]; }
    Rva00565085Record *begin;
    Rva00565085Record *end;
    Rva00565085Record *storage;
};

struct Rva002B99F8Request
{
	void *m_vtbl;
	unsigned char m_player[4];
	int m_templateToken;
	unsigned char m_region[4];
	bool m_captured;
};

struct Rva00565106Vector
{
	unsigned size() const { return end - begin; }
	Rva002B99F8Request *begin;
	Rva002B99F8Request *end;
	Rva002B99F8Request *storage;
};

class LivingWorldCampaignAct
{
public:
	void rva00564EC0();
	void SetPlayerControlOfArmies();
	void MoveArmies();
	void rva00565106();
private:
	unsigned char m_pad00[0x14];
	ActVectorView<LivingWorldCampaignActEntry> m_entries;
	unsigned char m_pad20[0xC];
	Rva00565085Vector records;
	Rva00565106Vector requests;
	unsigned char m_pad44[0x64];
	Rec00564C08 *m_beginA8;
	Rec00564C08 *m_endAC;
};

void LivingWorldCampaignAct::SetPlayerControlOfArmies()
{
	Rec00564C08 *begin = m_beginA8;
	Rec00564C08 *end = m_endAC;
	for (Rec00564C08 *p = begin; p != end; ++p)
	{
		Rva002E1948Entry *entry = (*(Rva002B48E1 **)&TheLivingWorldLogic)->rva002B48E1(p->m_name4);
		if (entry != 0)
			((Rva00318D14ByteSlot *)entry)->set(p->m_flag8);
	}
}

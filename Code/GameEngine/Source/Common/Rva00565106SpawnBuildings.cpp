// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
#include "ascii_string.h"
// ?rva00565106@LivingWorldCampaignAct@@QAEXXZ, retail 0x00565106 (66 bytes). Same class as the rowed
// MoveArmies (Rva00565085.cpp, 0x00565085): the second record vector, 20-byte spawn requests at
// +0x38/+0x3C, each handed to LivingWorldLogic::spawnBuilding (0x002B99F8, rowed). WorldBuilder's twin
// 0x0143A8C0 is unnamed, so the method keeps its address token.
class LivingWorldLogic
{
public:
	void spawnBuilding(const struct Rva002B99F8Request *request);	// 0x002B99F8
};
extern LivingWorldLogic *TheLivingWorldLogic;

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


struct Rec00564C08;

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

void LivingWorldCampaignAct::rva00565106()
{
	for (unsigned i = 0; i < requests.size(); ++i)
		TheLivingWorldLogic->spawnBuilding(&requests.begin[i]);
}

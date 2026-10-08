// cl: /O1 /G7 /arch:SSE /GX /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// stlport
// BFME1 donor de2635e7934f33f6f82a8dbba8a2bf02dee3cb98:
// game/GameEngine/Source/GameClient/Rva004498D0BurstEntries.cpp.
// Target 0x002A4646..0x002A470F: four 12-byte random variables followed
// by a list at +0x30; getValue calls at 0x002341A1; unsigned client frame
// through slot 0x7C; temporary integer/name record and list push_front.
// Donor suggests cursor-particle burst scheduling. The owner and member
// names remain unresolved; target reads the global random variable at +0xD54.

#include <list>
#include "ascii_string.h"

class GameClientRandomVariable
{
public:
	float getValue() const;
private:
	int distribution;
	float low, high;
};

struct TreeKey00242F5E
{
	int m_id;
	AsciiString m_name;
};

template <> void _STL::list<TreeKey00242F5E>::push_front(const TreeKey00242F5E &);

class Rva002A4646Client
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E();
	virtual void slot0F(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1A();
	virtual void slot1B(); virtual void slot1C(); virtual void slot1D();
	virtual void slot1E(); virtual unsigned int getFrame();
};

struct Rva002A4646GlobalData
{
	unsigned char padding[0xD54];
	GameClientRandomVariable factor;
};

class GameClient;
class GlobalData;
extern GameClient *TheGameClient;
extern GlobalData *TheWritableGlobalData;

class Rva002A4646BurstRecord
{
public:
	void rva002A4646(AsciiString name, unsigned int count);
private:
	GameClientRandomVariable first, second, third, fourth;
	_STL::list<TreeKey00242F5E> entries;
};

void Rva002A4646BurstRecord::rva002A4646(AsciiString name, unsigned int count)
{
	int total = (int)(((Rva002A4646GlobalData *)TheWritableGlobalData)->factor.getValue() * count + 0.5f);
	for (int i = 0; i < total; ++i)
	{
		TreeKey00242F5E entry;
		entry.m_id = (int)(((Rva002A4646Client *)TheGameClient)->getFrame() + first.getValue());
		entry.m_name = name;
		entries.push_front(entry);
	}
}

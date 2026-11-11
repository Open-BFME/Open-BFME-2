// cl: /O1 /DNDEBUG /MD
// stlport
//
// ?rva002B488E@Rva002BA8F1Logic@@QAEPAURva002B488EResult@@H@Z, retail 0x002B488E, 83B.
// The name is the one 8 matched callers already use. Target evidence: null
// key returns 0; otherwise walks the pointer vector at this+0x8C/+0x90
// (finish-minus-start shr 2 recomputed each pass), asks each element's
// rowed-pin 0x002E0A9F about the key and returns the first non-zero answer,
// else 0. Next to the LivingWorldLogic rows; names are placeholders.
#include <vector>

struct Rva002B488EResult;

#include "../../../../Include/GameLogic/Rva002E0A9FElem.h"

// What the +0x124 list holds: records keyed by the int at +0x20.
struct Rva002B3187Elem
{
	unsigned char m_pad00[0x20];
	int m_key;	// +0x20
};

class Rva002BA8F1Logic
{
public:
	Rva002B488EResult *rva002B488E(int key);
	Rva002B3187Elem *rva002B3187(int key);
	Rva002B488EResult *rva002B4929(int key);

private:
	unsigned char m_pad0[0x8C];
	std::vector<Rva002E0A9FElem *> m_elems;	// +0x8C
	unsigned char m_pad98[0x124 - 0x98];
	std::vector<Rva002B3187Elem *> m_records;	// +0x124
};

Rva002B488EResult *Rva002BA8F1Logic::rva002B488E(int key)
{
	if (key == 0)
		return 0;
	for (unsigned int i = 0; i < m_elems.size(); ++i)
	{
		int found = m_elems[i]->rva002E0A9F((void *)key);
		if (found)
			return (Rva002B488EResult *)found;
	}
	return 0;
}

// ?rva002B3187@Rva002BA8F1Logic@@QAEPAURva002B3187Elem@@H@Z, retail
// 0x002B3187, 75B: the first record of the +0x124 pointer vector whose +0x20
// key matches, else 0 (the same indexed search shape as the region manager's
// pending-battle lookups).
Rva002B3187Elem *Rva002BA8F1Logic::rva002B3187(int key)
{
	for (unsigned int i = 0; i < m_records.size(); ++i)
	{
		if (m_records[i]->m_key == key)
			return m_records[i];
	}
	return 0;
}

// ?rva002B4929@Rva002BA8F1Logic@@QAEPAURva002B488EResult@@H@Z, retail
// 0x002B4929, 31B: the army the players know by this id (rva002B488E), or
// failing that the +0x124 record keyed by it (rva002B3187).
Rva002B488EResult *Rva002BA8F1Logic::rva002B4929(int key)
{
	Rva002B488EResult *found = rva002B488E(key);
	if (!found)
		found = (Rva002B488EResult *)rva002B3187(key);
	return found;
}

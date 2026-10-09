// cl: /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD
// stlport
//
// ?rva005B4653@Rva005B486DOwner@@QAEXXZ
// retail 0x005B4653..0x005B486D (538 bytes) thiscall no arguments.
//
// Builds the create-a-hero power grid. WorldBuilder twin 0x01575640
// AptCreateAHero::Powers::BuildPowersData (AptCreateAHeroPowers.cpp asserts
// 539..655; wb-name-unverified) supplies the structure. The spelling is the
// existing pin used by the rowed tail 0x005B486D.
// Target evidence: resets the page (rowed 0x005B3D50); walks the hero at
// owner+0x27c by its rowed count/indexed button pair (0x00409EA0 and
// 0x00409EB3) and stores a fresh 28-byte cell (ctor 0x005B266D) under the
// button name at +0x10 through the rowed map subscript 0x005B4023; then
// repeats a pass over the map (rowed _M_increment 0x00024250) placing each
// unplaced cell in a new 16-byte row (memset plus the rowed row Add
// 0x005B269D and vector push_back 0x0059D2A3) or behind its prerequisite
// (rowed GetPrereqData 0x005B3FAB) until no cell waits on an unplaced one;
// an out-of-range prerequisite row returns early. Each row's slots are then
// moved right by the button's level (rowed get 0x002190A1 and the ten-entry
// rdata table at VA 0x00C72CAC). Finally the owned powers are re-added by
// level (rowed 0x00406ED7 lookup + _M_find 0x001F8437 + AddMyPower
// 0x005B3676) the hero's vslot 0x14 runs the rows are sorted (rowed sort
// 0x005B4610) and each placed cell gets its row index at +4.
#include "ascii_string.h"
#include <map>
#include <vector>
#include <string.h>

struct BfmeE16 { float x, y, z, w; };
namespace _STL { template<> void vector<BfmeE16>::push_back(const BfmeE16 &); }

class Rva002190A1DwordField
{
public:
	int get() const;
};

struct Rva005B2E09Cell
{
	Rva002190A1DwordField *m_button; // +0x00
	int m_row;                       // +0x04
	int m_column;                    // +0x08
	int m_index0c;                   // +0x0c
	int m_powerIndex;                // +0x10
	bool m_owned;                    // +0x14
	int m_18;                        // +0x18
};

// The 28-byte mapped value as the rowed subscript 0x005B4023 spells it.
struct TreeHintPayload005B3786 { unsigned int words[7]; };
namespace _STL { template<> TreeHintPayload005B3786 &map<AsciiString, TreeHintPayload005B3786>::operator[](const AsciiString &); }

// Rowed ctor 0x005B266D: button then -1 x4 then false then 0.
struct Rva005B266D
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	unsigned char m_14;
	int m_18;
	Rva005B266D(int arg);
};

struct Rva005B269DRow
{
	void *slots[4];
	void rva005B269D(Rva005B2E09Cell *c, int v, unsigned idx);
};

struct Rva005B2FDCItem { void *slots[4]; };
struct Rva005B26CEItemCmp {};
namespace _STL { template <class _RandomAccessIter, class _Compare> void sort(_RandomAccessIter, _RandomAccessIter, _Compare); }

class CommandButton;
class CreateAHeroHero
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	int rva00409EA0();
	const CommandButton *rva00409EB3(unsigned index);
};
class Rva00406ED7
{
public:
	const CommandButton *rva00406ED7(int idx);
};

struct Rva005B4653Owner
{
	char m_pad00[0x27c];
	CreateAHeroHero m_hero;
};

namespace AptCreateAHero
{
class Powers
{
public:
	void rva005B3D50();
	Rva005B2E09Cell *GetPrereqData(Rva005B2E09Cell *cell);
	void AddMyPower(Rva005B2E09Cell *cell, bool flash);
};
}

extern const int g_00C72CAC[];

class Rva005B486DOwner
{
public:
	void rva005B4653();
private:
	typedef _STL::map<AsciiString, Rva005B2E09Cell> PowerMap;
	char m_pad00[4];
	Rva005B4653Owner *m_owner;          // +0x04
	PowerMap m_powersNameMap;           // +0x08
	_STL::vector<BfmeE16> m_powerMatrix; // +0x14
	char m_pad20[0x50 - 0x20];
	int m_numPowers;                    // +0x50
};

void Rva005B486DOwner::rva005B4653()
{
	AptCreateAHero::Powers *powers = (AptCreateAHero::Powers *)this;
	powers->rva005B3D50();
	CreateAHeroHero *hero = &m_owner->m_hero;
	unsigned int count = hero->rva00409EA0();
	for (unsigned int i = 0; i < count; ++i)
	{
		const CommandButton *button = hero->rva00409EB3(i);
		if (!button)
			continue;
		Rva005B266D data((int)button);
		*(Rva005B266D *)&((_STL::map<AsciiString, TreeHintPayload005B3786> *)&m_powersNameMap)->operator[](*(const AsciiString *)((const char *)button + 0x10)) = data;
	}

	bool done;
	do
	{
		done = true;
		for (PowerMap::iterator it = m_powersNameMap.begin(); it != m_powersNameMap.end(); ++it)
		{
			Rva005B2E09Cell *data = &(*it).second;
			if (data->m_row >= 0 && data->m_column >= 0)
				continue;
			Rva005B2E09Cell *prereq = powers->GetPrereqData(data);
			if (!prereq)
			{
				Rva005B269DRow group;
				memset(&group, 0, sizeof(group));
				group.rva005B269D(data, m_powerMatrix.size(), 0);
				m_powerMatrix.push_back(*(BfmeE16 *)&group);
			}
			else
			{
				bool valid = prereq->m_row >= 0 && prereq->m_column >= 0;
				if (!valid)
				{
					done = false;
					continue;
				}
				unsigned int row = prereq->m_row;
				if (row >= m_powerMatrix.size())
					return;
				((Rva005B269DRow *)&m_powerMatrix[row])->rva005B269D(data, row, prereq->m_column + 1);
			}
		}
	} while (!done);

	for (BfmeE16 *g = m_powerMatrix.begin(); g != m_powerMatrix.end(); ++g)
	{
		Rva005B2E09Cell **slots = (Rva005B2E09Cell **)g;
		int maxSlot = 3;
		for (int j = maxSlot; j >= 0; --j)
		{
			Rva005B2E09Cell *data = slots[j];
			if (!data)
				continue;
			if (j == maxSlot)
				continue;
			unsigned int minLevel = data->m_button->get();
			if (minLevel)
				--minLevel;
			if (minLevel > 10)
				continue;
			int slot = g_00C72CAC[data->m_button->get() - 1];
			if (slot < j)
				slot = j;
			else if (slot > maxSlot)
				slot = maxSlot;
			slots[j] = 0;
			slots[slot] = data;
			data->m_column = slot;
			maxSlot = slot - 1;
		}
	}

	m_numPowers = 0;
	for (;;)
	{
		const CommandButton *button = ((Rva00406ED7 *)&m_owner->m_hero)->rva00406ED7(m_numPowers);
		if (!button)
			break;
		PowerMap::iterator it = m_powersNameMap.find(*(const AsciiString *)((const char *)button + 0x10));
		if (it == m_powersNameMap.end())
			break;
		powers->AddMyPower(&(*it).second, false);
	}
	m_owner->m_hero.slot14();
	_STL::sort((Rva005B2FDCItem *)m_powerMatrix.begin(), (Rva005B2FDCItem *)m_powerMatrix.end(), Rva005B26CEItemCmp());
	int row = 0;
	for (BfmeE16 *g = m_powerMatrix.begin(); g != m_powerMatrix.end(); ++row, ++g)
	{
		Rva005B2E09Cell **slots = (Rva005B2E09Cell **)g;
		for (int j = 0; j < 4; ++j)
		{
			Rva005B2E09Cell *cell = slots[j];
			if (cell)
				cell->m_row = row;
		}
	}
}

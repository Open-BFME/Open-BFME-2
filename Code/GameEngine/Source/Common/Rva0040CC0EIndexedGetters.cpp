// ?get@Rva0040CC0EIndexedField@@QBEHH@Z @0x0040CC0E 13B and ?get@Rva0040CB2CIndexedField@@QBEHH@Z @0x0040CB2C 14B
// Twin indexed getters into 8-byte entries at +0x40: first and second dword.
// Evidence: 10 callers of 0x40CC0E including StateMachine::getGoalObject 0x5E68C0; 38 callers of 0x40CB2C;
// sibling +4 twin shape; shared +0x40/+0x44 vector layout with 0x40CC1B linear search and 0x40CB3A binary search.
#include "../../Include/GameClient/Rva0040CC0EEntry.h"

class Rva0040CC0EIndexedField
{
public:
	int get(int index) const;
private:
	char m_pad[0x40];
	Rva0040CC0EEntry *m_entries;
};

int Rva0040CC0EIndexedField::get(int index) const
{
	return m_entries[index].first;
}

class Rva0040CB2CIndexedField
{
public:
	int get(int index) const;
private:
	char m_pad[0x40];
	Rva0040CC0EEntry *m_entries;
};

int Rva0040CB2CIndexedField::get(int index) const
{
	return m_entries[index].second;
}

// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
//
// ?addTeam@TeamsInfoRec@@QAEHPBVDict@@@Z retail 0x0032DA4E 184 bytes, plus its
// catch-all handler at 0x0032DB06 (20 bytes).
//
// Donor: Open-BFME-1 game/GameEngine/Source/GameLogic/Map/Rva0019BA40TeamRecAppend.cpp
// (reference/open-bfme-1 @ 6d943426; BFME1 0x0019BA40 append + catch 0x0019BB8B).
// The donor compiled at BFME 1's /O2 /Oy- does not place in game.dat; the same
// body compiled /O1 (the flag of the sibling SidesListTeamsInfoRecSwap.cpp,
// and what the __EH_prolog entry here implies) is byte-identical to retail
// apart from two adaptations, both read off retail:
//   - the free-list grow pushes a TEMPORARY: retail passes the out-of-line
//     ??0BfmeThingUBB return value (eax) straight to push_back 0x0032D2EA;
//   - the Dict set is ONE call to Dict::Rva00329CF0 (clear, then assign if
//     non-null), where BFME 1 inlined the clear and the guarded assignment.
//
// Target evidence: receiver layout as SidesListTeamsInfoRecSwap.cpp (map at
// +0x00, 16-byte element vector at +0x0C, shorts at +0x18/+0x1A); FuncInfo
// 0x00D24B10 (via __ehhandler 0x00B7B8C0) has one try block (state 1) whose
// single catch-all handler is 0x0072DB06 -- the funclet row below, so its
// parent= is read from the EH tables, not from adjacency. 15 call sites reach
// 0x0032DA4E. The method name addTeam is an inference from Zero Hour's
// TeamsInfoRec::addTeam(const Dict *) role (append one team dict); the int
// return is retail's (eax = index). 0x0032D103 is an unidentified TeamsInfoRec
// member taking the index, named by address.

#include <vector>

class Dict
{
public:
	~Dict() { releaseData(); }
	void clear();
	void Rva00329CF0(const Dict *src);
private:
	void releaseData();
	void *m_data;
};

class BfmeThingUBB
{
public:
	BfmeThingUBB();
	short m_next;
	short m_previous;
	short m_reserved;
	short m_free;
	int m_generation;
	Dict m_dict;
};

class TeamsInfoRec
{
public:
	int addTeam(const Dict *dict);
	void rva0032D103(int index);

private:
	char m_map[0xc];
	std::vector<BfmeThingUBB> m_teams;
	short m_numActive;
	short m_freeHead;
};
int TeamsInfoRec::addTeam(const Dict *dict)
{
	if (m_freeHead == 0)
	{
		int index = (int)m_teams.size();
		m_teams.push_back(BfmeThingUBB());
		m_freeHead = (short)index;
	}

	int index = m_freeHead;
	BfmeThingUBB *team = m_teams.begin() + index;
	team->m_dict.Rva00329CF0(dict);
	try
	{
		rva0032D103(index);
	}
	catch (...)
	{
		team->m_dict.clear();
		throw;
	}
	m_freeHead = team->m_next;
	m_teams[m_teams[0].m_previous].m_next = (short)index;
	team->m_previous = m_teams[0].m_previous;
	team->m_next = 0;
	m_teams[0].m_previous = (short)index;
	++m_numActive;
	return index;
}

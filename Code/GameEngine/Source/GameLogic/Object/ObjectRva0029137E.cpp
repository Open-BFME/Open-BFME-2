// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// ?rva0029137E@Object@@QAE_NAAVAsciiString@@@Z @0x0029137E 109B: Object bool fill AsciiString via template plus Team check. Evidence: rowed rva0028F518 ThePlayerList bfmeAskRV getRelationship cmp 2 set isEmpty neg-sbb-inc callers 0x0029EE98 0x004E769E. Stash 0.93 tmpl in edi vs retail eax.
#include "ascii_string.h"

enum Relationship
{
	REL_ENEMY = 0,
	REL_NEUTRAL = 1,
	REL_ALLY = 2
};

class Team
{
public:
	Relationship getRelationship(const Team *other) const;
};

class BfmeMemberRV
{
public:
	bool bfmeAskRV();
public:
	char m_pad00[0x2ec];
	Team *m_team2ec;
};

class PlayerList
{
public:
	char m_pad00[0x10];
	BfmeMemberRV *m_p10;
};

extern PlayerList *ThePlayerList;

struct ObjectTmplPart
{
	char m_pad00[0x5c];
	AsciiString m_str5c;
};

class Object
{
public:
	bool rva0029137E(AsciiString &out);
	bool rva0028F518();
private:
	char m_pad00[4];
	ObjectTmplPart *m_p04;
	char m_pad08[0x304 - 8];
	Team *m_team304;
};

bool Object::rva0029137E(AsciiString &out)
{
	if (!rva0028F518())
		return false;
	PlayerList *pl = ThePlayerList;
	Team *myTeam = m_team304;
	BfmeMemberRV *member = pl->m_p10;
	if (!member || !myTeam)
		return false;
	if (member->bfmeAskRV()) {
		Team *other = member->m_team2ec;
		if (myTeam->getRelationship(other) == REL_ALLY)
			return false;
	}
	if (!m_p04)
		return false;
	((StringBase<char> *)&out)->set(*(const StringBase<char> *)&m_p04->m_str5c);
	return !((const StringBase<char> *)&out)->isEmpty();
}

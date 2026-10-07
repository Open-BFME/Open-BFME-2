// cl: /O1 /DNDEBUG /MD /DWIN32 /D_WINDOWS
//
// ?rva00298AAD@Object@@QAEXPAVTeam@@@Z @0x00298AAD 55B. Object thiscall
// ret 4 (one Team* arg): team-change gate driving status 0x3E plus the
// pinned 0x298480 hook.
//
// Target evidence (game.dat, read-only, capstone): frameless thiscall
// (push esi/edi; arg from [esp+0xC]); rowed callees testStatus 0x4E536
// and setStatus 0x23DB0D (0x3E, true); arg compared against m_team
// +0x304; pinned thiscall rva00298480 0x298480 with the team.
// Object layout (template-adjacent team slot +0x304) after
// ObjectSetProducer.cpp. Identity unproven: honest address-derived
// name; neighbour range bodies reuse this TU's views.
class Team
{
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_3E = 0x3E
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes s) const;
	void setStatus(ObjectStatusTypes s, bool set);
	void rva00298480(Team *team);
	void rva00298AAD(Team *team);
private:
	unsigned char m_pad00[0x304];
	Team *m_team; // +0x304
};

// ?rva00298AAD@Object@@QAEXPAVTeam@@@Z
void Object::rva00298AAD(Team *team)
{
	if (team == 0)
		return;
	if (testStatus(OBJECT_STATUS_3E))
		return;
	if (team == m_team)
		return;
	setStatus(OBJECT_STATUS_3E, true);
	rva00298480(team);
}

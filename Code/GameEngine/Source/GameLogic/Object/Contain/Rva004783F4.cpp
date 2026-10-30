// cl: /DNDEBUG /MD /EHsc
//
// ?rva004783F4@Rva004783F4@@QAEPAVTeam@@XZ, retail 0x004783F4, 24 bytes.
// Honest-address method: if the +0xFC team id is zero return null,
// else return TheTeamFactory->findTeamByID(id) through the rowed
// ?findTeamByID@TeamFactory row. Offset +0xFC is the first member after
// the 0xFC OpenContain base (GarrisonContainDtor precedent); owner is not
// proven by a vtable here so the address name is used. Evidence: caller
// 0x00480BFD, TheTeamFactory global 0x00A028BC, rowed findTeamByID
// 0x0039F761.

#include "../../../../Include/Common/TeamBFME2.h"
class TeamFactory;

class TeamFactory
{
public:
	Team *findTeamByID(unsigned int id);
};

extern TeamFactory *TheTeamFactory;

class Rva004783F4Primary
{
public:
	virtual void p00();
	unsigned char m_pad[0x20 - 4];
};

class Rva004783F4ContainIface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20();
	virtual void setOriginalTeam(Team *team);
};

class Rva004783F4 : public Rva004783F4Primary, public Rva004783F4ContainIface
{
public:
	virtual void setOriginalTeam(Team *team);
	Team *rva004783F4();

private:
	unsigned char m_pad[0xFC - 0x24];
	unsigned int m_instance; // +0xFC team id
};

// ?setOriginalTeam@Rva004783F4@@UAEXPAVTeam@@@Z @0x004783DC
void Rva004783F4::setOriginalTeam(Team *team)
{
	m_instance = team ? team->m_id : 0;
}

// ?rva004783F4@Rva004783F4@@QAEPAVTeam@@XZ @0x004783F4
Team *Rva004783F4::rva004783F4()
{
	if (m_instance == 0)
		return 0;
	return TheTeamFactory->findTeamByID(m_instance);
}

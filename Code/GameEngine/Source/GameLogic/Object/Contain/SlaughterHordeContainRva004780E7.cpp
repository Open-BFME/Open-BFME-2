// ?rva004780E7@SlaughterHordeContain@@UAEPAVPlayer@@PBV2@@Z
// cl: /DNDEBUG /MD /EHsc
//
// ?rva004780E7@SlaughterHordeContain@@UAEPAVPlayer@@PBV2@@Z, retail 0x004780E7, 90 bytes.
// Virtual slot 57 (offset 0xE4) of vtable 0x00C48AA0 (SlaughterHordeContain primary
// 0x00C48AA0 per SlaughterHordeContainDtor; secondary at +0x20 per nine-base
// OpenContain chain). GarrisonContain::getApparentControllingPlayer variant:
// owner player via m_object at primary +0x08 ([ecx-0x18] from +0x20 this),
// hide flag byte at primary +0x9DD ([ecx+0x9BD]), instance at primary +0xFC
// ([ecx+0xDC] via TheTeamFactory->findInstance pin 0x0039F761), observing
// default team at Player +0x2EC, ALLIES==2. Evidence: rowed callees
// getControllingPlayer@Object 0x0028AFA9 getRelationship@Player 0x002AD0C6
// getControllingPlayer@Team 0x0039D7CF, TheTeamFactory 0x00A028BC,
// GarrisonContain.cpp getApparentControllingPlayer donor shape.
//
// The hide-flag and null-myPlayer guards are one short-circuit test so both
// exits share the single materialize-eax exit at 0x0047813A; splitting them
// lets cl skip the dead `mov eax,edi` for the myPlayer==0 arm and lands one
// byte off (jump target 0x0047813C instead of 0x0047813A).

class Player;
class Team;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Player
{
public:
	Relationship getRelationship(const Team *team) const;
	unsigned char m_pad000[0x2EC];
	Team *m_defaultTeam; // +0x2EC
};

class Team
{
public:
	Player *getControllingPlayer() const;
};

class Rva0039F761Owner
{
public:
	Team *findInstance(void *instance);
};

class TeamFactory;
extern TeamFactory *TheTeamFactory;

class B0
{
public:
	virtual void b0();
protected:
	const void *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class B1
{
public:
	virtual void b1();
};

class B2
{
public:
	virtual void b2();
private:
	unsigned char m_pad[12];
};

#define GSLOT08(a,b,c,d,e,f,g,h) virtual void a() = 0; virtual void b() = 0; virtual void c() = 0; virtual void d() = 0; virtual void e() = 0; virtual void f() = 0; virtual void g() = 0; virtual void h() = 0;
#define GSLOT16(a) GSLOT08(a##0,a##1,a##2,a##3,a##4,a##5,a##6,a##7) GSLOT08(a##8,a##9,a##A,a##B,a##C,a##D,a##E,a##F)

class B3
{
public:
	GSLOT16(g0)
	GSLOT16(g1)
	GSLOT16(g2)
	GSLOT08(g30,g31,g32,g33,g34,g35,g36,g37)
	virtual void g38() = 0;
	virtual Player *rva004780E7(const Player *observing) = 0;
};

class B4
{
public:
	virtual void b4();
};

class B5
{
public:
	virtual void b5();
};

class B6
{
public:
	virtual void b6();
};

class B7
{
public:
	virtual void b7();
};

class B8
{
public:
	virtual void b8();
private:
	unsigned char m_pad[0xC8 - 4];
};

class GarrisonContain : public B0, public B1, public B2, public B3, public B4, public B5, public B6, public B7, public B8
{
public:
	void *m_instance; // +0xFC
	unsigned char m_pad100[0x9DD - 0x100];
	bool m_hideFlag; // +0x9DD (secondary +0x9BD)
	unsigned char m_pad9DE[0x9E0 - 0x9DE];
};

class SlaughterHordeContain : public GarrisonContain
{
public:
	virtual Player *rva004780E7(const Player *observing);
private:
	int m_9E0;
	int m_9E4;
	int m_9E8;
};

Player *SlaughterHordeContain::rva004780E7(const Player *observing)
{
	Player *myPlayer = m_object->getControllingPlayer();
	if (!m_hideFlag || !myPlayer)
		return myPlayer;
	if (!observing)
		return myPlayer;
	if (myPlayer->getRelationship(observing->m_defaultTeam) == ALLIES)
		return myPlayer;
	Team *team = ((Rva0039F761Owner *)TheTeamFactory)->findInstance(m_instance);
	if (team)
		return team->getControllingPlayer();
	return myPlayer;
}

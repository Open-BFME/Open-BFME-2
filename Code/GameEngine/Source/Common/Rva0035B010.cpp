// cl: /DNDEBUG /MD
// ?rva0035B010@Rva0035AFE4@@QAE_NPAVPlayer@@PAVObject@@@Z retail 0x0035B010 46B
// Chain method on the relationship-mask class: null-check both args, fetch
// Team from Object+0x304, pass Player::getRelationship result into the rowed
// mask pred 0x0035AFE4 on this.
// Evidence: chain lane (calls landed 0x0035AFE4), AFE4 header already cites
// caller 0x0035B031, callee rows getRelationship Team overload 0x002AD0C6
// plus pred 0x0035AFE4, caller at 0x00431048, ret 8 thiscall bool.
enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Team;
class Object;
class Player
{
public:
	Relationship getRelationship(const Team *that) const;
};

class Team
{
public:
	Player *getControllingPlayer() const;
};

class Object
{
public:
	char m_pad[0x304];
	Team *m_team;
};

class Rva0035AFE4
{
public:
	bool rva0035AFE4(int which);
	bool rva0035B010(Player *player, Object *obj);

private:
	char m_pad[0x1c];
	unsigned int m_1c;
};

bool Rva0035AFE4::rva0035B010(Player *player, Object *obj)
{
	if (player == 0 || obj == 0)
		return false;
	return rva0035AFE4(player->getRelationship(obj->m_team));
}

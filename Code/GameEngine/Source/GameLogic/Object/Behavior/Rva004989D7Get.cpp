// cl: /DNDEBUG /MD
// ?rva004989D7@Rva004989D7@@QBEPAVPlayer@@XZ @0x004989D7 8B
// Gap between GateOpenAndCloseBehaviorCtorShard 0x0049889C and Disp8 getter.
// Forwards member at +0x0C to rowed Object::getControllingPlayer 0x0028AFA9.
// Callers at 0x004E8F4D 0x004E91A5; landing unblocks 1.
class Object
{
public:
	class Player *getControllingPlayer() const;
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Player
{
public:
	Relationship getRelationship(const Object *obj) const;
};

class Rva004989D7
{
public:
	Player *rva004989D7() const;
	Relationship rva004989DF(const Player *p) const;
private:
	char m_pad[0x0C];
	Object *m_obj;
};

Player *Rva004989D7::rva004989D7() const
{
	return m_obj->getControllingPlayer();
}

Relationship Rva004989D7::rva004989DF(const Player *p) const
{
	return p->getRelationship(m_obj);
}

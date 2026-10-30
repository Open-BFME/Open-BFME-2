// cl: /MD
//
// Twin walkers 0x4E8FF6/0x4E9040: sweep [m_00..m_04), and for each
// gate-open element with a null relationship run the 0x49924B (or
// 0x4992D5 with a set flag) step, then poke the rowed 0x2E713F tail
// through the AI singleton. Retail 0x004E8FF6 74B, 0x004E9040 76B.
// Callee pins are honest address-derived candidates; the 0x4992D5
// (1, null) order follows its push sequence.

class Player;

enum Relationship
{
	REL_NONE = 0
};

class GateOpenAndCloseBehavior
{
	friend class Rva004E8FF6;
public:
	bool rva00498980();
	Relationship getRelationship(const Player *arg) const;	// 0x004989DF
private:
	void rva0049924B(bool open);			// rowed private members at 0x0049924B
	void rva004992D5(bool open, bool flag);	// and 0x004992D5
};

class Rva002E713FOwner
{
public:
	void rva002E713F();
};

class AI;
extern AI *TheAI;	// 0x009FF0F8, AI/ai.cpp's global

class Rva004E8FF6
{
public:
	void rva004E8FF6(void *player);
	void rva004E9040(void *player);

private:
	void **m_00;
	void **m_04;
};

// ?rva004E8FF6@Rva004E8FF6@@QAEXPAX@Z @0x004E8FF6 74B.
void Rva004E8FF6::rva004E8FF6(void *player)
{
	void **end = m_04;
	for (void **p = m_00; p != end; ++p)
	{
		void *o = *p;
		if (((GateOpenAndCloseBehavior *)o)->rva00498980())
		{
			int relationship = ((GateOpenAndCloseBehavior *)o)->getRelationship((const Player *)player);
			if (relationship == 0)
				((GateOpenAndCloseBehavior *)o)->rva0049924B((bool)relationship);
		}
	}
	((Rva002E713FOwner *)*(void **)((char *)TheAI + 0x10))->rva002E713F();
}

// ?rva004E9040@Rva004E8FF6@@QAEXPAX@Z @0x004E9040 76B.
void Rva004E8FF6::rva004E9040(void *player)
{
	void **end = m_04;
	for (void **p = m_00; p != end; ++p)
	{
		void *o = *p;
		if (((GateOpenAndCloseBehavior *)o)->rva00498980())
		{
			int relationship = ((GateOpenAndCloseBehavior *)o)->getRelationship((const Player *)player);
			if (relationship == 0)
				((GateOpenAndCloseBehavior *)o)->rva004992D5(true, (bool)relationship);
		}
	}
	((Rva002E713FOwner *)*(void **)((char *)TheAI + 0x10))->rva002E713F();
}

// cl: /MD
//
// Twin walkers 0x4E8FF6/0x4E9040: sweep [m_00..m_04), and for each
// gate-open element with a null relationship run the 0x49924B (or
// 0x4992D5 with a set flag) step, then poke the rowed 0x2E713F tail
// through the AI singleton. Retail 0x004E8FF6 74B, 0x004E9040 76B.
// Callee pins are honest address-derived candidates; the 0x4992D5
// (1, null) order follows its push sequence.

class GateOpenAndCloseBehavior
{
	friend class Rva004E8FF6;
public:
	bool rva00498980();
private:
	void rva0049924B(bool open);			// rowed private members at 0x0049924B
	void rva004992D5(bool open, bool flag);	// and 0x004992D5
};

class Player;

class Player;

enum Relationship
{
	REL_NONE = 0
};

class Rva004989D7
{
public:
	Relationship rva004989DF(const Player *arg) const;
};


class Rva002E713FOwner
{
public:
	void rva002E713F();
};

class AI;
extern AI *TheAI;	// 0x009FF0F8, ai_Rva002FD791.cpp's global

class Rva004E8FF6
{
public:
	void rva004E8FF6(void *arg);
	void rva004E9040(void *arg);

private:
	void **m_00;
	void **m_04;
};

// ?rva004E8FF6@Rva004E8FF6@@QAEXPAX@Z @0x004E8FF6 74B.
void Rva004E8FF6::rva004E8FF6(void *arg)
{
	void **end = m_04;
	for (void **p = m_00; p != end; ++p)
	{
		void *o = *p;
		if (((GateOpenAndCloseBehavior *)o)->rva00498980())
		{
			int r = ((Rva004989D7 *)o)->rva004989DF((const Player *)arg);
			if (r == 0)
				((GateOpenAndCloseBehavior *)o)->rva0049924B((bool)r);
		}
	}
	((Rva002E713FOwner *)*(void **)((char *)TheAI + 0x10))->rva002E713F();
}

// ?rva004E9040@Rva004E8FF6@@QAEXPAX@Z @0x004E9040 76B.
void Rva004E8FF6::rva004E9040(void *arg)
{
	void **end = m_04;
	for (void **p = m_00; p != end; ++p)
	{
		void *o = *p;
		if (((GateOpenAndCloseBehavior *)o)->rva00498980())
		{
			int r = ((Rva004989D7 *)o)->rva004989DF((const Player *)arg);
			if (r == 0)
				((GateOpenAndCloseBehavior *)o)->rva004992D5(true, (bool)r);
		}
	}
	((Rva002E713FOwner *)*(void **)((char *)TheAI + 0x10))->rva002E713F();
}

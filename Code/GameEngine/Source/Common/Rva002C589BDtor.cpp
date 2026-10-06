// cl: /DNDEBUG /MD
// ??1Rva002C589B@@QAE@XZ @0x002C589B 24B: non-virtual dtor that deletes the
// +0x24 heap object via the rowed Rva003ECDB7 dtor 0x003ECDB7 plus the rowed
// operator delete 0x0002FD60. Called by the unclaimed deleting dtor 0x0050526D
// plus two vector cleanups 0x0050549A and 0x00505710. Same +0x24 member is
// created by the unclaimed ctor 0x002C5C1F which formats AIThreatFinder%d.
// Owner identity unproven so the name stays address-derived.
class Rva003ECDB7Object
{
public:
	~Rva003ECDB7Object();
};

enum ObjectID
{
	INVALID_ID = 0
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Rva002C589B
{
public:
	~Rva002C589B();
	void rva002C5843(bool v);
	Object *rva002C5DA6();

private:
	char m_pad[0x18];
	bool m_18;
	bool m_19;
	char m_pad1A[0xA];
	Rva003ECDB7Object *m_ptr;
	char m_pad28[0xC];
	ObjectID m_34;
};

Rva002C589B::~Rva002C589B()
{
	delete m_ptr;
}

void Rva002C589B::rva002C5843(bool v)
{
	if (m_18 != v) {
		m_18 = v;
		if (v)
			m_19 = 1;
	}
}

Object *Rva002C589B::rva002C5DA6()
{
	return m_34 ? TheGameLogic->findObjectByID(m_34) : 0;
}

// cl: /O1 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva0053ED1A@@QAE@XZ retail 0x0053ED1A 86B.
// Evidence: constructs the primary base through the pinned
// GameEngineDeletingBase ctor 0x001B4E63 (state 0), the secondary base at +0xC
// through 0x005C6D4D, installs vtables 0x00C69464 at +0 and 0x00C6944C at
// +0xC, builds the vector at +0x48 through the pinned _Vector_base ctor
// 0x00211E58 with an allocator temporary, then zeroes +0x54 and +0x58. Slot 0
// of the +0xC vftable is a this-12 thunk to ??_G, so the secondary base leads
// with a virtual dtor; it is inline and empty, so no unwind state follows it.
// Names are generated; the vector's element type and the secondary base's
// contents are not established.
#include <vector>

class GameEngineDeletingBase
{
public:
	GameEngineDeletingBase();
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[8];
};

class Rva005C6D4D
{
public:
	Rva005C6D4D();
	virtual ~Rva005C6D4D() {}
private:
	char m_pad04[0x38];
};

class Rva0053ED1A : public GameEngineDeletingBase, public Rva005C6D4D
{
public:
	Rva0053ED1A();
	virtual ~Rva0053ED1A();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void rva0053EDD2();
private:
	_STL::vector<int> m_at48;
	int m_at54;
	int m_at58;
};

Rva0053ED1A::Rva0053ED1A() : m_at54(0), m_at58(0)
{
}

class GameLogic;
extern GameLogic *TheGameLogic;
class Object;
enum ObjectID
{
	INVALID_ID = 0
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
class Rva005C6C7B
{
public:
	void reset();
};
class Rva005C65F1
{
public:
	void rva005C65F1();
};

void Rva0053ED1A::rva0053EDD2()
{
	Object *obj = TheGameLogic->findObjectByID(*(ObjectID *)&m_at48);
	if (obj == 0)
		return ((Rva005C6C7B *)this)->reset();
	else
		return ((Rva005C65F1 *)this)->rva005C65F1();
}

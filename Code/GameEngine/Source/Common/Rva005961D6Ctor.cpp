// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /G7 /arch:SSE
// ?rva00596269@Rva005961D6@@QAEXXZ
// stlport
// ??0Rva005961D6@@QAE@XZ, retail 0x005961D6, 79 bytes.
// Derived ctor calling base Rva0025BFE3 ctor at 0x0025BFC7, then two
// Rva003ECA4BElement ctors at +0x10 and +0x54 (0x44 apart, rowed at 0x003ECA4B),
// then vector<BfmeE16> at +0x98 via rowed vector_base at 0x00211E58. Stores
// derived vtable 0x00870A4C. Layout: base 0x10 bytes (vtable+vector), two
// 0x44 elements abutting (+0x10..+0x53, +0x54..+0x97), vector 12 bytes at +0x98.
// Caller at 0x004E0363 constructs this; unblocks 0x004E030B.
#include <vector>
struct BfmeE16 { float x, y, z, w; };
class Rva0025BFE3
{
public:
	Rva0025BFE3();
	virtual ~Rva0025BFE3();
private:
	_STL::vector<BfmeE16> m_vec04;
};
class Rva003ECA4BElement
{
public:
	Rva003ECA4BElement();
};
class Rva005961D6 : public Rva0025BFE3
{
public:
	Rva005961D6();
	void rva00596269();

private:
	Rva003ECA4BElement m_e10;
	char m_pad11[0x43];
	Rva003ECA4BElement m_e54;
	char m_pad55[0x43];
	_STL::vector<BfmeE16> m_vec98;
};
Rva005961D6::Rva005961D6() : Rva0025BFE3(), m_e10(), m_e54(), m_vec98()
{
}

#include "GameLogicObjectLookupView.h"

class Object;
class Player;

class Rva003ECA69Element
{
public:
	void clear();
	class Rva003ECA69Element *rva003ECB52(struct Rva003ECB52Arg *arg);
};

struct Rva003ECB52Inner
{
	char m_pad[0x51c];
	float m_value;
	int m_index;
};

struct Rva003ECB52Arg
{
	void *m_vtbl;
	Rva003ECB52Inner *m_ptr;
};

class Rva005C4AD1LeaField
{
public:
	void *get() const;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

extern GameLogic *TheGameLogic;

// ?rva00596269@Rva005961D6@@QAEXXZ @0x00596269 (98B): clears the +0x54 element
// then scans the +0x04 id list via 0x005C4AD1 resolving each through
// findObjectByID and accumulating matching controlling-player objects via
// 0x003ECB52. Evidence: caller of rowed clear 0x003ECA69 and rowed 0x003ECB52;
// +0x54 matches the second 0x44 element; +0x304 vs +0x2ec selects same player.
void Rva005961D6::rva00596269()
{
	Rva003ECA69Element *elem = reinterpret_cast<Rva003ECA69Element *>((char *)this + 0x54);
	elem->clear();
	void *p = reinterpret_cast<Rva005C4AD1LeaField *>(this)->get();
	const void *tp = (char *)p + 4;
	ObjectID *begin = *reinterpret_cast<ObjectID **>(p);
	ObjectID *end = *reinterpret_cast<ObjectID *const *>(tp);
	for (ObjectID *it = (begin?begin:begin); it != end; ++it) {
		Object *obj = TheGameLogic->findObjectByID(*it);
		int v304 = *reinterpret_cast<int *>((char *)obj + 0x304);
		Player *player = obj->getControllingPlayer();
		if (v304 == *reinterpret_cast<int *>((char *)player + 0x2ec))
			elem->rva003ECB52(reinterpret_cast<Rva003ECB52Arg *>(obj));
	}
}

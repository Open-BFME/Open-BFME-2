// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
//
// ??0LivingWorld@@QAE@XZ retail 0x002C0120..0x002C021A (250 bytes EH).
// WB 0x00D25950 is LivingWorld::LivingWorld (LivingWorld.cpp; its assert
// "LivingWorld created before LivingWorldManager" guards the manager call).
// Retail stores vtable 0x007FE508. The dtor 0x002BFB2D (rowed under the opaque
// class name Rva002BFB2D with deleting dtor 0x002BFD53) restores it and
// unwinds in the same order.
//
// Bases: the rowed list base 0x00330757 (vector plus flags) is declared
// first, then Snapshot. MSVC places the vfptr base at +0 and the list at
// +4, so the list constructor runs before the vtable store. Retail EH map
// 0x0091E4C0 is exactly 0:~list(+4) 1:~Snapshot 2:~Rva002BF807(+0x28)
// 3:hash_map(+0x98) 4:hash_map(+0xAC). Members: +0x14 = 1 / four bools /
// a zeroed float pair (+0x1C) / two bools / the rowed 44-byte Rva002BF807
// (+0x28) / two zeroed float triples (+0x54 +0x60) / three floats / a bool /
// three floats / an int / a zeroed int pair (+0x8C) / a bool / two rowed
// hash_map constructors 0x002C00C1. The body notifies TheLivingWorldManager
// (rowed 0x00213A85) when present and then runs the rowed reset 0x002BFBF7
// on this.
//
// Codegen evidence: the WB debug body gives the pair and triples their own
// EH states (empty inline destructors here). Those place both leas where
// retail has them. Retail never stores EH state 1 (Snapshot) before the
// +0x28 constructor call. It stores state 0 right after the list
// constructor. That is what cl emits when the Rva002BF807 constructor is
// declared nothrow, so the view declares it throw(). The mangled name is
// unchanged. Field meanings beyond the WB layout remain unresolved.
#include "Common/Snapshot.h"

struct Rva002C00C1Element
{
	char bytes[1];
};

namespace _STL
{
template <class T> struct hash;
template <class T> struct equal_to;
template <class T> class allocator;
template <class T1, class T2> struct pair;
template <class K, class V, class H, class E, class A> class hash_map
{
public:
	hash_map();
	~hash_map();
private:
	int m_storage[0x14 / 4];
};
}

typedef _STL::hash_map<int, Rva002C00C1Element, _STL::hash<int>, _STL::equal_to<int>,
	_STL::allocator<_STL::pair<const int, Rva002C00C1Element> > > LivingWorldTable;

class Rva00330757Member
{
public:
	Rva00330757Member();
	~Rva00330757Member();
private:
	int m_storage[0x10 / 4];
};

class Rva002BF807
{
public:
	Rva002BF807() throw();
	~Rva002BF807();
private:
	int m_storage[0x2C / 4];
};

class Rva00213A85
{
public:
	void rva00213A85();
};

class Rva002BFBF7
{
public:
	void rva002BFBF7();
};

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

struct LivingWorldPair
{
	int m_first;
	int m_second;
	LivingWorldPair() : m_first(0), m_second(0) {}
};

struct LivingWorldVec2
{
	float x;
	float y;
	LivingWorldVec2() : x(0.0f), y(0.0f) {}
	~LivingWorldVec2() {}
};

struct LivingWorldVec3
{
	float x;
	float y;
	float z;
	LivingWorldVec3() : x(0.0f), y(0.0f), z(0.0f) {}
	~LivingWorldVec3() {}
};

class LivingWorld : public Rva00330757Member, public Snapshot
{
public:
	LivingWorld();
	virtual ~LivingWorld();
protected:
	virtual void loadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
private:
	int m_14;
	bool m_18;
	bool m_19;
	bool m_1A;
	bool m_1B;
	LivingWorldVec2 m_1C;
	bool m_24;
	bool m_25;
	Rva002BF807 m_28;
	LivingWorldVec3 m_54;
	LivingWorldVec3 m_60;
	float m_6C;
	float m_70;
	float m_74;
	bool m_78;
	float m_7C;
	float m_80;
	float m_84;
	int m_88;
	LivingWorldPair m_8C;
	bool m_94;
	LivingWorldTable m_98;
	LivingWorldTable m_AC;
};

LivingWorld::LivingWorld()
	: m_14(1), m_18(false), m_19(false), m_1A(false), m_1B(false),
	  m_24(false), m_25(false),
	  m_6C(0.0f), m_70(0.0f), m_74(0.0f), m_78(false),
	  m_7C(0.0f), m_80(0.0f), m_84(0.0f), m_88(0), m_94(false)
{
	if (TheLivingWorldManager)
		reinterpret_cast<Rva00213A85 *>(TheLivingWorldManager)->rva00213A85();
	reinterpret_cast<Rva002BFBF7 *>(this)->rva002BFBF7();
}

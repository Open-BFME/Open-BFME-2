// cl: /O1 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ??1Rva002C589B@@QAE@XZ @0x002C589B 24B: non-virtual dtor that deletes the
// +0x24 heap object via the rowed Rva003ECDB7 dtor 0x003ECDB7 plus the rowed
// operator delete 0x0002FD60. Called by the unclaimed deleting dtor 0x0050526D
// plus two vector cleanups 0x0050549A and 0x00505710. Same +0x24 member is
// created by the rowed ctor 0x002C5C1F which formats AIThreatFinder%d.
// WorldBuilder identifies AITarget; the existing address-derived ABI is retained.
// AITarget constructor 2C5C1F..2C5CF7 (RET12), 216 bytes. WorldBuilder's
// AITarget.cpp ctor and AIThreatFinder%d string identify the object; existing
// Rva002C589B ABI names are retained for the rowed callers and teardown.
// All offsets, 0x56C allocation and globals are target instruction facts.
// The position wrapper initializes the canonical 12-byte Coord3D subobject
// before later members, preserving retail's constructor scheduling.
#include "ascii_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "GameLogicObjectLookupView.h"
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
template<class T> __forceinline volatile T &r1_vwrite(T &value) { return *(volatile T *)&value; }
// The +0x24 pointee's reset below reads 12 zero bytes at +0x554 and calls the
// rowed disp32 dword clearer at +0x564 (0x003ECB0B), as the bank established.
class Rva003ECB0BDwordClearer
{
public:
	void clear();
	char m_pad[0x554];
	Coord3D m_vec;
};
struct AITargetPosition : public Coord3D
{
    __forceinline AITargetPosition() { x=0; y=0; z=0; }
};
class Rva003ECD60Object
{
public:
    Rva003ECD60Object(const StringBase<char> &name, bool flag);
    char storage[0x56C]; // opaque target-sized object; real constructor owns fields
};
extern unsigned int g_00DFEFC0;
// Inferred serial-counter role; original static member spelling is unknown.
unsigned int g_AITargetThreatFinderSerial;
class Rva003ECDB7Object
{
public:
	~Rva003ECDB7Object();
    void registerName();
};

extern GameLogic *TheGameLogic;

class Rva002C589B
{
public:
	Rva002C589B(int kind, int limit, void *owner);
	~Rva002C589B();
	void rva002C5843(bool v);
	void rva002C58B3();
	Object *rva002C5DA6();

private:
    void *m_owner;
    int m_kind, m_frame;
    AITargetPosition m_position;
    bool m_18, m_19;
    int m_unknown1C, m_limit;
    Rva003ECDB7Object *m_ptr;
    float m_threat;
    int m_invalid, m_count;
    ObjectID m_34;
    unsigned int m_id;
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

// ?rva002C58B3@Rva002C589B@@QAEXXZ @0x002C58B3 92B: reset. int at +8 to -1,
// floats of the canonical position to 0, bytes at +0x18/+0x19 and int at
// +0x1C to 0, 12 zero bytes at m_ptr+0x554 via a Coord3D temp copy, the rowed
// clear 0x003ECB0B on m_ptr, ObjectID at +0x34 to INVALID_OBJECT_ID. The volatile
// wrapper on the m_19/m_position.x stores is what keeps retail's byte stores
// before the callee-saved push edi (T1 volatile-store-pair lever).
void Rva002C589B::rva002C58B3()
{
	m_frame = -1;
	m_unknown1C = 0;
	r1_vwrite(m_19) = false;
	r1_vwrite(m_18) = false;
	r1_vwrite(m_position.x) = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;
	_ReadWriteBarrier();
	Coord3D tmp = { 0.0f, 0.0f, 0.0f };
	((Rva003ECB0BDwordClearer *)m_ptr)->m_vec = tmp;
	((Rva003ECB0BDwordClearer *)m_ptr)->clear();
	m_34 = INVALID_OBJECT_ID;
}

Object *Rva002C589B::rva002C5DA6()
{
	return m_34 ? TheGameLogic->findObjectByID(m_34) : 0;
}

Rva002C589B::Rva002C589B(int kind, int limit, void *owner)
    : m_owner(owner), m_kind(kind), m_frame(0), m_18(true), m_19(false),
      m_unknown1C(0), m_limit(limit), m_ptr(0), m_threat(0), m_invalid(-1),
      m_count(1), m_34(INVALID_OBJECT_ID), m_id(g_00DFEFC0++)
{
    AsciiString name;
    name.format("AIThreatFinder%d", g_AITargetThreatFinderSerial++);
    m_ptr=(Rva003ECDB7Object *)new Rva003ECD60Object(
        *(const StringBase<char> *)&name, true);
    m_ptr->registerName();
}

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
	Rva002C589B(int kind, int limit, void *owner);
	~Rva002C589B();
	void rva002C5843(bool v);
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

Object *Rva002C589B::rva002C5DA6()
{
	return m_34 ? TheGameLogic->findObjectByID(m_34) : 0;
}

Rva002C589B::Rva002C589B(int kind, int limit, void *owner)
    : m_owner(owner), m_kind(kind), m_frame(0), m_18(true), m_19(false),
      m_unknown1C(0), m_limit(limit), m_ptr(0), m_threat(0), m_invalid(-1),
      m_count(1), m_34(INVALID_ID), m_id(g_00DFEFC0++)
{
    AsciiString name;
    name.format("AIThreatFinder%d", g_AITargetThreatFinderSerial++);
    m_ptr=(Rva003ECDB7Object *)new Rva003ECD60Object(
        *(const StringBase<char> *)&name, true);
    m_ptr->registerName();
}

// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// PhysicsUpdate owned bodies use the BFME UpdateModule and coordinate layouts.
#include <vector>
#include <string.h>
#pragma function(memset)
#include "../../../../../Libraries/Include/Lib/BfmeE16.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

enum UpdateSleepTime
{
    UPDATE_SLEEP_NONE = 1,
    UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum ObjectID { INVALID_ID = 0 };

class Thing;
class ModuleData;
// Retail 0x0053EC42 reads the object ID at +0x74 and writes this +0x58.
class Object
{
public:
    ObjectID getID() const { return m_id; }
private:
    unsigned char m_pad00[0x74];
    ObjectID m_id;
};
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class PhysicsBehavior : public UpdateModule
{
public:
	virtual UpdateSleepTime update(); // UpdateModuleInterface slot 0, the rowed override
	PhysicsBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~PhysicsBehavior();
	void setIgnoreCollisionsWith(const Object *obj);
private:
	_STL::vector<BfmeE16> m_elements;
	Coord3D m_bfme2C;
	Coord3D m_bfme38;
	float m_bfme44;
	float m_bfme48;
	int m_bfme4C;
	int m_bfme50;
	int m_bfme54;
	int m_bfme58;
	bool m_bfme5C;
	unsigned char m_bfme5D;
	bool m_bfme5E;
	bool m_bfme5F;
	int m_bfme60;
	int m_bfme64;
};

// Address-derived codegen view; only the 12-byte stride is witnessed.
struct Rva00390729Element { int opaque[3]; };

// Call the owned allocate/copy operation, not another template copy.
struct BfmeE12;

struct Coord3D;

class Rva000E016A {
public:
    BfmeE12 *rva000E016A(unsigned int, Coord3D *, Coord3D *);
};

// ?reserve@?$vector@URva00390729Element@@V?$allocator@URva00390729Element@@@_STL@@@_STL@@QAEXI@Z @0x00390729 125B. Identity: vector reserve with 12-byte stride; start/finish/end at +0/+4/+8; capacity check via idiv 0xC; empty path via allocator 0x395928; grow path via helper 0xE016A; free via 0x30830.
// Evidence: callers 0xE0B3D/0x3909AE/0x48C487; callees rowed/pinned in packet; neighbours 0x3901C9/0x3907A6; same 125B shape as rowed BfmeE12 reserve 0x3B0224.

// STLport reserve with the native allocate/copy provider at 0xE016A.
template <>
void _STL::vector<Rva00390729Element>::reserve(unsigned int n)
{
    if (capacity() < n) {
        const size_type old_size = size();
        pointer tmp;
        if (this->_M_start) {
            tmp = (pointer)((Rva000E016A *)this)->rva000E016A(n,
                (Coord3D *)this->_M_start, (Coord3D *)this->_M_finish);
            _M_clear();
        } else {
            tmp = this->_M_end_of_storage.allocate(n);
        }
        _M_set(tmp, tmp + old_size, tmp + n);
    }
}

// ?rva003908A7@@YGPAXPAX@Z, retail 0x003908A7, 27 bytes.
// memset the first four bytes, set flag 0x10 on the dword there, return the
// input pointer. Evidence: memset import thunk 0x006291AE (three pushes:
// dest, 0, 4); orl $0x10,(%esi); stdcall ret 4 returning the pointer.
// memset is msvcr71's, called through its import thunk at 0x006291AE
// rather than expanded inline: <string.h>'s memset with
// #pragma function(memset).

void *__stdcall rva003908A7(void *p)
{
	memset(p, 0, 4);
	*reinterpret_cast<int *>(p) |= 0x10;
	return p;
}

// ?setIgnoreCollisionsWith@PhysicsBehavior@@QAEXPBVObject@@@Z @0x0053EC42
void PhysicsBehavior::setIgnoreCollisionsWith(const Object *obj)
{
    m_bfme58 = obj ? obj->getID() : INVALID_ID;
}

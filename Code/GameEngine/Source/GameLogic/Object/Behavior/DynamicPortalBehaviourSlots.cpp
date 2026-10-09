// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// stlport
//
// Two DynamicPortalBehaviour overrides that run its pinned private member
// 0x00461257 (the one its slot-1 loadPostProcess tail-calls). The matched ctor
// 0x00460B6C installs, over UpgradeModule, the BehaviorModuleInterface vtable
// 0x00C42808 at +0x0C and 0x00C427A8 at +0x20; each override is compiled with
// its subobject this. Names are by address.
//
// ?rva00461284@DynamicPortalBehaviour@@UAEXH@Z, retail 0x00461284, 22 bytes:
// +0x0C slot 45 (the argument unread); runs the member unless TheGameLogic's
// +0x6E flag is set.
// ?rva0046132F@DynamicPortalBehaviour@@UAEXXZ, retail 0x0046132F, 12 bytes:
// +0x20 slot 1; clears +0x3D, then runs the member.
#include "../../../../../Libraries/Source/WWVegas/WWLib/Object872.h"

class Object;
class ModuleData;

class GameLogic
{
public:
	unsigned char m_pad00[0x6E];
	bool m_6E; // +0x6E
};

extern GameLogic *TheGameLogic;

template <int N> class Rva00461284Slots : public Rva00461284Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00461284Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface : public Rva00461284Slots<45>
{
public:
	virtual void rva00461284(int a1) = 0;
};

struct Iface10 : public Rva00461284Slots<10> { virtual void rva0046129A() = 0; unsigned char m_pad[4]; };
struct Iface18 { virtual void f18(); };
struct Iface1C { virtual void f1C(); };

class Rva0046132FIface
{
public:
	virtual void gap0() = 0;
	virtual void rva0046132F() = 0;
};

class UpgradeModule : public BehaviorModule, public BehaviorModuleInterface, public Iface10, public Iface18, public Iface1C, public Rva0046132FIface
{
public:
    void rva004CE4A0();
};

class DynamicPortalBehaviour : public UpgradeModule
{
public:
	virtual void rva00461284(int a1);
	virtual void rva0046129A();
	virtual void rva0046132F();
private:
	void rva00461257();
	unsigned char m_pad24[0x3C - 0x24];
	bool m_3C;
	bool m_3D; // +0x3D
};

// ?rva00461284@DynamicPortalBehaviour@@UAEXH@Z @0x00461284
void DynamicPortalBehaviour::rva00461284(int)
{
	if (!TheGameLogic->m_6E)
		rva00461257();
}

// ?rva0046132F@DynamicPortalBehaviour@@UAEXXZ @0x0046132F
void DynamicPortalBehaviour::rva0046132F()
{
	m_3D = false;
	rva00461257();
}

// Target 0x00461257 is the private member tail-called by both rowed virtual
// slots above and by loadPostProcess at 0x00461274. The Ghidra 29B body checks
// member bytes +0x3D and +0x3C plus the module-data byte +0x13C, then tail-jumps
// to the address-derived 0x00460F90 callee. The behavior identity comes from
// its vtable callers; the helper's identity and semantics remain unknown.
class Rva00460F90
{
public:
	void rva00460F90();
};

void DynamicPortalBehaviour::rva00461257()
{
	const unsigned char *moduleData = (const unsigned char *)m_moduleData;
	if (!m_3D && (moduleData[0x13C] != 0 || m_3C))
		reinterpret_cast<Rva00460F90 *>(this)->rva00460F90();
}

// The target Ghidra boundary at 0x00460872 is 43B. It loads the pointer at
// this+8, adds 0x94, then calls the rowed BfmeObject872Header copy ctor at
// RVA 0x002CF108 (VA 0x006CF108) into a 16-byte local. Bit 7 of local+4 selects
// 0x14 or 0x1E. The neutral header view and observed offsets do not establish
// the enclosing object's identity or field meaning.
class Rva00460872
{
public:
	int rva00460872();

private:
	unsigned char m_pad00[8];
	const unsigned char *m_source;
};

// ?rva00460872@Rva00460872@@QAEHXZ
int Rva00460872::rva00460872()
{
	BfmeObject872Header local(*(const BfmeObject872Header *)(m_source + 0x94));
	unsigned char selected = (unsigned char)((*(const unsigned int *)((const char *)&local + 4) >> 7) & 1);
	return selected ? 0x1E : 0x14;
}

#include "ascii_string.h"
class Drawable;
class Thing
{
public:
    Drawable *getDrawable() const;
};
class Object
{
public:
    void *rva0028BCF4() const;
    char pad00[0x74];
    unsigned id;
    char pad78[0x258 - 0x78];
    void *ai;
};
class Rva00272C42
{
public:
    void rva00272C42(const char *text);
};
class Pathfinder
{
public:
    void RemoveObjectFromPathfindMap(Object *);
    void AddObjectToPathfindMap(Object *);
};
class AI
{
public:
    char pad[0x10];
    Pathfinder *pathfinder;
};
extern AI *TheAI;
struct Rva0046129AData
{
    char pad[0x138];
    AsciiString name;
};
class Rva0046129AExit
{
public:
    virtual void f0() = 0;
    virtual void f1() = 0;
    virtual void set(unsigned id) = 0;
};
// +10 mux slot10 of native DynamicPortalBehaviour table. Upgrade apply,
// optional Drawable string forwarding, remove/add in TheAI's pathfinder,
// then primary helper460F90 and optional exit-interface slot8 with Object id.
// The string+138 and Object id74/AI258 are target facts. No reference donor
// establishes the original override spelling or forwarded string semantics.
void DynamicPortalBehaviour::rva0046129A()
{
    rva004CE4A0();
    Object *object = m_object;
    Drawable *drawable = ((const Thing *)object)->getDrawable();
    if (drawable)
    {
        const Rva0046129AData *data = (const Rva0046129AData *)m_moduleData;
        if (data->name.getLength() > 0)
        {
            ((Rva00272C42 *)drawable)->rva00272C42(data->name.str());
            TheAI->pathfinder->RemoveObjectFromPathfindMap(object);
            TheAI->pathfinder->AddObjectToPathfindMap(object);
        }
    }
    ((Rva00460F90 *)this)->rva00460F90();
    if (object->ai)
    {
        Rva0046129AExit *exit = (Rva0046129AExit *)object->rva0028BCF4();
        if (exit)
            exit->set(object->id);
    }
}

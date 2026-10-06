// cl: /DNDEBUG /MD
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

struct Iface10 { virtual void f10(); unsigned char m_pad[4]; };
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
};

class DynamicPortalBehaviour : public UpgradeModule
{
public:
	virtual void rva00461284(int a1);
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

// cl: /O1 /DNDEBUG /MD
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
	unsigned char m_pad24[0x3D - 0x24];
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

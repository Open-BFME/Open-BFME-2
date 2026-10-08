// cl: /DNDEBUG /MD /EHsc
//
// ??1FakePathfindPortalBehaviour@@UAE@XZ, retail 0x004619F2, 84 bytes
// (pinned; rowed deleting wrapper 0x00461C03). Stores
// five vtables (+0x00/+0x0C/+0x10/+0x20/+0x24), calls the helper 0x0046183B
// on this in EH state 0, then the opaque MI base dtor 0x0024A797, the only
// entry in retail's unwind map. The helper is pinned here under an address
// name from this call; its other caller 0x0046190A reaches it from the
// +0x20 interface. The +0x14..+0x1F words sit in the third base so the
// fourth and fifth vptrs land at +0x20/+0x24 (base layout as in
// Rva0024A797Derived.cpp; members after +0x28 follow the rowed ctor).
class Rva0024A797
{
public:
	virtual ~Rva0024A797();
private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class FakePathfindPortalBehaviour_B2
{
public:
	virtual void f2();
private:
	int m_14;
	int m_18;
	int m_1C;
};

class FakePathfindPortalBehaviour_B3
{
public:
	virtual void f3();
};

class FakePathfindPortalBehaviour_B4
{
public:
	virtual void f4();
};

class FakePathfindPortalBehaviour : public Rva0024A797, public MiBase1, public FakePathfindPortalBehaviour_B2,
	public FakePathfindPortalBehaviour_B3, public FakePathfindPortalBehaviour_B4
{
public:
	virtual ~FakePathfindPortalBehaviour();
	void rva0046183B();
	void rva004618D4();
private:
	char m_28[8];
	bool m_30;
	bool m_31;
	bool m_32;
	int m_34;
};

FakePathfindPortalBehaviour::~FakePathfindPortalBehaviour()
{
	rva0046183B();
}

class AI;
extern AI *TheAI;

class Rva002E9042
{
public:
	void rva002E9042(void *arg);
};

class Rva004618D4Caller
{
public:
	void rva002E7023();
};

struct Rva004618D4AI
{
	char m_pad00[0x10];
	Rva002E9042 *m_p10;
};

// ?rva004618D4@FakePathfindPortalBehaviour@@QAEXXZ, retail 0x004618D4 (54B): forwards the two
// waypoints at +0x28/+0x2C to the TheAI+0x10 object, calls its no-argument helper through the
// local thiscall view, then clears the +0x32 flag.
void FakePathfindPortalBehaviour::rva004618D4()
{
	Rva002E9042 *obj = (*reinterpret_cast<Rva004618D4AI **>(&TheAI))->m_p10;
	obj->rva002E9042(*reinterpret_cast<void **>(m_28));
	obj = (*reinterpret_cast<Rva004618D4AI **>(&TheAI))->m_p10;
	obj->rva002E9042(*reinterpret_cast<void **>(m_28 + 4));
	reinterpret_cast<Rva004618D4Caller *>((*reinterpret_cast<Rva004618D4AI **>(&TheAI))->m_p10)->rva002E7023();
	m_32 = false;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f4@FakePathfindPortalBehaviour_B4@@UAEXXZ=??1Coord2D@@QAE@XZ")

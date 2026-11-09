// cl: /MD
//
// Opaque single-inheritance destructors tail-calling CrateCollide::~
// CrateCollide at 0x004BC4FC (matched opaque MI base dtor in
// Rva004BB68EDerived.cpp; only declared here so each tail-call resolves to
// the ledger address instead of a same-TU definition). Each class below
// derives singly from the MI base (inheriting its +0x00/+0x0C/+0x10 vptr
// layout, including the family-shared +0x0C secondary 0xC5A040) and
// overrides all three vptrs before tail-calling the base destructor.
// Owner identities are unproven (opaque Rva names). One ledger row per
// destructor, landed one commit at a time.

class Rva004BC4FC_Root
{
public:
	virtual ~Rva004BC4FC_Root();

private:
	char m_pad04[8];
};

class Rva004BC4FC_Mid
{
public:
	virtual void f1();
};

class Object;
struct Coord3D;

// The collide interface (+0x10): its only slot is onCollide.
class Rva004BC4FC_B2
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal) = 0;
};

class CrateCollide : public Rva004BC4FC_Root, public Rva004BC4FC_Mid, public Rva004BC4FC_B2
{
public:
	virtual ~CrateCollide();
	// Rowed at 0x004BC56D (CrateCollide.cpp); every crate's +0x10 table holds it.
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);
};



class Rva004BCB0D : public CrateCollide
{
public:
	virtual ~Rva004BCB0D();
};

Rva004BCB0D::~Rva004BCB0D()
{
}




// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f1@Rva004BC4FC_Mid@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.

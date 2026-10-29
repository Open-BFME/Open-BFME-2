// Empty multiple-inheritance destructor at retail 0x00466B45.
// Direct bases reproduce the ascending vptr stores and terminal teardown.
// Class names are address-derived; original identities remain unresolved.

class Rva00039D6AFlatBase
{
public:
	virtual ~Rva00039D6AFlatBase();

	unsigned int m_pad[ 2 ];
};

class Rva00220240FlatDtorM0 { public: virtual void anchor(); };
class Rva00220240FlatDtorM1 { public: virtual void anchor() = 0; unsigned int m_pad[ 3 ]; };
class Rva00220240FlatDtorM2 { public: virtual void anchor() = 0; };
class Rva00220240FlatDtorM3 { public: virtual void anchor() = 0; };
class Rva00220240FlatDtorM4 { public: virtual void anchor() = 0; };
class Rva00220240FlatDtorM5 { public: virtual void anchor(); };
class Rva00220240FlatDtorM6 { public: virtual void anchor(); };
class Rva00220240FlatDtorM7 { public: virtual void anchor(); };
class Rva00220240FlatDtor : public Rva00039D6AFlatBase, public Rva00220240FlatDtorM0, public Rva00220240FlatDtorM1, public Rva00220240FlatDtorM2, public Rva00220240FlatDtorM3, public Rva00220240FlatDtorM4, public Rva00220240FlatDtorM5, public Rva00220240FlatDtorM6, public Rva00220240FlatDtorM7
{
public:
	virtual ~Rva00220240FlatDtor();
};

Rva00220240FlatDtor::~Rva00220240FlatDtor()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?anchor@Rva00220240FlatDtorM7@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?anchor@Rva00220240FlatDtorM6@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?anchor@Rva00220240FlatDtorM0@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?anchor@Rva00220240FlatDtorM5@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")

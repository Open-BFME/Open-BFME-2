// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG
// stlport
//
// ??1DockUpdate@@UAE@XZ, retail 0x0058A0F4, 125 bytes.
// Identity: the scalar deleting destructor 0x0058A177 in slot 0 of DockUpdate's
// vtable 0x00C70378 (audited in UpdateModuleDeletingDtors.cpp: ctor 0x0058A290
// stores it, xfer 0x0058A410 matches the dock fields) calls this body, and the
// derived dock updates' destructors tail-call it as Zero Hour's do; that
// wrapper is emitted and rowed here.
// Opaque MI base dtor tail-called by the three rowed 32-byte derived dtors in
// Rva0058A0F4Derived.cpp. Body: compiler vptr restores (+0 +0x0C +0x10
// +0x20), inline frees of three POD vector buffers at +0x6C, +0x60, +0x54
// (0x00030830), then ~Rva0024A797 0x0024A797. Base view as in
// SpecialAbilityUpdateDtor.cpp; element types and owner unrecovered.
#include <vector>

class Rva0049B47C
{
public:
	virtual ~Rva0049B47C() throw();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class PrimaryP58A0F4 : public Rva0049B47C, public MiBase1
{
public:
	~PrimaryP58A0F4() {}
};

class Rva0024A797_B2
{
public:
	virtual void f2();

private:
	char m_pad08[12];
};

class Rva0024A797 : public PrimaryP58A0F4, public Rva0024A797_B2
{
public:
	virtual ~Rva0024A797();
};

class Rva0058A0F4_B20
{
public:
	virtual void f20();
};

class DockUpdate : public Rva0024A797, public Rva0058A0F4_B20
{
public:
	virtual ~DockUpdate();

private:
	unsigned char m_pad24[0x54 - 0x24];
	_STL::vector<int> m_54;
	_STL::vector<int> m_60;
	_STL::vector<int> m_6C;
};

DockUpdate::~DockUpdate()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f20@Rva0058A0F4_B20@@UAEXXZ=?isClearToApproach@DockUpdate@@UBE_NPBVObject@@@Z")

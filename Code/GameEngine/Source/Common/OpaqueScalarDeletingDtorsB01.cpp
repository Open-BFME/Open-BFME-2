// cl: /O1 /MD
//
// Scalar deleting destructors of the 28B flag-test shape, batch B01:
// push esi / mov esi,ecx / call <dtor> / test [esp+8],1 / je / push esi /
// call ??3 (0x2FD60) / pop ecx / mov eax,esi / pop esi / ret 4.
//
// Target facts: each ??_G body and the destructor address it calls are read
// from the retail bytes; the destructor is a Ghidra-inventoried function
// start with no other pin or ledger row, and is pinned opaquely.
// Not established: the owning class, its layout and its destructor body.
// Each class below is therefore declared with nothing but the virtual
// destructor the ??_G needs; __declspec(noinline) keeps that destructor out
// of line so the ??_G calls it through the pin, and its empty body here is a
// placeholder, not a claim (present-unmatched). Names are address-derived
// (Rva<dtor rva>) and disclaim identity.
// Audit 2026-09-26: all 30 wrapper/callee boundaries and both calls verified.
// Retired 2026-10-17: the 0x000D1E6C/0x000D1E88 pair. Its owner is proven to
// be ShareBufferClass<unsigned> -- the pinned dtor's vtable store 0xBCE330 is
// the vtable the rowed ctor 0xD1DE2 and the rowed copy ctor 0x15B000 install --
// so both bodies now live under their real names in
// Code/Libraries/Source/WWVegas/WW3D2/ShareBufferClassUnsignedCtor.cpp.
// Virtual declarations are emission scaffolds, not recovered class layouts.
// Nine wrappers have no pointer occurrence in retail .rdata/.data; virtual
// ownership is unproven for those, as documented in the audit table.
// See docs/reconstruction/deleting-destructor-identity-audit.md.

struct EmitVtableTag;

// ??_GRva000C2980@@UAEPAXI@Z @0x000C3808 28B; calls pinned ??1 at 0x000C2980
class Rva000C2980 { public: Rva000C2980(EmitVtableTag *); virtual ~Rva000C2980(); };
// ?<Rva000C2980::Rva000C2980> absent-from-retail
Rva000C2980::Rva000C2980(EmitVtableTag *) {}

// ??_GRva000D1BA6@@UAEPAXI@Z @0x000D208D 28B; calls pinned ??1 at 0x000D1BA6
class Rva000D1BA6 { public: Rva000D1BA6(EmitVtableTag *); virtual ~Rva000D1BA6(); };
// ?<Rva000D1BA6::Rva000D1BA6> absent-from-retail
Rva000D1BA6::Rva000D1BA6(EmitVtableTag *) {}

// ??_GRva00142FE0@@UAEPAXI@Z @0x000E00A4 28B; calls pinned ??1 at 0x00142FE0
class Rva00142FE0 { public: Rva00142FE0(EmitVtableTag *); virtual ~Rva00142FE0(); };
// ?<Rva00142FE0::Rva00142FE0> absent-from-retail
Rva00142FE0::Rva00142FE0(EmitVtableTag *) {}

// ??_GRva000E5033@@UAEPAXI@Z @0x000E583E 28B; calls pinned ??1 at 0x000E5033
class Rva000E5033 { public: Rva000E5033(EmitVtableTag *); virtual ~Rva000E5033(); };
// ?<Rva000E5033::Rva000E5033> absent-from-retail
Rva000E5033::Rva000E5033(EmitVtableTag *) {}

class Rva000E488F;
class Rva000E57FF
{
public:
	void rva000E57FF(Rva000E488F *arg);
};

class Rva000E585A
{
public:
	void rva000E585A(Rva000E488F *arg);
};

// ??_GVegetationFXShaderParameterSourceNamespace@@UAEPAXI@Z @0x000E63C0 28B; calls pinned ??1 at 0x000E6387
class FXShaderParameterBinder;
class VegetationFXShaderParameterSourceNamespace { public: VegetationFXShaderParameterSourceNamespace(EmitVtableTag *); virtual ~VegetationFXShaderParameterSourceNamespace(); virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry); };
// ?<VegetationFXShaderParameterSourceNamespace::VegetationFXShaderParameterSourceNamespace> absent-from-retail
VegetationFXShaderParameterSourceNamespace::VegetationFXShaderParameterSourceNamespace(EmitVtableTag *) {}

// ??_GRva000E6C6F@@UAEPAXI@Z @0x000E6D78 28B; calls pinned ??1 at 0x000E6C6F
class Rva000E6C6F { public: Rva000E6C6F(EmitVtableTag *); virtual ~Rva000E6C6F(); };
// ?<Rva000E6C6F::Rva000E6C6F> absent-from-retail
Rva000E6C6F::Rva000E6C6F(EmitVtableTag *) {}

// ??_GRva000E9BAC@@UAEPAXI@Z @0x000E9CDF 28B; calls pinned ??1 at 0x000E9BAC
class Rva000E9BAC { public: Rva000E9BAC(EmitVtableTag *); virtual ~Rva000E9BAC(); };
// ?<Rva000E9BAC::Rva000E9BAC> absent-from-retail
Rva000E9BAC::Rva000E9BAC(EmitVtableTag *) {}

// ??_GRva000EFC45@@UAEPAXI@Z @0x000F1698 28B; calls pinned ??1 at 0x000EFC45
class Rva000EFC45 { public: Rva000EFC45(EmitVtableTag *); virtual ~Rva000EFC45(); };
// ?<Rva000EFC45::Rva000EFC45> absent-from-retail
Rva000EFC45::Rva000EFC45(EmitVtableTag *) {}

// ??_GRva000F26DC@@UAEPAXI@Z @0x000F2B81 28B; calls pinned ??1 at 0x000F26DC
class Rva000F26DC { public: Rva000F26DC(EmitVtableTag *); virtual ~Rva000F26DC(); };
// ?<Rva000F26DC::Rva000F26DC> absent-from-retail
Rva000F26DC::Rva000F26DC(EmitVtableTag *) {}

// ??_GRva000F2797@@UAEPAXI@Z @0x000F2B9D 28B; calls pinned ??1 at 0x000F2797
class Rva000F2797 { public: Rva000F2797(EmitVtableTag *); virtual ~Rva000F2797(); };
// ?<Rva000F2797::Rva000F2797> absent-from-retail
Rva000F2797::Rva000F2797(EmitVtableTag *) {}

// ??_GRva00102188@@UAEPAXI@Z @0x001021BE 28B; calls pinned ??1 at 0x00102188
class Rva00102188 { public: Rva00102188(EmitVtableTag *); virtual ~Rva00102188(); };
// ?<Rva00102188::Rva00102188> absent-from-retail
Rva00102188::Rva00102188(EmitVtableTag *) {}

// ??_GRva00104DB0@@UAEPAXI@Z @0x00104F16 28B; calls pinned ??1 at 0x00104DB0
class Rva00104DB0 { public: Rva00104DB0(EmitVtableTag *); virtual ~Rva00104DB0(); };
// ?<Rva00104DB0::Rva00104DB0> absent-from-retail
Rva00104DB0::Rva00104DB0(EmitVtableTag *) {}

// ??_GRva001095B2@@UAEPAXI@Z @0x0010B9C9 28B; calls pinned ??1 at 0x001095B2
class Rva001095B2 { public: Rva001095B2(EmitVtableTag *); virtual ~Rva001095B2(); };
// ?<Rva001095B2::Rva001095B2> absent-from-retail
Rva001095B2::Rva001095B2(EmitVtableTag *) {}

// ??_GRva0010F7EE@@UAEPAXI@Z @0x0010F7D2 28B; calls pinned ??1 at 0x0010F7EE
// Retail BCFAB0 has two slots: 10F7D2 and the rowed handle forwarder 5D124D.
// Match the factory's complete table instead of emitting a truncated copy.
class Rva0010F7EE { public: Rva0010F7EE(EmitVtableTag *); virtual ~Rva0010F7EE(); virtual int rva005D124D(); };
// ?<Rva0010F7EE::Rva0010F7EE> absent-from-retail
Rva0010F7EE::Rva0010F7EE(EmitVtableTag *) {}

// ??_GRva0010F83E@@UAEPAXI@Z @0x0010F822 28B; calls pinned ??1 at 0x0010F83E
class Rva0010F83E { public: Rva0010F83E(EmitVtableTag *); virtual ~Rva0010F83E(); };
// ?<Rva0010F83E::Rva0010F83E> absent-from-retail
Rva0010F83E::Rva0010F83E(EmitVtableTag *) {}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below; bind the donor spelling to that owner so one
// address keeps one definition.
//   0x000C2980 -> ??1Rva000C2980@@QAE@XZ
#pragma comment(linker, "/alternatename:??1Rva000C2980@@UAE@XZ=??1Rva000C2980@@QAE@XZ")
//   0x000D1BA6 -> ??1Rva006DABB0@@UAE@XZ
#pragma comment(linker, "/alternatename:??1Rva000D1BA6@@UAE@XZ=??1Rva006DABB0@@UAE@XZ")
//   0x000E5033 -> ??1Gen_uw_000e5033@@QAE@XZ
#pragma comment(linker, "/alternatename:??1Rva000E5033@@UAE@XZ=??1Gen_uw_000e5033@@QAE@XZ")
//   0x000E6C6F -> ??1Rva000E6AC0@@UAE@XZ
#pragma comment(linker, "/alternatename:??1Rva000E6C6F@@UAE@XZ=??1Rva000E6AC0@@UAE@XZ")
//   0x000EFC45 -> ??1Geometry@@QAE@XZ
#pragma comment(linker, "/alternatename:??1Rva000EFC45@@UAE@XZ=??1Geometry@@QAE@XZ")
//   0x000F26DC -> ??1W3DVolumetricShadow@@UAE@XZ
#pragma comment(linker, "/alternatename:??1Rva000F26DC@@UAE@XZ=??1W3DVolumetricShadow@@UAE@XZ")
//   0x000F2797 -> ??1W3DShadowGeometryManager@@QAE@XZ
#pragma comment(linker, "/alternatename:??1Rva000F2797@@UAE@XZ=??1W3DShadowGeometryManager@@QAE@XZ")
//   0x00142FE0 -> ??1RenderInfoClass@@QAE@XZ
#pragma comment(linker, "/alternatename:??1Rva00142FE0@@UAE@XZ=??1RenderInfoClass@@QAE@XZ")

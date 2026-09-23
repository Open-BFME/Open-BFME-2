// cl: /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?Do_Onetime_Device_Dependent_Inits@DX8Wrapper@@SAXXZ @ 0x001245A0 (283B).
// Dedicated TU: this function spans DX8Caps, DX8MeshRendererClass,
// TextureFilterClass, BoxRenderObjClass, VertexMaterialClass and
// DynamicVBAccessClass, so a self-contained declaration set (DX8CapsRecreate.cpp
// precedent) is used instead of adopting any one subsystem's real header.
//
// BFME1 donor (byte-identical structure, 157B @ 0x0090ADC0):
// reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/
// DX8Wrapper_Do_Onetime_Device_Dependent_Inits.cpp. BFME2 keeps the donor's
// spine (caps recreation, texture filter table, TheDX8MeshRenderer alloc +
// Init + empty member, material/box/vertex inits, default render states)
// and adds two blocks accounting for the extra 126 bytes:
//   1. Right after the caps call (0x001207B0, already matched), retail
//      copies six dwords from the global at VA 0xDECA08 into a stack local
//      and logs them via DebugLogTyped (already matched, Log_DX8_ErrorCode.cpp)
//      with fourcc 'DXHW' (0x44584857) and size 0x18.
//   2. After TheDX8MeshRenderer is constructed, retail additionally allocates
//      a second 0x30-byte object (ctor pinned below) and stores it at VA
//      0xDF6F94 -- the SAME address MeshModelReset.cpp / MeshModelClassDtor.cpp
//      already read through TheMeshGapFillerContext /
//      Rva00DF6F94GapFillerContext (DeleteModelGapFiller pinned @0x1732E2),
//      so this call site is that object's construction and reuses the
//      established class name instead of inventing a new one.
// The two throwing `new` expressions are why retail carries an EH frame
// (push -1 / fs:[0]) that the donor's single `new` already required.
//
// Callees 0x0017E210 and 0x00177923 have no prior identity; named with the
// same Rva<hex>Init address-derived convention the donor itself uses for its
// own unlabeled BFME1 inits (Rva00917280Init / Rva0090F760Init), matching
// their call shape here (plain no-arg calls, same position in the sequence
// as the donor's trailing unlabeled inits). The empty member call at
// 0x0069E440 reuses the donor's Rva00944C40Empty naming pattern rebased onto
// BFME2's actual RVA -- this address already ICF-folds many unrelated empty
// bodies in the ledger, so this is one more candidate name at a body that is
// genuinely just `ret`.

class TextureFilterClass
{
public:
	enum TextureFilterMode
	{
		TEXTURE_FILTER_BILINEAR = 0
	};

	static void _Init_Filters( TextureFilterMode mode );
};

class DX8MeshRendererClass
{
public:
	DX8MeshRendererClass();
	void Init( void );
	void Rva0069E440Empty( void );

private:
	char m_body[ 0x4C ];
};

// Opaque context behind the GapFiller-delete gate; established by
// MeshModelReset.cpp / MeshModelClassDtor.cpp as the class living at
// VA 0xDF6F94. This TU adds its constructor.
class Rva00DF6F94GapFillerContext
{
public:
	Rva00DF6F94GapFillerContext();

private:
	char m_body[ 0x30 ];
};

class VertexMaterialClass
{
public:
	static void Init( void );
};

class BoxRenderObjClass
{
public:
	static void Init( void );
};

class DynamicVBAccessClass
{
public:
	static void bfmeRva0013A7D0( void );
};

class DX8Wrapper
{
public:
	static void Do_Onetime_Device_Dependent_Inits( void );

protected:
	static void Set_Default_Global_Render_States( void );
};

void __cdecl Rva001207B0Init( void *device );
void __cdecl Rva0017E210Init( void );
void __cdecl Rva00177923Init( void );
void __cdecl DebugLogTyped( unsigned tag, void *data, unsigned size );

void *__cdecl operator new( unsigned int size );

// The six dwords retail copies from VA 0xDECA08..0xDECA1F before logging
// them; field identity is not established, only the boundary and size.
struct DX8CapsSnapshot
{
	unsigned Field0;
	unsigned Field1;
	unsigned Field2;
	unsigned Field3;
	unsigned Field4;
	unsigned Field5;
};

extern void *g_dx8Device;
extern DX8CapsSnapshot g_dx8CapsSnapshot;
extern TextureFilterClass::TextureFilterMode g_dx8FilterMode;
extern DX8MeshRendererClass *TheDX8MeshRenderer;
extern Rva00DF6F94GapFillerContext *TheMeshGapFillerContext;

// ?Do_Onetime_Device_Dependent_Inits@DX8Wrapper@@SAXXZ
void DX8Wrapper::Do_Onetime_Device_Dependent_Inits( void )
{
	Rva001207B0Init( g_dx8Device );

	DX8CapsSnapshot snapshot = g_dx8CapsSnapshot;
	DebugLogTyped( 'DXHW', &snapshot, sizeof( snapshot ) );

	TextureFilterClass::_Init_Filters( g_dx8FilterMode );

	TheDX8MeshRenderer = new DX8MeshRendererClass;
	TheDX8MeshRenderer->Init();
	TheDX8MeshRenderer->Rva0069E440Empty();

	TheMeshGapFillerContext = new Rva00DF6F94GapFillerContext;

	BoxRenderObjClass::Init();
	VertexMaterialClass::Init();
	Rva0017E210Init();
	Rva00177923Init();
	DynamicVBAccessClass::bfmeRva0013A7D0();
	Set_Default_Global_Render_States();
}

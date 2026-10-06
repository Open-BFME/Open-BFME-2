// cl: /DNDEBUG /MD /EHsc
// Retail 0x00904230: DX8CALL(BeginScene()) wrapped by a matching enter/leave helper.

struct IDirect3DDevice8;

struct IDirect3DDevice8Vtbl
{
	void *reserved[41];
	long (__stdcall *BeginScene)(IDirect3DDevice8 *self);
};

struct IDirect3DDevice8
{
	IDirect3DDevice8Vtbl *lpVtbl;
};

// Retail 0x009588E0 is the error-reporting inline COM wrapper reached from
// Begin_Scene_Inner's enter and leave edges.  The browser dispatch object is
// shared with the WOL wrapper family; this view only supplies the slot that
// this body actually calls.
struct _GUID { unsigned char bytes[16]; };
typedef _GUID GUID;
struct IUnknown;

extern void __stdcall _com_issue_errorex(long error, IUnknown *object,
	const GUID &iid);

struct BfmeGuidTSA
{
	char m_bfmeBytes[16];
};

extern BfmeGuidTSA g_bfmeIidTSA;

class Rva00958D30
{
public:
	struct Vtable
	{
		void *slot00;
		void *slot04;
		void *slot08;
		void *slot0c;
		void *slot10;
		void *slot14;
		void *slot18;
		void *slot1c;
		void *slot20;
		void *slot24;
		void *slot28;
		void *slot2c;
		void *slot30;
		void *slot34;
		void *slot38;
		long (__stdcall *slot3c)(Rva00958D30 *self);
	};

	long invoke()
	{
		long result = vtable->slot3c(this);
		if (result < 0)
			_com_issue_errorex(result, (IUnknown *)this,
				reinterpret_cast<const GUID &>(g_bfmeIidTSA));
		return result;
	}

	Vtable *vtable;
};

struct Rva00959410Ptr
{
	Rva00958D30 *m_p;
	Rva00958D30 *operator->() const
	{
		return m_p;
	}
	operator bool() const
	{
		return m_p != 0;
	}
};

extern Rva00959410Ptr Rva00959410Dispatch;

// ?bfmeDebugTouch009588e0@@YAXXZ
__declspec(noinline) void bfmeDebugTouch009588e0(void)
{
	if (Rva00959410Dispatch)
		Rva00959410Dispatch->invoke();
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static void Begin_Scene_Inner(void);

private:
protected:
	static IDirect3DDevice8 *D3DDevice;
private:
	static unsigned D3DCallCount;
};

// ?Begin_Scene_Inner@DX8Wrapper@@SAXXZ
void DX8Wrapper::Begin_Scene_Inner(void)
{
	bfmeDebugTouch009588e0();
	D3DDevice->lpVtbl->BeginScene(D3DDevice);
	++D3DCallCount;
	bfmeDebugTouch009588e0();
}
// ?Rva00959410Dispatch@@3URva00959410Ptr@@A: the global at VA 0xdf7040 is ?g_bfmeObjECF@@3PAUBfmeObjECF@@A.
#pragma comment(linker, "/alternatename:?Rva00959410Dispatch@@3URva00959410Ptr@@A=?g_bfmeObjECF@@3PAUBfmeObjECF@@A")

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?D3DCallCount@DX8Wrapper@@0IA=?number_of_DX8_calls@@3IA")

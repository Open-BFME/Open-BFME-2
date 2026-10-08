// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// ??0Rva00224CDC@@QAE@XZ @0x00224CDC 83B
// Subsystem ctor: EH baseConstruct via novtable Shell-pattern base, then own
// vtable 0x007E6EE8, then the hash_map-shaped member at +0xC constructed via
// the rowed ICF twin ?dup_00224c76@@YAXXZ (gen-alias for the ArmorTemplateMap
// ctor whose canonical body is 0x00360B99), then setName AptButtonTooltipMap.
// ArmorMapShim keeps a nontrivial destructor so the ctor emits the EH cleanup
// state retail keeps for the member; its body calls the twin through a
// __fastcall pointer so the reloc names the address retail actually calls.
// Evidence: caller new 0x20 at 0x00224D80; rowed baseConstruct 0x001B4E63,
// StringBase ctor 0x00037BA0, setName 0x0006F3CC.
#include "ascii_string.h"
#include <cstddef>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

class __declspec(novtable) BFME2NativeNetworkBase
{
public:
	__forceinline BFME2NativeNetworkBase() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual ~BFME2NativeNetworkBase() { _ReadWriteBarrier(); }
private:
	char m_flag;
	int m_value;
};

class SubsystemInterface
{
public:
	void setName(AsciiString name);
};

void __cdecl dup_00224c76(void);
typedef void (__fastcall *ArmorMapCtorFn)(void *);

struct ArmorMapShim
{
	char m_buf[0x1C];
	ArmorMapShim() { ((ArmorMapCtorFn)&dup_00224c76)(this); }
	~ArmorMapShim() { _ReadWriteBarrier(); }
};

class Rva00224CDC : public BFME2NativeNetworkBase
{
public:
	Rva00224CDC();
	virtual ~Rva00224CDC();
private:
	ArmorMapShim m_0C;
};

Rva00224CDC::Rva00224CDC()
{
	((SubsystemInterface *)this)->setName("AptButtonTooltipMap");
}

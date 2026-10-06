// cl: /GX /DNDEBUG /MD
extern "C" const void *const vtbl_00BC5128[];  // ??_7Rva001DA2D5Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BC5128=??_7Rva001DA2D5Base@@6B@")

#include "../../Include/Common/Rva00041004Lock.h"
//
// ??1Rva0010F0C4@@UAE@XZ, retail 0x0010F0C4, 76 bytes.
// Virtual dtor closing the volatile +0x08 stream via mss32 AIL_close_stream
// (throw() so the manual close takes no EH state) when non-null, destroying
// the +0x14 Rva0040EDB member through its rowed/pinned dtor, then restoring
// base vtable 0x00BC5128. Derived vtable 0x00BCFAAC is compiler-emitted
// (DIR32). Volatile reproduces retail's memory-direct cmp/push/mov with no
// register caching. Member dtor is throwing (single EH state 0, EH prolog). Shape follows
// CastleMemberBehaviorModuleDataDtor (derived store plus member plus base).
// Evidence: derived 0x00BCFAAC then base 0x00BC5128; IAT mss32
// AIL_close_stream; member call ??1Rva0040EDB at 0x00040EDB; caller
// ??_GRva0010F0C4@@UAEPAXI@Z at 0x0010F6EE.

typedef void *HSTREAM;
extern "C" __declspec(dllimport) void __stdcall AIL_close_stream(HSTREAM stream) throw();

class Rva0010F0C4Base
{
public:
	virtual ~Rva0010F0C4Base()
	{
		*(const void **)this = reinterpret_cast<const void *>(((unsigned int)vtbl_00BC5128));
	}
};

class Rva0010F0C4 : public Rva0010F0C4Base
{
public:
	virtual ~Rva0010F0C4();

private:
	int m_unused04; // +0x04
	volatile HSTREAM m_stream08; // +0x08 closed via AIL_close_stream
	char m_pad0C[8]; // +0x0C..+0x13
	Rva0040EDB m_member14; // +0x14
};

Rva0010F0C4::~Rva0010F0C4()
{
	if (m_stream08 != 0) {
		AIL_close_stream(m_stream08);
		m_stream08 = 0;
	}
}

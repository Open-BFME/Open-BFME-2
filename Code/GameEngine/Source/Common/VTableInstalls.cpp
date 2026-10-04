// Bare vtable installs: nine-byte __thiscall members with one shape:
//
//     mov eax,ecx / mov dword [eax],<VTABLE> / ret
//
// The vtable pointer at offset zero of `this` is overwritten with a literal
// vtable address and nothing else is touched. The classes are otherwise
// unidentified: each body gets a TU-local class with an explicit vtable
// member (no virtuals, so the compiler emits the immediate store instead
// of a vtable reference) and an address-derived name.
// No // cl: line (defaults match the frameless nine-byte shape).
extern "C" const void *const vtbl_00C18DFC[];  // ??_7Rva0037F57E@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C18DFC=??_7Rva0037F57E@@6B@")

extern "C" const void *const vtbl_00BBC8D4[];  // ??_7_Messages@_STL@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BBC8D4=??_7_Messages@_STL@@6B@")
extern "C" const void *const vtbl_00C7A660[];  // ??_7Rva0060061A@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C7A660=??_7Rva0060061A@@6B@")

#define BFME_VTABLE_INSTALL(NAME, VTABLE) \
	class NAME \
	{ \
	public: \
		NAME *init(); \
		void *m_vtable; \
	}; \
	NAME *NAME::init() \
	{ \
		m_vtable = VTABLE; \
		return this; \
	}

BFME_VTABLE_INSTALL(Rva00019EB0VTableInstall, reinterpret_cast<void *>(((unsigned int)vtbl_00BBC8D4)))
BFME_VTABLE_INSTALL(Rva000910D8VTableInstall, reinterpret_cast<void *>(0x00BC7F74))
BFME_VTABLE_INSTALL(Rva0037F4C0VTableInstall, reinterpret_cast<void *>(((unsigned int)vtbl_00C18DFC)))
BFME_VTABLE_INSTALL(Rva005114BDVTableInstall, reinterpret_cast<void *>(0x00C6573C))
BFME_VTABLE_INSTALL(Rva00600611VTableInstall, reinterpret_cast<void *>(((unsigned int)vtbl_00C7A660)))
BFME_VTABLE_INSTALL(Rva00602635VTableInstall, reinterpret_cast<void *>(0x00C7A84C))

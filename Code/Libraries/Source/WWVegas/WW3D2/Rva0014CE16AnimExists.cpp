// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ?Rva0014CE16_AnimExists@@YA_NPBD@Z @ 0x0014CE16 (81 bytes).
// Animation-asset existence check: builds the "a*"+name key lowercased in
// a 512-byte buffer and returns the registry contains-check. No SEH (no
// object lifetimes); the checker address is pinned.

extern "C" char *_mbscpy(char *destination, const char *source);
extern "C" __declspec(dllimport) char *__cdecl _strlwr(char *string);

// Registry contains-check (retail 0x0061F0D0, 28B): null name or null
// registry answers false, else tail-calls the registry lookup 0xA21170.
extern bool __cdecl Render_Obj_Exists(const char *name);

// ?Rva0014CE16_AnimExists@@YA_NPBD@Z
bool Rva0014CE16_AnimExists(const char *name)
{
	if (name == 0)
		return false;

	char lookup[512];
	_mbscpy(lookup, "a*");
	_mbscpy(lookup + 2, name);
	_strlwr(lookup);
	return Render_Obj_Exists(lookup);
}

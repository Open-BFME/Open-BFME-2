// cl: /O1 /Oi- /MD
// Shared case-sensitive C-string ordering used by the strcmp-keyed
// red-black tree family in the 0x00600854-0x00604518 band (at least seven
// insert_unique instantiations call it). Retail reaches strcmp through
// the import thunk, so the declaration is plain (no dllimport) and
// intrinsics are off (/Oi-); /O1 gives the pop-pop cleanup and ecx
// result register.

// 0x0006038D4 (27B): true if strcmp(a, b) < 0.
extern "C" int __cdecl strcmp(const char *a, const char *b);

bool __stdcall Rva0006038D4CStrLess(const char *a, const char *b)
{
	return strcmp(a, b) < 0;
}

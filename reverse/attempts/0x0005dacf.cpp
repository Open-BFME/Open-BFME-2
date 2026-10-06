// ?rva0005DACF@MilesAudioManager@@QAEXABH@Z
// partial score=0.85 date=2026-10-06
// cl: /O1 /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX-
// MilesAudioManager vtable 0x00BC55B0#23/#24. Retail loads the argument's first
// dword into eax BEFORE pushing the constants (mov eax,[esp+4]; mov eax,[eax];
// push 1,0,1,0; push eax); this body pushes [eax] directly after the constants.
// /O2 hoists the load but into edx. 0x0005D734's first param is a pointer (a
// 260-byte local buffer at caller 0x0005A606), so the arg is likely an object
// whose first dword is a char pointer; an STLport string c_str() also gave push [eax].
typedef int Int;
class MilesAudioManager
{
public:
	void rva0005D734(Int a, Int b, Int c, Int d, Int e);
	void rva0005DACF(const Int &a);
};
void MilesAudioManager::rva0005DACF(const Int &a)
{
	rva0005D734(a, 0, 1, 0, 1);
}

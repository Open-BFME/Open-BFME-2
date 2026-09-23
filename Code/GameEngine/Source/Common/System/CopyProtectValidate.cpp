// cl: /O1
// CopyProtect::validate, retail 0x00232D0C, 44 bytes. Checks the launcher
// view starts with 'M' and matches the G4 registry string past the first
// byte. BFME1's Code/GameEngine/Source/Common/System/CopyProtection.cpp
// gives the source; two release-build repairs: the DEBUG_LOG calls are
// compiled away as in the matched siblings, and the expected text comes
// from the rowed ?GetRegistryG4@@YAPBDXZ getter at 0x0002FAE0 rather than
// a hardcoded Generals string. Kept in its own TU so callers cannot see
// (and inline) this body.

extern "C" int __cdecl strcmp(const char *a, const char *b);

const char *GetRegistryG4(void);

class CopyProtect
{
public:
	static bool validate(void);

private:
	static void *s_protectedData;
};

bool CopyProtect::validate(void)
{
	void *data = s_protectedData;
	if (data != 0 && *(char *)data == 'M')
	{
		return strcmp((char *)data + 1, GetRegistryG4() + 1) ? false : true;
	}
	return false;
}

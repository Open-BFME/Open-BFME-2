// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?Rva000FDCD7Get@@YAHXZ @0x000FDCD7 26B; chain of W3DShaderManager::canRenderToTexture.
// Retail: call 0x000F630C / test al,al / jne / xor eax,eax / ret / xor eax,eax / mov [0x00DE1F50],0x00DB5BD4 / inc eax / ret.
// Target facts: calls the rowed ?canRenderToTexture@W3DShaderManager@@SA_NXZ (0x000F630C); tests the bool in al so the false path needs xor; sets data 0x009E1F50 to data 0x009B5BD4 then returns 1 else 0.
// Callers: none; callees: 0x000F630C only.
// Not established: owning TU/class and global identities; names are address-derived.
// 0x009E1F50 is slot 9 of W3DFilters[10] (0x009E1F2C, defined in W3DShaderManager.cpp);
// 0x00DB5BD4 is the statically initialised filter object whose vftable 0x007CF440
// has this function as slot 0 (the filter's init registering itself).
class W3DFilterInterface;
extern W3DFilterInterface *W3DFilters[10];
class Rva000FDCD7Filter;
extern Rva000FDCD7Filter g_00DB5BD4; // the filter object at 0x00DB5BD4 (unowned)
class W3DShaderManager
{
public:
	static bool canRenderToTexture(void);
};

int Rva000FDCD7Get(void)
{
	if (!W3DShaderManager::canRenderToTexture())
		return 0;
	W3DFilters[9] = (W3DFilterInterface *)&g_00DB5BD4;
	return 1;
}

// cl: /MD
// ?rva000FD4B3@Rva000FD4B3@@QAEHXZ @0x000FD4B3 27B; chain of W3DShaderManager::canRenderToTexture.
// Retail: push esi / mov esi,ecx / call 0x000F630C / test al,al / jne / xor eax,eax / pop esi / ret / xor eax,eax / mov [0x00DE1F34],esi / inc eax / pop esi / ret.
// Target facts: calls ?canRenderToTexture@W3DShaderManager@@SA_NXZ (0x000F630C); tests the bool in al so the false path needs xor; stores this into data 0x009E1F34 then returns 1 else 0.
// Callers: none; callees: 0x000F630C only. Owner unknown so class is address-derived.
// Not established: owning class identity beyond this-pointer store; global identity.
// 0x009E1F34 is slot 2 of W3DFilters[10] (0x009E1F2C, defined in W3DShaderManager.cpp);
// this is a filter init registering itself (FT_VIEW_MOTION_BLUR_FILTER in Zero Hour).
class W3DFilterInterface;
extern W3DFilterInterface *W3DFilters[10];
class W3DShaderManager
{
public:
	static bool canRenderToTexture(void);
};
class Rva000FD4B3
{
public:
	int rva000FD4B3();
};

int Rva000FD4B3::rva000FD4B3()
{
	if (!W3DShaderManager::canRenderToTexture())
		return 0;
	W3DFilters[2] = (W3DFilterInterface *)this;
	return 1;
}

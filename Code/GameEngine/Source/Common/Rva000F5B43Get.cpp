// cl: /MD
// ?Rva000F5B43Get@@YAHXZ @0x000F5B43 19B; two-global init.
// Retail: xor eax,eax / inc eax / mov [0x00DE1F28],(unsigned int)&g_00DB5A34 / mov [0x00DE1F20],eax / ret.
// Target facts: sets data 0x009E1F28 to data 0x009B5A34 and data 0x009E1F20 to 1 then returns 1.
// Callers: none; callees: none.
// The two stored slots are W3DShaders[1] (VA 0x00DE1F28) and
// W3DShadersPassCount[1] (VA 0x00DE1F20), the tables W3DShaderManager.cpp
// defines (its ctor 0x00075480 zeroes both); the stored value is the shroud
// texture shader instance (ShroudTextureShaderSet.cpp: this is that shader's
// init slot), defined below with the other shader and filter objects.
// Not established: owning class name; the function name is address-derived.
class ShaderInterface;
extern ShaderInterface *W3DShaders[2];
extern int W3DShadersPassCount[2];

extern const void *const *shroudTextureShader[3];

int Rva000F5B43Get(void)
{
	*(unsigned int *)&W3DShaders[1] = (unsigned int)&shroudTextureShader;
	W3DShadersPassCount[1] = 1;
	return 1;
}

// Retail's static shader and filter objects, from retail's words: each holds its table in .data, with
// nothing else initialized. Each slot is the ledger row at the native address. The lists are what
// W3DShaderManager::init walks; Rva00066A9ABody.cpp holds the two master lists.
extern "C" int __cdecl _purecall(void);
extern "C" {
void __identifier("?Create@GameFileClass@@UAEHXZ")();
void __identifier("?Rva000F5B43Get@@YAHXZ")();
void __identifier("?Rva000FDCD7Get@@YAHXZ")();
void __identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z")();
void __identifier("?bfmeDropDF@BfmeThingDF@@QAEHXZ")();
void __identifier("?init@ScreenBWFilter@@UAEHXZ")();
void __identifier("?init@ScreenBWFilterDOT3@@UAEHXZ")();
void __identifier("?postRender@Rva000FC34FFilter@@UAE_NW4FilterModes@@AAVCoord2D@@AA_NPAV3@@Z")();
void __identifier("?preRender@Rva000FDD1C@@UAE_NAA_NAAW4CustomScenePassModes@@@Z")();
void __identifier("?reset@Rva000FBA4ASecondary@@UAEXXZ")();
void __identifier("?reset@Rva000FC63DFilter@@MAEXXZ")();
void __identifier("?reset@ShroudTextureShader@@EAEXXZ")();
void __identifier("?rva000F6329@Rva000F6329@@QAE_NPA_NH@Z")();
void __identifier("?rva000F6335@Rva000F6335@@QAE_NHHHH@Z")();
void __identifier("?rva000FBA0F@Rva000FBA0F@@QAE_NPA_NH@Z")();
void __identifier("?rva000FBA57@Rva000FBA4A@@UAE_NHHHPAVCoord2D@@@Z")();
void __identifier("?rva000FDD1C@Rva000FDD1C@@QAE_NHHHH@Z")();
void __identifier("?rva000FDD1CFirst@Rva000FDD1C@@UAEHH@Z")();
void __identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")();
void __identifier("?set@Rva000FC34FFilter@@MAEHW4FilterModes@@@Z")();
void __identifier("?set@ScreenBWFilter@@MAEHW4FilterModes@@@Z")();
void __identifier("?set@ShroudTextureShader@@EAEHH@Z")();
}

// VA 0x00BCF1D8
extern "C" const void *const g_shroudTextureShaderTable[11] = {
	(const void *)&__identifier("?set@ShroudTextureShader@@EAEHH@Z"), // slot 0, RVA 0x000F5D3B
	(const void *)&__identifier("?reset@ShroudTextureShader@@EAEXXZ"), // slot 1, RVA 0x000F5B5F
	(const void *)&__identifier("?Rva000F5B43Get@@YAHXZ"), // slot 2, RVA 0x000F5B43
	(const void *)&__identifier("?Create@GameFileClass@@UAEHXZ"), // slot 3, RVA 0x000910FB
	(const void *)&_purecall, // slot 4, RVA 0x0003B810
	(const void *)&__identifier("?Create@GameFileClass@@UAEHXZ"), // slot 5, RVA 0x000910FB
	(const void *)&__identifier("?rva000F6329@Rva000F6329@@QAE_NPA_NH@Z"), // slot 6, RVA 0x000F6329
	(const void *)&__identifier("?rva000F6335@Rva000F6335@@QAE_NHHHH@Z"), // slot 7, RVA 0x000F6335
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // slot 8, RVA 0x005CB9FF
	(const void *)&_purecall, // slot 9, RVA 0x0003B810
	(const void *)&_purecall, // slot 10, RVA 0x0003B810
};

// VA 0x00BCF364
extern "C" const void *const g_screenBWFilterTable[7] = {
	(const void *)&__identifier("?init@ScreenBWFilter@@UAEHXZ"), // slot 0, RVA 0x000FB9D4
	(const void *)&__identifier("?bfmeDropDF@BfmeThingDF@@QAEHXZ"), // slot 1, RVA 0x000FC903
	(const void *)&__identifier("?rva000FBA0F@Rva000FBA0F@@QAE_NPA_NH@Z"), // slot 2, RVA 0x000FBA0F
	(const void *)&__identifier("?rva000FBA57@Rva000FBA4A@@UAE_NHHHPAVCoord2D@@@Z"), // slot 3, RVA 0x000FBA57
	(const void *)&__identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z"), // slot 4, RVA 0x005CB9FA
	(const void *)&__identifier("?set@ScreenBWFilter@@MAEHW4FilterModes@@@Z"), // slot 5, RVA 0x000FBC67
	(const void *)&__identifier("?reset@Rva000FC63DFilter@@MAEXXZ"), // slot 6, RVA 0x000FC8B4
};

// VA 0x00BCF380
extern "C" const void *const g_screenBWFilterDOT3Table[7] = {
	(const void *)&__identifier("?init@ScreenBWFilterDOT3@@UAEHXZ"), // slot 0, RVA 0x000FBA20
	(const void *)&__identifier("?Create@GameFileClass@@UAEHXZ"), // slot 1, RVA 0x000910FB
	(const void *)&__identifier("?rva000FBA0F@Rva000FBA0F@@QAE_NPA_NH@Z"), // slot 2, RVA 0x000FBA0F
	(const void *)&__identifier("?postRender@Rva000FC34FFilter@@UAE_NW4FilterModes@@AAVCoord2D@@AA_NPAV3@@Z"), // slot 3, RVA 0x000FC04C
	(const void *)&__identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z"), // slot 4, RVA 0x005CB9FA
	(const void *)&__identifier("?set@Rva000FC34FFilter@@MAEHW4FilterModes@@@Z"), // slot 5, RVA 0x000FC34F
	(const void *)&__identifier("?reset@Rva000FBA4ASecondary@@UAEXXZ"), // slot 6, RVA 0x000FD551
};

// VA 0x00BCF440
extern "C" const void *const g_filterObject5BD4Table[7] = {
	(const void *)&__identifier("?Rva000FDCD7Get@@YAHXZ"), // slot 0, RVA 0x000FDCD7
	(const void *)&__identifier("?Create@GameFileClass@@UAEHXZ"), // slot 1, RVA 0x000910FB
	(const void *)&__identifier("?preRender@Rva000FDD1C@@UAE_NAA_NAAW4CustomScenePassModes@@@Z"), // slot 2, RVA 0x000FDCF1
	(const void *)&__identifier("?rva000FDD1C@Rva000FDD1C@@QAE_NHHHH@Z"), // slot 3, RVA 0x000FDD1C
	(const void *)&__identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z"), // slot 4, RVA 0x005CB9FA
	(const void *)&__identifier("?rva000FDD1CFirst@Rva000FDD1C@@UAEHH@Z"), // slot 5, RVA 0x000FDDB8
	(const void *)&__identifier("?reset@Rva000FBA4ASecondary@@UAEXXZ"), // slot 6, RVA 0x000FD551
};

// VA 0x00DB5A34: the shroud texture shader.
const void *const *shroudTextureShader[3] = { g_shroudTextureShaderTable, 0, 0 };

// VA 0x00DB5B54, 0x00DB5B5C and 0x00DB5BD4.
extern "C" const void *const *__identifier("?screenBWFilter@@3VScreenBWFilter@@A")[2] = { g_screenBWFilterTable, 0 };
extern "C" const void *const *__identifier("?screenBWFilterDOT3@@3VScreenBWFilterDOT3@@A")[2] = { g_screenBWFilterDOT3Table, 0 };
extern "C" const void *const *__identifier("?g_00DB5BD4@@3VRva000FDCD7Filter@@A")[1] = { g_filterObject5BD4Table };

// VA 0x00DB5A64, defined with its class in ScreenCrossFadeFilterUpdateFadeLevel.cpp.
extern "C" char __identifier("?screenCrossFadeFilter@@3VScreenCrossFadeFilter@@A");

// VA 0x00DB439C, 0x00DB4348, 0x00DB4364 and 0x00DB4394.
void *g_shaderList0[2] = { (void *)&shroudTextureShader, 0 };
void *g_filterList0[2] = { (void *)&__identifier("?g_00DB5BD4@@3VRva000FDCD7Filter@@A"), 0 };
void *g_filterList1[3] = { (void *)&__identifier("?screenBWFilter@@3VScreenBWFilter@@A"),
	(void *)&__identifier("?screenBWFilterDOT3@@3VScreenBWFilterDOT3@@A"), 0 };
void *g_filterList3[2] = { (void *)&__identifier("?screenCrossFadeFilter@@3VScreenCrossFadeFilter@@A"), 0 };

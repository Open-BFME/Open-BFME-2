// cl: /MD /EHsc
//
// ?rva0007BA35@Rva0007BA35@@QAEXXZ @ 0x0007BA35 (161B):
// __thiscall method on the +0x20/+0x24 holder object reached by tail jmp
// from 0x0009A2CD via g_00DE1FF8. Copies 12B g_00DB4470 -> g_00DB447C,
// clamps first dword to >=0x800 when GameLODManager+0x177c >= 4, then
// guarded rva152d1c(4) on each non-null holder under DX8DeviceGuard
// (Lock in ctor Assert in dtor). Owner unproven so honest address name.
// Callees by row/pin names.

class GameLODManager
{
public:
	char m_pad[0x177c];
	int m_177c;
};
extern GameLODManager *TheGameLODManager;

struct Db12
{
	int v0;
	int v1;
	int v2;
};
extern Db12 g_00DB4470;
extern Db12 g_00DB447C;

struct FieldParse;
extern const FieldParse g_shadowMapFieldParseTable[];

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;

class Rva00152D1CObj
{
public:
	void rva152d1c(int);
};

void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();

class DX8DeviceGuard
{
public:
	DX8DeviceGuard()
	{
		BFME_DX8_Thread_Lock();
	}
	~DX8DeviceGuard()
	{
		BFME_DX8_Thread_Assert();
	}
};

class Rva0007BA35
{
public:
	void rva0007BA35();
private:
	int m_pad00[8];
	Rva00152D1CObj *m_20;
	Rva00152D1CObj *m_24;
};

void Rva0007BA35::rva0007BA35()
{
	g_00DB447C = g_00DB4470;
	GameLODManager *mgr = TheGameLODManager;
	int lod = mgr->m_177c;
	if (lod >= 4)
	{
		int tmp = 0x800;
		int *p = &g_00DB447C.v0;
		if (g_00DB447C.v0 < 0x800)
			p = &tmp;
		g_00DB447C.v0 = *p;
	}
	if (m_20 != 0)
	{
		DX8DeviceGuard guard;
		m_20->rva152d1c(4);
	}
	if (m_24 != 0)
	{
		DX8DeviceGuard guard;
		m_24->rva152d1c(4);
	}
}

// The BlockParse node at VA 0x00DB4488 registers token "ShadowMap" with
// this callback (target registration row at 0x007ABFE3). The target table at
// VA 0x00BC6BA8 names its fields MapSize, MaxViewDistance, and
// MinShadowedTerrainHeight. The other tested fields remain unnamed here.
void parseShadowMapBlock(INI *ini)
{
	g_00DB447C = g_00DB4470;
	if (*reinterpret_cast<int *>(reinterpret_cast<char *>(ini) + 8) == 2 &&
		TheGameLODManager->m_177c >= 4)
	{
		int minimumMapSize = 0x800;
		int *mapSize;
		if (g_00DB447C.v0 < minimumMapSize)
			mapSize = &minimumMapSize;
		else
			mapSize = &g_00DB447C.v0;
		g_00DB447C.v0 = *mapSize;
	}
	ini->initFromINI(&g_00DB447C, g_shadowMapFieldParseTable);
	int mode = *reinterpret_cast<int *>(reinterpret_cast<char *>(ini) + 8);
	if (mode != 2 && mode != 4)
	{
		if (*reinterpret_cast<unsigned char *>(
			reinterpret_cast<char *>(TheWritableGlobalData) + 0xD45))
			g_00DB447C.v0 = 0x1000;
		g_00DB4470 = g_00DB447C;
	}
}

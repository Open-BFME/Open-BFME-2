// cl: /MD /EHsc
//
// ?rva0007BA35@Rva0007BA35@@QAEXXZ @ 0x0007BA35 (161B):
// __thiscall method on the +0x20/+0x24 holder object reached by tail jmp
// from 0x0009A2CD via g_00DE1FF8. Copies 12B g_00DB4470 -> g_00DB447C,
// clamps first dword to >=0x800 when GameLODManager+0x177c >= 4, then
// guarded rva152d1c(4) on each non-null holder under DX8DeviceGuard
// (Lock in ctor Assert in dtor). Owner unproven so honest address name.
// Callees by row/pin names.

#include "../../Include/Common/GameLODManager.h"
extern GameLODManager *TheGameLODManager;

struct Db12
{
	int v0;
	int v1;
	int v2;
};
// Native configuration snapshots at VA DB4470 and DB447C, each 12 bytes.
// Keep the established dword storage view: +0 is MapSize (int), +4 is
// MaxViewDistance (float bits 1000.0f), and +8 is MinShadowedTerrainHeight
// (float bits 0.0f), as independently witnessed by the field parse table.
Db12 g_defaultShadowMapSettings = { 1024, 0x447A0000, 0 };
Db12 g_shadowMapSettings = { 1024, 0x447A0000, 0 };

class INI;
typedef void (*INIFieldParseProc)(INI *, void *, void *, const void *);
#include "../../Include/Common/INI/FieldParse.h"

#include "../../Include/Common/INI/INI.h"

// Complete native .rdata table VA BC6BA8..BC6BE8; the next word is an
// independent float constant. Tokens, callbacks and field offsets are target
// facts; the existing table name describes its witnessed ShadowMap use.
extern const FieldParse g_shadowMapFieldParseTable[] = {
	{ "MapSize", &INI::parseInt, 0, 0 },
	{ "MaxViewDistance", &INI::parseReal, 0, 4 },
	{ "MinShadowedTerrainHeight", &INI::parseReal, 0, 8 },
	{ 0, 0, 0, 0 }
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;

#include "../../Include/Common/Rva00152D1CObj.h"

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
	g_shadowMapSettings = g_defaultShadowMapSettings;
	GameLODManager *mgr = TheGameLODManager;
	int lod = mgr->word177C;
	if (lod >= 4)
	{
		int minimumMapSize = 0x800;
		int *mapSize = &g_shadowMapSettings.v0;
		if (g_shadowMapSettings.v0 < 0x800)
			mapSize = &minimumMapSize;
		g_shadowMapSettings.v0 = *mapSize;
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
	g_shadowMapSettings = g_defaultShadowMapSettings;
	if (*reinterpret_cast<int *>(reinterpret_cast<char *>(ini) + 8) == 2 &&
		TheGameLODManager->word177C >= 4)
	{
		int minimumMapSize = 0x800;
		int *mapSize;
		if (g_shadowMapSettings.v0 < minimumMapSize)
			mapSize = &minimumMapSize;
		else
			mapSize = &g_shadowMapSettings.v0;
		g_shadowMapSettings.v0 = *mapSize;
	}
	ini->initFromINI(&g_shadowMapSettings, g_shadowMapFieldParseTable);
	int mode = *reinterpret_cast<int *>(reinterpret_cast<char *>(ini) + 8);
	if (mode != 2 && mode != 4)
	{
		if (*reinterpret_cast<unsigned char *>(
			reinterpret_cast<char *>(TheWritableGlobalData) + 0xD45))
			g_shadowMapSettings.v0 = 0x1000;
		g_defaultShadowMapSettings = g_shadowMapSettings;
	}
}

// INI block registration (LINK-236). Each unit links its own 12-byte BlockParse nodes onto
// theBlockParseList from a file-scope object whose inline constructor does the link; MSVC 7.1
// builds token and parse in .data, so the node's .text$yc initializer is only the 21-byte link
// (retail .CRT$XCU 0x007ABFE3, node 0x00DB4488). It is the last entry before its run's pool-init marker 0x007ABFF8,
// so it is the marker unit's own node, not a marker-less INI wrapper's; this file defines its
// callback.
typedef void (*INIBlockParse)( INI *ini );
extern struct BlockParse *theBlockParseList;
struct BlockParse
{
	BlockParse *next;
	const char *token;
	INIBlockParse parse;

	BlockParse( const char *token, INIBlockParse parse ) : next(theBlockParseList), token(token), parse(parse)
	{
		theBlockParseList = this;
	}
};

BlockParse theShadowMapBlockParse( "ShadowMap", parseShadowMapBlock );

// cl: /DNDEBUG /MD
//
// ?rva003BD598@Rva003BD598@@QAEXXZ @0x003BD598 72B (dump range 18).
// Thiscall clearer ending in a tail jump: clears its +0x0C byte, runs the
// pinned GameLogic 0x00376D49 member, re-enters through the pinned 0x003BBAD3
// member (retail passes this in ecx although the callee body only reads
// globals, so the rowed free-function name cannot spell the call), drops
// bibs through a qualified direct call to rowed virtual
// W3DTerrainVisual::removeAllBibs when the visual global is set, flags the
// campaign manager byte, applies the rowed 0x002036A9 imm setter, and
// tail-jumps the pinned 0x0021A54A member on the hero-manager global.
class GameLogic
{
public:
	void rva00376D49();
};
extern GameLogic *TheGameLogic;

class Rva003BBAD3
{
public:
	void rva003BBAD3();
};

class TerrainVisual
{
public:
	virtual void removeAllBibs();
};
class W3DTerrainVisual : public TerrainVisual
{
public:
	virtual void removeAllBibs();
};
extern TerrainVisual *TheTerrainVisual;	// defined in GameClient.cpp

class Rva00E02D6C
{
public:
	char m_pad[0x2D];
	bool m_flag2D;
};
extern Rva00E02D6C *TheCampaignManager;

class Rva002036A9DwordImmSetter
{
public:
	void apply();
};
extern Rva002036A9DwordImmSetter *TheImmSetter;

class Rva0021A54A
{
public:
	void rva0021A54A();
};
extern Rva0021A54A *TheHeroManager;

class Rva003BD598
{
public:
	void rva003BD598();
private:
	char m_pad[0x0C];
	unsigned char m_flagC;
};

void Rva003BD598::rva003BD598()
{
	m_flagC = 0;
	TheGameLogic->rva00376D49();
	((Rva003BBAD3 *)this)->rva003BBAD3();
	if (TheTerrainVisual != 0)
		static_cast<W3DTerrainVisual *>(TheTerrainVisual)->W3DTerrainVisual::removeAllBibs();
	TheCampaignManager->m_flag2D = true;
	TheImmSetter->apply();
	TheHeroManager->rva0021A54A();
}

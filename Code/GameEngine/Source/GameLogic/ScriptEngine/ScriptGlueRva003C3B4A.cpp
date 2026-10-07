// cl: /DNDEBUG /MD
//
// ?rva003C3B4A@Rva003BE5C9@@QAEXXZ @0x003C3B4A 51B (dump range 18).
// Sibling member of rowed 0x003BE5C9 on the same this (no ecx reload for
// the head call): runs the rowed victory emit, sets the campaign flag,
// drops bibs through a qualified direct call to rowed virtual
// W3DTerrainVisual::removeAllBibs when the visual global is set, applies
// the rowed 0x002036B4 setter, and tail-jumps the pinned 0x0021A54A
// member on the hero-manager global.
class Rva003BE5C9
{
public:
	void rva003BE5C9();
	void rva003C3B4A();
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

class Rva002036B4GlobalCopier
{
public:
	void apply();
};
extern Rva002036B4GlobalCopier *TheCopier;

class Rva0021A54A
{
public:
	void rva0021A54A();
};
extern Rva0021A54A *TheHeroManager;

void Rva003BE5C9::rva003C3B4A()
{
	rva003BE5C9();
	TheCampaignManager->m_flag2D = true;
	if (TheTerrainVisual != 0)
		static_cast<W3DTerrainVisual *>(TheTerrainVisual)->W3DTerrainVisual::removeAllBibs();
	TheCopier->apply();
	TheHeroManager->rva0021A54A();
}

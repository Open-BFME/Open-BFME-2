// stlport
// cl: /D_OPERATOR_NEW_DEFINED_ /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS=1 /D_STLP_USE_MALLOC /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /ICode/Libraries/Include /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// The W3D particle system manager of BFME 2's FXParticleSystem
// (vftable 0x007C4C20, class Rva0004CA4C). Owner proven by the sibling slot 36
// (0x0004CF9A), whose smudge path names this file in its
// GetGameClientRandomValueReal literal; WorldBuilder twin 0x007FB050 names the
// handle TrackingPtr<FXParticleSystem::ParticleSystem> (RvaSmartPtr12 here).
//
// ?rva0004CF9A@Rva0004CA4C@@QAEXAAVRenderInfoClass@@@Z, retail
// 0x0004CF9A..0x0004D47D (1251 bytes), slot 36: the main particle pass.
// Target facts: runs once per ready flag (+0xA8, cleared); zeroes the
// g_bfmeVal991 smudge counter and +0x20 of the g_bfmeB991 view, takes the
// terrain's maximum visible box and adds one smudge set (0x002D291B on the
// g_bfmeB991 object). Systems of type 6 are skipped, sort lists 1 queued
// while static sort lists are on. A system whose type name (+0x10) starts
// with the dword 'SMUD' draws no particles: when g_bfmeB991's +0x04 is not 1,
// the heat-effects byte at +0x25 of TheWritableGlobalData is set and the
// system's 0x0004CABD test (+0x0C is 7 or 8) fails, each particle of the
// +0xA4 storage (slot 8 first, +0x64 next) inside the box grown by its size
// adds a smudge (0x002D2996) with its position, a random offset within its
// spread, its size and alpha; the first one stores its colour at +0x40.
// Other systems draw through draw-module slot 4 with the +0x68 handle naming
// the current one. Then the queued sort lists as in slot 37, the on-screen
// count to manager slot 15, and the snow manager's render (0x0009470F).
// The 0x0004CABD getter lies inside this unit's retail range and is defined
// here: with its body visible the system pointer stays in ESI across the call
// as in retail.
//
// ?rva0004D47D@Rva0004CA4C@@QAEXAAVRenderInfoClass@@@Z, retail
// 0x0004D47D..0x0004D636 (441 bytes), slot 37: the pass over particle
// systems of type 6 (+0x0C), the ones slot 36 skips. Target facts: on-screen
// count +0x5C and the draw modules' count +0x54 reset, the terrain's maximum
// visible box from the camera frustum, sort lists 1 queued into the +0xAC
// vector pair while WW3D's static sort lists are on, the rest drawn through
// draw-module slot 4, then both sort-list vectors drawn back to front with
// the second sorting flag 0x00DB5F7D cleared, and SortingRendererClass::Flush.
// The zeroed reference local at [ebp-0x1C] (EH state 0, never released) is
// the twin's ref-counted local released at the end; its type is not
// established.
#include "Lib/Coord3D.h"
#include "Lib/RGBColor.h"
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

class RenderInfoClass;
class FrustumClass;
class ParticleSystem;
ParticleSystem *Make001FCBD7();

class AABoxClass
{
public:
	Coord3D Center;
	Coord3D Extent;
};

class CameraClass
{
public:
	const FrustumClass &Get_Frustum() const
	{
		Update_Frustum();
		return *reinterpret_cast<const FrustumClass *>(m_pad + 0x100);
	}

protected:
	void Update_Frustum() const;			// 0x001340B0

private:
	unsigned char m_pad[0x100];
};

#include "../../../../Libraries/Source/WWVegas/WW3D2/RenderInfoClass.h"

class BaseHeightMapRenderObjClass
{
public:
	Bool getMaximumVisibleBox(const FrustumClass &frustum, AABoxClass *box, Bool ignoreMaxHeight);	// 0x0006B1FA
};


class RvaSmartPtr12
{
public:
	RvaSmartPtr12(ParticleSystem *particleSystem)
	{
		m_ptr = particleSystem;
		if (m_ptr)
			attach();
		else
		{
			m_pad08 = 0;
			m_pad04 = 0;
		}
	}
	void attach();					// 0x0004CB9A
	RvaSmartPtr12(const RvaSmartPtr12 &that);	// 0x0004CC19
	~RvaSmartPtr12() { if (m_ptr) rva0004CBC0(); }
	RvaSmartPtr12 &operator=(const RvaSmartPtr12 &that) throw();	// 0x0004CC3D
	void rva0004CBC0();				// 0x0004CBC0
	ParticleSystem *get() const { return m_ptr; }
	operator bool() const { return m_ptr != 0; }
	ParticleSystem *operator->() const { return m_ptr ? m_ptr : Make001FCBD7(); }

private:
	ParticleSystem *m_ptr;
	int m_pad04;
	int m_pad08;
};

#include <vector>
#include <list>
// Compare typed nodes locally, as in NetPacket.cpp; retail inlines this test.
namespace _STL {
template <class T, class L, class R>
static inline bool operator!=(const _List_iterator<T, L>& a, const _List_iterator<T, R>& b)
{ return a._M_node != b._M_node; }
}
template<> void _STL::vector<RvaSmartPtr12>::push_back(const RvaSmartPtr12 &);
template<> RvaSmartPtr12 *_STL::vector<RvaSmartPtr12>::erase(RvaSmartPtr12 *, RvaSmartPtr12 *);

class Rva001F4D2D { public: Real rva001F4D2D(); };		// 0x001F4D2D
class Rva001F4E1BSlot { public: const RGBColor *get() const; };	// 0x001F4E1B
#include "../../../../GameEngine/Include/GameClient/Rva001F4DC4.h"
class Rva001F4DF9 { public: Real rva001F4DF9(); };		// 0x001F4DF9

class Particle
{
public:
	Real getSize() { return reinterpret_cast<Rva001F4D2D *>(this)->rva001F4D2D(); }
	const RGBColor *getColor() const { return reinterpret_cast<const Rva001F4E1BSlot *>(this)->get(); }
	Real getSpread() { return reinterpret_cast<Rva001F4DC4 *>(this)->rva001F4DC4(); }
	Real getAlpha() { return reinterpret_cast<Rva001F4DF9 *>(this)->rva001F4DF9(); }

	unsigned char m_pad00[0x1C];
	Coord3D m_pos;					// +0x1C
	unsigned char m_pad28[0x64 - 0x28];
	Particle *m_next;				// +0x64
};

class ParticleStorage
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual Particle *getFirstParticle();		// slot 8 (+0x20)
};

class ParticleDrawModule
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual Int doParticles(RenderInfoClass &rinfo, void *box, Int *count);	// slot 4 (+0x10)
};

class Rva0004CABDSevenEight
{
public:
	__declspec(noinline) int get() const { if (m_value == 7 || m_value == 8) return 1; return 0; }
	char m_pad[0xC];
	int m_value;
};

class ParticleSystem
{
public:
	Bool isSevenOrEight() const { return (unsigned char)reinterpret_cast<const Rva0004CABDSevenEight *>(this)->get() != 0; }
	const AsciiString &getParticleTypeName() const { return m_particleTypeName; }

	unsigned char m_pad00[0x0C];
	Int m_0C;					// +0x0C
	AsciiString m_particleTypeName;			// +0x10
	unsigned char m_pad14[0x24 - 0x14];
	UnsignedInt m_sortList;				// +0x24
	unsigned char m_pad28[0xA4 - 0x28];
	ParticleStorage *m_storage;			// +0xA4
	unsigned char m_padA8[0x1C4 - 0xA8];
	ParticleDrawModule *m_drawModule;		// +0x1C4
};

class ParticleSystemManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14();
	virtual void setOnScreenParticleCount(Int count);	// slot 15 (+0x3C)

	unsigned char m_pad04[0x4C - 0x04];
	_STL::list<RvaSmartPtr12> m_allParticleSystems;	// +0x4C
};

struct SmudgeVector3
{
	void Set(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	Real X, Y, Z;
};

struct SmudgeVector2
{
	void Set(Real x, Real y) { X = x; Y = y; }
	Real X, Y;
};

struct Smudge
{
	unsigned char m_pad00[0x0C];
	SmudgeVector3 m_pos;				// +0x0C
	SmudgeVector2 m_offset;				// +0x18
	Real m_size;					// +0x20
	Real m_opacity;					// +0x24
};

struct SmudgeSet
{
	Smudge *addSmudgeToSet();			// 0x002D2996
};

class SmudgeManager
{
public:
	SmudgeSet *addSmudgeSet();			// 0x002D291B
};

class BfmeB991
{
public:
	unsigned char m_pad00[0x04];
	Int m_04;					// +0x04
	unsigned char m_pad08[0x20 - 0x08];
	Int m_smudgeCountLastFrame;			// +0x20
	unsigned char m_pad24[0x40 - 0x24];
	Int m_color;					// +0x40
};

#include "../../../../GameEngine/Include/Common/GlobalData.h"

class W3DSnowManager
{
public:
	void render(RenderInfoClass &rinfo);		// 0x0009470F
};
class SnowManager;

#include "../../../../Libraries/Source/WWVegas/WW3D2/SortingRendererClass.h"

#include "../../../../Libraries/Source/WWVegas/WW3D2/WW3DClass.h"

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
extern ParticleSystemManager *TheParticleSystemManager;
extern unsigned char g_Va00DB5F7D;
extern BfmeB991 *g_bfmeB991;
// Native render counter at RVA 0x009E1CF0; shared with bfmeGo991B.
Int g_bfmeVal991 = 0;
extern GlobalData *TheWritableGlobalData;
extern SnowManager *TheSnowManager;

Real GetGameClientRandomValueReal(Real lo, Real hi, char *file, Int line);	// 0x00234111

static inline Real Fabs(Real val)
{
	Int value = *(Int *)&val;
	value &= 0x7fffffff;
	return *(Real *)&value;
}

class TextureBaseClass { public: void Release_Ref(); };
struct Rva0004D47DAssetRef
{
	TextureBaseClass *m_ptr;
	Rva0004D47DAssetRef() : m_ptr(0) {}
	~Rva0004D47DAssetRef() { if (m_ptr) m_ptr->Release_Ref(); }
};

class Rva0004CA4C
{
public:
	void rva0004CF9A(RenderInfoClass &rinfo);
	void rva0004D47D(RenderInfoClass &rinfo);

private:
	void *m_vtbl;
	unsigned char m_pad04[0x54 - 0x04];
	Int m_54;					// +0x54
	unsigned char m_pad58[0x5C - 0x58];
	Int m_onScreenParticleCount;			// +0x5C
	unsigned char m_pad60[0x68 - 0x60];
	RvaSmartPtr12 m_current;			// +0x68
	unsigned char m_pad74[0xA8 - 0x74];
	Bool m_readyToRender;				// +0xA8
	unsigned char m_padA9[0xAC - 0xA9];
	_STL::vector<RvaSmartPtr12> m_sortLists[2];	// +0xAC
};

void Rva0004CA4C::rva0004CF9A(RenderInfoClass &rinfo)
{
	if (!m_readyToRender)
		return;
	m_readyToRender = false;

	g_bfmeVal991 = 0;
	if (g_bfmeB991)
		g_bfmeB991->m_smudgeCountLastFrame = 0;

	const FrustumClass &frustum = rinfo.Camera.Get_Frustum();
	AABoxClass bbox;
	TheTerrainRenderObject->getMaximumVisibleBox(frustum, &bbox, true);

	Real bcX = bbox.Center.x;
	Real bcY = bbox.Center.y;
	Real bcZ = bbox.Center.z;
	Real beX = bbox.Extent.x;
	Real beY = bbox.Extent.y;
	Real beZ = bbox.Extent.z;

	SmudgeSet *set = 0;
	if (g_bfmeB991)
		set = reinterpret_cast<SmudgeManager *>(g_bfmeB991)->addSmudgeSet();

	Rva0004D47DAssetRef assetRef;
	m_current = 0;

	_STL::list<RvaSmartPtr12> &particleSysList = TheParticleSystemManager->m_allParticleSystems;
	for (_STL::list<RvaSmartPtr12>::iterator it = particleSysList.begin(); it != particleSysList.end(); ++it)
	{
		RvaSmartPtr12 sys(*it);
		ParticleSystem *raw = sys.get();
		if (!raw)
			continue;
		if (raw->m_0C == 6)
			continue;

		if (WW3D::AreStaticSortListsEnabled && raw->m_sortList > 0 && raw->m_sortList < 2)
		{
			m_sortLists[raw->m_sortList].push_back(sys);
			continue;
		}

		if (*((UnsignedInt *)raw->getParticleTypeName().str()) == 0x44554D53)
		{
			if (g_bfmeB991 && g_bfmeB991->m_04 != 1 && TheWritableGlobalData->field0025)
			{
				Bool colorSet = false;
				if (!raw->isSevenOrEight())
				{
					for (Particle *particle = raw->m_storage->getFirstParticle(); particle; particle = particle->m_next)
					{
						Real psize = particle->getSize();
						if (Fabs(particle->m_pos.x - bcX) > psize + beX)
							continue;
						if (Fabs(particle->m_pos.y - bcY) > psize + beY)
							continue;
						if (Fabs(particle->m_pos.z - bcZ) > psize + beZ)
							continue;
						if (!colorSet)
						{
							g_bfmeB991->m_color = particle->getColor()->getAsInt();
							colorSet = true;
						}
						Smudge *smudge = set->addSmudgeToSet();
						Real spread = particle->getSpread();
						smudge->m_pos.Set(particle->m_pos.x,particle->m_pos.y,particle->m_pos.z);
						smudge->m_offset.Set(GetGameClientRandomValueReal(spread * -2.0f, spread * 2.0f,
							"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\W3DFXParticleSystem.cpp", 195),GetGameClientRandomValueReal(-spread, spread,
							"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\W3DFXParticleSystem.cpp", 195));
						smudge->m_size = psize;
						smudge->m_opacity = particle->getAlpha();
						g_bfmeVal991++;
					}
				}
			}
			continue;
		}

		if (raw->m_drawModule)
		{
			m_current = sys;
			m_onScreenParticleCount += sys->m_drawModule->doParticles(rinfo, &bbox, &m_54);
			m_current = 0;
			continue;
		}
	}

	if (WW3D::AreStaticSortListsEnabled)
	{
		unsigned char saved = g_Va00DB5F7D;
		if (saved)
			g_Va00DB5F7D = 0;
		for (Int k = 1; k >= 0; k--)
		{
			_STL::vector<RvaSmartPtr12> &list = m_sortLists[k];
			for (Int j = list.size() - 1; j >= 0; j--)
			{
				RvaSmartPtr12 sys(list[j]);
				if (!sys)
					continue;
				if (sys->m_drawModule)
				{
					m_current = sys;
					m_onScreenParticleCount += sys->m_drawModule->doParticles(rinfo, &bbox, &m_54);
					m_current = 0;
				}
			}
			list.clear();
		}
		if (saved)
			g_Va00DB5F7D = 1;
	}

	TheParticleSystemManager->setOnScreenParticleCount(m_onScreenParticleCount);
	if (TheSnowManager)
		reinterpret_cast<W3DSnowManager *>(TheSnowManager)->render(rinfo);
}

void Rva0004CA4C::rva0004D47D(RenderInfoClass &rinfo)
{
	m_onScreenParticleCount = 0;
	AABoxClass bbox;
	TheTerrainRenderObject->getMaximumVisibleBox(rinfo.Camera.Get_Frustum(), &bbox, true);
	m_54 = 0;

	Rva0004D47DAssetRef assetRef;

	_STL::list<RvaSmartPtr12> &particleSysList = TheParticleSystemManager->m_allParticleSystems;
	for (_STL::list<RvaSmartPtr12>::iterator it = particleSysList.begin(); it != particleSysList.end(); ++it)
	{
		RvaSmartPtr12 sys(*it);
		if (!sys)
			continue;
		if (sys->m_0C != 6)
			continue;
		if (WW3D::AreStaticSortListsEnabled && sys->m_sortList > 0 && sys->m_sortList < 2)
		{
			m_sortLists[sys->m_sortList].push_back(sys);
			continue;
		}
		if (sys->m_drawModule)
		{
			m_onScreenParticleCount += sys->m_drawModule->doParticles(rinfo, &bbox, &m_54);
			continue;
		}
	}

	if (WW3D::AreStaticSortListsEnabled)
	{
		unsigned char saved = g_Va00DB5F7D;
		if (saved)
			g_Va00DB5F7D = 0;
		for (Int k = 1; k >= 0; k--)
		{
			_STL::vector<RvaSmartPtr12> &list = m_sortLists[k];
			for (Int j = list.size() - 1; j >= 0; j--)
			{
				RvaSmartPtr12 sys(list[j]);
				if (!sys)
					continue;
				ParticleDrawModule *drawModule = sys->m_drawModule;
				if (drawModule)
					m_onScreenParticleCount += drawModule->doParticles(rinfo, &bbox, &m_54);
			}
			list.clear();
		}
		if (saved)
			g_Va00DB5F7D = 1;
	}

	SortingRendererClass::Flush();
}

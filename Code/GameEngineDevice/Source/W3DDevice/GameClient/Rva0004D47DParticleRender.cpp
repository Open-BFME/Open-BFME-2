// flags: region default (reverse/retail_inventory/flag_regions.csv)
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ?rva0004D47D@Rva0004D47D@@QAEXAAVRenderInfoClass@@@Z
// Retail 0x0004D47D..0x0004D636 (441 bytes) RET4: the particle render pass.
// Zero Hour's W3DParticleSystemManager::doParticles is the semantic lead
// (camera frustum, TheTerrainRenderObject maximum visible box, walk of
// TheParticleSystemManager's system list); BFME2 walks the list of
// 12-byte system handles at manager +0x4C instead and hands each type-6
// system to its draw module (system +0x1C4, virtual slot 4, which adds the
// drawn count to +0x5C and updates +0x54). With static sort lists enabled,
// systems on layer 1 are deferred into the per-layer handle vectors at
// +0xAC and drawn afterwards, last first, layer by layer, with the global
// byte at VA 0x00DB5F7D cleared around them; SortingRendererClass::Flush
// ends the pass.
// Evidence: retail callees (CameraClass::Update_Frustum 0x001340B0,
// getMaximumVisibleBox 0x0006B1FA, the rowed RvaSmartPtr12 copy/unlink and
// vector<RvaSmartPtr12> push_back/erase, Flush 0x0012F190), offsets, and the
// unwind map at 0x00CFF41C: state 0 is a null texture reference released
// through ??1?$RefCountPtr@VTextureClass@@@@QAE@XZ (0x0017098D), states 1
// and 2 the handle copies released through 0x002115C5. The receiver is not
// identified, so its names are address-derived.
#include <list>

// Retail compares typed list nodes inline, as in NetPacket.cpp.
namespace _STL {
template <class T, class L, class R>
static __forceinline bool operator!=(const _List_iterator<T, L> &a, const _List_iterator<T, R> &b)
{ return a._M_node != b._M_node; }
}

#include <vector>
// bfme link decl-only begin
namespace _STL { template <> unsigned int const & max<unsigned int>(unsigned int const &, unsigned int const &); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?push_back@?$vector@VRvaSmartPtr12@@V?$allocator@VRvaSmartPtr12@@@_STL@@@_STL@@QAEXABVRvaS:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class RvaSmartPtr12;
namespace _STL { template <> void vector<RvaSmartPtr12,allocator<RvaSmartPtr12> >::push_back(RvaSmartPtr12 const &); }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@VRvaSmartPtr12@@V?$allocator@VRvaSmartPtr12@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class RvaSmartPtr12;
namespace _STL { template <> void vector<RvaSmartPtr12,allocator<RvaSmartPtr12> >::_M_clear(); }
// Suppress this TU's non-retail copy of ??$_Construct@VRvaSmartPtr12@@V1@@_STL@@YAXPAVRvaSmartPtr12@@ABV1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _Construct<RvaSmartPtr12,RvaSmartPtr12>(RvaSmartPtr12 *,RvaSmartPtr12 const &); }
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@VRvaSmartPtr12@@V?$allocator@VRvaSmartPtr12@@@_STL@@@_STL@@IA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<RvaSmartPtr12,allocator<RvaSmartPtr12> >::_M_insert_overflow(RvaSmartPtr12 *,RvaSmartPtr12 const &,__false_type const &,unsigned int,bool); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAVRvaSmartPtr12@@@_STL@@YAXPAVRvaSmartPtr12@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class RvaSmartPtr12;
namespace _STL { template <> void _Destroy<RvaSmartPtr12 *>(RvaSmartPtr12 *,RvaSmartPtr12 *); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAVRvaSmartPtr12@@V1@V?$allocator@VRvaSmartPtr12@@@_STL@@@_S:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class RvaSmartPtr12;
namespace _STL { template <> RvaSmartPtr12 * _STLP_alloc_proxy<RvaSmartPtr12 *,RvaSmartPtr12,allocator<RvaSmartPtr12> >::allocate(unsigned int); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@VRvaSmartPtr12@@@_STL@@QBEXPAVRvaSmartPtr12@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class RvaSmartPtr12;
namespace _STL { template <> void allocator<RvaSmartPtr12>::deallocate(RvaSmartPtr12 *,unsigned int) const; }

#include "../../../../GameEngine/Include/Common/FrustumClass.h"
struct Vector3Data { float X, Y, Z; };
#include "../../../../Libraries/Source/WWVegas/WWMath/AABoxClass.h"

class CameraClass
{
protected:
	void Update_Frustum() const;
public:
	const FrustumClass &Get_Frustum() const
	{
		Update_Frustum();
		return *(const FrustumClass *)((const char *)this + 0x100);
	}
};

#include "../../../../Libraries/Source/WWVegas/WW3D2/RenderInfoClass.h"

class BaseHeightMapRenderObjClass
{
public:
	bool getMaximumVisibleBox(const FrustumClass &frustum, AABoxClass *box, bool ignoreMaxHeight);
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

#include "../../../../Libraries/Source/WWVegas/WW3D2/SortingRendererClass.h"

#include "../../../../Libraries/Source/WWVegas/WW3D2/WW3DClass.h"

// The byte owned by GlobalByteGetters.cpp; cleared while deferred layers draw.
extern unsigned char g_Va00DB5F7D;

class TextureClass
{
public:
	void Release_Ref();
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	~RefCountPtr()
	{
		if (Referent != 0)
			Referent->Release_Ref();
	}
	T *Referent;
};

class Rva0004D47DDrawModule
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual int render(RenderInfoClass &rinfo, AABoxClass &box, int *count);
};

class Rva0004D47DSystem
{
public:
	unsigned char m_pad00[0x0C];
	int m_type;					   // +0x0C
	unsigned char m_pad10[0x24 - 0x10];
	unsigned int m_layer;			 // +0x24
	unsigned char m_pad28[0x1C4 - 0x28];
	Rva0004D47DDrawModule *m_draw;	// +0x1C4
};

// The 12-byte particle-system handle (system, previous, next).
class RvaSmartPtr12
{
public:
	void rva0004CBC0();
	RvaSmartPtr12(const RvaSmartPtr12 &that);
	RvaSmartPtr12 &operator=(const RvaSmartPtr12 &that);
	~RvaSmartPtr12()
	{
		if (m_ptr)
			rva0004CBC0();
	}
	Rva0004D47DSystem *get() const { return m_ptr; }

private:
	Rva0004D47DSystem *m_ptr;
	int m_pad04;
	int m_pad08;
};

// Declaration-only: the vector teardown's _Destroy is the rowed 0x00211F9A copy;
// this TU would emit a private one through a scalar deleting destructor.
namespace _STL {
template <> void _Destroy<RvaSmartPtr12>(RvaSmartPtr12 *);
}

class ParticleSystemManager
{
public:
	unsigned char m_pad00[0x4C];
	_STL::list<RvaSmartPtr12> m_systems; // +0x4C
};
extern ParticleSystemManager *TheParticleSystemManager;

class Rva0004D47D
{
public:
	void rva0004D47D(RenderInfoClass &rinfo);

private:
	unsigned char m_pad00[0x54];
	int m_54;
	unsigned char m_pad58[0x5C - 0x58];
	int m_5c;
	unsigned char m_pad60[0xAC - 0x60];
	_STL::vector<RvaSmartPtr12> m_layers[2]; // +0xAC
};

void Rva0004D47D::rva0004D47D(RenderInfoClass &rinfo)
{
	m_5c = 0;
	const FrustumClass &frustum = rinfo.Camera.Get_Frustum();
	AABoxClass bbox;
	TheTerrainRenderObject->getMaximumVisibleBox(frustum, &bbox, true);
	m_54 = 0;
	RefCountPtr<TextureClass> texture;
	_STL::list<RvaSmartPtr12> &systems = TheParticleSystemManager->m_systems;
	for (_STL::list<RvaSmartPtr12>::iterator it = systems.begin(); it != systems.end(); ++it) {
		RvaSmartPtr12 handle(*it);
		Rva0004D47DSystem *sys = handle.get();
		if (!sys)
			continue;
		if (sys->m_type != 6)
			continue;
		if (WW3D::AreStaticSortListsEnabled && sys->m_layer > 0 && sys->m_layer < 2) {
			m_layers[sys->m_layer].push_back(handle);
			continue;
		}
		if (Rva0004D47DDrawModule *draw = sys->m_draw)
			m_5c += draw->render(rinfo, bbox, &m_54);
		else
			continue;
	}
	if (WW3D::AreStaticSortListsEnabled) {
		unsigned char saved = g_Va00DB5F7D;
		if (saved)
			g_Va00DB5F7D = 0;
		for (int layer = 1; layer >= 0; --layer) {
			_STL::vector<RvaSmartPtr12> &deferred = m_layers[layer];
			for (int i = (int)deferred.size() - 1; i >= 0; --i) {
				RvaSmartPtr12 handle(deferred[i]);
				Rva0004D47DSystem *sys = handle.get();
				if (!sys)
					continue;
				if (Rva0004D47DDrawModule *draw = sys->m_draw)
					m_5c += draw->render(rinfo, bbox, &m_54);
			}
			deferred.erase(deferred.begin(), deferred.end());
		}
		if (saved)
			g_Va00DB5F7D = 1;
	}
	SortingRendererClass::Flush();
}

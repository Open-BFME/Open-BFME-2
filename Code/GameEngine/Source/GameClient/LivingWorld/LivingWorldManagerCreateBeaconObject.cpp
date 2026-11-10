// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /ICode/GameEngine/Include /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?CreateBeaconObject@LivingWorldManager@@QAEXHPBVCoord2D@@H@Z
// retail 0x00213171..0x002133E0 (623 bytes EH) thiscall RET 0xC.
//
// Identity (WorldBuilder): the twin 0x00B602E0 is
// LivingWorldManager::CreateBeaconObject (LivingWorldManager.cpp; its
// debug-only crash text "Unhandled beacon type in
// LivingWorldManager::CreateBeaconObject" line 1333); the sole retail caller
// 0x003F43D3 calls it on TheLivingWorldManager (0x009FE1C8) with an id the
// 8-byte position at its +0x28 and type 0. This replaces the placeholder pin
// ?rva00213171@Rva00DFE1C8Host@@QAEXHPAXH@Z (Rva00DFE1C8Host is the same
// singleton).
// Body: the beacon name comes from the rowed BattleMarker formatter
// rva0060E7F0 (0x00211245); when the id is not yet in the int-key hash_map at
// +0x218 a 0xB0-byte beacon (rowed ctor 0x003FD14D given the name's address
// as in CreateSound) builds its render object through the rowed
// LivingWorldVisual::createRenderObject 0x003FCEA3 from one of three model
// names (+0xCC/+0xD4/+0xD0 by type 0/1/2; layer 1/2/1 else 6) with an empty
// sub-object list; rva0010E4F6 makes it unique; with a render object it is
// placed at the position's ground height (g_00DFEF18 rva002BF5B0 then
// +0xEC added) through Set_Transform (slot 21) and added to that scene
// (slot 17); the beacon gets +0x30 = 1 a unit scale at +0xA0 and
// rva003FB9EB(30 0). The beacon is stored in the map and handed to
// rva002BFFD4 with the layer; the beacon sound (+0x160) plays through
// TheAudio addAudioEvent (slot 25) when set.
// WorldBuilder evaluates the render object through an inline getter and the
// ground point / translation through Vector3 constructors: both shapes are
// needed for retail's evaluation order. Member and view names besides the
// method are address-derived or descriptive.
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include "ascii_string.h"
#include "Coord2D.h"
#include "Coord3D.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include <vector>
#include <hash_map>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * const * vector<void *,allocator<void *> >::begin()const  { return this->_M_start; } }
// The beacon map's _M_find (0x002888D4, fold-proof here) inlines size(); a
// declaration-only size() made this unit's copy call it. Bind to the kept
// retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// bfme link decl-only begin
namespace _STL { template <> void swap<_STLP_alloc_proxy<void **, void *, allocator<void *> > >(_STLP_alloc_proxy<void **, void *, allocator<void *> > &, _STLP_alloc_proxy<void **, void *, allocator<void *> > &); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(unsigned int, allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(unsigned int, void *const &, allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::begin(); }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::swap(vector<void *, allocator<void *> > &); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
}
// map<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); an explicit specialization declaration
// suppresses this TU's copy so callers bind retail's instead.
namespace _STL {
template <> bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const;
}

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}

extern "C" AsciiString rva0060E7F0(int marker);
void rva0010E4F6(void *robj, bool flag);

class RenderObjClass;

#include "../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"
static __forceinline void initBeaconTransform(Matrix3D &transform) {transform.Row[0].X=1.0f;transform.Row[0].Y=0.0f;transform.Row[0].Z=0.0f;transform.Row[0].W=0.0f;transform.Row[1].X=0.0f;transform.Row[1].Y=1.0f;transform.Row[1].Z=0.0f;transform.Row[1].W=0.0f;transform.Row[2].X=0.0f;transform.Row[2].Y=0.0f;transform.Row[2].Z=1.0f;transform.Row[2].W=0.0f;}
static __forceinline void setBeaconTranslation(Matrix3D &tm,float x,float y,float z) {tm.Row[0].W=x;tm.Row[1].W=y;tm.Row[2].W=z;}



#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

class Rva00213171RenderObj
{
public:
#define RENDER_SLOT(n) virtual void slot##n();
	RENDER_SLOT(00) RENDER_SLOT(01) RENDER_SLOT(02) RENDER_SLOT(03)
	RENDER_SLOT(04) RENDER_SLOT(05) RENDER_SLOT(06) RENDER_SLOT(07)
	RENDER_SLOT(08) RENDER_SLOT(09) RENDER_SLOT(10) RENDER_SLOT(11)
	RENDER_SLOT(12) RENDER_SLOT(13) RENDER_SLOT(14) RENDER_SLOT(15)
	RENDER_SLOT(16) RENDER_SLOT(17) RENDER_SLOT(18) RENDER_SLOT(19)
	RENDER_SLOT(20)
	virtual void Set_Transform(const Matrix3D &m); // slot 21 (+0x54)
};

// The ground lookup 0x002BF5B0, rowed as Rva002BF4F3::rva002BF5B0.
#include "../../../Include/Common/Rva002BF4F3.h"

// The layer registration 0x002BFFD4, rowed as Rva002BFF5A::rva002BFFD4.
struct Rva002BFFD4Template;
class Rva002BFF5A
{
public:
	void rva002BFFD4(Rva002BFFD4Template *object, int layer, unsigned int extra);
};

class Rva002D3627Host;
class LivingWorld; extern LivingWorld *TheLivingWorld;

class Rva00213171Scene
{
public:
	RENDER_SLOT(00) RENDER_SLOT(01) RENDER_SLOT(02) RENDER_SLOT(03)
	RENDER_SLOT(04) RENDER_SLOT(05) RENDER_SLOT(06) RENDER_SLOT(07)
	RENDER_SLOT(08) RENDER_SLOT(09) RENDER_SLOT(10) RENDER_SLOT(11)
	RENDER_SLOT(12) RENDER_SLOT(13) RENDER_SLOT(14) RENDER_SLOT(15)
	RENDER_SLOT(16)
	virtual void addRenderObject(RenderObjClass *robj); // slot 17 (+0x44)
};

class AudioManager;
extern AudioManager *TheAudio;

class Rva00213171AudioView
{
public:
	RENDER_SLOT(00) RENDER_SLOT(01) RENDER_SLOT(02) RENDER_SLOT(03)
	RENDER_SLOT(04) RENDER_SLOT(05) RENDER_SLOT(06) RENDER_SLOT(07)
	RENDER_SLOT(08) RENDER_SLOT(09) RENDER_SLOT(10) RENDER_SLOT(11)
	RENDER_SLOT(12) RENDER_SLOT(13) RENDER_SLOT(14) RENDER_SLOT(15)
	RENDER_SLOT(16) RENDER_SLOT(17) RENDER_SLOT(18) RENDER_SLOT(19)
	RENDER_SLOT(20) RENDER_SLOT(21) RENDER_SLOT(22) RENDER_SLOT(23)
	RENDER_SLOT(24)
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event); // slot 25 (+0x64)
#undef RENDER_SLOT
};

class LivingWorldVisual
{
public:
	virtual void setHouseColor(const int &color);
	RenderObjClass *createRenderObject(const AsciiString &modelName,
		const _STL::vector<AsciiString> &subObjectNames, int shadowType, const int *houseColor);
	RenderObjClass *getRenderObject() { return m_primaryRObj; }
	char m_pad04[4];
	RenderObjClass *m_primaryRObj; // +0x08
};

class Rva003FB9C8
{
public:
	void rva003FB9EB(int a, int b);
};

class Rva003FD14D : public LivingWorldVisual
{
public:
	Rva003FD14D(int nameAddress);
	char m_pad0C[0x24];
	int m_30;
	char m_pad34[0x6c];
	Coord3D m_a0;
	char m_padAC[4];
};

struct LivingWorldManagerData
{
	char m_pad00[0xb8];
	AsciiString m_beaconModel0; // +0xB8 (manager +0xCC)
	AsciiString m_beaconModel2; // +0xBC (manager +0xD0)
	AsciiString m_beaconModel1; // +0xC0 (manager +0xD4)
	char m_padC4[0x14];
	float m_beaconHeight; // +0xD8 (manager +0xEC)
	char m_padDC[0x70];
	OpaqueRefElement4 m_beaconSound; // +0x14C (manager +0x160)
};

class LivingWorldManager
{
public:
	void CreateBeaconObject(int id, const Coord2D *pos, int type);
private:
	char m_pad00[0x14];
	LivingWorldManagerData m_data; // +0x14
	char m_pad164[0x218 - 0x164];
	_STL::hash_map<int, Rva003FD14D *> m_beacons; // +0x218
};

// With size() inlined, this unit's spare _M_bkt_num_key copy would differ from
// the first copy in link order. Bind to the kept copy instead of emitting one.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int hashtable<pair<const int, Rva003FD14D *>, int, hash<int>, _Select1st<pair<const int, Rva003FD14D *> >, equal_to<int>, allocator<pair<const int, Rva003FD14D *> > >::_M_bkt_num_key(const int &__key) const { return _M_hash(__key) % _M_buckets.size(); } }

void LivingWorldManager::CreateBeaconObject(int id, const Coord2D *pos, int type)
{
	AsciiString name = rva0060E7F0(id);
	if (m_beacons.find(id) == m_beacons.end())
	{
		Rva003FD14D *beacon = new Rva003FD14D((int)&name);
		AsciiString model;
		int layer = 6;
		switch (type)
		{
		case 0:
			model = m_data.m_beaconModel0;
			layer = 1;
			break;
		case 1:
			model = m_data.m_beaconModel1;
			layer = 2;
			break;
		case 2:
			model = m_data.m_beaconModel2;
			layer = 1;
			break;
		}
		beacon->createRenderObject(model, _STL::vector<AsciiString>(), 0, 0);
		rva0010E4F6(beacon->getRenderObject(), false);
		if (beacon->m_primaryRObj != 0)
		{
			Matrix3D tm;
	initBeaconTransform(tm);
			Vector3 ground(pos->x, pos->y, 0.0f);
			((Rva002BF4F3 *)((Rva002D3627Host *)TheLivingWorld))->rva002BF5B0((const Vector3 *)pos, &ground);
			setBeaconTranslation(tm,pos->x,pos->y,ground.Z + m_data.m_beaconHeight);
			((Rva00213171RenderObj *)beacon->m_primaryRObj)->Set_Transform(tm);
			((Rva00213171Scene *)((Rva002D3627Host *)TheLivingWorld))->addRenderObject(beacon->getRenderObject());
			beacon->m_30 = 1;
			Coord3D scale;
			scale.x = scale.y = scale.z = 1.0f;
			beacon->m_a0 = scale;
			((Rva003FB9C8 *)beacon)->rva003FB9EB(30, 0);
		}
		m_beacons[id] = beacon;
		((Rva002BFF5A *)((Rva002D3627Host *)TheLivingWorld))->rva002BFFD4((Rva002BFFD4Template *)beacon, layer, 0);
		if (m_data.m_beaconSound.referent != 0)
		{
			BfmeAudioEventPrefix136 sound(m_data.m_beaconSound, 1);
			((Rva00213171AudioView *)TheAudio)->addAudioEvent(&sound);
		}
	}
}

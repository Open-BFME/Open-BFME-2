// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native 0x00083780..0x000837F1, RET 8; standing-water observer slot 1
// of vtable BC70F0. Owner is WaterRenderObjClass, the rowed WaterRenderObjClass
// destructor at 82140. Native allocates A4, calls the rowed Rva008291D
// constructor 82F6A, retains at +4, pushes into its vector at this+40,
// and releases via 7DEEF. Constructor's established API takes void*.
// Real STLport vector definitions expose the growth/copy call graph and let
// MSVC reuse the dead area argument for the counted temporary.
// Observer/base offsets are target-derived; original member spelling is unknown.
#include <new>

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

#include <vector>
// bfme link decl-only begin
namespace _STL { template <> unsigned int const & max<unsigned int>(unsigned int const &, unsigned int const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva00082C1DElement@@@_STL@@YAXPAURva00082C1DElement@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00082C1DElement;
namespace _STL { template <> void _Destroy<Rva00082C1DElement *>(Rva00082C1DElement *,Rva00082C1DElement *); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva00082BE6Element@@@_STL@@YAXPAURva00082BE6Element@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00082BE6Element;
namespace _STL { template <> void _Destroy<Rva00082BE6Element *>(Rva00082BE6Element *,Rva00082BE6Element *); }
// Suppress this TU's non-retail copy of ??$__destroy_aux@PAURva00082C1DElement@@@_STL@@YAXPAURva00082C1DElement@@0ABU__false_type@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00082C1DElement;
namespace _STL { template <> void __destroy_aux<Rva00082C1DElement *>(Rva00082C1DElement *,Rva00082C1DElement *,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__destroy_aux@PAURva00082BE6Element@@@_STL@@YAXPAURva00082BE6Element@@0ABU__false_type@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00082BE6Element;
namespace _STL { template <> void __destroy_aux<Rva00082BE6Element *>(Rva00082BE6Element *,Rva00082BE6Element *,__false_type const &); }

#include "../../../../../Libraries/Source/Apt/AptRefTarget.h"
namespace _STL {template<> vector<TreeHintRef00217D4C>::~vector();
template<> TreeHintRef00217D4C*vector<TreeHintRef00217D4C>::erase(TreeHintRef00217D4C*,TreeHintRef00217D4C*);}

class Rva00081BAFVector { public: void reserve(unsigned int n); };
class Rva00081C17Vector { public: void reserve(unsigned int n); };

struct Rva002BA8F1Listener;
class Rva005A0B4CList { public: void append(Rva002BA8F1Listener *listener); };

class StandingWaveArea;
class RiverArea;

// Counted renderable prefix: vtable, then the reference count.
class WaterAreaRenderable
{
public:
	void *m_vtable;
	int m_references;
};

class Rva00308DF0;
#include "../../../../../GameEngine/Include/GameLogic/StandingWaterArea.h"
class Rva008291D : public WaterAreaRenderable
{
public:
	Rva008291D(void *area);
private:
	char m_body[0x40 - 8];
public:Rva00308DF0 *m_area;
private:char m_tail[0xA4-0x44];
};

class RenderableRiverArea : public WaterAreaRenderable
{
public:
	RenderableRiverArea(void *area);
private:
	char m_body[0x5C - 8];
};

// Counted handles as the loops hold them: retain on construction, release
// through 0x0007DEEF. Each is spelled as the element of its push_back row.
#define WATER_AREA_REF(Name, T) struct Name { 	T *m_ptr; 	Name(T *p) : m_ptr(p) { if (m_ptr) ++m_ptr->m_references; } 	Name(const Name &other):m_ptr(other.m_ptr){if(m_ptr)++m_ptr->m_references;} ~Name() { if (m_ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr); } };
WATER_AREA_REF(Rva00082BE6Element, Rva008291D)
WATER_AREA_REF(Rva00082C1DElement, RenderableRiverArea)

template <class T> struct AreaSetEntry
{
	int m_id;
	T *m_area;
};

class CreateAHeroData;
#include "../../../../../GameEngine/Include/Common/Rva002B7250.h"

template <class T> class AreaSet
{
public:
	char m_observers[0x14];
	AreaSetEntry<T> *m_begin;
	AreaSetEntry<T> *m_end;
	void removeObserver(void*p){reinterpret_cast<Rva002B7250*>(this)->rva002B7250((CreateAHeroData*)p);}
	unsigned int size() const { return m_end - m_begin; }
};

struct WaterAreaCursor
{
	const void *m_set;
	int m_index;
	WaterAreaCursor(const void *set, int index) : m_set(set), m_index(index) {}
};
// Existing cdecl binding at 7E394, independently verified as the 29-byte
// two-word equality body. Its visibility preserves the outer receiver in EBX.
extern "C" inline __declspec(noinline) bool __cdecl rva0007E394CursorEqual(
    const WaterAreaCursor &a, const WaterAreaCursor &b)
{
    return a.m_set == b.m_set && a.m_index == b.m_index;
}

// The renderables vector as one STLport vector<counted handle>.
typedef _STL::vector<TreeHintRef00217D4C> WaterAreaRenderables;

template <class Element, class Reserve> class WaterAreaRenderableList
	: public WaterAreaRenderables
{
public:
	__forceinline WaterAreaRenderableList() {}
	__forceinline ~WaterAreaRenderableList() {}
	void reserve(unsigned int n) { reinterpret_cast<Reserve *>(this)->reserve(n); }
	void push_back(const Element &ref) { reinterpret_cast<_STL::vector<Element> *>(this)->push_back(ref); }
	void swapInto(WaterAreaRenderables *out)
	{
		reinterpret_cast<_STL::vector<int> *>(out)->swap(*reinterpret_cast<_STL::vector<int> *>(this));
	}
};

class WaterRenderObjHead
{
public:
	virtual ~WaterRenderObjHead();
private:
	char m_body[0xC8 - 4];
};
// Area set observer: vtables 0x00BC70F0 (standing water, at +0xC8),
// 0x00BC70E0 (rivers, at +0xCC) and 0x00BC70D0 (+0xD0). Slot 1 takes the id
// and the area that was added.
template <class T> class AreaSetObserver
{
public:
	virtual void slot0(int id);
	virtual void onAreaAdded(int id, T *area);
	virtual void slot2(int a, int b);
	virtual void slot3(int a, int b);
};
class WaterWaveArea;

class WaterRenderObjClass : public WaterRenderObjHead,
	public AreaSetObserver<StandingWaveArea>, public AreaSetObserver<RiverArea>,
	public AreaSetObserver<WaterWaveArea>
{
public:
	virtual ~WaterRenderObjClass();
	virtual void onAreaAdded(int id, StandingWaveArea *area);
	virtual void onAreaAdded(int id, RiverArea *area);
	void rva0008385F(AreaSet<StandingWaveArea> *areas, WaterAreaRenderables *out);
	void rva00083959(AreaSet<RiverArea> *areas, WaterAreaRenderables *out);
void rva000B3FD0();
	void rva00083A7A(AreaSet<StandingWaveArea>*,AreaSet<RiverArea>*,AreaSet<WaterWaveArea>*);
private:
	char m_unknownD4[0x104 - 0xD4];
	AreaSet<StandingWaveArea> *m_standingAreas;
	_STL::vector<Rva00082BE6Element> m_standingRenderables;
	AreaSet<RiverArea> *m_riverAreas;
	_STL::vector<Rva00082C1DElement> m_riverRenderables;
AreaSet<WaterWaveArea> *m_waveAreas;
};

// 0x00083780, 113 bytes, RET8: a standing water area was added.
void WaterRenderObjClass::onAreaAdded(int, StandingWaveArea *area)
{
	Rva00082BE6Element ref(new Rva008291D(area));
	m_standingRenderables.push_back(ref);
}


// Native 0x000837F1..0x0008385F, RET 8; river observer slot 1 at BC70E0.
// The constructor's established void* parameter and 5C allocation are native.
void WaterRenderObjClass::onAreaAdded(int, RiverArea *area)
{
    m_riverRenderables.push_back(Rva00082C1DElement(new RenderableRiverArea(area)));
}

// 0x0008385F, 250 bytes, RET8: build a renderable for every standing water
// area, subscribe to the set, then swap the new list into *out.
void WaterRenderObjClass::rva0008385F(AreaSet<StandingWaveArea> *areas, WaterAreaRenderables *out)
{
	unsigned int count = areas->size();
	WaterAreaRenderableList<Rva00082BE6Element, Rva00081BAFVector> list;
	list.reserve(count);
	WaterAreaCursor end(areas, areas->size());
	for (WaterAreaCursor it(areas, 0); !rva0007E394CursorEqual(it, end); ++it.m_index)
		list.push_back(Rva00082BE6Element(new Rva008291D(areas->m_begin[it.m_index].m_area)));
	reinterpret_cast<Rva005A0B4CList *>(areas)->append(
		reinterpret_cast<Rva002BA8F1Listener *>(static_cast<AreaSetObserver<StandingWaveArea> *>(this)));
	list.swapInto(out);
}


// 0x00083959, 247 bytes, RET8: the same for the river areas.
void WaterRenderObjClass::rva00083959(AreaSet<RiverArea> *areas, WaterAreaRenderables *out)
{
	unsigned int count = areas->size();
	WaterAreaRenderableList<Rva00082C1DElement, Rva00081C17Vector> list;
	list.reserve(count);
	WaterAreaCursor end(areas, areas->size());
	for (WaterAreaCursor it(areas, 0); !rva0007E394CursorEqual(it, end); ++it.m_index)
		list.push_back(Rva00082C1DElement(new RenderableRiverArea(areas->m_begin[it.m_index].m_area)));
	reinterpret_cast<Rva005A0B4CList *>(areas)->append(
		reinterpret_cast<Rva002BA8F1Listener *>(static_cast<AreaSetObserver<RiverArea> *>(this)));
	list.swapInto(out);
}

// Native 83A7A..83B7B RET12: replace all three area subscriptions, rebuild
// standing/river lists and initialize each standing-area shader. The +40
// area pointer and the pre-existing 308C31 member binding come from retail.
void WaterRenderObjClass::rva00083A7A(AreaSet<StandingWaveArea>*standing,AreaSet<RiverArea>*rivers,AreaSet<WaterWaveArea>*waves)
{
 if(m_standingAreas) {
  m_standingAreas->removeObserver(static_cast<AreaSetObserver<StandingWaveArea>*>(this));m_standingAreas=0;
  m_riverAreas->removeObserver(static_cast<AreaSetObserver<RiverArea>*>(this));m_riverAreas=0;
  m_waveAreas->removeObserver(static_cast<AreaSetObserver<WaterWaveArea>*>(this));m_waveAreas=0;
 }
 WaterAreaRenderables *sl=(WaterAreaRenderables*)&m_standingRenderables;
 sl->erase(sl->begin(),sl->end());
 WaterAreaRenderables *rl=(WaterAreaRenderables*)&m_riverRenderables;
 rl->erase(rl->begin(),rl->end());
 rva0008385F(standing,sl);m_standingAreas=standing;
 rva00083959(rivers,rl);m_riverAreas=rivers;
 reinterpret_cast<Rva005A0B4CList*>(waves)->append(reinterpret_cast<Rva002BA8F1Listener*>(static_cast<AreaSetObserver<WaterWaveArea>*>(this)));
 m_waveAreas=waves;
 for(_STL::vector<Rva00082BE6Element>::iterator i=m_standingRenderables.begin();i!=m_standingRenderables.end();++i) {
  Rva00082BE6Element ref(*i);
  ((StandingWaterArea *)ref.m_ptr->m_area)->loadFXShaderSetup();
 }
}

// Terrain load at 9213F calls the full water owner through REL32 at 9241D.
// This no-argument thiscall is the shared relocation-free RET at B3FD0.
// The original method name is unproven; it contributes zero unique bytes.
void WaterRenderObjClass::rva000B3FD0()
{
}

// ?onAreaAdded@Rva0082140@@UAEXHPAVStandingWaveArea@@@Z
// partial score=0.66 date=2026-10-11
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Water render object: the renderables it keeps for the map's standing water
// and river areas.
//
// Target facts. The owner is the object whose destructor is rowed at
// 0x00082140 (W3DWater.cpp, WB 0x742CF0 WaterRenderObjClass destructor): three
// area-set observer bases at +0xC8/+0xCC/+0xD0, the standing water area set at
// +0x104 with its renderables vector at +0x108, the river area set at +0x114
// with its vector at +0x118. Each area set keeps 8-byte entries {id, area}
// between +0x14 and +0x18 and walks them with the {set, index} cursor whose
// equality test is rowed at 0x0007E394 (AreaSet<RiverArea/StandingWaveArea> in
// WB). The area set's observer list is rowed at 0x005A0B4C.
// The renderables are counted handles: the count is at +4 and the release is
// the rowed fastcall 0x0007DEEF. A standing water renderable is 0xA4 bytes
// (constructor 0x00082F6A, destructor rowed at 0x0008291D as Rva008291D), a
// river renderable is 0x5C bytes (constructor 0x00083547; its rendering method
// getter is rowed at 0x00083A50 under RenderableRiverArea).
// The vector operations are the folded STLport bodies already in the ledger,
// spelled as their rows: reserve 0x00081BAF/0x00081C17, push_back
// 0x00082BE6/0x00082C1D, swap 0x00567ECD, the base constructor 0x00211E58 and
// the destructor 0x000806B4.
// Method names are address-derived; what each one does is read from its body.
//
// BANK NOTE (ryan-seat1, 2026-10-11). Four bodies in one TU: 0x00083780
// (113B), 0x000837F1 (110B), 0x0008385F (250B), 0x00083959 (247B); 0x00083A7A
// (257B) calls the last two. Every callee except the two renderable
// constructors resolves through existing rows/pins with this file's views
// (the this-adjusted +0x40/+0x4C member offsets of the observer overrides come
// out exact). The constructors are unrowed, so landing needs two new pins via
// tools/pin_admission.py --add: ??0Rva008291D@@QAE@PAVStandingWaveArea@@@Z ->
// 0x00082F6A and ??0RenderableRiverArea@@QAE@PAVRiverArea@@@Z -> 0x00083547
// (matching.md allows pinning an unmatched callee; earlier verdicts treated
// them as hard blockers). Same calls and EH states (the two builders also
// same size; the callbacks emit 108/111B against 110/113B); the one wall
// is retail's stack packing: the counted handle lives in the dead home of the
// area parameter ([ebp+0xC] / [ebp+8]) and its pointer stays in esi/edi across
// push_back, so the inline release does not reload it. cl here gives the
// handle its own local and reloads it after the call, which also moves
// `this` (0x8385F/0x83959: ebx in retail, spilled here). Tried without
// change: named handle, const handle, const member, temporary, a visible
// STLport-shaped push_back body, a by-value forwarding helper (inline and
// out of line). See docs/recipes.md "Stack-slot packing".

void *__cdecl operator new(unsigned int size);
void __cdecl operator delete(void *p);

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

namespace _STL {
template <class T> class allocator { public: allocator() {} };
template <class T, class A> class _Vector_base
{
public:
	_Vector_base(const A &a);
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
struct __false_type {};
template <class T1, class T2> void _Construct(T1 *p, const T2 &value);
template <class T, class A = allocator<T> > class vector : public _Vector_base<T, A>
{
public:
	~vector();
	void push_back(const T &x)
	{
		if (this->_M_finish != this->_M_end_of_storage)
		{
			_Construct(this->_M_finish, x);
			++this->_M_finish;
		}
		else
			_M_insert_overflow(this->_M_finish, x, __false_type(), 1UL, true);
	}
	void _M_insert_overflow(T *position, const T &x, const __false_type &, unsigned long n, bool atEnd);
	void swap(vector &x);
};
}

struct TreeHintRef00217D4C;
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

class Rva008291D : public WaterAreaRenderable
{
public:
	Rva008291D(StandingWaveArea *area);
private:
	char m_body[0xA4 - 8];
};

class RenderableRiverArea : public WaterAreaRenderable
{
public:
	RenderableRiverArea(RiverArea *area);
private:
	char m_body[0x5C - 8];
};

// Counted handles as the loops hold them: retain on construction, release
// through 0x0007DEEF. Each is spelled as the element of its push_back row.
#define WATER_AREA_REF(Name, T) struct Name { 	T *m_ptr; 	Name(T *p) : m_ptr(p) { if (m_ptr) ++m_ptr->m_references; } 	~Name() { if (m_ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr); } };
WATER_AREA_REF(Rva00082BE6Element, Rva008291D)
WATER_AREA_REF(Rva00082C1DElement, RenderableRiverArea)

template <class T> struct AreaSetEntry
{
	int m_id;
	T *m_area;
};

template <class T> class AreaSet
{
public:
	char m_observers[0x14];
	AreaSetEntry<T> *m_begin;
	AreaSetEntry<T> *m_end;
	unsigned int size() const { return m_end - m_begin; }
};

struct WaterAreaCursor
{
	const void *m_set;
	int m_index;
	WaterAreaCursor(const void *set, int index) : m_set(set), m_index(index) {}
};
extern "C" bool __cdecl rva0007E394CursorEqual(const WaterAreaCursor &a, const WaterAreaCursor &b);

// The renderables vector as one STLport vector<counted handle>.
typedef _STL::vector<TreeHintRef00217D4C> WaterAreaRenderables;

template <class Element, class Reserve> class WaterAreaRenderableList
	: public _STL::_Vector_base<int, _STL::allocator<int> >
{
public:
	__forceinline WaterAreaRenderableList() : _STL::_Vector_base<int, _STL::allocator<int> >(_STL::allocator<int>()) {}
	~WaterAreaRenderableList() { reinterpret_cast<WaterAreaRenderables *>(this)->~vector(); }
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

class Rva0082140 : public WaterRenderObjHead,
	public AreaSetObserver<StandingWaveArea>, public AreaSetObserver<RiverArea>,
	public AreaSetObserver<WaterWaveArea>
{
public:
	virtual ~Rva0082140();
	virtual void onAreaAdded(int id, StandingWaveArea *area);
	virtual void onAreaAdded(int id, RiverArea *area);
	void rva0008385F(AreaSet<StandingWaveArea> *areas, WaterAreaRenderables *out);
	void rva00083959(AreaSet<RiverArea> *areas, WaterAreaRenderables *out);
private:
	char m_unknownD4[0x104 - 0xD4];
	AreaSet<StandingWaveArea> *m_standingAreas;
	_STL::vector<Rva00082BE6Element> m_standingRenderables;
	AreaSet<RiverArea> *m_riverAreas;
	_STL::vector<Rva00082C1DElement> m_riverRenderables;
};

// 0x00083780, 113 bytes, RET8: a standing water area was added.
void Rva0082140::onAreaAdded(int, StandingWaveArea *area)
{
	Rva00082BE6Element ref(new Rva008291D(area));
	m_standingRenderables.push_back(ref);
}

// 0x000837F1, 110 bytes, RET8: a river area was added.
void Rva0082140::onAreaAdded(int, RiverArea *area)
{
	m_riverRenderables.push_back(Rva00082C1DElement(new RenderableRiverArea(area)));
}

// 0x0008385F, 250 bytes, RET8: build a renderable for every standing water
// area, subscribe to the set, then swap the new list into *out.
void Rva0082140::rva0008385F(AreaSet<StandingWaveArea> *areas, WaterAreaRenderables *out)
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
void Rva0082140::rva00083959(AreaSet<RiverArea> *areas, WaterAreaRenderables *out)
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

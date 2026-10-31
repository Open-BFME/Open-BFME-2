// cl: /O1 /G7 /arch:SSE /EHsc /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// LargeGroupAudioSoundKeyPair subject bookkeeping (retail 0x00568920..0x00569863).
//
// Identity (target): WorldBuilder's LargeGroupAudioSoundKeyPair.cpp keeps these
// bodies in retail's order: 0x00568920 (0x0143F9F0) directly before
// setupDuckingTarget 0x00568939 (0x0143FA30), then updateSubject 0x00569628
// (0x014413B0), the unnamed 0x0056979A (0x01441A20) and 0x005697F7
// (0x01441AC0), and unregisterSubject 0x00569863 (0x01441BC0). The WorldBuilder
// asserts in unregisterSubject ("Less than zero units on LGAS grid set") read
// the total weight at +0x64; 0x005697F7 adds the same weight back, and the
// 0x003EDE44 worker dispatches the three subject callbacks. The two unnamed
// bodies keep address-derived method names.
// The subject's vtable slots (previous position, position, weight, keys) are
// read from these callers; the class names of the grid, ducking-slot and
// pending-add helpers stay address-derived.
// 0x00568920 and 0x00568939 moved here from their split-out unit: 0x00568939
// and 0x005697F7 keep THIS in ECX across the 0x00568920 call, which MSVC only
// does for a callee compiled earlier in the same unit.
// Shape notes: BFME 2's Coord2D has a user-declared destructor, which is what
// makes 0x0056979A's caller-side argument copy record its address (a copy
// constructor alone does not). WorldBuilder's 0x005697F7 stores the getKeys()
// result in a local before the overlap test; spelling it that way gives
// retail's register assignment (subject in ESI, THIS in EDI).
// The owning AudioMap destroys each key pair through 0x0056A061. Its
// WorldBuilder twin confirms the destructor identity; the native cleanup
// sequence independently establishes members at 0/C/10/14/20/40/4C/58.
// The first twelve bytes remain an opaque owning container: its destructor
// is the existing 0x003ED94F provider. Automatic member destruction preserves
// all eight retail EH states, including the throwing allocation free.
// BFME1 donor revision reviewed: cee35b7d8 (semantic/reference search only).
void __cdecl Rva00030830FreeAllocation(void *);
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <cstdlib>
#define free Rva00030830FreeAllocation
#include <set>
// Keep the typed tree comparison local, as in W3DShroudInterpolate.cpp.
// Its unused external base wrapper differs from the selected provider.
namespace _STL {
template <class Value, class Left, class Right>
static inline bool operator!=(const _Rb_tree_iterator<Value, Left> &a,
                              const _Rb_tree_iterator<Value, Right> &b)
{ return a._M_node != b._M_node; }
}
#include <vector>
#include <algorithm>
#undef free
#include "ascii_string.h"

class ModuleData;
struct BfmeStringRecord00568CE0;
class Rva00568A20;
// Keep native inline frees without publishing competing allocator helpers.
namespace _STL {
template<> __declspec(dllimport) __forceinline void allocator<BfmeStringRecord00568CE0>::deallocate(BfmeStringRecord00568CE0 *p, size_t) const { if(p) Rva00030830FreeAllocation(p); }
template<> __declspec(dllimport) __forceinline void _STLP_alloc_proxy<BfmeStringRecord00568CE0 *,BfmeStringRecord00568CE0,allocator<BfmeStringRecord00568CE0> >::deallocate(BfmeStringRecord00568CE0 *p, size_t n) { __stl_alloc_rebind(static_cast<allocator<BfmeStringRecord00568CE0> &>(*this), (BfmeStringRecord00568CE0 *)0).deallocate(p,n); }
template<> __declspec(dllimport) __forceinline void allocator<const ModuleData *>::deallocate(const ModuleData * *p, size_t) const { if(p) Rva00030830FreeAllocation(p); }
template<> __declspec(dllimport) __forceinline void _STLP_alloc_proxy<const ModuleData * *,const ModuleData *,allocator<const ModuleData *> >::deallocate(const ModuleData * *p, size_t n) { __stl_alloc_rebind(static_cast<allocator<const ModuleData *> &>(*this), (const ModuleData * *)0).deallocate(p,n); }
template<> __declspec(dllimport) __forceinline void allocator<Rva00568A20>::deallocate(Rva00568A20 *p, size_t) const { if(p) Rva00030830FreeAllocation(p); }
template<> __declspec(dllimport) __forceinline void _STLP_alloc_proxy<Rva00568A20 *,Rva00568A20,allocator<Rva00568A20> >::deallocate(Rva00568A20 *p, size_t n) { __stl_alloc_rebind(static_cast<allocator<Rva00568A20> &>(*this), (Rva00568A20 *)0).deallocate(p,n); }
}

// The native allocator ignores the element count. Keep its null-guarded
// free inline, including member cleanup, and leave whole-container owners
// to their rowed units (vector69D63 and node creation568D95).
namespace _STL {
template<> __declspec(dllimport) __forceinline _Vector_base<BfmeStringRecord00568CE0,allocator<BfmeStringRecord00568CE0> >::~_Vector_base() { if(this->_M_start) Rva00030830FreeAllocation(this->_M_start); }
template<> __declspec(dllimport) __forceinline _Vector_base<const ModuleData *,allocator<const ModuleData *> >::~_Vector_base() { if(this->_M_start) Rva00030830FreeAllocation(this->_M_start); }
template<> vector<BfmeStringRecord00568CE0>::~vector();
template<> __declspec(dllimport) __forceinline void vector<const ModuleData *>::_M_clear() { _Destroy(this->_M_start, this->_M_finish); this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start); }
}


// BFME 2's Coord2D (MathCoord2D.h), kept under the pair name the grid lookup
// 0x005C8176 is pinned with.
struct FloatPair
{
	FloatPair() {}
 // Nontrivial coordinate return has the same two-float physical ABI.
 FloatPair(float a,float b):x(a),y(b){}
 operator float *() { return &x; }
	FloatPair(const FloatPair &floatPair) : x(floatPair.x), y(floatPair.y) {}
	~FloatPair() {}
	__forceinline bool isExactlyEqualTo(const FloatPair &floatPair) const { return x == floatPair.x && y == floatPair.y; }
	float x;
	float y;
};

struct Rva00568FE4Key { float x; float y; unsigned short w; unsigned short pad; };
struct Rva00568FE4Less {
	bool operator()(const Rva00568FE4Key &a, const Rva00568FE4Key &b) const {
		if (a.x < b.x) return false;
		if (a.x > b.x) return true;
		if (a.y < b.y) return false;
		if (a.y > b.y) return true;
		return a.w < b.w;
	}
};
typedef _STL::multiset<Rva00568FE4Key, Rva00568FE4Less, _STL::allocator<Rva00568FE4Key> > Rva00568FE4Multi;
namespace _STL {
template<> _Rb_tree_node<Rva00568FE4Key> *_Rb_tree<Rva00568FE4Key,Rva00568FE4Key,_Identity<Rva00568FE4Key>,Rva00568FE4Less,allocator<Rva00568FE4Key> >::_M_create_node(const Rva00568FE4Key &);
}

class Rva005C8176 { public: void *rva005C8176(FloatPair p); };
struct Rva005C8876Position;struct Rva005C8876Grid;
class LargeGroupAudioGridCell
{
public:
	Rva005C8876Position getPreferredAudioPosition(Rva005C8876Grid*);
	void update(Rva005C8876Grid*);
	void addToWeight(unsigned short weight);
	void subtractFromWeight(unsigned short weight);
};
class Rva00569543 {
	char m_pad[0x4C];
	_STL::vector<const ModuleData *> m_sorted;
	_STL::vector<const ModuleData *> m_mods;
public:
	void rva00569543(const ModuleData *m);
	void rva005695F2(const ModuleData *m);
};
class HostClass005C815B
{
public:
	void method_005C836F(int key, float value);
	void method_005C839B(int,int);
	void method_005C834A(int a, int b) throw();
	void method_005C815B();
};

struct Rva00568939Elem
{
	char m_00[8];
	float m_08;
	int m_0c;
	bool m_10;
	char m_pad11[3];
};

class HostClass005C815B;
// Layout the two ducking helpers below read (+0x14/+0x18 element range,
// four grid slots at +0x2C); a view of LargeGroupAudioSoundKeyPair's storage.
struct LargeGroupAudioSoundKeyPairDuckingView
{
	char m_pad[0x14];
	Rva00568939Elem *m_begin14;
	Rva00568939Elem *m_end18;
	char m_pad1C[0x10];
	union
	{
		int m_vals[4];
		HostClass005C815B *m_slots[4];
	};
};
class Rva0056887D
{
public:
	Rva0056887D &rva0056887D(const Rva0056887D &src, unsigned short w);

private:
	int m00; // +0
	int m04; // +4
	short m08; // +8
};
struct Rva003CDDB0Range
{
public:
	bool method(const Rva003CDDB0Range *other);
	const int *m_begin; // +0x00
	const int *m_end; // +0x04
};

class LargeGroupAudioSubject
{
public:
	virtual FloatPair getPreviousPosition() = 0;
	virtual FloatPair getPosition() = 0;
	virtual void vslot08() = 0;
	virtual void vslot0C() = 0;
	virtual void vslot10() = 0;
	virtual void vslot14() = 0;
	virtual unsigned short getWeight() = 0;
	virtual const Rva003CDDB0Range *getKeys() = 0;
};

class Rva003ED94FDtor { public: ~Rva003ED94FDtor(); void *header; int flags; };
class LargeGroupAudioAudioMap;
// This is the existing empty-vector constructor view at 1F81BF. Its name
// belongs to the fold owner; the target key-map original type stays opaque.
class ObjectCreationList {public: ObjectCreationList(); char opaque[12];};
struct Rva0056A061KeyMap : ObjectCreationList { ~Rva0056A061KeyMap(){reinterpret_cast<Rva003ED94FDtor *>(this)->Rva003ED94FDtor::~Rva003ED94FDtor();} };
class OpaqueRefCounted { public: void Release_Ref(); };
struct Rva0056A061Ref { Rva0056A061Ref():value(0){} OpaqueRefCounted *value; ~Rva0056A061Ref(){if(value)value->Release_Ref();} };
class LargeGroupAudioSoundKeyPair;
class Rva00569373
{
public:
	void rva00569373(void *);
	char m_pad00[0x58];
private:
	LargeGroupAudioSoundKeyPair **volatile m_begin; // +0x58
	LargeGroupAudioSoundKeyPair **m_end; // +0x5C
};
struct Rva005694CDElem;
class Rva00569393
{
public:
	void rva005694CD();
	void rva00569393(void *tag);
	char m_pad00[0x14];
private:
	Rva005694CDElem *m_begin; // +0x14
	Rva005694CDElem *m_end; // +0x18
	char m_pad1C[0x10];
	void *m_slots[4]; // +0x2C
	char m_pad3C[0x4];
	::_STL::vector<void *, ::_STL::allocator<void *> > m_40; // +0x40
	::_STL::vector<void *, ::_STL::allocator<void *> > m_4C; // +0x4C
};
class Rva00568F04
{
public:
	void rva00568F04(void *item);
	char m_pad00[0x58];
private:
	void **m_begin; // +0x58
	void **m_end; // +0x5C
};
class Rva00568F04;
struct BfmeStringRecord00568CE0 {
    AsciiString text0, text1;
    unsigned int word0;
    Rva00568F04 *subject;
    unsigned char flag;
    BfmeStringRecord00568CE0();
    BfmeStringRecord00568CE0(const BfmeStringRecord00568CE0 &o);
};
// Native transfer569BBC and WB unnamed twin1442480 establish version/Xfer
// protocol. WB-named1442010 establishes xferGridCellVector identity.
// ModuleData pointer vectors are opaque four-byte emitter views only.
struct VersionPair { unsigned char minimum,current; };
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../Include/Common/BfmeXfer.h"
class Rva00568A05
{
public:
	Rva00568A05 &operator=(const Rva00568A05 &other);
private:
	int m00; // +0x00 +0
	int m04; // +0x04 +4
	short m08; // +0x08 +8
	char m_pad0A[0x2];
};

struct Rva005688D2Base
{
public:
	char m_pad00[0x10];
	float m_scale; // +0x10
};
// Native 5688D2 returns its two-float output address in EAX and RET8.
// Its caller569ABD consumes that EAX as a live temporary with an empty
// destructor. This typed-return body is an emitted byte/relocation twin of
// the existing explicit-output provider; original source spelling is unknown.
// Native constant BC6C50 is -0.5f; scale belongs to owner+10 reached at this+3C.
class Rva005C83C0DivAvgField;
class Rva005688D2
{
public:
	void rva005688D2(float *out, int mode);
	int rva00568991();
	FloatPair rva005688D2(int mode);
	char m_pad00[0x2C];
private:
	Rva005C83C0DivAvgField *m_slots[4]; // +0x2C
	Rva005688D2Base *m_base; // +0x3C
};
FloatPair Rva005688D2::rva005688D2(int mode)
{
 float first,second;
 if(mode==0 || mode==2)first=0;
 else first=m_base->m_scale * -0.5f;
 if(mode==0 || mode==1)second=0;
 else second=m_base->m_scale * -0.5f;
 return FloatPair(first,second);
}

// Retail passes one source pointer (RET4), keeps it in EDI, and reuses its
// dead argument home for the four-grid counter and then the output flag at
// byte3. This four-byte carrier models that observed ABI and storage reuse;
// it does not claim the original source-language argument type.
struct Rva0056A378Source {
 union { const LargeGroupAudioSoundKeyPair *source; int count; struct { char pad[3]; bool ok; } result; };
};
class LargeGroupAudioKeyMap {public: LargeGroupAudioKeyMap &operator=(const LargeGroupAudioKeyMap &);};
struct OpaqueRefElement4 { void *m_referent; OpaqueRefElement4 &operator=(const OpaqueRefElement4 &);};
// Existing rowed adjustor destructor5C8565, called before scalar delete.
class Rva005C8565
{
public:
	~Rva005C8565();
};
struct Rva00569F0CVec : _STL::vector<BfmeStringRecord00568CE0,_STL::allocator<BfmeStringRecord00568CE0> > {
 void rva00569F0C(void *,void *,bool *);
};
class Rva005C865B {public: Rva005C865B(void *,float *); char opaque[0x1C];};
class Rva005C81D8 {public: void rva005C81D8(Rva005C8176 *,Rva005C8176 *,Rva005C8176 *);};
class LargeGroupAudioSoundKeyPair;
class LargeGroupAudioAudioMap;
class LargeGroupAudioSubject;
class Rva005C8176;
struct Rva005C8876Grid;
struct BfmeStringRecord00568CE0;
class BitRange;
class Xfer;
struct VersionPair;
struct FloatPair;
struct Rva0056A378Source;
class LargeGroupAudioSoundKeyPair
{
public:
 int getGrid(int index);
 void removeDuckingTarget(BitRange *host, void *tag);
 void removePointersToGridCellsInDuckingTarget(BitRange *host, void *tag);
 bool rva00568920() const;	// 0x00568920
 void rva00568939(int key);	// 0x00568939
 LargeGroupAudioSoundKeyPair(LargeGroupAudioAudioMap *owner, const char *name);
 ~LargeGroupAudioSoundKeyPair();
 void rva0056A378(Rva0056A378Source arg);
 void rva00569BBC(Xfer *, VersionPair *);
 void allocateGrids();
 void update(bool*);
 void setupAllDuckingTargets();
 void xferGridCellVector(Xfer *, void *, VersionPair *);
 void rva0056979A(const FloatPair &pos, unsigned short weight);
 void rva005697F7(LargeGroupAudioSubject *subject);
 void unregisterSubject(LargeGroupAudioSubject *subject);
 void updateSubject(LargeGroupAudioSubject *subject);
private:
 Rva0056A061KeyMap m_keys;
 Rva0056A061Ref m_owner;
 AsciiString m_name;
 _STL::vector<BfmeStringRecord00568CE0> m_subjects;
 Rva00568FE4Multi m_pendingAdds;
 Rva005C8176 *m_grids[4];
 Rva005C8876Grid *m_grid;
 _STL::vector<const ModuleData *> m_v40;
 _STL::vector<const ModuleData *> m_v4C;
 _STL::vector<const ModuleData *> m_v58;
 int m_totalWeight;
};
LargeGroupAudioSoundKeyPair::~LargeGroupAudioSoundKeyPair(){
 reinterpret_cast<Rva00569373 *>(this)->rva00569373((void *)1);
 _STL::vector<BfmeStringRecord00568CE0> *v=&m_subjects;
 for(BfmeStringRecord00568CE0 *it=v->begin();it!=m_subjects.end();++it){if(it->subject)it->subject->rva00568F04(this);}
 reinterpret_cast<Rva00569393 *>(this)->rva005694CD();
}

bool LargeGroupAudioSoundKeyPair::rva00568920() const
{
	const LargeGroupAudioSoundKeyPairDuckingView *largeGroupAudioSoundKeyPairDuckingView = (const LargeGroupAudioSoundKeyPairDuckingView *)this;
	for (int i = 0; i < 4; ++i)
		if (largeGroupAudioSoundKeyPairDuckingView->m_vals[i] == 0)
			return false;
	return true;
}

void LargeGroupAudioSoundKeyPair::rva00568939(int key)
{
	LargeGroupAudioSoundKeyPairDuckingView *largeGroupAudioSoundKeyPairDuckingView = (LargeGroupAudioSoundKeyPairDuckingView *)this;
	if (!rva00568920())
		return;
	for (Rva00568939Elem *e = largeGroupAudioSoundKeyPairDuckingView->m_begin14; e != largeGroupAudioSoundKeyPairDuckingView->m_end18; ++e) {
		if (e->m_0c != key)
			continue;
		if (e->m_10)
			return;
		HostClass005C815B **slot = largeGroupAudioSoundKeyPairDuckingView->m_slots;
		for (int left = 4; left != 0; --left, ++slot) {
			if (*slot != 0) {
				float f = e->m_08;
				(*slot)->method_005C836F(key, f);
			}
		}
		e->m_10 = true;
		return;
	}
}

void LargeGroupAudioSoundKeyPair::updateSubject(LargeGroupAudioSubject *subject)
{
	if (!((Rva003CDDB0Range *)this)->method(subject->getKeys()))
		return;
	FloatPair oldPos = subject->getPreviousPosition();
	FloatPair newPos = subject->getPosition();
	if (oldPos.isExactlyEqualTo(newPos))
		return;
	unsigned short weight = subject->getWeight();
	if (rva00568920())
	{
		for (int i = 0; i < 4; ++i)
		{
			if (m_grids[i] != 0)
			{
				LargeGroupAudioGridCell *oldCell = (LargeGroupAudioGridCell *)m_grids[i]->rva005C8176(oldPos);
				LargeGroupAudioGridCell *newCell = (LargeGroupAudioGridCell *)m_grids[i]->rva005C8176(newPos);
				if (oldCell != newCell)
				{
					if (oldCell != 0)
					{
						oldCell->subtractFromWeight(weight);
						((Rva00569543 *)this)->rva005695F2((const ModuleData *)oldCell);
					}
					if (newCell != 0)
					{
						newCell->addToWeight(weight);
						((Rva00569543 *)this)->rva005695F2((const ModuleData *)newCell);
					}
				}
			}
		}
	}
	else
	{
		Rva00568FE4Key key;
		key.x = oldPos.x;
		key.y = oldPos.y;
		key.w = weight;
		Rva00568FE4Multi::iterator it = m_pendingAdds.find(key);
		if (it != m_pendingAdds.end())
			m_pendingAdds.erase(it);
		key.x = newPos.x;
		key.y = newPos.y;
		key.w = weight;
		m_pendingAdds.insert(key);
	}
}

// WB143EA40 names allocateGrids. Native569ABD proves allocations1C and
// four ordered neighbour hookups through neutral5C81D8. /G7 closes the
// pending key's 16-bit weight load; target has no zero-extension instruction.
void LargeGroupAudioSoundKeyPair::allocateGrids()
{
 for(int i=0;i<4;++i){
  if(m_grids[i]){reinterpret_cast<Rva00569393 *>(this)->rva005694CD();i=0;}
  m_grids[i]=reinterpret_cast<Rva005C8176 *>(new Rva005C865B(reinterpret_cast<void *>(m_grid),reinterpret_cast<Rva005688D2 *>(this)->rva005688D2(i)));
 }
 reinterpret_cast<Rva005C81D8 *>(m_grids[0])->rva005C81D8(m_grids[1],m_grids[2],m_grids[3]);
 reinterpret_cast<Rva005C81D8 *>(m_grids[1])->rva005C81D8(m_grids[0],m_grids[3],m_grids[2]);
 reinterpret_cast<Rva005C81D8 *>(m_grids[2])->rva005C81D8(m_grids[3],m_grids[0],m_grids[1]);
 reinterpret_cast<Rva005C81D8 *>(m_grids[3])->rva005C81D8(m_grids[2],m_grids[1],m_grids[0]);
 setupAllDuckingTargets();
 Rva00568FE4Multi::iterator it=m_pendingAdds.begin(),end=m_pendingAdds.end();
 for(;it!=end;++it)rva0056979A(reinterpret_cast<const FloatPair &>(*it),it->w);
 m_pendingAdds.clear();
}

void LargeGroupAudioSoundKeyPair::rva0056979A(const FloatPair &pos, unsigned short weight)
{
	for (int i = 0; i < 4; ++i)
	{
		if (m_grids[i] != 0)
		{
			LargeGroupAudioGridCell *cell = (LargeGroupAudioGridCell *)m_grids[i]->rva005C8176(pos);
			if (cell != 0)
			{
				cell->addToWeight(weight);
				((Rva00569543 *)this)->rva005695F2((const ModuleData *)cell);
			}
		}
	}
}

void LargeGroupAudioSoundKeyPair::rva005697F7(LargeGroupAudioSubject *subject)
{
	const Rva003CDDB0Range *keys = subject->getKeys();
	if (!((Rva003CDDB0Range *)this)->method(keys))
		return;
	FloatPair pos = subject->getPosition();
	unsigned short weight = subject->getWeight();
	m_totalWeight += weight;
	if (rva00568920())
		rva0056979A(pos, weight);
	else
	{
		Rva0056887D record;
		m_pendingAdds.insert((const Rva00568FE4Key &)record.rva0056887D((const Rva0056887D &)pos, weight));
	}
}

void LargeGroupAudioSoundKeyPair::unregisterSubject(LargeGroupAudioSubject *subject)
{
	if (!((Rva003CDDB0Range *)this)->method(subject->getKeys()))
		return;
	FloatPair pos = subject->getPreviousPosition();
	unsigned short weight = subject->getWeight();
	m_totalWeight -= weight;
	if (rva00568920())
	{
		for (int i = 0; i < 4; ++i)
		{
			if (m_grids[i] != 0)
			{
				LargeGroupAudioGridCell *cell = (LargeGroupAudioGridCell *)m_grids[i]->rva005C8176(pos);
				if (cell != 0)
				{
					cell->subtractFromWeight(weight);
					((Rva00569543 *)this)->rva005695F2((const ModuleData *)cell);
				}
			}
		}
	}
	else
	{
		Rva00568FE4Key key;
		key.x = pos.x;
		key.y = pos.y;
		key.w = weight;
		Rva00568FE4Multi::iterator it = m_pendingAdds.find(key);
		if (it != m_pendingAdds.end())
			m_pendingAdds.erase(it);
	}
}

LargeGroupAudioSoundKeyPair::LargeGroupAudioSoundKeyPair(LargeGroupAudioAudioMap *owner, const char *name):m_owner(),m_grid(reinterpret_cast<Rva005C8876Grid*>(owner)),m_totalWeight(0){
 for(int i=0;i<4;++i)m_grids[i]=0;
 m_v4C.reserve(40);m_v40.reserve(40);
 if(name)m_name.set(name);
}

void LargeGroupAudioSoundKeyPair::rva0056A378(Rva0056A378Source arg)
{
 const LargeGroupAudioSoundKeyPair *other=arg.source;
 if(other==this)return;
 Rva005C8565 **slot=reinterpret_cast<Rva005C8565 **>(m_grids);
 arg.count=4;
 do {
  Rva005C8565 *s=*slot;
  if(s){s->~Rva005C8565(); ::operator delete(s); *slot=0;}
  ++slot;
 }while(--arg.count);
 reinterpret_cast<LargeGroupAudioKeyMap *>(this)->operator=(*reinterpret_cast<const LargeGroupAudioKeyMap *>(other));
 *reinterpret_cast<OpaqueRefElement4 *>(&m_owner)=*reinterpret_cast<const OpaqueRefElement4 *>(&other->m_owner);
 ((StringBase<char> &)(m_name)).set((const StringBase<char> &)(other->m_name));
 Rva00569F0CVec *v=reinterpret_cast<Rva00569F0CVec *>(&m_subjects);
 v->rva00569F0C(const_cast<BfmeStringRecord00568CE0 *>(other->m_subjects.begin()),const_cast<BfmeStringRecord00568CE0 *>(other->m_subjects.end()),&arg.result.ok);
 for(BfmeStringRecord00568CE0 *e=m_subjects.begin();e!=m_subjects.end();++e)e->subject=0;
}

void LargeGroupAudioSoundKeyPair::rva00569BBC(Xfer *xfer, VersionPair *version)
{
 if(version->current>=3)*xfer == m_totalWeight;
 else if(xfer->IsLoading())m_totalWeight=300000;
 bool hasGrids=rva00568920();
 if(version->current>=5){
  *xfer == hasGrids;
  unsigned count=m_pendingAdds.size();
  *xfer == count;
  if(xfer->IsLoading()){
   m_pendingAdds.clear();
   if(count>0){
    FloatPair position;position.x=0;position.y=0;
    do{
     Rva0056887D record;
     record.rva0056887D(reinterpret_cast<const Rva0056887D &>(position),0);
     *xfer == *reinterpret_cast<Coord2D *>(&record);
     *xfer == *reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(&record)+8);
     m_pendingAdds.insert(reinterpret_cast<const Rva00568FE4Key &>(record));
    }while(--count);
   }
  }else{
   Rva00568FE4Multi::iterator it=m_pendingAdds.begin(),end=m_pendingAdds.end();
   for(;it!=end;++it){
    Rva0056887D record;
    reinterpret_cast<Rva00568A05 *>(&record)->operator=(*reinterpret_cast<const Rva00568A05 *>(&*it));
    *xfer == *reinterpret_cast<Coord2D *>(&record);
    *xfer == *reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(&record)+8);
   }
  }
 }else if(xfer->IsLoading()){
  m_pendingAdds.clear();hasGrids=m_totalWeight>0;
 }
 if(!hasGrids){
  if(xfer->IsLoading() && rva00568920())reinterpret_cast<Rva00569393 *>(this)->rva005694CD();
 }else{
  if(xfer->IsLoading() && !rva00568920())allocateGrids();
  for(int left=4,i=0;left;--left,++i)reinterpret_cast<HostClass005C815B *>(m_grids[i])->method_005C839B(reinterpret_cast<int>(xfer),reinterpret_cast<int>(version));
  xferGridCellVector(xfer,&m_v4C,version);
  xferGridCellVector(xfer,&m_v40,version);
 }
}

void LargeGroupAudioSoundKeyPair::xferGridCellVector(Xfer *xfer, void *storage, VersionPair *)
{
 _STL::vector<const ModuleData *> *vec=reinterpret_cast<_STL::vector<const ModuleData *> *>(storage);
 int count=static_cast<int>(vec->size());
 *xfer == count;
 if(xfer->IsLoading()){vec->clear();vec->reserve(count);}
 for(int index=0;index<count;++index){
  FloatPair position;position.x=0;position.y=0;
  if(xfer->IsStoring())position=*reinterpret_cast<const FloatPair *>((*vec)[index]);
  *xfer == reinterpret_cast<Coord2D &>(position);
  if(xfer->IsLoading()){
   for(unsigned grid=0;grid<4;++grid){
    if(m_grids[grid]){
     const ModuleData *cell=reinterpret_cast<const ModuleData *>(m_grids[grid]->rva005C8176(position));
     if(cell && reinterpret_cast<const FloatPair *>(cell)->isExactlyEqualTo(position)){
      vec->push_back(cell);break;
     }
    }
   }
  }
 }
}
// Native 56A4AA..56A83B is the 913-byte RET4 update. WorldBuilder
// 1440080 names LargeGroupAudioSoundKeyPair::update; no clean BF1/ZH
// source for this BFME-specific method was found. The existing owner
// independently establishes +3C configuration, +40 active/+4C candidates,
// and +64 total weight. Target bytes supply the thresholds at E0/E2,
// displaced 12-byte records, neighbor weights/flags, and full queue clear.
// push_back receives the existing neighbor/best/iterator pointer references:
// that preserves their native homes and the live candidate-vector base.
// The raw pool-ref constructor only increments the witnessed +8C counter
// and cannot throw; retail keeps the allocation EH state across that call.
// Capture the pool target before the audio callback writes through &holder.
// friend_setList is a proven whole-body fold of the native setter, not a
// claim that an audio target is a GameMessage. Address-derived views remain
// provisional; the original event/player and payload names are unresolved.


struct BfmePoolHolder88
{
	unsigned char m_pad[0x88];
	OpaqueRefCounted m_ref;
};

class BfmePoolRef10
{
public:
	BfmePoolHolder88 *m_target;
	__forceinline BfmePoolRef10() : m_target(0) {}
	BfmePoolRef10(const BfmePoolRef10 &other);
	BfmePoolRef10 &operator=(const BfmePoolRef10 &other);
	void rva000519BD();
	BfmePoolRef10(BfmePoolHolder88 *) throw();
	__forceinline ~BfmePoolRef10() { if (m_target != 0) m_target->m_ref.Release_Ref(); }
};



class HostClass005C8E0A
{
public:
	void method_005C8E0A();
	BfmePoolRef10 rva005C8E2C();
	char m_pad00[8];
	BfmePoolRef10 m_pool08;
	HostClass005C8E0A *neighbors[8];
 char pad2C[0x18];
 unsigned short weight;
 unsigned char m_byte46;
 union { unsigned char flags;struct { unsigned char lowNibble:4;unsigned char highNibble:4; }; };
 void method_005C908B(BfmePoolRef10,unsigned char);
};

class Rva00568A20
{
public:
	BfmePoolRef10 m_ref;
	HostClass005C8E0A *m_host;
	unsigned char m_byte;
	char m_pad[3];
	Rva00568A20(const Rva00568A20 &o);
	Rva00568A20() : m_ref(), m_host(0) {}
};


class ModuleData;




class Rva0056A3FF
{
public:
	void rva0056A3FF(HostClass005C8E0A *host, _STL::vector<Rva00568A20> *vec);
	char m_pad00[0x40];
private:
	_STL::vector<void *> m_vec4040; // +0x40
};
struct Rva00568721Cmp
{
public:
	bool operator()(const void *a, const void *b) const;
};
struct BfmeEventPositionView {float x,y,z;};
struct Rva005C8876Position {float x,y,z;Rva005C8876Position(){} Rva005C8876Position(const Rva005C8876Position&p):x(p.x),y(p.y),z(p.z){} };
struct Rva005C8876Grid {char pad[0xE0];unsigned short startWeight,continueWeight;unsigned char mode;};

class Rva0051D93 {public:Rva0051D93(const OpaqueRefElement4&,const BfmeEventPositionView&,int);char data[0x90];};
class GameMessageList;
class GameMessage {public:void friend_setList(GameMessageList*);};
class AudioManager;
extern AudioManager *TheAudio;
class AudioCalls {
public:
 virtual void s00();virtual void s01();virtual void s02();virtual void s03();
 virtual void s04();virtual void s05();virtual void s06();virtual void s07();
 virtual void s08();virtual void s09();virtual void s10();virtual void s11();
 virtual void s12();virtual void s13();virtual void s14();virtual void s15();
 virtual void s16();virtual void s17();virtual void s18();virtual void s19();
 virtual void s20();virtual void s21();virtual void s22();virtual void s23();
 virtual GameMessageList *start(BfmePoolRef10*);
 virtual void s25();virtual void s26();virtual void stop(int);
};
extern class GameLogic *TheGameLogic;
struct LogicFrame {char pad[0x40];unsigned frame;};
namespace _STL {
template<> void vector<Rva00568A20>::reserve(unsigned);
template<> vector<BfmePoolRef10>::~vector();
template<> void sort<void**,Rva00568721Cmp>(void**,void**,Rva00568721Cmp);

template<> _Vector_base<int,allocator<int> >::_Vector_base(const allocator<int>&);
}
void LargeGroupAudioSoundKeyPair::update(bool *flag)
{
 int startWeight=m_grid->startWeight,continueWeight=m_grid->continueWeight;
 if(!rva00568920() && m_totalWeight>=startWeight){
  if(!*flag || reinterpret_cast<LogicFrame*>(TheGameLogic)->frame<=1){
   reinterpret_cast<LargeGroupAudioSoundKeyPair*>(this)->allocateGrids();*flag=true;
  }
 }else if(rva00568920() && m_totalWeight<=0){
  reinterpret_cast<Rva00569393*>(this)->rva005694CD();
 }
 if(rva00568920()){
  if(!m_v4C.empty()){
   _STL::vector<Rva00568A20> displaced;displaced.reserve(m_v40.size());
   for(unsigned i=0;i<m_v4C.size();++i){
    HostClass005C8E0A *cell=reinterpret_cast<HostClass005C8E0A*>(const_cast<ModuleData*>(m_v4C[i]));
    if(cell->m_pool08.m_target){
     if(cell->weight<continueWeight)reinterpret_cast<Rva0056A3FF*>(this)->rva0056A3FF(cell,reinterpret_cast<_STL::vector<Rva00568A20>*>(&displaced));
     else {HostClass005C8E0A **p=cell->neighbors;
     for(int left=8;left;--left,++p){
      HostClass005C8E0A *neighbor=*p;
      if(neighbor && neighbor->weight>cell->weight)reinterpret_cast<Rva0056A3FF*>(this)->rva0056A3FF(cell,reinterpret_cast<_STL::vector<Rva00568A20>*>(&displaced));
     }}
    }else if(cell->lowNibble>0){
     HostClass005C8E0A **p=cell->neighbors;
     for(int left=8;left;--left,++p){
      HostClass005C8E0A *neighbor=*p;
      if(neighbor && neighbor->m_pool08.m_target && neighbor->weight<cell->weight){
       reinterpret_cast<Rva0056A3FF*>(this)->rva0056A3FF(neighbor,reinterpret_cast<_STL::vector<Rva00568A20>*>(&displaced));
       m_v4C.push_back(reinterpret_cast<const ModuleData* const&>(neighbor));
      }
     }
    }
   }
   for(Rva00568A20 *e=displaced.begin();e!=displaced.end();++e){
    HostClass005C8E0A *best=0;
    for(int n=0;n<=8;++n){
     HostClass005C8E0A *cell=n==8?e->m_host:e->m_host->neighbors[n];
     if(cell && cell->weight>=startWeight && cell->lowNibble<=0){
      if(best){
       if(cell->weight>best->weight || (cell->weight==best->weight && cell->highNibble<best->highNibble)){
        reinterpret_cast<Rva00569543*>(this)->rva005695F2(reinterpret_cast<const ModuleData*>(best));best=cell;
       }else reinterpret_cast<Rva00569543*>(this)->rva005695F2(reinterpret_cast<const ModuleData*>(cell));
      }else best=cell;
     }
    }
    if(best){
     unsigned char mode=e->m_host==best?e->m_byte:m_grid->mode;
     best->method_005C908B(e->m_ref,mode);
     m_v40.push_back(reinterpret_cast<const ModuleData* const&>(best));
    }else {int handle=*reinterpret_cast<int*>(reinterpret_cast<char*>(e->m_ref.m_target)+0xC); reinterpret_cast<AudioCalls*>(TheAudio)->stop(handle);}
   }
   _STL::sort(reinterpret_cast<void**>(const_cast<ModuleData**>(m_v4C.begin())),reinterpret_cast<void**>(const_cast<ModuleData**>(m_v4C.end())),Rva00568721Cmp());
   const ModuleData **i=m_v4C.begin();
   for(;i!=m_v4C.end();++i){
    HostClass005C8E0A* const &cell=*reinterpret_cast<HostClass005C8E0A**>(const_cast<ModuleData**>(i));
    if(cell->weight<startWeight)break;
    if(cell->lowNibble<=0){
     Rva005C8876Position position=reinterpret_cast<LargeGroupAudioGridCell*>(cell)->getPreferredAudioPosition(m_grid);
     BfmePoolRef10 holder(reinterpret_cast<BfmePoolHolder88*>(new Rva0051D93(reinterpret_cast<const OpaqueRefElement4&>(m_owner),reinterpret_cast<const BfmeEventPositionView&>(position),0)));
     GameMessage *message=reinterpret_cast<GameMessage*>(holder.m_target);
     GameMessageList *handle=reinterpret_cast<AudioCalls*>(TheAudio)->start(&holder);
     message->friend_setList(handle);
     cell->method_005C908B(holder,0);
     m_v40.push_back(*i);
    }
   }
   m_v4C.clear();
  }
  for(const ModuleData **p=m_v40.begin();p!=m_v40.end();++p)reinterpret_cast<LargeGroupAudioGridCell*>(const_cast<ModuleData*>(*p))->update(m_grid);
 }
}

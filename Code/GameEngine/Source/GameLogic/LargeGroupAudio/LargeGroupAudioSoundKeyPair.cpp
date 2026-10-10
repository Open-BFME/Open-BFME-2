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
#include <vector>
#undef free
#include "ascii_string.h"

class ModuleData;

// BFME 2's Coord2D (MathCoord2D.h), kept under the pair name the grid lookup
// 0x005C8176 is pinned with.
struct FloatPair
{
	FloatPair() {}
 // Nontrivial coordinate return has the same two-float physical ABI.
 FloatPair(float a,float b):x(a),y(b){}
 operator float *() { return &x; }
	FloatPair(const FloatPair &o) : x(o.x), y(o.y) {}
	~FloatPair() {}
	__forceinline bool isExactlyEqualTo(const FloatPair &o) const { return x == o.x && y == o.y; }
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

class Rva005C8176 { public: void *rva005C8176(FloatPair p); };
class LargeGroupAudioGridCell
{
public:
	void addToWeight(unsigned short weight);
	void subtractFromWeight(unsigned short weight);
};
class Rva00569543 { public: void rva005695F2(const ModuleData *m); };
class HostClass005C815B
{
public:
	void method_005C836F(int key, float value);
 void method_005C839B(int,int);
};

struct Rva00568939Elem
{
	char m_00[8];
	float m_08;
	int m_0c;
	bool m_10;
	char m_pad11[3];
};

class Rva00568920
{
public:
	bool rva00568920() const;
	void rva00568939(int key);
private:
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
	char m_storage[0xC];
};
struct Rva003CDDB0Range { bool method(const Rva003CDDB0Range *other); };

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
class Rva00569373 {public: void rva00569373(void *);};
class Rva00569393 {public: void rva005694CD();};
class Rva00568F04 {public: void rva00568F04(void *);};
struct BfmeStringRecord00568CE0 { char opaque00[12]; Rva00568F04 *subject; char opaque10[4]; ~BfmeStringRecord00568CE0(); };
// Native transfer569BBC and WB unnamed twin1442480 establish version/Xfer
// protocol. WB-named1442010 establishes xferGridCellVector identity.
// ModuleData pointer vectors are opaque four-byte emitter views only.
struct VersionPair { unsigned char minimum,current; };
class Xfer {
public:
 virtual ~Xfer();
 virtual bool IsLoading() const;
 virtual bool IsStoring() const;
 virtual bool IsCRC() const;
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void xferPosition(FloatPair *);
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void xferUnsigned(unsigned *);
 virtual void xferInt(int *);
 virtual void xferWeight(unsigned short *);
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void xferBool(bool *);
};
class Rva00568A05 { public: Rva00568A05 &operator=(const Rva00568A05 &); };

struct Rva005688D2Base { char pad[0x10]; float scale; };
// Native 5688D2 returns its two-float output address in EAX and RET8.
// Its caller569ABD consumes that EAX as a live temporary with an empty
// destructor. This typed-return body is an emitted byte/relocation twin of
// the existing explicit-output provider; original source spelling is unknown.
// Native constant BC6C50 is -0.5f; scale belongs to owner+10 reached at this+3C.
class Rva005688D2 {
public:
 FloatPair rva005688D2(int mode);
private:
 char pad[0x3C]; Rva005688D2Base *base;
};
FloatPair Rva005688D2::rva005688D2(int mode)
{
 float first,second;
 if(mode==0 || mode==2)first=0;
 else first=base->scale * -0.5f;
 if(mode==0 || mode==1)second=0;
 else second=base->scale * -0.5f;
 return FloatPair(first,second);
}

class LargeGroupAudioSoundKeyPair;
// Retail passes one source pointer (RET4), keeps it in EDI, and reuses its
// dead argument home for the four-grid counter and then the output flag at
// byte3. This four-byte carrier models that observed ABI and storage reuse;
// it does not claim the original source-language argument type.
struct Rva0056A378Source {
 union { const LargeGroupAudioSoundKeyPair *source; int count; struct { char pad[3]; bool ok; } result; };
};
class LargeGroupAudioKeyMap {public: LargeGroupAudioKeyMap &operator=(const LargeGroupAudioKeyMap &);};
struct OpaqueRefElement4 { void *m_referent; OpaqueRefElement4 &operator=(const OpaqueRefElement4 &);};
class Rva005C8565 {public: void rva005C8565();};
struct Rva00569F0CVec { void *m_begin,*m_end,*m_pad; void rva00569F0C(void *,void *,bool *);};
class Rva005C865B {public: Rva005C865B(void *,float *); char opaque[0x1C];};
class Rva005C81D8 {public: void rva005C81D8(Rva005C8176 *,Rva005C8176 *,Rva005C8176 *);};
class LargeGroupAudioSoundKeyPair
{
public:
 LargeGroupAudioSoundKeyPair(LargeGroupAudioAudioMap *owner, const char *name);
 ~LargeGroupAudioSoundKeyPair();
 void rva0056A378(Rva0056A378Source arg);
 void rva00569BBC(Xfer *, VersionPair *);
 void allocateGrids();
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
 int unknown3C;
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

bool Rva00568920::rva00568920() const
{
	for (int i = 0; i < 4; ++i)
		if (m_vals[i] == 0)
			return false;
	return true;
}

void Rva00568920::rva00568939(int key)
{
	if (!rva00568920())
		return;
	for (Rva00568939Elem *e = m_begin14; e != m_end18; ++e) {
		if (e->m_0c != key)
			continue;
		if (e->m_10)
			return;
		HostClass005C815B **slot = m_slots;
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
	if (((Rva00568920 *)this)->rva00568920())
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
  m_grids[i]=reinterpret_cast<Rva005C8176 *>(new Rva005C865B(reinterpret_cast<void *>(unknown3C),reinterpret_cast<Rva005688D2 *>(this)->rva005688D2(i)));
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
	if (((Rva00568920 *)this)->rva00568920())
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
	if (((Rva00568920 *)this)->rva00568920())
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

LargeGroupAudioSoundKeyPair::LargeGroupAudioSoundKeyPair(LargeGroupAudioAudioMap *owner, const char *name):m_owner(),unknown3C((int)owner),m_totalWeight(0){
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
  if(s){s->rva005C8565(); ::operator delete(s); *slot=0;}
  ++slot;
 }while(--arg.count);
 reinterpret_cast<LargeGroupAudioKeyMap *>(this)->operator=(*reinterpret_cast<const LargeGroupAudioKeyMap *>(other));
 *reinterpret_cast<OpaqueRefElement4 *>(&m_owner)=*reinterpret_cast<const OpaqueRefElement4 *>(&other->m_owner);
 m_name.set(other->m_name);
 Rva00569F0CVec *v=reinterpret_cast<Rva00569F0CVec *>(&m_subjects);
 v->rva00569F0C(const_cast<BfmeStringRecord00568CE0 *>(other->m_subjects.begin()),const_cast<BfmeStringRecord00568CE0 *>(other->m_subjects.end()),&arg.result.ok);
 for(BfmeStringRecord00568CE0 *e=reinterpret_cast<BfmeStringRecord00568CE0 *>(v->m_begin);e!=m_subjects.end();++e)e->subject=0;
}

void LargeGroupAudioSoundKeyPair::rva00569BBC(Xfer *xfer, VersionPair *version)
{
 if(version->current>=3)xfer->xferInt(&m_totalWeight);
 else if(xfer->IsLoading())m_totalWeight=300000;
 bool hasGrids=reinterpret_cast<Rva00568920 *>(this)->rva00568920();
 if(version->current>=5){
  xfer->xferBool(&hasGrids);
  unsigned count=m_pendingAdds.size();
  xfer->xferUnsigned(&count);
  if(xfer->IsLoading()){
   m_pendingAdds.clear();
   if(count>0){
    FloatPair position;position.x=0;position.y=0;
    do{
     Rva0056887D record;
     record.rva0056887D(reinterpret_cast<const Rva0056887D &>(position),0);
     xfer->xferPosition(reinterpret_cast<FloatPair *>(&record));
     xfer->xferWeight(reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(&record)+8));
     m_pendingAdds.insert(reinterpret_cast<const Rva00568FE4Key &>(record));
    }while(--count);
   }
  }else{
   Rva00568FE4Multi::iterator it=m_pendingAdds.begin(),end=m_pendingAdds.end();
   for(;it!=end;++it){
    Rva0056887D record;
    reinterpret_cast<Rva00568A05 *>(&record)->operator=(*reinterpret_cast<const Rva00568A05 *>(&*it));
    xfer->xferPosition(reinterpret_cast<FloatPair *>(&record));
    xfer->xferWeight(reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(&record)+8));
   }
  }
 }else if(xfer->IsLoading()){
  m_pendingAdds.clear();hasGrids=m_totalWeight>0;
 }
 if(!hasGrids){
  if(xfer->IsLoading() && reinterpret_cast<Rva00568920 *>(this)->rva00568920())reinterpret_cast<Rva00569393 *>(this)->rva005694CD();
 }else{
  if(xfer->IsLoading() && !reinterpret_cast<Rva00568920 *>(this)->rva00568920())allocateGrids();
  for(int left=4,i=0;left;--left,++i)reinterpret_cast<HostClass005C815B *>(m_grids[i])->method_005C839B(reinterpret_cast<int>(xfer),reinterpret_cast<int>(version));
  xferGridCellVector(xfer,&m_v4C,version);
  xferGridCellVector(xfer,&m_v40,version);
 }
}

void LargeGroupAudioSoundKeyPair::xferGridCellVector(Xfer *xfer, void *storage, VersionPair *)
{
 _STL::vector<const ModuleData *> *vec=reinterpret_cast<_STL::vector<const ModuleData *> *>(storage);
 int count=static_cast<int>(vec->size());
 xfer->xferInt(&count);
 if(xfer->IsLoading()){vec->clear();vec->reserve(count);}
 for(int index=0;index<count;++index){
  FloatPair position;position.x=0;position.y=0;
  if(xfer->IsStoring())position=*reinterpret_cast<const FloatPair *>((*vec)[index]);
  xfer->xferPosition(&position);
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

// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /ICode/Libraries/Include/Lib /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include "Coord3D.h"
#include <vector>
// Import-inline: this unit's bfmealloc _Vector_base<Object*> dtor copy is not retail's
// EH-framed body (0x001F1609); its uses here are all inlined, so none is emitted.
class Object;
namespace _STL { template <> __declspec(dllimport) __forceinline _Vector_base<Object *, allocator<Object *> >::~_Vector_base() { if (this->_M_start != 0) this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start); } }
// Likewise vector<Object*>'s dtor: retail's out-of-line copy is the tail jump to
// that EH-framed body (0x001F22A3), so import-inline it too; throw() keeps the
// inlined copies free of EH states, as the plain inline form is.
namespace _STL { template <> __declspec(dllimport) __forceinline vector<Object *, allocator<Object *> >::~vector() throw() { _Destroy(this->_M_start, this->_M_finish); } }

struct BfmeE8
{
	float m_distSq;
	void *m_item;
};

struct Rva004C7621Pos
{
	char m_pad[0x38];
	float m_x;
	float m_y;
};

struct Rva004C734DElement;
struct Rva004C7621Range
{
 Rva004C734DElement *m_first;
 Rva004C734DElement *m_last;
};

void Rva00030830FreeAllocation(void *);
typedef bool (*BfmeE8Less)(const BfmeE8 &, const BfmeE8 &);
namespace _STL {
template <class T, class Pred> void sort(T, T, Pred);
template <> void sort<BfmeE8 *, BfmeE8Less>(BfmeE8 *, BfmeE8 *, BfmeE8Less);
// Native cleanup calls the potentially throwing game allocator, not the CRT.
template<> inline void allocator<BfmeE8>::deallocate(BfmeE8 *p,unsigned int) const
{ if(p) Rva00030830FreeAllocation(p); }
// The whole emitted 29-byte constructor and allocator-proxy call retain
// the already admitted E8 fold at 211E58. Its visible body proves the
// unnamed allocator temporary cannot escape; AIGroupRva00372571.cpp
// documents the same target-supported default-argument frame pattern.
template<> __declspec(noinline)
_Vector_base<BfmeE8,allocator<BfmeE8> >::_Vector_base(const allocator<BfmeE8> &a)
 : _M_start(0),_M_finish(0),_M_end_of_storage(a,0) {}
}
bool Rva0007B701Cmp(const BfmeE8 &, const BfmeE8 &);

class Object;
class Player;
struct Rva00372571Params
{
	const Coord3D *m_pos;
	bool m_addWaypoint;
	Object *m_ignoreObstacle;
	Object *m_target;
	const float *m_facing;
	int m_formationType;
	Player *m_player;
	bool m_attackMove;
};
#include "../../../../Include/GameLogic/AIGroup.h"
#include "../../../../Include/GameLogic/AI.h"
extern AI *TheAI;

// Two-pointer range view; the caller passes the vector member at entry +4.
// The capacity word is not read by this helper.
class BfmeVecAV
{
public:
	Object **m_begin;
	Object **m_end;
};

// Native 16-byte record: one Object* followed by a three-word vector.
// Only the first two vector words are used by the group-copy helper.
struct Rva004C734DElement
{
	Object *owner;
	_STL::vector<Object *> members;
 Rva004C734DElement(const Rva004C734DElement &);
 ~Rva004C734DElement() {}
};
struct ManTheWallsObjectPositionView
{
	unsigned char m_beforePosition[0x38];
	Coord3D m_position;
};

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
#include "../../../../Include/GameLogic/Module/SpecialPowerModule.h"


// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModule : public BehaviorModule, public SpecialPowerModuleInterface
{
public:
	SpecialPowerModule( Thing *thing, const ModuleData *moduleData );
public:
	virtual ~SpecialPowerModule();
};

#include "../../../Common/PartitionRangeQueryCallView.h"
// bfme link decl-only begin
namespace _STL { template <> void vector<BfmeE8, allocator<BfmeE8> >::_M_insert_overflow(BfmeE8 *, BfmeE8 const &, __false_type const &, unsigned int, bool); }
// bfme link decl-only end
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}
#include "../../../../Include/GameLogic/PartitionFilter.h"

// A KindOfMaskType as the mask filters copy it (0x0004543D).
#include "../../../../Include/Common/BfmeFixedStorage0004543D.h"

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second.
#include "../../../../Include/GameLogic/Rva0026119DFilter.h"
#include "../../../../Include/GameLogic/Rva002611BFFilter.h"
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

#include "../../../../Include/GameLogic/Module/Rva00045411BitSet.h"
#include "../../../../Include/GameClient/Drawable.h"
template<int Bits> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
#include "../../../../Include/GameLogic/Rva00260EB1Filter.h"


// Existing whole-map query provider returns this one-word handle. Native
// 4C78AF calls 6256F0 and the canonical next/dtor at 45623/4AA28;
// Provider names remain neutral, not original type claims. Every native
// caller calls the 34-byte /O1 teardown 4AA28 out of line; this unit emits
// that body (the payload storage dtor folds to 7FAB3, as in
// BfmeWideResultTeardown.cpp). BfmeResultSourceA's /O2 copy inlines the
// storage free and is not retail's.
struct BfmeWideResultPayload { void *m_storage; unsigned char m_unmodelled[0x0c]; int m_refCount; ~BfmeWideResultPayload(); };
struct BfmeResultA { void *m_value; BfmeResultA(); BfmeResultA(const BfmeResultA &);
 __declspec(noinline) ~BfmeResultA() {
  void *&payload = m_value;
  --static_cast<BfmeWideResultPayload *>(payload)->m_refCount;
  if (static_cast<BfmeWideResultPayload *>(payload)->m_refCount == 0)
   delete static_cast<BfmeWideResultPayload *>(payload);
 } };
#include "../../../../Include/Common/BfmeResultForwardB.h"
extern PartitionManager *ThePartitionManager;



// An object and a vector (ctor 0x004BA1B2).
class Rva004BA1B2
{
public:
	Rva004BA1B2();
	~Rva004BA1B2() {}
private:
	Object *m_owner;
	_STL::vector<Object *> m_members;
};

// Existing provider's opaque sixteen-byte record call view; target4C78AF
// passes the exact sixteen-byte Object/member-vector entry at this call.
struct Rva004C7878Record { Rva004C7878Record(); Rva004C7878Record(const Rva004C7878Record&); __declspec(noinline) ~Rva004C7878Record() { void *storage=*(void **)(bytes+4); if(storage) Rva00030830FreeAllocation(storage); } Rva004C7878Record &operator=(const Rva004C7878Record&); private: char bytes[16]; };
typedef _STL::vector<Rva004C7878Record> Rva004C78AFList;
namespace _STL { template<> void vector<Rva004C7878Record,allocator<Rva004C7878Record> >::push_back(const Rva004C7878Record &); }

namespace _STL {
template<> inline __declspec(noinline) _Vector_base<Object *,allocator<Object *> >::_Vector_base(const allocator<Object *> &a) : _M_start(0),_M_finish(0),_M_end_of_storage(a,0) {}
template<> inline void allocator<Object *>::deallocate(Object **p,unsigned int) const { if(p) free(p); }
template<> void vector<Object *,allocator<Object *> >::push_back(Object * const &);
template<> void vector<BfmeE8,allocator<BfmeE8> >::push_back(const BfmeE8 &);
}
// Keep the proven29B record-vector base as the exclusive provider, as the
// E8 specialization above does. An earlier library COMDAT emits14B and
// otherwise wins the link despite this caller reproducing native29.
namespace _STL {
template<> __declspec(noinline) _Vector_base<Rva004C7878Record,allocator<Rva004C7878Record> >::_Vector_base(const allocator<Rva004C7878Record> &a):_M_start(0),_M_finish(0),_M_end_of_storage(a,0) {}
template<> inline void allocator<Rva004C7878Record>::deallocate(Rva004C7878Record *p,unsigned int) const { if(p) Rva00030830FreeAllocation(p); }
template<> inline __declspec(noinline) void _Destroy<Rva004C7878Record *>(Rva004C7878Record *first,Rva004C7878Record *last) { for(;first!=last;++first) first->~Rva004C7878Record(); }
template<> inline __declspec(noinline) vector<Rva004C7878Record,allocator<Rva004C7878Record> >::~vector() { _Destroy(_M_start,_M_finish); }
}
class ManTheWallsSpecialPower : public SpecialPowerModule
{
public:
	ManTheWallsSpecialPower( Thing *thing, const ModuleData *moduleData );
	void rva004C70AD(BfmeVecAV *range, AIGroup *group);
	void rva004C7167(Rva004C734DElement *entry);
	void rva004C7621(Rva004C7621Range *, const Rva004C7621Pos *, _STL::vector<BfmeE8, _STL::allocator<BfmeE8> > *);
	BfmeVecAV *rva004C76AC(Rva004C7621Range *, const Rva004C7621Pos *);
	void rva004C7734(Rva004C7621Range *, BfmeWideResult *);
	bool rva004C78AF(Rva004C78AFList *);
public:
	// retail slot 4: the rowed ?getModuleNameKey@ManTheWallsSpecialPower@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

ManTheWallsSpecialPower::ManTheWallsSpecialPower( Thing *thing, const ModuleData *moduleData )
	: SpecialPowerModule( thing, moduleData )
{
}

// Native 4C70AD..4C70CF, RET8. The ManTheWalls helper 4C7167 restores
// its receiver into ECX before this call; WB 1268D00 does the same, and
// WB 1268D90 saves ECX as this. Thus the earlier free __stdcall claim
// reproduced bytes but omitted a real receiver. The receiver is unused here.
// Loop semantics were carried by BFME1 9e3be919b10ae956e3c8a13995e0d62f2be1d016
// game/GameEngine/Source/Common/BfmeConv1746.cpp; target calls AIGroup::add
// and independently establishes the two pointer fields and Object* elements.
// The original method and range-type names remain unknown.
void ManTheWallsSpecialPower::rva004C70AD(BfmeVecAV *range, AIGroup *group)
{
	for (Object **it = range->m_begin; it != range->m_end; ++it)
		group->add(*it);
}

// Native 4C7167..4C71D3 (108B, RET4); WB 1268D00. Creates an AI group,
// adds the entry's Object* range and issues the existing group command
// using its owner's +38 position, then destroys the group. All eight
// command-block fields, their write order and the zero source are native
// observations. Command semantics and the method's original name are open.
// The member helper ABI above accounts for the formerly unexplained ECX
// save/restore; the old free-function declaration omitted six native bytes.
void ManTheWallsSpecialPower::rva004C7167(Rva004C734DElement *entry)
{
	AIGroup *group = TheAI->createGroup();
	if (group)
	{
		rva004C70AD((BfmeVecAV *)&entry->members, group);
		Rva00372571Params params;
		params.m_formationType = -1;
		params.m_pos = &((ManTheWallsObjectPositionView *)entry->owner)->m_position;
		params.m_addWaypoint = false;
		params.m_ignoreObstacle = 0;
		params.m_target = 0;
		params.m_facing = 0;
		params.m_player = 0;
		params.m_attackMove = false;
		group->groupMoveToPosition(&params, 0);
		TheAI->destroyGroup(group);
	}
}

// Native 4C7621..4C76AC (139B, RET12). The 4C76AC caller restores
// ManTheWalls this; WB 1268940 and its 1268800 callee witness the member
// ABI independently. The native loop reads each 16-byte entry's Object
// position at +38/+3C and stores the address of its vector member at +4.
// BfmeE8 and range names remain neutral; the established distance-sort
// semantics are retained from the prior byte-exact C++ reconstruction.
void ManTheWallsSpecialPower::rva004C7621(Rva004C7621Range *range, const Rva004C7621Pos *ref, _STL::vector<BfmeE8, _STL::allocator<BfmeE8> > *out)
{
	float refs[3];
	refs[0] = ref->m_x;
	refs[1] = ref->m_y;
	Rva004C734DElement *rec = range->m_first;
	for (; rec != range->m_last; ++rec) {
		float *p = (float *)((char *)rec->owner + 0x38);
		float dx = p[0];
		float dy = p[1];
		dx -= refs[0];
		dy -= refs[1];
		BfmeE8 e;
		e.m_item = &rec->members;
		e.m_distSq = dy * dy + dx * dx;
		out->push_back(e);
	}
	_STL::sort(out->begin(), out->end(), &Rva0007B701Cmp);
}

// Native4C76AC..4C7734 (136B, RET8), WB1268940. Collect/sort the
// squared-distance candidates, then choose the first member-vector whose
// size is at most the ascending threshold 0..9. After ten passes the
// native body reads the nearest entry unconditionally. Method/type names
// stay neutral; control flow, E8 stride, vector offsets and cleanup are native.
BfmeVecAV *ManTheWallsSpecialPower::rva004C76AC(Rva004C7621Range *range,const Rva004C7621Pos *object) {
 _STL::vector<BfmeE8> candidates;
 rva004C7621(range,object,&candidates);
 for(int count=0;count<10;++count) {
  for(_STL::vector<BfmeE8>::iterator i=candidates.begin();i!=candidates.end();++i) {
   BfmeVecAV *members=(BfmeVecAV *)i->m_item;
   if((unsigned)(members->m_end-members->m_begin)<=(unsigned)count)
    return (BfmeVecAV *)i->m_item;
  }
 }
 return (BfmeVecAV *)candidates[0].m_item;
}

// Native4C7734..4C7767 (51B, RET8); WB1268CB0. Assign each yielded
// Object to the selected entry's member vector. Native ECX save/restore
// proves the primary ManTheWalls receiver; 1F211B owns Object* push_back.
void ManTheWallsSpecialPower::rva004C7734(Rva004C7621Range *range,BfmeWideResult *hits)
{
 for(Object *other=hits->next();other;other=hits->next())
 {
  _STL::vector<Object *> *members=(_STL::vector<Object *> *)rva004C76AC(range,(const Rva004C7621Pos *)other);
  members->push_back(other);
 }
}

// Native entry constructor22 is owned here by its retail caller; the
// Object-vector base29 also matches its existing retail provider. This keeps
// the allocator temporary from escaping and retains native EH transitions.
inline __declspec(noinline) Rva004BA1B2::Rva004BA1B2() {}

// Native4C78AF..4C799B (236B RET4); called by4C799B and WB1268A50.
// Query every Object matching kind115 and owner relationship4, then append
// its sixteen-byte Object/vector entry. The Object-vector member is proven
// by the exact same-file assignment and group helpers; opaque record and
// query facade names belong to existing providers. Original names are open.
// size()>0 preserves native SAR/SETNE; !=0 folds into a longer TEST mask.
bool ManTheWallsSpecialPower::rva004C78AF(Rva004C78AFList *out)
{
	BfmeResultA legacyHits = ((BfmeResultForwardB *)ThePartitionManager)->bfmeForwardResultB((int)
		Rva00260EB1Filter(*(Object **)((char *)this+8), 4, false).link(&Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 115),
			*(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE)));
	for (Object *other = ((BfmeWideResult *)&legacyHits)->next(); other; other = ((BfmeWideResult *)&legacyHits)->next()) {
		Rva004BA1B2 entry;
		((Rva004C734DElement *)&entry)->owner = other;
		out->push_back(*(const Rva004C7878Record *)&entry);
	}
	return out->size() > 0;
}

// Native4C799B..4C7AEB (336B RET4), WB1268A50. The saved receiver is
// secondary+10; subtract10 for primary helpers and read its owner at-8.
// No original virtual-slot or argument identity is inferred. This call view
// avoids claiming the earlier base-view order describes the full class.
// Gather kind115 entries, assign live kind109 hits (relationship4; reject
// the owner), and issue each nonempty entry's group command. Native copy29,
// sixteen-byte iteration, vector buffers and every cleanup are independent
// target observations; the three cleanup folds have whole-body/relocation/EH
// pin_admission proof. The argument is unused in both native and this body.
class ManTheWallsSpecialPowerSlotView {
public:
 void doSpecialPower(int unused);
};
void ManTheWallsSpecialPowerSlotView::doSpecialPower(int unused)
{
 Rva004C78AFList entries;
 ManTheWallsSpecialPower *primary=(ManTheWallsSpecialPower *)((char *)this-0x10);
 if(primary->rva004C78AF(&entries)) {
  Object *owner=*(Object **)((char *)this-8);
  BfmeResultA hits=((BfmeResultForwardB *)ThePartitionManager)->bfmeForwardResultB((int)
   Rva00260EB1Filter(owner,4,false).link(&Rva0026119DFilter())->link(
    Rva002611BFFilter(owner).link(&Rva0004584D(
     *(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0,109),
     *(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE))));
  primary->rva004C7734((Rva004C7621Range *)&entries,(BfmeWideResult *)&hits);
  for(Rva004C734DElement *i=(Rva004C734DElement *)entries.begin();i!=(Rva004C734DElement *)entries.end();++i) {
   Rva004C734DElement entry(*i);
   if(entry.members.size()>0) primary->rva004C7167(&entry);
  }
 }
}

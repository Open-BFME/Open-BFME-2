// cl: /Ireference/shims/bfme2_ascii /O1 /Ob1 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
#include <new>
#include <hash_map>
#include <cstddef>
// Mutable bucket access is visible so the erase backend has its native shape.
// The earlier native external provider remains selected under normal COMDAT policy.
namespace _STL {
template <> inline void *&_STL::vector<void*>::operator[](size_t n) { return *(this->_M_start + n); }
}
// Visible ordinary size access lets native bucket helpers inline the storage
// operation; normal COMDAT policy preserves the earlier selected provider.
namespace _STL {
template <> inline size_t vector<void*>::size() const { return size_t(this->_M_finish - this->_M_start); }
}
// Suppress this TU's non-retail vector<void*> begin/end copies (family2-LK3 rows 6/9):
// the retail copies serve the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}
// Suppress the TU's non-retail const-begin copy (row 54 family-LK3): the
// /Od retail copy in stlport_vector_voidptr.cpp serves the link instead.
namespace _STL {
template <> vector<void *>::const_iterator _STL::vector<void *>::begin() const;
}
#include "ascii_string.h"
// The ordinary const subscript is visible for the same native helper shape.
// Its external copy is checked against the existing selected provider.
namespace _STL { template <> inline void *const &vector<void *>::operator[](size_t n) const { return *(this->_M_start + n); } }
// ?rva0020EE29@Rva0020EE29@@QAEXXZ @0x0020EE29 51B
// Clears each entry of the pointer vector at inner+0x2c/+0x30 (inner = *(this+8))
// by calling rowed ?rva003F209C@Rva003F209C@@QAEXXZ. Evidence: retail
// (end-begin)>>2 count with reload-each-iteration loop over [eax+edi*4];
// same inner layout as caller 0x0020F795 second loop over [esi+0x2c].

class Rva003F209C
{
public:
	void rva003F209C();
	void rva003F20E5(int a1, int a2);
};

struct Rva0020EE29Inner
{
	char m_pad[0x2c];
	Rva003F209C **m_begin;
	Rva003F209C **m_end;
	void rva0020F5B3();
};

// ?rva0020FB8B@Rva0020EE29@@QAEXPAURva0020FB8BNode@@@Z @0x0020FB8B 132B
// Moves the +0x14 entry whose key matches the argument out of that vector
// and into the +0x20 ModuleData vector: searches by the argument's +0x34
// against each entry's indirect +0x34, notifies the VA 0x00DFE1C8 singleton
// (rowed-pending 0x00212655) with the argument's +0x30, reserves the source
// count in the destination, pushes the argument, and erases the found slot.
// Evidence: retail peeled search with the pointer advance plus the separate
// erase index; the reserve count reads the source vector; the push_back
// spills the argument home before taking its address (by-ref const); the
// erase takes the single begin+index position. The +0x20 12-byte span fits
// exactly before the +0x2c members 0x0020F795 zeroes, so it is modeled as a
// three-word vector. Node identity is unproven (recursive key view).
struct Rva0020FB8BKey
{
	char m_pad[0x34];
	int m_34;
};

struct Rva0020FB8BNode
{
	Rva0020FB8BKey *m_00;
	char m_pad[0x2C];
	int m_30;
	int m_34;
};

struct Rva0020FB8BVec14
{
	Rva0020FB8BNode **m_begin;
	Rva0020FB8BNode **m_end;
	void **vecErase(void **pos);
};

struct Rva0020FB8BVec20
{
	void *m_begin;
	void *m_end;
	void *m_storage;
	void vecReserve(unsigned n);
	void vecPushBack(void *&p);
};


class Rva0020EE29
{
public:
	void rva0020EE29();
	void rva0020F795();
	void rva0020F483();
	void rva002100E6(void *a1, void *a2);
	void rva002101C6(void *a1);
	bool rva0020F91D(void *a1, void *a2, void *a3);
	void *rva0020F9F6(void *a1, void *a2, void *filter);
	void *rva0020FAEA(float *a1, void *a2);
	void *rva0020FAB4(int a1, int a2);
	void rva0020FB8B(Rva0020FB8BNode *arg);

private:
	char m_pad[8];
	Rva0020EE29Inner *m_inner;
	int m_0C;
	int m_10;
	Rva0020FB8BVec14 m_14;
	char m_pad1C[4];
	Rva0020FB8BVec20 m_20;
	int m_2C;
	int m_30;
};

void Rva0020EE29::rva0020EE29()
{
	Rva0020EE29Inner *inner = m_inner;
	if (!inner)
		return;
	for (unsigned i = 0; i < (unsigned)(((char *)inner->m_end - (char *)inner->m_begin) >> 2); ++i)
		inner->m_begin[i]->rva003F209C();
}

// ?rva0020F9F6@Rva0020EE29@@QAEPAXPAX00@Z @0x0020F9F6 190B
// Finds the first entry of the inner pointer vector at +0x2c/+0x30 accepted
// by the rowed-pending predicate at 0x0020F91D, skipping the excluded entry:
// with a non-null filter it first tests the filter itself, then every other
// entry; with a null filter it tests every entry. Answers the entry or null.
// Evidence: retail reload-each-iteration count loop over [esi+0x2c] (same as
// rva0020EE29 above); four call sites of 0x0020F91D with this in ecx and the
// (candidate, a1, a2) stack shape; the +0x268 gate on the VA 0x00DFE1C8
// singleton; the zero-then-counter shared by the null checks and both loops.
// The candidate and argument pointers are opaque here (callers pass two
// 24-byte float blocks); the vector element type matches rva0020EE29 above.
struct Rva00DFE1C8Host
{
	char m_pad[0x268];
	int m_268;
	void rva00212655(int val);
	void rva002122D4(void *a);
};
// Bind to the existing data-ledger owner; keep the retail access view local.
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

// The complete 190B ray search is owned by LivingWorldCandidateRaySearch.cpp.
// Keep its declaration above for this unit's already verified callers.

// ?OnTurnEnding@LivingWorldRegionManager@@UAEXHH@Z @0x0020FB41 74B
// Resets the +0xC/+0x10 state and runs every entry of the inner pointer
// vector at +0x8 (+0x2c/+0x30) through rowed ?rva003F20E5 (two stack args,
// this = entry), after the pinned ?rva0020F685 on the whole object.
// A virtual of the two-slot table 0x00BE4350 that the manager's ctor and dtor
// (0x0021042D, 0x00210B38) store at +4, slot 1; WorldBuilder's dtor stores
// the twin table 0x01E25EBC at +4 too, whose slot 1 is its
// LivingWorldRegionManager::OnTurnEnding (own assert name). MSVC passes such
// an override the +4 subobject as this, hence retail's lea ecx,[esi-4] for
// the whole-object call and the members read 4 below their offsets. Evidence:
// the zero register doubles as the loop counter; reload-each-iteration count
// loop over [esi+0x2c] like rva0020EE29 above. Argument meanings are unproven
// (passed opaquely to the entry method).
class Rva0020F685
{
public:
	void rva0020F685();
};

#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include "../../../../GameEngine/Include/Common/RegionTurnObserverView.h"
#include "../../../../GameEngine/Include/GameLogic/LivingWorldRegionManager.h"

void LivingWorldRegionManager::OnTurnEnding(int a1, int a2)
{
	((Rva0020F685 *)this)->rva0020F685();
	field0C = 0;
	field10 = 0;
	// Retail advances past the inner header once and reads begin/end from
	// the advanced pointer ([esi]/[esi+4]), so the traversal below addresses
	// the begin/end pair through &m_begin rather than re-adding +0x2c.
	Rva003F209C ***bounds = &((Rva0020EE29Inner *)field08)->m_begin;
	for (unsigned i = 0; i < (unsigned)(((char *)bounds[1] - (char *)bounds[0]) >> 2); ++i)
		bounds[0][i]->rva003F20E5(a1, a2);
}

// ?rva0020FAEA@Rva0020EE29@@QAEPAXPAMPAX@Z @0x0020FAEA 87B
// Builds the two search-key blocks on the stack (six floats at B, with A
// aliasing its tail) and runs the 0x0020F9F6 finder over the inner vector.
// Evidence: retail movss fills from the [ebp+8] float pair plus the .rdata
// floats 10000.0f (VA 0x00BC8970) and -1.0f (VA 0x00BBB9AC, both verified by
// the float gate); the early arg2 push and the A-then-B push order match the
// (candidate, A, B) finder shape. EAX carries the finder result through
// leave/ret 8; 0x00318C32 stores it at +0x8C and 0x002B2858 compares it
// against the requested region. The return type must therefore be a pointer.
void *Rva0020EE29::rva0020FAEA(float *a1, void *a2)
{
	float data[6];
	data[0] = a1[0];
	data[1] = a1[1];
	data[2] = 10000.0f;
	data[3] = 0.0f;
	data[4] = 0.0f;
	data[5] = -1.0f;
	return rva0020F9F6(data, data + 3, a2);
}

// ?rva0020FAB4@Rva0020EE29@@QAEXHH@Z @0x0020FAB4 54B
// Queries the VA 0x00DFEF18 singleton (vtable slot 13) to fill two 12-byte
// out-blocks on the stack, then runs the 0x0020F9F6 finder (pinned) over the
// inner vector with those blocks. Evidence: retail lea/push of the two
// ebp-0x18/ebp-0xc blocks around the indirect slot-13 call, then the same
// (B, A, arg2) push shape 0x0020FAEA uses for the finder; return discarded.
// Block contents and the query identity are unproven (out-params).
class Rva00DFEF18QueryHost
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13(int a1, void *bBlock, void *aBlock);
	void *rva002BFDAE(void *a);
};

class LivingWorld; extern LivingWorld *TheLivingWorld;

struct Rva0020FAB4Block
{
	char m_data[12];
};

// Caller5C98C0 tests EAX and reads returned item+1A2; the native finder
// result is forwarded intact. The former void declaration discarded this ABI.
void *Rva0020EE29::rva0020FAB4(int a1, int a2)
{
	Rva0020FAB4Block bBlock;
	Rva0020FAB4Block aBlock;
	((Rva00DFEF18QueryHost *)TheLivingWorld)->v13(a1, &bBlock, &aBlock);
	return rva0020F9F6(&bBlock, &aBlock, (void *)a2);
}

// ?ActivateRegion@Rva002104C7@@QAE_NPAX0@Z @0x002104C7 38B
// Looks up the first handle through the rowed member 0x002104B6 on this and,
// when found, runs the member 0x0020E374 on this with the lookup result and
// the second handle. Answers false on a null lookup and true otherwise (the
// member result is discarded). Evidence: retail pushes the lookup arg and
// calls 0x002104B6 with the incoming ecx (thiscall on this, which reads
// [ecx+8]); the (p, a2) push order puts the lookup result first.
class Rva002104C7
{
public:
	bool ActivateRegion(void *a1, void *a2);
	void rva0020E374(void *a1, void *a2);
};

class Rva00210390;
class Rva002104B6
{
public:
	void *rva002104B6(void *a1);

private:
	char m_pad[8];
	Rva00210390 *m_08;
};

bool Rva002104C7::ActivateRegion(void *a1, void *a2)
{
	void *p = ((Rva002104B6 *)this)->rva002104B6(a1);
	if (!p)
		return false;
	rva0020E374(p, a2);
	return true;
}

// ?rva00210390@Rva00210390@@QAEPAXPBVAsciiString@@@Z @0x00210390 38B
// Looks up the AsciiString key in the bucket table at this+0x38 through the
// rowed Rva00056F61::rva0041534B and answers the found node's payload at
// +0x8, or null when the lookup misses. Evidence: retail add ecx,0x38 into
// the rowed call with the key and a hidden 8-byte out-iterator; the test/je
// on the returned node plus the [node+8] load (the payload slot the rowed
// TU documents). Iterator and key types mirror the rowed TU (receive-only;
// no construction here, so no user ctor).
class AsciiString;
class Rva00056F61;
#include "../../../../GameEngine/Include/GameClient/Rva0041534BIter.h"
struct Rva00210390Node
{
	char m_pad[8];
	void *m_payload;
};

class Rva00210390
{
public:
	void *rva00210390(const AsciiString *key);
};

#include "../../../../GameEngine/Include/GameClient/Rva00056F61.h"

void *Rva00210390::rva00210390(const AsciiString *key)
{
	Rva0041534BIter it = ((Rva00056F61 *)((char *)this + 0x38))->rva0041534B(key);
	if (it.m_node)
		return ((Rva00210390Node *)it.m_node)->m_payload;
	return 0;
}

// ?rva002104B6@Rva002104B6@@QAEPAXPAX@Z @0x002104B6 12B
// Forwards to the rowed 0x00210390 bucket lookup on the embedded object at
// +0x8 with the same key, or answers null when it is absent. Evidence:
// retail tests [ecx+8] then tail-jumps (no frame, args already in place) to
// the rowed body; the null path zeroes eax and callee-cleans the one arg.

void *Rva002104B6::rva002104B6(void *a1)
{
	if (!m_08)
		return 0;
	return m_08->rva00210390((const AsciiString *)a1);
}

// ?rva0020E374@Rva002104C7@@QAEXPAX0@Z @0x0020E374 13B
// This-retargeting forward: runs the rowed-pending 0x003EFDF5 with the
// first stack slot as its object and the second as its argument, discarding
// this. Evidence: retail pushes [esp+8] then moves the other [esp+8] to ecx
// (the slot shift after the push); callee-clean ret 8.
class Rva003EFDF5Host
{
public:
	void rva003EFDF5(void *a);
};

void Rva002104C7::rva0020E374(void *a1, void *a2)
{
	((Rva003EFDF5Host *)a1)->rva003EFDF5(a2);
}

// ?rva0020FD42@Rva0020FD42@@QAEXPAX0@Z @0x0020FD42 61B
// Clears the argument's +0x0 vector through the rowed-pending two-arg erase
// at 0x00532803, then notifies via the rowed-pending 0x003EFC1C on the
// object at [this+8]+0x4c with the argument's +0x12c dword, skipping out
// when any link is null. The first stack arg is unused by retail. Evidence:
// retail pushes [esi+4]/[esi] with this=arg into the erase; the three
// test/je null gates in order; the final member call shape.
// The folded four-byte-element erase at 0x00532803 is bound through an
// existing provider spelling; the argument's element type is unproven.
struct Rva005334A4Element;
namespace _STL {
template <> Rva005334A4Element *vector<Rva005334A4Element>::erase(Rva005334A4Element *, Rva005334A4Element *);
}

struct Rva0020FD42Arg
{
	_STL::vector<Rva005334A4Element> m_vec;
	char m_pad[0x120];
	int m_12C;
};

struct Rva0020FD42P
{
	char m_pad[0x4C];
	struct Rva003EFC1CHost *m_4C;
};

struct Rva003EFC1CHost
{
	void rva003EFC1C(int val, void *arg);
};

class Rva0020FD42
{
public:
	void rva0020FD42(void *a1, void *a2);
	void rva002100E6(void *a1, void *a2);
	void rva002101C6(void *a1);

private:
	char m_pad[8];
	Rva0020FD42P *m_08;
};

void Rva0020FD42::rva0020FD42(void *a1, void *a2)
{
	Rva0020FD42Arg *arg = (Rva0020FD42Arg *)a2;
	arg->m_vec.erase(arg->m_vec.begin(), arg->m_vec.end());
	Rva0020FD42P *p = m_08;
	if (!p)
		return;
	Rva003EFC1CHost *q = p->m_4C;
	if (!q)
		return;
	// Retail checks the first arg slot here and reuses that register for the
	// +0x12c read, so both go through one checked copy (a1 may be a distinct
	// instance of the same layout rather than arg itself).
	Rva0020FD42Arg *a1s = (Rva0020FD42Arg *)a1;
	if (!a1s)
		return;
	q->rva003EFC1C(a1s->m_12C, arg);
}

// ?rva002101C6@Rva0020EE29@@QAEXPAX@Z @0x002101C6 60B
// Runs the argument's vtable slot-10 with a two-byte flags block, then
// runs the rowed-pending same-class 0x002100E6 twice (once per member
// vector at +0x14/+0x20) with the argument. Evidence: retail lea+push of
// the ebp-4 block with this=arg into the indirect slot-10 call; the two
// lea/push/mov/call sequences into 0x002100E6 with this passthrough. Slot
// and flag meanings are unproven.
class Rva002101C6Arg
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10(void *b);
};

void Rva0020EE29::rva002101C6(void *arg)
{
	unsigned char b[2];
	b[0] = 1;
	b[1] = 1;
	((Rva002101C6Arg *)arg)->v10(b);
	rva002100E6(arg, &m_14);
	rva002100E6(arg, &m_20);
}

// LivingWorldRegionManager::loadPostProcess at 0x002102CA.
// Runs every entry of the +0x8 inner vector through its vtable slot-1, runs
// the rowed-pending same-class 0x0020F483, and tail-jumps to the
// rowed-pending inner 0x0020F5B3. Evidence: retail bounds-pointer traversal
// with the reload-each-iteration count (rowed-EE29 idiom, indexed here
// because the loop body calls out); the frameless-compatible tail jump
// after restoring the saves; no null check on the inner. The slot-1 callee
// goes through a stand-in element type (vtable layout only).
class Rva002102CAElem
{
public:
	virtual void v00();
	virtual void v01();
};

void LivingWorldRegionManager::loadPostProcess()
{
	Rva002102CAElem ***bounds = (Rva002102CAElem ***)&((Rva0020EE29Inner *)field08)->m_begin;
	for (unsigned i = 0; i < (unsigned)(((char *)bounds[1] - (char *)bounds[0]) >> 2); ++i)
		bounds[0][i]->v01();
	reinterpret_cast<Rva0020EE29 *>(this)->rva0020F483();
	((Rva0020EE29Inner *)field08)->rva0020F5B3();
}

// ?rva0020F795@Rva0020EE29@@QAEXXZ @0x0020F795 157B
// Resets a slice of members, then when the +0x8 inner is present notifies
// per entry and drains it: the first loop reports every +0x14 entry's +0x30
// to the VA 0x00DFE1C8 singleton (rowed-pending 0x00212655); then the
// rowed-pending 0x0020F685 and the rowed clear run on this; the gated
// rowed-pending 0x003EF1B8 fires when the singleton's +0x268 is set; the
// second loop runs every inner entry through the rowed-pending 0x003F3F27.
// Evidence: retail reload-each-iteration counts in both loops (calls inside
// block strength reduction); the member zeroes before the inner check with
// the +0x8 null store running on both paths; ebp used as a saved zero, not
// a frame. Element identities are unproven (address-derived views).
class Rva003EF14A
{
public:
	void rva003EF1B8();
};

class Rva003F3F27
{
public:
	void rva003F3F27();
};

void Rva0020EE29::rva0020F795()
{
	Rva0020EE29 *self = this;
	for (unsigned i = 0; i < (unsigned)(((char *)self->m_14.m_end - (char *)self->m_14.m_begin) >> 2); ++i)
		((Rva00DFE1C8Host *)TheLivingWorldManager)->rva00212655(self->m_14.m_begin[i]->m_30);
	((Rva0020F685 *)self)->rva0020F685();
	self->rva0020EE29();
	self->m_0C = 0;
	self->m_10 = 0;
	self->m_2C = 0;
	self->m_30 = 0;
	if (self->m_inner) {
		if (((Rva00DFE1C8Host *)TheLivingWorldManager)->m_268)
			((Rva003EF14A *)((Rva00DFE1C8Host *)TheLivingWorldManager)->m_268)->rva003EF1B8();
		Rva003F3F27 ***bounds = (Rva003F3F27 ***)&self->m_inner->m_begin;
		for (unsigned j = 0; j < (unsigned)(((char *)bounds[1] - (char *)bounds[0]) >> 2); ++j)
			bounds[0][j]->rva003F3F27();
	}
	self->m_inner = 0;
}

class Rva003FD14D;
// LINK: rva002C004F's rowed home is Rva002BFF5A (Rva002C004FErase.cpp, 0x2C004F);
// the old Rva002D3627Host spelling named an unresolved symbol. The global keeps
// its pointer type, the call binds the rowed member through a cast.
class Rva002D3627Host;
#include "../../../../GameEngine/Include/Common/Rva002BFF5A.h"

class Rva00212655Virt { public: virtual void *v00(int); };

// Complete native 212655..2126BB and WB B608E0. The map at +218 is
// established by the verified CreateBeaconObject body. Resolve by id,
// report the beacon's string at +4 on the DFEF18 singleton, invoke its
// slot-zero cleanup with zero, scalar-delete the result, then erase the
// saved iterator. The original method name remains unproven.
void Rva00DFE1C8Host::rva00212655(int arg)
{
    _STL::hash_map<int,Rva003FD14D*> &beacons = *(_STL::hash_map<int,Rva003FD14D*>*)((char*)this+0x218);
    _STL::hash_map<int,Rva003FD14D*>::iterator it = beacons.find(arg);
    if (it != beacons.end()) {
        Rva003FD14D *beacon = it->second;
        ((Rva002BFF5A *)((Rva002D3627Host *)TheLivingWorld))->rva002C004F(((AsciiString*)((char*)beacon+4))->str());
        Rva00212655Virt *view = (Rva00212655Virt*)beacon;
        void *allocation = view ? view->v00(0) : 0;
        ::operator delete(allocation);
        beacons.erase(it);
    }
}

// 0x00211570 is owned by its existing retail source unit.


// ?rva002115D0@Rva002115D0@@QAEXPAX0@Z @0x002115D0 28B
// Uses the master-pinned StringBase<char>(const char*) constructor at
// 0x0037BA0 on the first handle with the existing g_bfmeEmptyF9 symbol, then
// answers the handle. The second handle is unused by retail; the zeroed slot
// is dead. Target evidence: the call site sets ecx from the first handle and
// pushes the empty-string address. The 28-byte hidden-result construction is
// already rowed in GameClient/System/Rva002115D0String.cpp.
extern char g_bfmeEmptyF9[];

class Rva002115D0
{
public:
	void *rva002115D0(void *a1, void *a2);
};


// Native21BEC1 preserves an incoming const CreateAHeroClass receiver and
// returns the subclass lookup pointer. Keep its address-placeholder identifier;
// the public declaration is a TU-local callable view, not original visibility.
#include "../../../../GameEngine/Include/GameLogic/CreateAHeroManager.h"

class CreateAHeroManager::CreateAHeroSubClass
{
public:
    int *rva0021BD22(int key) const;
};

class CreateAHeroManager::CreateAHeroClass
{
private:
    const CreateAHeroSubClass *rva00219B9E(unsigned int subClassIndex) const;
public:
    int *Rva0021BEC1(int a1, int a2) const;
};

int *CreateAHeroManager::CreateAHeroClass::Rva0021BEC1(int a1, int a2) const
{
    const CreateAHeroSubClass *subClass = rva00219B9E((unsigned int)a2);
    return subClass ? subClass->rva0021BD22(a1) : 0;
}

// ?rva002103B6@Rva002103B6@@QAEXPBVAsciiString@@@Z @0x002103B6 119B
// Rebuilds the +0x2c vector from the +0x20 vector through the rowed
// 0x00210390 lookup: range-erases and reserves the destination, then per
// source entry looks up with the passed key object, maps a hit to its +0x12c
// (else -1), and pushes that through the rowed-pending 0x002E01C6 on the
// destination. Evidence: retail erase/reserve/count shapes; the rowed call
// with this=key-arg; the hit/-1 select; the &local push into 0x002E01C6;
// reload-each-iteration count (calls inside). Vector identities unproven.
struct Rva002103B6Vec
{
	void **m_begin;
	void **m_end;
	void *m_storage;
	void **vecEraseR(void **first, void **last);
	void vecReserveR(unsigned n);
	void vecPushR(int *v);
};

class Rva00210D6DElem
{
public:
	void rva003F0DC6();
};

class Rva00210D6DVec5C
{
public:
	void **m_begin;
	void **m_end;
};

class LivingWorldRegionBonusRule
{
public:
	void CacheRegionIDs(Rva00210390 *a1);
};

class Rva002103B6
{
public:
	void rva002103B6(Rva00210390 *a1);
	void rva002106D6();

private:
	char m_pad[0x20];
	Rva002103B6Vec m_20vec;
	Rva002103B6Vec m_2Cvec;
	char m_pad38[0x24];
	Rva00210D6DVec5C m_5Cvec;
};

// ?rva002106D6@Rva002103B6@@QAEXXZ @0x002106D6 84B
// Runs every entry of the +0x2c vector through the rowed-pending 0x003F0DC6,
// then every entry of the +0x5c vector through the rowed 0x002103B6 with
// this as its key object. Evidence: retail reload-each-iteration counts in
// both loops (calls inside); the member calls with this=entry; the shared
// +0x2c vector with the 0x002103B6 rebuilder itself. Key-object identity is
// provisional (address-derived casts).

void Rva002103B6::rva002106D6()
{
	// Counts go through pointers (retail end-first); bodies stay direct.
	Rva002103B6Vec *vec2C = &m_2Cvec;
	for (unsigned i = 0; i < (unsigned)(((char *)vec2C->m_end - (char *)vec2C->m_begin) >> 2); ++i)
		((Rva00210D6DElem *)m_2Cvec.m_begin[i])->rva003F0DC6();
	Rva00210D6DVec5C *vec5C = &m_5Cvec;
	for (unsigned j = 0; j < (unsigned)(((char *)vec5C->m_end - (char *)vec5C->m_begin) >> 2); ++j)
		((LivingWorldRegionBonusRule *)m_5Cvec.m_begin[j])->CacheRegionIDs((Rva00210390 *)this);
}

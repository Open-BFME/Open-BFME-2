// ?rva0020F832@Rva0020EE29@@QAE_NPAX0@Z
// partial score=0.85 date=2026-10-08
// ?rva0020F832@Rva0020EE29@@QAE_NPAX0@Z
// partial score=0.85 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /Ob1 /vmb /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB
#include <new>
#include "ascii_string.h"
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
	void rva0020F685();
	void rva0020F795();
	void rva0020F483();
	void rva002100E6(void *a1, void *a2);
	void rva002101C6(void *a1);
	void rva002102CA();
	bool rva0020F91D(void *a1, void *a2, void *a3);
	void *rva0020F9F6(void *a1, void *a2, void *filter);
	bool rva0020F832(void *entry, void *state);
	void rva0020ED8E(void *entry, void *state);
	void rva0020FAEA(float *a1, void *a2);
	void rva0020FAB4(int a1, int a2);
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

// ?rva0020F9F6@Rva0020EE29@@QAEPAXPAX00@Z present-unmatched
void *Rva0020EE29::rva0020F9F6(void *a1, void *a2, void *filter)
{
	Rva0020EE29Inner *inner = m_inner;
	unsigned i = 0;
	if (!inner)
		return 0;
	if (((Rva00DFE1C8Host *)TheLivingWorldManager)->m_268 == (int)i)
		return 0;
	if (filter != 0) {
		if (rva0020F91D(filter, a1, a2))
			return filter;
		for (i = 0; i < (unsigned)(((char *)inner->m_end - (char *)inner->m_begin) >> 2); ++i) {
			if (inner->m_begin[i] == filter)
				continue;
			if (rva0020F91D(inner->m_begin[i], a1, a2))
				return inner->m_begin[i];
		}
		return 0;
	}
	for (i = 0; i < (unsigned)(((char *)inner->m_end - (char *)inner->m_begin) >> 2); ++i) {
		if (rva0020F91D(inner->m_begin[i], a1, a2))
			return inner->m_begin[i];
	}
	return 0;
}

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
class Rva0020FB41Outer
{
public:
	void rva0020F685();
};

class Rva0020FB41Primary
{
public:
	virtual void v00();
};

class Rva00BE4350Turn
{
public:
	virtual void rva0020EB07(int a1, int a2);
	virtual void OnTurnEnding(int a1, int a2);
};

class LivingWorldRegionManager : public Rva0020FB41Primary, public Rva00BE4350Turn
{
public:
	virtual void OnTurnEnding(int a1, int a2);

private:
	Rva0020EE29Inner *m_08;
	int m_0C;
	int m_10;
};

void LivingWorldRegionManager::OnTurnEnding(int a1, int a2)
{
	((Rva0020FB41Outer *)this)->rva0020F685();
	m_0C = 0;
	m_10 = 0;
	// Retail advances past the inner header once and reads begin/end from
	// the advanced pointer ([esi]/[esi+4]), so the traversal below addresses
	// the begin/end pair through &m_begin rather than re-adding +0x2c.
	Rva003F209C ***bounds = &m_08->m_begin;
	for (unsigned i = 0; i < (unsigned)(((char *)bounds[1] - (char *)bounds[0]) >> 2); ++i)
		bounds[0][i]->rva003F20E5(a1, a2);
}

// ?rva0020FAEA@Rva0020EE29@@QAEXPAMPAX@Z @0x0020FAEA 87B
// Builds the two search-key blocks on the stack (six floats at B, with A
// aliasing its tail) and runs the 0x0020F9F6 finder over the inner vector.
// Evidence: retail movss fills from the [ebp+8] float pair plus the .rdata
// floats 10000.0f (VA 0x00BC8970) and -1.0f (VA 0x00BBB9AC, both verified by
// the float gate); the early arg2 push and the A-then-B push order match the
// (candidate, A, B) finder shape; return discarded by retail.
void Rva0020EE29::rva0020FAEA(float *a1, void *a2)
{
	float data[6];
	data[0] = a1[0];
	data[1] = a1[1];
	data[2] = 10000.0f;
	data[3] = 0.0f;
	data[4] = 0.0f;
	data[5] = -1.0f;
	rva0020F9F6(data, data + 3, a2);
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

extern Rva00DFEF18QueryHost *g_00DFEF18query;
#pragma comment(linker, "/alternatename:?g_00DFEF18query@@3PAVRva00DFEF18QueryHost@@A=?g_00DFEF18@@3PAVRva002D3627Host@@A")

struct Rva0020FAB4Block
{
	char m_data[12];
};

void Rva0020EE29::rva0020FAB4(int a1, int a2)
{
	Rva0020FAB4Block bBlock;
	Rva0020FAB4Block aBlock;
	g_00DFEF18query->v13(a1, &bBlock, &aBlock);
	rva0020F9F6(&bBlock, &aBlock, (void *)a2);
}

// ?rva0020FB8B@Rva0020EE29@@QAEXPAURva0020FB8BNode@@@Z present-unmatched
void Rva0020EE29::rva0020FB8B(Rva0020FB8BNode *arg)
{
	unsigned i = 0;
	Rva0020FB8BVec14 *vec = &m_14;
	Rva0020FB8BNode **pp = (Rva0020FB8BNode **)vec->m_begin;
	for (; i < (unsigned)(((char *)vec->m_end - (char *)vec->m_begin) >> 2); ++i, ++pp) {
		if (arg->m_34 == (*pp)->m_00->m_34)
			goto found;
	}
	goto end;
found:
	((Rva00DFE1C8Host *)TheLivingWorldManager)->rva00212655(arg->m_30);
	m_20.vecReserve((unsigned)(((char *)vec->m_end - (char *)vec->m_begin) >> 2));
	m_20.vecPushBack((void *&)arg);
	vec->vecErase((void **)((char *)vec->m_begin + i * 4));
end:
	;
}

// ?rva002104C7@Rva002104C7@@QAE_NPAX0@Z @0x002104C7 38B
// Looks up the second handle through the rowed-pending free 0x002104B6 and,
// when found, runs the rowed-pending member 0x0020E374 on this with the
// first handle and the lookup result. Answers false on a null lookup and
// true otherwise (the member result is discarded). Evidence: retail pushes
// the lookup arg with no ecx setup (free call) but passes this to the
// member; the (p, a2) push order puts the lookup result first.
class Rva002104C7
{
public:
	bool rva002104C7(void *a1, void *a2);
	void rva0020E374(void *a1, void *a2);
};

void *__stdcall rva002104B6(void *a1);

bool Rva002104C7::rva002104C7(void *a1, void *a2)
{
	void *p = rva002104B6(a1);
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
struct Rva0041534BIter
{
	void *m_node;
	Rva00056F61 *m_table;
};
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

class Rva00056F61
{
public:
	Rva0041534BIter rva0041534B(const AsciiString *key);
};

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
class Rva002104B6
{
public:
	void *rva002104B6(void *a1);

private:
	char m_pad[8];
	Rva00210390 *m_08;
};

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
struct Rva0020FD42Arg
{
	void **m_begin;
	void **m_end;
	char m_pad[0x124];
	int m_12C;
	void **vecErase2(void **first, void **last);
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
	arg->vecErase2(arg->m_begin, arg->m_end);
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

// ?rva002102CA@Rva0020EE29@@QAEXXZ @0x002102CA 68B
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

void Rva0020EE29::rva002102CA()
{
	Rva002102CAElem ***bounds = (Rva002102CAElem ***)&m_inner->m_begin;
	for (unsigned i = 0; i < (unsigned)(((char *)bounds[1] - (char *)bounds[0]) >> 2); ++i)
		bounds[0][i]->v01();
	rva0020F483();
	m_inner->rva0020F5B3();
}

// ?rva0020F685@Rva0020EE29@@QAEXXZ @0x0020F685 141B
// Notifies (rowed-pending free 0x002FD60) for every entry of the +0x14 and
// +0x20 vectors with the entry's vtable slot-0 result under a zero argument
// (or null for a null entry), then range-erases both vectors through the
// rowed two-arg erase. Evidence: retail pop-ecx cleanup of the notify arg
// (cdecl); the identical halves over [ebx+0x14]/[ebx+0x20]; the erase calls
// with this=vector and (begin,end). Slot-0 goes through a stand-in element
// type (vtable layout only); the vectors reuse the rowed-erase helper.
class Rva0020F685Elem
{
public:
	virtual void *v00(int zero);
};

void rva002FD60(void *v);

// ?rva0020F685@Rva0020EE29@@QAEXXZ present-unmatched
void Rva0020EE29::rva0020F685()
{
	Rva0020EE29 *self = this;
	Rva0020FD42Arg *vec14 = (Rva0020FD42Arg *)((char *)self + 0x14);
	for (unsigned i = 0; i < (unsigned)(((char *)vec14->m_end - (char *)vec14->m_begin) >> 2); ++i) {
		Rva0020F685Elem *elem = (Rva0020F685Elem *)vec14->m_begin[i];
		void *v = elem ? elem->v00(0) : 0;
		rva002FD60(v);
	}
	vec14->vecErase2(vec14->m_begin, vec14->m_end);
	Rva0020FD42Arg *vec20 = (Rva0020FD42Arg *)((char *)self + 0x20);
	for (unsigned j = 0; j < (unsigned)(((char *)vec20->m_end - (char *)vec20->m_begin) >> 2); ++j) {
		Rva0020F685Elem *elem = (Rva0020F685Elem *)vec20->m_begin[j];
		void *v = elem ? elem->v00(0) : 0;
		rva002FD60(v);
	}
	vec20->vecErase2(vec20->m_begin, vec20->m_end);
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
class Rva003EF1B8Host
{
public:
	void rva003EF1B8();
};

class Rva0020F795Elem2
{
public:
	void rva003F3F27();
};

void Rva0020EE29::rva0020F795()
{
	Rva0020EE29 *self = this;
	for (unsigned i = 0; i < (unsigned)(((char *)self->m_14.m_end - (char *)self->m_14.m_begin) >> 2); ++i)
		((Rva00DFE1C8Host *)TheLivingWorldManager)->rva00212655(self->m_14.m_begin[i]->m_30);
	((Rva0020FB41Outer *)self)->rva0020F685();
	self->rva0020EE29();
	self->m_0C = 0;
	self->m_10 = 0;
	self->m_2C = 0;
	self->m_30 = 0;
	if (self->m_inner) {
		if (((Rva00DFE1C8Host *)TheLivingWorldManager)->m_268)
			((Rva003EF1B8Host *)((Rva00DFE1C8Host *)TheLivingWorldManager)->m_268)->rva003EF1B8();
		Rva0020F795Elem2 ***bounds = (Rva0020F795Elem2 ***)&self->m_inner->m_begin;
		for (unsigned j = 0; j < (unsigned)(((char *)bounds[1] - (char *)bounds[0]) >> 2); ++j)
			bounds[0][j]->rva003F3F27();
	}
	self->m_inner = 0;
}

// ?rva00212655@Rva00212655@@QAEXH@Z @0x00212655 102B
// Resolves an entry through the +0x218 member, reports it, and links it:
// the member lookup takes the address of the incoming arg slot as its
// out-parameter and answers the entry or null; a null entry ends the body.
// Otherwise the entry's +8 sub-object selects a dword (its +4 plus 8, or
// the VA 0x00BBAC1C constant) reported to the VA 0x00DFEF18 singleton
// (rowed-pending 0x002C004F); the sub-object runs the notify idiom (virtual
// slot-0 under zero, else null) into the rowed-pending free 0x002FD60; then
// the rowed-pending 0x001E2861 links {entry, this+0x218} on this+0x218.
// Evidence: retail lea/mov/call shapes per site; the garbage-push inline
// struct (address taken then both words stored); ebp-frame with EH-free
// SEH-style locals; the singleton and notify pins already in this TU.
// Entry and singleton identities are unproven (address-derived views).
class Rva00212655Sub;

class Rva00212655Entry
{
public:
	void *m_00;
	char m_pad[4];
	Rva00212655Sub *m_08sub;
};

class Rva00212655Sub
{
public:
	void *m_00;
	int m_04;
};

class Rva00212655Vec218
{
public:
	void *rva002888D4(void **out);
	void rva001E2861(void *pair);
};

class Rva002C004FHost
{
public:
	void rva002C004F(void *val);
};

class Rva00212655Virt
{
public:
	virtual void *v00(int zero);
};

class Rva00212655
{
public:
	void rva00212655(int arg);

private:
	char m_pad[0x218];
	Rva00212655Vec218 m_218;
};

void rva002FD60(void *v);

// ?rva00212655@Rva00212655@@QAEXH@Z present-unmatched
void Rva00212655::rva00212655(int arg)
{
	void *entry = m_218.rva002888D4((void **)&arg);
	if (!entry)
		return;
	Rva00212655Sub *sub = ((Rva00212655Entry *)entry)->m_08sub;
	int val;
	if (sub->m_04)
		val = sub->m_04 + 8;
	else
		val = 0xBBAC1C;
	((Rva002C004FHost *)((Rva00DFE1C8Host *)TheLivingWorldManager))->rva002C004F((void *)val);
	Rva00212655Virt *virt = (Rva00212655Virt *)sub;
	void *nv = virt ? virt->v00(0) : 0;
	rva002FD60(nv);
	struct Pair { void *a; void *b; } p = { entry, &m_218 };
	m_218.rva001E2861(&p);
}

// ?rva00210F09@Rva00210F09@@QAEXXZ @0x00210F09 30B
// Runs the rowed-pending same-class 0x000B3FD0, then when this is non-null
// runs its vtable slot-0 under zero and reports through the rowed free
// 0x002FD60 (pop-cleaned). Evidence: retail member call with this
// passthrough; the defensive this-null check; the indirect slot-0 call
// shape shared with the 0x0020F685 loop body; bare ret.
class Rva00210F09
{
public:
	void rva00210F09();
	void rva000B3FD0();
};

// ?rva00210F09@Rva00210F09@@QAEXXZ present-unmatched
void Rva00210F09::rva00210F09()
{
	rva000B3FD0();
	// Retail shares one zero across the null check (cmp esi,eax), the
	// slot-0 argument (push eax) and the result, so it is one variable.
	void *v = 0;
	if (this == v)
		return;
	v = ((Rva0020F685Elem *)this)->v00((int)v);
	rva002FD60(v);
}

// ?Rva00210E5B@@YGXPAX0@Z @0x00210E5B 33B
// Looks up the first handle through the VA 0x00DFEF18 singleton
// (rowed-pending 0x002BFDAE) and, when found, runs the rowed-pending
// 0x003FA781 on it with the second handle. Evidence: retail pushes the arg
// with this=singleton (direct call, callee-clean); the null test; the
// second push reads the other arg slot after the callee-cleaned call.
// Free function (no this); handles opaque.
class Rva003FA781Host
{
public:
	void rva003FA781(void *a);
};

void __stdcall Rva00210E5B(void *a1, void *a2)
{
	void *p = g_00DFEF18query->rva002BFDAE(a1);
	if (!p)
		return;
	((Rva003FA781Host *)p)->rva003FA781(a2);
}

// ?rva002110DF@Rva002110DF@@QAEXH@Z @0x002110DF 66B
// Runs every entry of the +0x258 vector through the rowed-pending
// 0x003FCDD5 with the forwarded arg. Evidence: retail reload-each-iteration
// count (calls inside block strength reduction, rowed-EE29 idiom); the arg
// pushed straight from its incoming slot; this-cached callee. Element
// identity unproven (address-derived view).
class Rva002110DFElem
{
public:
	void rva003FCDD5(int a);
};

class Rva002110DF
{
public:
	void rva002110DF(int a1);

private:
	char m_pad[0x258];
	Rva002110DFElem **m_258begin;
	Rva002110DFElem **m_25Cend;
};

// ?rva002110DF@Rva002110DF@@QAEXH@Z present-unmatched
void Rva002110DF::rva002110DF(int a1)
{
	for (unsigned i = 0; i < (unsigned)(((char *)m_25Cend - (char *)m_258begin) >> 2); ++i)
		m_258begin[i]->rva003FCDD5(a1);
}

// 0x00211570 is owned by its existing retail source unit.


// ?Rva002122FD@@YGXPAX@Z @0x002122FD 30B
// Free __stdcall lookup chain: resolves through the VA 0x00DF36A4 singleton
// (rowed-pending 0x0009FA65), then feeds that into the VA 0x00DFE1C8
// singleton (rowed-pending 0x002122D4). Evidence: retail loads each global
// to ecx per call (direct, callee-clean); single pushes; ret 4. Handles
// opaque; singletons share this TU's externs.
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class AsciiString;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &a);
};

class Rva002122D4Host
{
public:
	void rva002122D4(void *a);
};

extern NameKeyGenerator *g_rva00DF36A4;

void __stdcall Rva002122FD(void *a1)
{
	void *t = (void *)g_rva00DF36A4->nameToKey(*(const AsciiString *)a1);
	((Rva00DFE1C8Host *)TheLivingWorldManager)->rva002122D4(t);
}

// ?Rva0021618A@@YAPAXHHH@Z @0x0021618A 27B
// Free __cdecl forwarder: passes its three dwords plus the address of a
// one-byte stack slot to the rowed-pending free 0x00215F83 and answers its
// value opaquely. Evidence: retail reserves via push with the byte addressed
// at [ebp-1] (2101C6 two-byte precedent); caller-side add-esp cleanup.
// Return flows to 0x00216245; unproven beyond the bytes.
void *rva00215F83(int a1, int a2, int a3, void *b);

void *Rva0021618A(int a1, int a2, int a3)
{
	unsigned char b;
	return rva00215F83(a1, a2, a3, &b);
}

// ?rva00216245@Rva00216245@@QAEPAXH@Z @0x00216245 34B
// Forwards two member pointers plus the arg through the rowed free
// 0x0021618A and answers its value unless it equals the +0x2c member, when
// it answers null (branchless neg/sbb mask). Evidence: retail push order
// plus the caller-side add-esp cleanup; the neg/sbb/and select on the
// result. Slot meanings unproven.
class Rva00216245
{
public:
	void *rva00216245(int a1);

private:
	char m_pad[0x28];
	void *m_28;
	void *m_2C;
};

void *Rva00216245::rva00216245(int a1)
{
	void *p2 = m_2C;
	void *r = Rva0021618A((int)m_28, (int)p2, a1);
	return (r != p2) ? r : 0;
}

// ?rva002115D0@Rva002115D0@@QAEXPAX0@Z @0x002115D0 28B
// Uses the master-pinned StringBase<char>(const char*) constructor at
// 0x0037BA0 on the first handle with the existing g_bfmeEmptyF9 symbol, then
// answers the handle. The second handle is unused by retail; the zeroed slot
// is dead. Target evidence: the call site sets ecx from the first handle and
// pushes the empty-string address. The helper body remains present-unmatched.
extern char g_bfmeEmptyF9[];

class Rva002115D0
{
public:
	void *rva002115D0(void *a1, void *a2);
};

// ?rva002115D0@Rva002115D0@@QAEPAXPAX0@Z present-unmatched
void *Rva002115D0::rva002115D0(void *a1, void *a2)
{
	// Retail reserves and zeroes a slot it never reads; a plain = 0 store
	// is dead and MSVC elides the whole frame, so this models the observed
	// read-modify-write which survives as the and-slot.
	int unused;
	unused &= 0;
	::new (a1) AsciiString(g_bfmeEmptyF9);
	return a1;
}

// Dump-range-7 0x0021BE2x free-lookup batch (each 31-32B, __stdcall).
// Each resolves its second handle through the rowed-pending free 0x00219B9E
// and, when found, runs one rowed-pending member on it with the first
// handle, answering that value; on a miss two answer 0 and two answer -1.
// Evidence: retail pushes with no ecx setup (free, callee-clean ret 8); the
// null test with xor (0) or or--1 (-1); this=result member calls. Handles
// opaque; second-stage identities unproven (one host, address-derived).
class Rva0021BDAccess
{
public:
	void *rva0021BD22(unsigned int a);
};

class Rva00219B9ERet
{
public:
	int rva0021BC2C(int a);
	int rva0021BDAB(int a);
	int rva0021BC53(int a);
};

void *__stdcall Rva00219B9E(int a);

int __stdcall Rva0021BE23(int a1, int a2)
{
	void *p = Rva00219B9E(a2);
	if (p)
		return ((Rva00219B9ERet *)p)->rva0021BC2C(a1);
	return 0;
}

// 0x0021BE42 rowed by another seat from Rva0021BE42Chain.cpp; the twin
// body here is intentionally absent to keep a single owner.
int __stdcall Rva0021BEA2(int a1, int a2)
{
	void *p = Rva00219B9E(a2);
	if (p)
		return ((Rva00219B9ERet *)p)->rva0021BC53(a1);
	return 0;
}

int __stdcall Rva0021BEC1(int a1, int a2)
{
	void *p = Rva00219B9E(a2);
	if (p)
		return (int)((Rva0021BDAccess *)p)->rva0021BD22((unsigned int)a1);
	return 0;
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

// ?rva002103B6@Rva002103B6@@QAEXPAVRva00210390@@@Z present-unmatched
void Rva002103B6::rva002103B6(Rva00210390 *a1)
{
	Rva002103B6Vec *vec = &m_2Cvec;
	vec->vecEraseR(vec->m_begin, vec->m_end);
	vec->vecReserveR((unsigned)(((char *)m_20vec.m_end - (char *)m_20vec.m_begin) >> 2));
	Rva002103B6Vec *vec20p = &m_20vec;
	for (unsigned i = 0; i < (unsigned)(((char *)vec20p->m_end - (char *)vec20p->m_begin) >> 2); ++i) {
		void *hit = a1->rva00210390((const AsciiString *)&m_20vec.m_begin[i]);
		// Value first (stays in eax through both arms), home second: retail
		// ors eax (not memory) then stores once for the push address.
		int v = hit ? *(int *)((char *)hit + 0x12C) : -1;
		int slot = v;
		vec->vecPushR(&slot);
	}
}

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

// Dump-range-7 0x0021BEE0/0x0021BF11/0x0021BF42 entry dispatchers (49-50B,
// __thiscall, 3 args). Each bounds-checks the index against the +0x14c flat
// 32-byte table, then runs one rowed 0x0021BE2x lookup on &table[index] with
// the other two handles, answering its value; on a miss answers 0 or -1
// matching that callee. Evidence: retail end-minus-begin sar-5 count with
// jae-out; the shl-5-plus-base entry address into ecx (this for the member
// spelling, pinned); the [esp+...] pushes in entry order. Table and entry
// identities unproven (address-derived views).
struct Rva0021BEEntry
{
	char m_data[32];
	int rva0021BE23(int a1, int a3);
	int rva0021BEA2(int a1, int a3);
	int rva0021BE42(int a1, int a3);
};

struct Rva0021BETable
{
	void *m_begin;
	void *m_end;
};

class Rva0021BFxx
{
public:
	int rva0021BEE0(int a1, int a2, int a3);
	int rva0021BF11(int a1, int a2, int a3);
	int rva0021BF42(int a1, int a2, int a3);

private:
	char m_pad[0x14C];
	Rva0021BETable m_14Ctable;
};

// ?rva0021BEE0@Rva0021BFxx present-unmatched
int Rva0021BFxx::rva0021BEE0(int a1, int a2, int a3)
{
	Rva0021BETable *t = &m_14Ctable;
	unsigned n = (unsigned)(((char *)t->m_end - (char *)t->m_begin) >> 5);
	if ((unsigned)a2 < n) {
		return ((Rva0021BEEntry *)((char *)t->m_begin + a2 * 32))->rva0021BE23(a1, a3);
	}
	return 0;
}

// ?rva0021BF11@Rva0021BFxx present-unmatched
int Rva0021BFxx::rva0021BF11(int a1, int a2, int a3)
{
	Rva0021BETable *t = &m_14Ctable;
	unsigned n = (unsigned)(((char *)t->m_end - (char *)t->m_begin) >> 5);
	if ((unsigned)a2 < n) {
		return ((Rva0021BEEntry *)((char *)t->m_begin + a2 * 32))->rva0021BEA2(a1, a3);
	}
	return 0;
}

// ?rva0021BF42@Rva0021BFxx present-unmatched
int Rva0021BFxx::rva0021BF42(int a1, int a2, int a3)
{
	Rva0021BETable *t = &m_14Ctable;
	unsigned n = (unsigned)(((char *)t->m_end - (char *)t->m_begin) >> 5);
	if ((unsigned)a2 < n) {
		return ((Rva0021BEEntry *)((char *)t->m_begin + a2 * 32))->rva0021BE42(a1, a3);
	}
	return -1;
}

// Native20F832..20F91D RET8: apply state+14 to the entry, move its
// matching node from vector14 to vector20, reset the battle key, then
// invoke an optional script string copied from entry+6C. WB B55590
// corroborates the control flow; original entry/method names are unknown.
class Rva003F2A8C { public: void rva003F2A8C(int value); };
struct Rva0020F832Entry { char pad[0x6c]; AsciiString script; };
struct Rva0020F832State { char pad[0x14]; int value; };
struct Rva0020F832Node { char pad[0x24]; void *entry; char pad28[8]; int key; };
class Rva0020E5BB { public: void rva0020E63F(int key, int field3c); };
class Rva00E02D6C { public: void rva003B8D71(const AsciiString &script); };
extern Rva00E02D6C *TheCampaignManager;
void __stdcall rva0020F309(void *entry, int state);
// The rowed stdcall forwarder ignores ECX. This call view retains the
// native caller's ECX receiver as well as its two callee-clean stack words.
union Rva0020F309Call {
 void (__stdcall *function)(void *, int);
 void (Rva0020EE29::*member)(void *, int);
};

bool Rva0020EE29::rva0020F832(void *entry, void *state)
{
 ((Rva003F2A8C *)entry)->rva003F2A8C(((Rva0020F832State *)state)->value);
 Rva0020FB8BVec14 *source = &m_14;
 for (unsigned i = 0; i < (unsigned)(source->m_end - source->m_begin); ++i) {
  if (((Rva0020F832Node *)source->m_begin[i])->entry == entry) {
   ((Rva00DFE1C8Host *)TheLivingWorldManager)->rva00212655(
    ((Rva0020F832Node *)source->m_begin[i])->key);
   m_20.vecPushBack((void *&)source->m_begin[i]);
   source->vecErase((void **)&source->m_begin[i]);
   break;
  }
 }
 Rva0020F309Call call;
 call.function = &rva0020F309;
 (this->*call.member)(entry, (int)state);
 rva0020ED8E(entry, state);
 ((Rva0020E5BB *)this)->rva0020E63F(0, 0);
 AsciiString script(((Rva0020F832Entry *)entry)->script);
 if (!script.isEmpty()) {
  TheCampaignManager->rva003B8D71(script);
  return false;
 }
 return true;
}

// cl: /O1 /Ob1 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB
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
	bool rva0020F91D(void *a1, void *a2, void *a3);
	void *rva0020F9F6(void *a1, void *a2, void *filter);
	void rva0020FAEA(float *a1, void *a2);
	void rva0020FAB4(int a1, int a2);
	void rva0020FB8B(Rva0020FB8BNode *arg);

private:
	char m_pad[8];
	Rva0020EE29Inner *m_inner;
	char m_pad0C[8];
	Rva0020FB8BVec14 m_14;
	char m_pad1C[4];
	Rva0020FB8BVec20 m_20;
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
};
extern Rva00DFE1C8Host *g_rva00DFE1C8;

// ?rva0020F9F6@Rva0020EE29@@QAEPAXPAX00@Z present-unmatched
void *Rva0020EE29::rva0020F9F6(void *a1, void *a2, void *filter)
{
	Rva0020EE29Inner *inner = m_inner;
	unsigned i = 0;
	if (!inner)
		return 0;
	if (g_rva00DFE1C8->m_268 == (int)i)
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

// ?rva0020FB41@Rva0020FB41@@QAEXHH@Z @0x0020FB41 74B
// Resets the +0x8/+0xC state and runs every entry of the inner pointer
// vector at +0x4 (+0x2c/+0x30) through rowed-pending ?rva003F20E5 (two
// stack args, this = entry). The rowed-pending ?rva0020F685 runs first on
// the enclosing object at this-4. Evidence: retail lea ecx,[esi-4] call;
// the zero register doubles as the loop counter; reload-each-iteration
// count loop over [esi+0x2c] like rva0020EE29 above. Argument meanings are
// unproven (passed opaquely to the entry method).
class Rva0020FB41Outer
{
public:
	void rva0020F685();
};

class Rva0020FB41
{
public:
	void rva0020FB41(int a1, int a2);

private:
	int m_00;
	Rva0020EE29Inner *m_04;
	int m_08;
	int m_0C;
};

void Rva0020FB41::rva0020FB41(int a1, int a2)
{
	((Rva0020FB41Outer *)((char *)this - 4))->rva0020F685();
	m_08 = 0;
	m_0C = 0;
	// Retail advances past the inner header once and reads begin/end from
	// the advanced pointer ([esi]/[esi+4]), so the traversal below addresses
	// the begin/end pair through &m_begin rather than re-adding +0x2c.
	Rva003F209C ***bounds = &m_04->m_begin;
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
	g_rva00DFE1C8->rva00212655(arg->m_30);
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

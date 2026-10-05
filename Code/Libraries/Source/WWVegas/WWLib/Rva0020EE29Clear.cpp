// cl: /O1 /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
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

class Rva0020EE29
{
public:
	void rva0020EE29();
	bool rva0020F91D(void *a1, void *a2, void *a3);
	void *rva0020F9F6(void *a1, void *a2, void *filter);

private:
	char m_pad[8];
	Rva0020EE29Inner *m_inner;
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

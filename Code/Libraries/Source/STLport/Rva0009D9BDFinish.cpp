// ?rva0009D9BD@Rva0009D9BD@@QAEXXZ
// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva0009D9BD@Rva0009D9BD@@QAEXXZ, retail 0x0009D9BD, 64 bytes.
// Index loop over vector<void*> at +0x1C0 via rowed thunk 0x000518E0
// then erase begin-end via rowed 0x0031BD55. Evidence: sar 2 count,
// push [eax+edi*4] plus thunk plus erase, 2 unblocked plus 3 callers.
//
// Retail recomputes the count in eax on both the entry and the loop-back
// edge: `mov eax,[esi+4] ; sub eax,[esi] ; sar eax,2`. STLport size()
// materializes start into eax first and counts in ecx instead, which is why
// the plain `i < vec.size()` spelling is 2 bytes wider per pass.
//
// Spelling the span by hand over the vector's own finish/start pair gives the
// 2-byte `sub X,[r]` count, and keeping that difference SIGNED keeps the shift
// arithmetic: an unsigned bound turns `sar eax,2 ; je` into
// `test eax,0xfffffffc ; jbe`. Both together reproduce retail exactly, with the
// count recomputed per pass as retail does rather than hoisted.
#include <vector>

// The loop callee is the rowed free thunk at 0x000518E0. Retail loads the
// global instance into ecx and pushes only the element, and that thunk's body
// reads its argument from [esp+4] without touching ecx. Calling it as the
// pinned member `?handle@Gen0003AC38@@QAEXPAX@Z` gives exactly that shape:
// Rva000518E0Thunk.cpp binds the two names with an /alternatename, and
// reverse/symbols.csv pins this one at 0x000518E0.
class Gen0003AC38
{
public:
	void handle(void *p);
};

extern class Gen0003AC38 *g_shadowManager;

class Rva0009D9BD
{
public:
	void rva0009D9BD();
	void rva0009D9FD();

private:
	unsigned char m_pad00[0x19C];
	void *m_19C;
	unsigned char m_pad1A0[0x1C0 - 0x1A0];
	_STL::vector<void *> m_vec;
};

// ?rva0009D9BD@Rva0009D9BD@@QAEXXZ
void Rva0009D9BD::rva0009D9BD()
{
	int *span = (int *)&m_vec;
	_STL::vector<void *> &vec = m_vec;
	for (unsigned int i = 0; i < (unsigned)((span[1] - span[0]) >> 2); ++i)
		g_shadowManager->handle(vec[i]);
	vec.erase(vec.begin(), vec.end());
}

// ?rva0009D9FD@Rva0009D9BD@@QAEXXZ, retail 0x0009D9FD, 43 bytes.
// Single-slot prologue to rva0009D9BD: when the +0x19C slot is set, run it
// through the same global handle thunk, clear it, and tail-jump into the
// vector version.
void Rva0009D9BD::rva0009D9FD()
{
	void *slot = m_19C;
	if (slot) {
		g_shadowManager->handle(slot);
		m_19C = 0;
		rva0009D9BD();
	}
}

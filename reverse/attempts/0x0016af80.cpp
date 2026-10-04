// ?rva0016AF80@Rva0016AF80@@QAE_NAAVChunkLoadClass@@@Z
// partial score=0.85 date=2026-10-04
// ?rva0016AF80@Rva0016AF80@@QAE_NAAVChunkLoadClass@@@Z
//
// Retail body 0x0016AF80, 72 bytes. Bulk vertex-chunk reader: Resize the
// ShareBuffer<Vector3> store at +0x40 to the VertexCount at +0x28, then a single
// ChunkLoadClass::Read; returns read == expected.
//
// Two structural facts, both verified against the real headers this pass:
//
//  - ChunkLoadClass::Read is `uint32 Read(void *buf, uint32 nbytes)`
//    (chunkio.h:203, impl chunkio.cpp:97), so SIZE IS PUSHED LAST. The argument
//    order is therefore NOT the lever the previous bank assumed.
//  - Resize has no shared declaration. The matched TU
//    Code/Libraries/Source/WWVegas/WWLib/sharebuf_vector3_resize.cpp declares it
//    inside a local ShareBufferClass stub (lines 33-42), with the layout the
//    ledger records as raw8 arrayC count10 alignment14. Compiling against the
//    shared sweep/sharebuf.h instead fails with C2039 `Resize` is not a member,
//    so the hand-rolled stub below is required, not a shortcut.
//
// Residual, as measured this pass (79B against retail's 72B, first diff +0x8):
//
//   1. GUARD POLARITY. Retail emits `jne +6`, so the early `return false` is the
//      FALL-THROUGH. MSVC 7.1 always lays the syntactically-first early return
//      out as the branch TARGET and emits `je`, then lays out the remaining ~60
//      bytes around it. Swept: inverted nested guards, single-exit `bool ok`,
//      goto-to-a-shared-fail, and the early-return-at-the-tail form all emit
//      `je`; the bool-ok form is 80B.
//
//   2. THE 7 BYTES OF OVERSHOOT (new this pass). With the count left in EAX and
//      re-read after the call, MSVC DOES reach retail's tail -- it emits the
//      `mov esi,[esi+0x28]`, the `lea edx,[esi+esi*2] / add / add` = count*12
//      chain and `cmp eax,ecx` -- but then emits `xor edx,edx / sete dl /
//      mov al,dl` (4B) where retail has `sete al` (3B), AND it reloads the
//      cload reference off the stack a second time (`mov ecx,[esp+0x10]`) where
//      retail reads `[esp+8]` once. Those two together are exactly 79 vs 72.
//      Retail holds the count in a callee-saved register ACROSS the call and
//      reads the reference argument ONCE; caching the count across the call
//      fixes the reload but loses the second *12 recompute, which is the same
//      trade-off the previous bank recorded, now pinned from the correct side.
// cl: /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
#include "always.h"
#include "refcount.h"
#include "bittype.h"
#include "chunkio.h"

class Vector3 { public: float x, y, z; Vector3() {} };

template<class T>
class ShareBufferClass : public RefCountClass
{
public:
	void Resize(int newsize);
	T *Get_Array(void) { return Array; }
protected:
	T *RawBuffer;
	T *Array;
	int Count;
	int Alignment;
};

class Rva0016AF80
{
public:
	bool rva0016AF80(ChunkLoadClass &cload);
private:
	virtual ~Rva0016AF80();
	char m_pad04[0x28 - 0x4];
	int m_count28;
	char m_pad2C[0x40 - 0x2C];
	ShareBufferClass<Vector3> *m_vertex40;
};

// ?rva0016AF80@Rva0016AF80@@QAE_NAAVChunkLoadClass@@@Z present-unmatched
bool Rva0016AF80::rva0016AF80(ChunkLoadClass &cload)
{
	if (m_vertex40 == 0)
		return false;
	m_vertex40->Resize(m_count28);
	Vector3 *buf = m_vertex40->Get_Array();
	if (buf == 0)
		return false;
	unsigned long got = cload.Read(buf, m_count28 * (int)sizeof(Vector3));
	return got == (unsigned long)(m_count28 * (int)sizeof(Vector3));
}

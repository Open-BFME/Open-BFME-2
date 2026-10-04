// ?rva0016AF80@Rva0016AF80@@QAE_NAAVChunkLoadClass@@@Z
// partial score=0.85 date=2026-10-04
// ?rva0016AF80@Rva0016AF80@@QAE_NAAVChunkLoadClass@@@Z
// partial score=0.85 date=2026-10-04
// cl: /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// ?rva0016AF80@Rva0016AF80@@QAE_NAAVChunkLoadClass@@@Z @0x0016AF80 72B.
// Bulk vertex-chunk reader sibling of 0x0016AFD0: Resize the ShareBuffer<Vector3>
// store at +0x40 to the VertexCount at +0x28 then single ChunkLoadClass::Read;
// returns read == expected. Evidence: rowed Resize 0x00169470 and Read 0x006151A0,
// caller at 0x0018B8F7, same MeshGeometryClass neighbours, honest address name.
//
// SEAT-3 re-bank of the previous 0.82 body. The previous bank cached m_vertex40
// and m_count28 in locals. Retail does neither: it keeps `this` in ESI for the
// whole body and reads EVERY member through it --
//   16af80  push esi / mov esi,ecx / mov ecx,[esi+0x40] / test ecx,ecx
//   16af90  mov eax,[esi+0x28]      <- count for the Resize, via this
//   16af99  mov ecx,[esi+0x40]      <- the buffer pointer RE-READ from this
//   16afa3  mov esi,[esi+0x28]      <- count RE-READ a second time
// so the local caches are what kept `this` dead and re-registered the body.
// Removing them (read every member straight off the implicit this pointer, and
// name neither the buffer nor the count) reproduces retail's plan exactly:
// 0x16AF80..0x16AF86 and 0x16AFA3..0x16AFB3 are byte-identical, including
// `mov ecx,[esp+8]`, the `lea edx,[esi+esi*2] / add edx,edx / add edx,edx`
// (= count*12) chain, both pushes and the call. First difference moves from
// +0x00 to +0x08.
//
// What is still open, precisely:
//
//  1. +0x08 BRANCH POLARITY (7-byte window). Retail emits `jne +6`, i.e. the
//     early `return false` is the FALL-THROUGH; this build emits `je +0x13`, so
//     the true path is the fall-through and the remaining ~60 bytes are laid out
//     differently. Swept this pass and all of them move the polarity the wrong
//     way or worse: `if (p != 0) { work } return false;` (both guards, and the
//     single-exit `bool ok` form) all outline the work to a cold block and emit
//     `je`; a goto-to-a-shared-fail-label form and a ternary guard are worse
//     still. MSVC 7.1 lays the syntactically-first early return out as the
//     branch TARGET, so no source spelling puts it in the fall-through slot.
//
//  2. THE TAIL. Retail computes count*12 a SECOND time into ECX after the Read
//     and compares Read's return value against it (`lea ecx,[esi+esi*2]; add
//     ecx,ecx; add ecx,ecx; cmp eax,ecx; sete al`). Spelling the comparison as
//     two independent products straddling the call DOES produce retail's second
//     *12 chain and `cmp eax,ecx`, but the compiler then models the comparison
//     result as a separate bool and emits `xor edx,edx / sete dl / mov al,dl`
//     instead of `sete al` -- the one dl/al pair, 4 bytes. With the count cached
//     across the call instead, `sete al` is right but the *12 is not recomputed.
//     The two properties are the same trade-off this compiler keeps refusing.
//
// Best shape measured this pass: 33 differing bytes but 62B, because the tail
// comparison folds to a constant (`n * 12 == m_count28 * 12` after the count is
// known equal) and the body loses the last 10 bytes. That is NOT an improvement
// on the bank -- retail is 72B and a wrong-size body cannot land -- so the bank
// is left at 0.82 with this analysis. What a next pass should try is the one
// thing not yet attempted: get the polarity from the CALLEE's argument layout
// rather than from the guard, i.e. change `ChunkLoadClass::Read`'s declared
// parameter order so the size expression is evaluated after the buffer
// expression, which is what decides whether the second *12 is a fresh read.
#include "always.h"
#include "refcount.h"
#include "bittype.h"
#include "chunkio.h"

class Vector3
{
public:
	float x, y, z;
	Vector3() {}
};

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
	// Every member is read straight off the implicit this pointer, and neither
	// the buffer nor the count is named: retail keeps `this` live in ESI for the
	// whole 72-byte body and re-reads both members, which is what the local
	// caches in the previous bank prevented.
	if (m_vertex40 == 0)
		return false;
	m_vertex40->Resize(m_count28);
	Vector3 *buf = m_vertex40->Get_Array();
	if (buf == 0)
		return false;
	unsigned long got = cload.Read(buf, m_count28 * (int)sizeof(Vector3));
	return got == (unsigned long)(m_count28 * (int)sizeof(Vector3));
}

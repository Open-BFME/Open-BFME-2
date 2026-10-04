// cl: /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
//
// ?rva0016AFD0@Rva0016AFD0@@QAE_NAAVChunkLoadClass@@@Z @0x0016AFD0 72B.
// Bulk vertex-chunk reader: Resize the ShareBuffer<Vector3> vertex store at
// +0x44 to the VertexCount at +0x28 then single ChunkLoadClass::Read of
// count*sizeof(Vector3) bytes; returns read == expected. Evidence: rowed
// Resize 0x00169470 and Read 0x006151A0 callees, caller at 0x0018B91E,
// MeshGeometryClass neighbours (Compute_Ram_Size, read_triangles) with the
// +0x28 count and +0x40/+0x44 buffers, honest address name since no vtable
// or claimant proves the owner.
//
// Three codegen facts the retail bytes pin down, each reproduced by the shape
// below rather than guessed:
//  * `this` lives in esi and m_vertex44/m_count28 are RE-READ after the Resize
//    call (mov ecx,[esi+0x44] / mov esi,[esi+0x28] again at +0x19/+0x23), so
//    the source touches m_vertex44 and m_count28 on both sides of the call
//    instead of caching them in locals that would need a callee-saved register.
//  * The first guard is written with an explicit `else`. That is what makes
//    cl lay the shared `xor al,al; pop esi; ret 4` block out at +0x0A, inline
//    and immediately after the test, with `jne` jumping over it and the buf
//    null check at +0x2A jumping back to it. A bare early return puts that
//    block at the function tail and flips the test to `je`.
//  * The size is read through Get_Vertex_Count() so the call is evaluated once
//    per use: retail computes count*12 twice (+0x2E into edx for the push and
//    +0x38 into ecx for the compare). A plain local count is CSE'd to one
//    multiply. The two-statement `matched` tail is what keeps the compare a
//    bare `cmp eax,ecx; sete al` instead of a zero-extended sete through edx.
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

class Rva0016AFD0
{
public:
	bool rva0016AFD0(ChunkLoadClass &cload);
private:
	virtual ~Rva0016AFD0();
	char m_pad04[0x28 - 0x4];
	int m_count28;
	char m_pad2C[0x44 - 0x2C];
	ShareBufferClass<Vector3> *m_vertex44;
	int Get_Vertex_Count() const { return m_count28; }
};

bool Rva0016AFD0::rva0016AFD0(ChunkLoadClass &cload)
{
	if (m_vertex44 == 0)
	{
		return false;
	}
	else
	{
		m_vertex44->Resize(m_count28);
		Vector3 *buf = m_vertex44->Get_Array();
		if (buf == 0)
			return false;
		bool matched = cload.Read(buf, Get_Vertex_Count() * sizeof(Vector3))
			== Get_Vertex_Count() * sizeof(Vector3);
		return matched;
	}
}
// cl: /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
//
// ?rva0016AF80@Rva0016AF80@@QAE_NAAVChunkLoadClass@@@Z @0x0016AF80 72B.
// Bulk vertex-chunk reader sibling of 0x0016AFD0: Resize the ShareBuffer<Vector3>
// store at +0x40 to the VertexCount at +0x28 then single ChunkLoadClass::Read;
// returns read == expected. Evidence: rowed Resize 0x00169470 and Read 0x006151A0,
// caller at 0x0018B8F7, same MeshGeometryClass neighbours, honest address name.
//
// Seat-6: the banked body had already fixed the register strategy (read every
// member off `this`, keep it in ESI, re-read after the Resize call) but was
// still a `je` with the false block outlined. The polarity lever the bank had
// not tried is the explicit `else` on the first guard, which makes cl lay the
// shared `xor al,al; pop esi; ret 4` block inline right after the test with
// `jne` jumping over it (verified byte-exact on the sibling 0x0016AFD0 first).
// The tail keeps `sete al` by routing the size through Get_Vertex_Count() (so
// the call is evaluated once per use and count*12 is computed twice) and
// assigning the comparison to `matched` before returning it.
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
	int Get_Vertex_Count() const { return m_count28; }
};

bool Rva0016AF80::rva0016AF80(ChunkLoadClass &cload)
{
	if (m_vertex40 == 0)
	{
		return false;
	}
	else
	{
		m_vertex40->Resize(m_count28);
		Vector3 *buf = m_vertex40->Get_Array();
		if (buf == 0)
			return false;
		bool matched = cload.Read(buf, Get_Vertex_Count() * sizeof(Vector3))
			== Get_Vertex_Count() * sizeof(Vector3);
		return matched;
	}
}
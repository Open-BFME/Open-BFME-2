// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/shims/stringinline /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas
// @0x000EC9C6 135B. Early-out on the live dwords, clear the flag bytes,
// then forward this into the four rowed callees.

#include "../../../GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeRecord.h"
#include "../../../GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeTypeRecord.h"

class VertexBufferClass;
class IndexBufferClass;

template <class T> struct PtrVector
{
	T *m_start, *m_finish, *m_endOfStorage;
	T *begin(void) { return m_start; }
	T &operator[](unsigned int n) { return *(begin() + n); }
	unsigned int size(void) const { return unsigned(m_finish - m_start); }
};

// The same tree buffer under its rowed name: its texture refresh is
// W3DTreeBuffer::updateTexture (0x000EB40F, protected).
class W3DTreeBuffer
{
	friend class Rva000EC9C6;
protected:
	void updateTexture();
};

class Rva000EC9C6
{
public:
	void rva000EB6BB(void);
	void rva000EBFD1(void);
	void rva000E663B(int arg);
	void rva000EC9C6(int arg);

private:
	void *m_vtable;
	PtrVector<VertexBufferClass *> m_vertexTree;
	PtrVector<int> m_curNumTreeVertices;
	PtrVector<IndexBufferClass *> m_indexTree;
	PtrVector<int> m_curNumTreeIndices;
	int m_at34;
	int m_at38;
	unsigned char m_pad3C[0x5c0 - 0x3C];
	Rva000EDA94Record m_trees[1200];
	int m_numTrees;
	bool m_anythingChanged;
	unsigned char m_at44545;
	unsigned char m_pad44546[0x44554 - 0x44546];
	bool m_initialized;
	unsigned char m_at44555;
	unsigned char m_at44556;
	unsigned char m_pad44557;
	Rva000EC67F m_treeTypes[64];
	unsigned char m_pad45c58[4];
	unsigned char m_at45C5C;
	unsigned char m_pad45C5D[3];
	int m_treeIndexStep;
	unsigned char m_at45C64;
};

void Rva000EC9C6::rva000EC9C6(int arg)
{
	if (m_at34 == 0)
		return;
	if (m_at44555 == 0)
		return;
	m_at44555 = 0;
	m_at45C5C = 0;
	if (m_at44556 != 0)
	{
		m_at44556 = 0;
		reinterpret_cast<W3DTreeBuffer *>(this)->updateTexture();
	}
	if (m_at38 == 0)
		return;

	unsigned char *slot = reinterpret_cast<unsigned char *>(&m_anythingChanged);
	if (*slot != 0)
	{
		rva000EB6BB();
		*(volatile unsigned char *)((char *)this + 0x45C5C) = 1;
		*slot = 0;
	}
	else
	{
		slot = &m_at44545;
		if (*slot != 0 || m_at45C64 != 0)
		{
			rva000EBFD1();
			m_at45C64 = 0;
			*slot = 0;
		}
	}
	if (*m_curNumTreeIndices.m_start != 0)
		rva000E663B(arg);
}

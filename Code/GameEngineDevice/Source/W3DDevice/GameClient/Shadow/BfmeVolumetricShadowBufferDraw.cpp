// cl: /DNDEBUG /MD /EHsc
// ?drawAndRelease@BfmeVolumetricShadowBufferLocks@@QAEXH@Z @0x00107865 252B via BFME1 BfmeVolumetricShadowBufferDraw donor
// Evidence: frees vertex/index WriteLocks at +0xc/+0x10 via rowed dtors plus operator delete; 30000 compares at +0x14/+0x18 with div; rowed Record_DX8_Polys plus CurrentCaps+0x90 check plus rowed Set_DX8_Render_State plus D3DDevice Draw slot 82; BFME1 donor BfmeVolumetricShadowBufferDraw.cpp names drawAndRelease.
class VertexBufferClass
{
public:
	class WriteLockClass
	{
	public:
		~WriteLockClass();
	};
};

class IndexBufferClass
{
public:
	class WriteLockClass
	{
	public:
		~WriteLockClass();
	};
};

void __cdecl operator delete(void *block);

class ShaderClass;
extern ShaderClass g_00DB5E98;

namespace Debug_Statistics
{
	void __cdecl Record_DX8_Polys_And_Vertices(int polys, int verts, const ShaderClass &shader);
}

class DX8Caps
{
public:
	char m_pad[0x90];
	unsigned int m_caps;
};

struct IDirect3DDevice8;
class DX8Wrapper
{
public:
	static void __cdecl Set_DX8_Render_State(unsigned long state, unsigned int value);
	static DX8Caps *CurrentCaps;
	static IDirect3DDevice8 *D3DDevice;
};

typedef long (__stdcall *BfmeDrawIndexedPrimitive)(IDirect3DDevice8 *, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);

class BfmeVolumetricShadowBufferLocks
{
	VertexBufferClass *m_vertexBuffer;
	IndexBufferClass *m_indexBuffer;
	unsigned int m_unreconstructed008;
	VertexBufferClass::WriteLockClass *m_vertexLock;
	IndexBufferClass::WriteLockClass *m_indexLock;
	unsigned int m_vertexCapacity;
	unsigned int m_indexCapacity;

public:
	void drawAndRelease(int frontFace);
};

void BfmeVolumetricShadowBufferLocks::drawAndRelease(int frontFace)
{
	VertexBufferClass::WriteLockClass *vertexLock = m_vertexLock;
	if (vertexLock != 0) {
		vertexLock->~WriteLockClass();
		operator delete(vertexLock);
	}
	IndexBufferClass::WriteLockClass *indexLock = m_indexLock;
	m_vertexLock = 0;
	if (indexLock != 0) {
		indexLock->~WriteLockClass();
		operator delete(indexLock);
	}
	m_indexLock = 0;
	if (m_vertexCapacity == 30000)
		return;
	unsigned int polygonCount = (30000 - m_indexCapacity) / 3;
	int vertexCount = 30000 - m_vertexCapacity;
	Debug_Statistics::Record_DX8_Polys_And_Vertices(polygonCount * 2, vertexCount * 2, g_00DB5E98);
	IDirect3DDevice8 *device = DX8Wrapper::D3DDevice;
	if (!(DX8Wrapper::CurrentCaps->m_caps & 0x100)) {
		if (!frontFace) {
			DX8Wrapper::Set_DX8_Render_State(0x16, 2);
			DX8Wrapper::Set_DX8_Render_State(0x37, 7);
		} else {
			DX8Wrapper::Set_DX8_Render_State(0x16, 2);
			DX8Wrapper::Set_DX8_Render_State(0x36, 7);
		}
	}
	(*(BfmeDrawIndexedPrimitive **)device)[82](device, 4, 0, 0, vertexCount, 0, polygonCount);
	if (!(DX8Wrapper::CurrentCaps->m_caps & 0x100)) {
		if (!frontFace) {
			DX8Wrapper::Set_DX8_Render_State(0x16, 3);
			DX8Wrapper::Set_DX8_Render_State(0x37, 8);
		} else {
			DX8Wrapper::Set_DX8_Render_State(0x16, 3);
			DX8Wrapper::Set_DX8_Render_State(0x36, 8);
		}
		(*(BfmeDrawIndexedPrimitive **)device)[82](device, 4, 0, 0, vertexCount, 0, polygonCount);
	}
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?D3DDevice@DX8Wrapper@@2PAUIDirect3DDevice8@@A=?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A")
#pragma comment(linker, "/alternatename:?CurrentCaps@DX8Wrapper@@2PAVDX8Caps@@A=?CurrentCaps@DX8Wrapper@@1PAVDX8Caps@@A")

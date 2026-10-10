// cl: /DNDEBUG /MD /EHsc
// ?drawAndRelease@W3DVolumetricShadowManagerV2@@QAEXH@Z @0x00107865 252B via BFME1 BfmeVolumetricShadowBufferDraw donor
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

// Zero Hour shader.h's SHADE_CNST field packing (SHIFT_DEPTHCOMPARE 0, DEPTHMASK 3, COLORMASK 4,
// DSTBLEND 5, FOG 8, PRIGRADIENT 10, SECGRADIENT 13, SRCBLEND 14, TEXTURING 16, ALPHATEST 18,
// CULLMODE 19, POSTDETAILCOLORFUNC 20, POSTDETAILALPHAFUNC 24).
#define BFME_SHADE_CNST(depth_compare, depth_mask, color_mask, src_blend, dst_blend, fog, pri_grad, sec_grad, texture, alpha_test, cullmode, post_det_color, post_det_alpha) \
	(	(depth_compare) << 0 | (depth_mask) << 3 | (color_mask) << 4 | (dst_blend) << 5 | (fog) << 8 | \
		(pri_grad) << 10 | (sec_grad) << 13 | (src_blend) << 14 | (texture) << 16 | \
		(alpha_test) << 18 | (cullmode) << 19 | (post_det_color) << 20 | (post_det_alpha) << 24)

class ShaderClass
{
public:
	ShaderClass(unsigned int bits) : ShaderBits(bits) {}
	unsigned int ShaderBits;
};

// The shader drawAndRelease reports to Debug_Statistics: this unit's initialised .data word at
// VA 0x00DB5E98 (retail 0x00101823 = LEQUAL, no depth/colour writes, dst ONE, primary gradient 6,
// post-detail colour 1). It follows this unit's copies of the header-static name tables
// (NONE/HOLD/KILL/SPAWN, NONE/CATAPULT_ROCK/TREBUCHET_ROCK, NONE/FRONT_DESTROYED..).
// Structural name, not a retail spelling.
ShaderClass BfmeShadowVolumeStatsShader(BFME_SHADE_CNST(3, 0, 0, 0, 1, 0, 6, 0, 0, 0, 0, 1, 0));

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
class W3DVolumetricShadowManagerV2;
class DX8Wrapper
{
	friend class W3DVolumetricShadowManagerV2;
public:
	static void __cdecl Set_DX8_Render_State(unsigned long state, unsigned int value);
protected:
	// dx8wrapper.cpp defines both protected (CurrentCaps@DX8Wrapper@@1PAVDX8Caps@@A and
	// D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A).
	static DX8Caps *CurrentCaps;
	static IDirect3DDevice8 *D3DDevice;
};

typedef long (__stdcall *BfmeDrawIndexedPrimitive)(IDirect3DDevice8 *, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);

class W3DVolumetricShadowManagerV2
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

void W3DVolumetricShadowManagerV2::drawAndRelease(int frontFace)
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
	Debug_Statistics::Record_DX8_Polys_And_Vertices(polygonCount * 2, vertexCount * 2, BfmeShadowVolumeStatsShader);
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


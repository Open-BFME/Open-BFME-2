// cl: /DNDEBUG /MD
//
// ?findTrack@WaterTracksRenderSystem@@QAEPAUFeNode@@PBM0H@Z @0x000FE207 137B.
// Evidence: container +0x10 head and +0xb0 next match Rva000FE001Move;
// float pairs +0x60/+0x64 vs arg2 and +0x58/+0x5c vs arg1 via movss/ucomiss;
// dword +0x30 vs arg3; ret 0xC with 3 stack args; caller 0x000FF7C8.

struct FeNode
{
public:
	char m_pad00[0x30];
	int m_30; // +0x30
	char m_pad34[0x8];
	unsigned char m_flag3c; // +0x3C
	char m_pad3D[0x1B];
	float m_58; // +0x58
	float m_5c; // +0x5C
	float m_60; // +0x60
	float m_64; // +0x64
	char m_pad68[0x48];
	FeNode *m_next; // +0xB0
	FeNode *m_prev; // +0xB4
};

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class ShaderClass {
public:
 ShaderClass() : bits(0x10441b) {}
 static ShaderClass _PresetAlphaShader;
 unsigned int bits;
 enum CullMode { CULL_MODE_DISABLE=0 };
 void Set_Cull_Mode(CullMode) {bits &= 0xffefffff;}
};


class VertexMaterialClass;
class WaterTracksObj;
class DX8VertexBufferClass;
class RenderInfoClass;
enum waveType {WaveTypePond,WaveTypeOcean};

class WaterTracksRenderSystem {
public:
	WaterTracksRenderSystem();
public:
	~WaterTracksRenderSystem();
public:
	void shutdown();
public:
	void releaseTrack(FeNode *);
public:
	void rva000FE8FC(FeNode *);
public:
	void init();
public:
	void ReAcquireResources();
public:
	WaterTracksObj *bindTrack(waveType);
public:
	void rva000FE188();
public:
	__declspec(noinline) FeNode *findTrack(const float *,const float *,int);
public:
	void *vertexBuffer,*indexBuffer;
public:
	VertexMaterialClass *material;
public:
	ShaderClass shader;
public:
	FeNode *m_tail10,*m_head14;
public:
	int stripX,stripY,batch;
public:
	float level;
public:
	AsciiString filename;
public:
	void rva000FE1AC();
public:
	void flush(RenderInfoClass &);
};

inline FeNode *WaterTracksRenderSystem::findTrack(const float *a, const float *b, int c)
{
	FeNode *node = m_tail10;
	while (node != 0)
	{
		unsigned char d1 = (node->m_60 == b[0]) ? 1 : 0;
		unsigned char a1 = (node->m_64 == b[1]) ? 1 : 0;
		if ((d1 & a1) != 0)
		{
			unsigned char d2 = (node->m_58 == a[0]) ? 1 : 0;
			unsigned char a2 = (node->m_5c == a[1]) ? 1 : 0;
			if ((d2 & a2) != 0)
			{
				if (node->m_30 == c)
					return node;
			}
		}
		node = node->m_next;
	}
	return 0;
}
// Select-any: W3DWaterTracks.cpp compiles an identical copy; the anchor keeps the rowed body emitted.
// ?bfmeAnchorRva000FE207Find absent-from-retail
void bfmeAnchorRva000FE207Find(WaterTracksRenderSystem *waterTracksRenderSystem) { waterTracksRenderSystem->findTrack(0, 0, 0); }

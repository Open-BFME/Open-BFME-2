// ?rva000E7546@W3DShrubBuffer@@QAE_NHPAM000@Z
// partial score=0.93 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// W3DShrubBuffer method at retail 0x000E7546 (175 bytes, ret 0x14; BFME1 twin 0x0071CF40, BFME2 layout: 2000 records of 0xA0 at +0x1958, types +0x4FB70): for a visible shrub whose type has a mesh and its +0x44 flag, reports
// the position, ten times the scale and two float pairs of the type, and returns whether it did.

typedef int Int;
typedef float Real;

struct Rva000E7546TypeRecord
{
	void *m_valid;
	unsigned char m_pad04[0x2c - 0x04];
	Real m_shadowAX;
	Real m_shadowAY;
	unsigned char m_pad34[0x3c - 0x34];
	Real m_shadowBX;
	Real m_shadowBY;
	unsigned char m_ready;
	unsigned char m_pad45[0x5c - 0x45];
};

struct Rva000E7546TreeRecord
{
	Real m_posX;
	Real m_posY;
	Real m_posZ;
	Real m_scale;
	unsigned char m_pad10[0x40 - 0x10];
	Int m_treeType;
	unsigned char m_enabled;
	unsigned char m_pad45[0xa4 - 0x45];
};

class W3DShrubBuffer
{
public:
	bool rva000E7546(Int index, Real *outPos, Real *outScale, Real *outShadowA, Real *outShadowB);

private:
	unsigned char m_pad0000[0x1958];
	Rva000E7546TreeRecord m_trees[2000];
	Int m_numTrees;
	unsigned char m_anythingChanged;
	unsigned char m_pad4fb5d[0x4fb70 - 0x4fb5d];
	Rva000E7546TypeRecord m_treeTypes[64];
};

// ?rva000E7546@W3DShrubBuffer@@QAE_NHPAM000@Z
bool W3DShrubBuffer::rva000E7546(Int index, Real *outPos, Real *outScale, Real *outShadowA, Real *outShadowB)
{
	if (index < m_numTrees) {
		Int type = m_trees[index].m_treeType;
		if (type >= 0 && m_trees[index].m_enabled && m_treeTypes[type].m_valid != 0 && m_treeTypes[type].m_ready) {
			outPos[0] = m_trees[index].m_posX;
			outPos[1] = m_trees[index].m_posY;
			outPos[2] = m_trees[index].m_posZ;
			*outScale = m_trees[index].m_scale * 10.0f;
			outShadowA[0] = m_treeTypes[type].m_shadowAX;
			outShadowA[1] = m_treeTypes[type].m_shadowAY;
			outShadowB[0] = m_treeTypes[type].m_shadowBX;
			outShadowB[1] = m_treeTypes[type].m_shadowBY;
			return true;
		}
	}
	return false;
}

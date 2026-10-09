// ?Rva000470D5GetTexture@@YA?AVBFME2ParticleTextureHandle@@PBURva000470D5Source@@@Z
// partial score=0.92 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// NEAR: identical instruction stream except retail loads the hidden return
// pointer into EDI at entry (after push esi/edi) while cl here loads it lazily
// in each branch; also the flag init and push scheduling move with it.
// Unwind dtor 0x0017098D is pinned as ??1BFME2ParticleTextureHandle@@QAE@XZ.
#include "ascii_string.h"
class TextureClass
{
public:
	virtual void slot00();
	unsigned short m_refCount;
	unsigned short m_pad06;
	void Release_Ref();
};
class BFME2ParticleTextureHandle
{
public:
	TextureClass *Ptr;
	BFME2ParticleTextureHandle(const BFME2ParticleTextureHandle &o) : Ptr(o.Ptr)
	{
		if (Ptr)
			++Ptr->m_refCount;
	}
	~BFME2ParticleTextureHandle()
	{
		if (Ptr)
			Ptr->Release_Ref();
	}
};
BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *name, int a, int b);
class ShroudFilter
{
public:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
};
class ShroudTexture
{
public:
	ShroudFilter *getFilter(void);
};
class TextureAsset
{
public:
	void rva00132FE9(bool flag);
};
struct Rva000470D5Source
{
	int m_00;
	int m_04;
	AsciiString m_name08;
	char m_pad0C[0x2C - 0x0C];
	BFME2ParticleTextureHandle *m_texture2C;
	unsigned int m_flags30;
};
BFME2ParticleTextureHandle Rva000470D5GetTexture(const Rva000470D5Source *src)
{
	unsigned int flags = src->m_flags30;
	if (flags & 2) {
		BFME2ParticleTextureHandle tex(*src->m_texture2C);
		((ShroudTexture *)&tex)->getFilter()->m_10 = 1;
		((ShroudTexture *)&tex)->getFilter()->m_0C = 1;
		return tex;
	}
	BFME2ParticleTextureHandle tex = BFME2LoadParticleTexture(src->m_name08.str(), 1, 0);
	((ShroudTexture *)&tex)->getFilter()->m_10 = 1;
	((ShroudTexture *)&tex)->getFilter()->m_0C = 1;
	((TextureAsset *)&tex)->rva00132FE9(true);
	return tex;
}

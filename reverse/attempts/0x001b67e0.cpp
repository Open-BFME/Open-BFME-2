// ?bfmeInitD70@@YAXPAX0@Z
// partial score=0.99 date=2026-09-22
// cl: /DNDEBUG /MD /O2

extern "C" void *__cdecl memset(void *block, int value, unsigned int bytes);
extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int bytes);
#pragma intrinsic(memset, memcpy)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class Bucket
{
public:
	enum BucketMagicEnum { Bucket_GLUE_NOT_IMPLEMENTED = 0 };
	static void *__cdecl operator new(unsigned int bytes, BucketMagicEnum tag);
};

void __declspec(noinline) __cdecl bfmeInitD70(void *self, void *src);

struct BfmeHolderE20
{
	unsigned char m_lead[0x40];
	int m_cfg[14];
	int m_78;
	int m_7C;
	int m_80;
	int m_84;
	int m_88;
	int m_8C;
	int m_90;
	int m_94;
	int m_98;
	int m_9C;
	int m_unusedA0[5];
	int m_B4;
	int m_unusedB8[3];
	int m_flag;
};

// ?bfmeMakeBZB@@YAPAXPAX@Z
void *__cdecl bfmeMakeBZB(void *src)
{
	BfmeHolderE20 *self = (BfmeHolderE20 *)Bucket::operator new(0xC8, Bucket::Bucket_GLUE_NOT_IMPLEMENTED);
	void *result = 0;

	if (self)
	{
		memset(self, 0, 0xC8);
		bfmeInitD70(self, src);
		self->m_flag = 1;
		result = self;
	}

	return result;
}

// ?bfmeInitD70@@YAXPAX0@Z, retail 0x001B67E0, 176 bytes. Config-block scaler
// init behind bfmeMakeBZB: copies the 14-dword config to +0x40, then derives
// the stride parameters at +0x78..+0x9C/+0xB4 with shift/multiply chains.
// Derived members keep position-honest names; the true codec roles are
// unproven (consumers only read +0x0). noinline keeps the rowed maker
// calling out instead of absorbing this body.
void __declspec(noinline) __cdecl bfmeInitD70(void *self, void *src)
{
	BfmeHolderE20 *state = (BfmeHolderE20 *)self;
	unsigned int *cells = (unsigned int *)src;
	unsigned int s0;
	unsigned int w;
	unsigned int h;
	unsigned int e;
	unsigned int t;
	unsigned int st;

	memcpy(state->m_cfg, cells, 14 * sizeof(int));
	s0 = (unsigned int)state->m_cfg[0] >> 3;
	w = state->m_cfg[1];
	h = state->m_cfg[2];
	e = w >> 3;
	state->m_94 = e;
	e *= s0;
	state->m_84 = e;
	st = state->m_cfg[3];
	t = e;
	t >>= 2;
	e += t * 2;
	state->m_8C = e;
	e = s0 * 8;
	state->m_90 = s0;
	s0 = e;
	e = h;
	e -= s0;
	e >>= 1;
	s0 = h + 1;
	s0 *= e;
	state->m_78 = s0;
	s0 = w + e * 2;
	s0 *= h;
	state->m_98 = h;
	h = e;
	w >>= 1;
	w += e;
	h >>= 1;
	w *= st;
	state->m_B4 = e;
	state->m_88 = t;
	e = h * st;
	t = st + 1;
	t *= h;
	w += h;
	t += s0;
	e += w;
	e += s0;
	state->m_7C = t;
	state->m_9C = st;
	state->m_80 = e;
}

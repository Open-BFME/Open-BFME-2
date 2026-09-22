// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /arch:SSE2 /Oi
// Combined TU: thiscall refreshPair (0x00699180) + setVolumes (0x006999C0).
// Helper body is the real member; no stand-in.
//
// Retail bodies: refreshPair 296B @0x00051ED6, refreshAll 28B @0x0005202C.
// Transferred from the BFME1 reconstruction (same Rva00699180Volume.cpp TU
// family). Retail adaptations, all measured from the target bytes:
// float-heavy refreshPair needs /arch:SSE2 with intrinsics (/Oi) so the
// slot copy folds to four movsd and the zero-fill to stosd;
// #pragma optimize("y", off) keeps its ebp frame while frameless
// refreshAll keeps the sibling-loop shape (no this reload); the clamp
// section is a rolled 0..3 loop here, and setVolumes is not claimed.
// Both bodies rowed: the m_scale reference local (float &scale) forces the
// scale-first mulss operand order retail shows (plain member reorder is
// commutative-inert); the pointer homes to eax via lea like retail.

class Rva00699180Owner
{
public:
	void refreshPair(int a, int b);
	void refreshAll();
	void setVolumes(float volume, unsigned char flags);

	char m_pad0[4];
	float m_base[12];
	float m_product[6];
	char m_pad4c[0x94 - 0x4c];
	float m_atten;
	float m_vol;
	float m_scale;
	char m_padA0[0xC8 - 0xA0];
	float m_slot[12][4];
};

extern "C" void *memcpy(void *dst, const void *src, unsigned int n);
extern "C" void *memset(void *dst, int v, unsigned int n);

#pragma optimize("y", off)
// ?refreshPair@Rva00699180Owner@@QAEXHH@Z
void Rva00699180Owner::refreshPair(int a, int b)
{
	int idx = b + a * 2;
	float *slot = (float *)((char *)this + 0xC8 + (idx << 4));
	float old[4];
	memcpy(old, slot, sizeof(old));

	if (a == 5)
	{
		slot[0] = 1.0f;
		slot[1] = 1.0f;
		slot[2] = 1.0f;
		slot[3] = 1.0f;
	}
	else if (*(unsigned char *)0x00DB3F7C)
	{
		slot[0] = *((float *)((char *)this + 4 + idx * 4)) * ((float *)0x00DB3F64)[a] * m_vol;
		if (b == 1)
			slot[0] = slot[0] * m_atten;
		float &scale = m_scale;
		slot[1] = scale * slot[0];
		slot[2] = m_product[a] * slot[0];
		slot[3] = scale * slot[2];

		for (int i = 0; i < 4; ++i)
		{
			float x = slot[i];
			if (x < 0.0f)
				x = 0.0f;
			else if (x > 1.0f)
				x = 1.0f;
			slot[i] = x;
		}
	}
	else
	{
		memset(slot, 0, sizeof(float) * 4);
	}

	for (int i = 0; i < 4; ++i)
	{
		if (slot[i] != old[i])
			*((unsigned char *)this + 0x188 + (b + a * 2) * 4 + i) = 2;
	}
}
#pragma optimize("", on)

// ?refreshAll@Rva00699180Owner@@QAEXXZ
void Rva00699180Owner::refreshAll()
{
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 2; ++j)
			refreshPair(i, j);
	}
}

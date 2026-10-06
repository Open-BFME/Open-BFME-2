// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// ?rva001680A6@Rva001680A6@@QAEXHPAXM@Z @0x001680A6 71B
// Unlock callee of 0x000D0091; guarded 12B copy plus float store plus flag clear.
// Evidence: retail push esi mov esi arg0 cmp esi [ecx+0xd0] jae skip; imul eax esi 0xc add eax [ecx+0xc8]; 3 dword copy via edi; mov eax [ecx+0xd8] movss [eax+esi*4] xmm0; and [ecx+0x12] 0xfd; ret 0xc; callers unclaimed; prev SidesList in Player.cpp contiguous.
class Rva001680A6
{
public:
	void rva001680A6(int index, void *src, float f);
	void rva001680ED(int index, void *dst, float *out);
private:
	char m_pad00[0x12];
	unsigned char m_12;
	char m_pad13[0xC8 - 0x13];
	void *m_c8;
	int m_cc;
	int m_d0;
	char m_padD4[0xD8 - 0xD4];
	float *m_d8;
};
void Rva001680A6::rva001680A6(int index, void *src, float f)
{
	if ((unsigned int)index < (unsigned int)m_d0)
	{
		char *dst = (char *)m_c8 + index * 12;
		int *d = (int *)dst;
		int *s = (int *)src;
		d[0] = s[0];
		d[1] = s[1];
		d[2] = s[2];
		m_d8[index] = f;
	}
	m_12 &= (unsigned char)0xFD;
}
void Rva001680A6::rva001680ED(int index, void *dst, float *out)
{
	if ((unsigned int)index < (unsigned int)m_d0)
	{
		float *src = (float *)((char *)m_c8 + index * 12);
		float *d = (float *)dst;
		d[0] = src[0];
		((int *)d)[1] = ((int *)src)[1];
		((int *)d)[2] = ((int *)src)[2];
		*out = m_d8[index];
	}
	else
	{
		float *d = (float *)dst;
		d[0] = 0.0f;
		d[1] = 0.0f;
		d[2] = 0.0f;
		*out = 0.0f;
	}
}

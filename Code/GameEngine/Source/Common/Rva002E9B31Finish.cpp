// ?Rva002E9B31Get@@YAHPAX@Z
// cl: /DNDEBUG /MD
// ?Rva002E9B31Get@@YAHPAX@Z @0x002E9B31 180B
// Free __cdecl int (void*) over an Object-like layout: +4 template, kind bytes
// +0x109 &4, +0x115 &0x20, +0x11F &0x80, float +0x52C, radius +0xB8.
// Evidence: 9 __cdecl callers; float immediates 2.0 10.0 20.0 0.0 0.1 0.3 at
// .rdata 0xBC28F4 0xBC2428 0xBC5CCC 0xBBAEAC 0xBC2424 0xBCCB3C; floor via
// msvcr71 IAT 0xBBA570; unblocks 0x002EBCA7 0x002EBCD6 0x002EBBFB 0x002EC479
// 0x005852DF.
extern "C" __declspec(dllimport) double __cdecl floor(double);

static __forceinline float fast_floor(float f)
{
	return (float)floor((double)f);
}

static __forceinline int fast_round(float f)
{
	int i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

struct Rva002E9B31Tmpl
{
	unsigned char m_pad00[0x109];
	unsigned char m_109;
	unsigned char m_pad10A[0x115 - 0x10A];
	unsigned char m_115;
	unsigned char m_pad116[0x11F - 0x116];
	unsigned char m_11F;
	unsigned char m_pad120[0x52C - 0x120];
	float m_52C;
};

struct Rva002E9B31Obj
{
	unsigned char m_pad00[4];
	Rva002E9B31Tmpl *m_tmpl;
	unsigned char m_pad08[0xB8 - 8];
	float m_B8;
};
int __cdecl Rva002E9B31Get(void *p)
{
	Rva002E9B31Obj *obj = (Rva002E9B31Obj *)p;
	Rva002E9B31Tmpl *tmpl = obj->m_tmpl;
	int s = 2;
	if ((tmpl->m_109 & 4) != 0 || (tmpl->m_115 & 0x20) != 0 || (tmpl->m_11F & 0x80) != 0)
		s = 4;
	float f = obj->m_B8 * 2.0f;
	if (f > 10.0f)
	{
		if (20.0f > f)
			f = 20.0f;
	}
	// Reading the field twice makes MSVC materialise its address (`add eax,0x52c`)
	// before the load, exactly as retail does; a single read folds the disp.
	if (tmpl->m_52C > 0.0f)
		f = tmpl->m_52C;
	float ff = fast_floor(f * 0.1f + 0.3f);
	int n = fast_round(ff);
	if (n == 0)
		return 1;
	int lim = s + s;
	if (n > lim)
		return lim + 1;
	return n;
}

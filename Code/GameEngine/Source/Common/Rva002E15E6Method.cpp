// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002E15E6@Rva002E15E6@@QAEXXZ @0x002E15E6 41B.
// Reset-after-free: if m_04==0 return; else free m_00->m_04 via rowed
// rva002E0D66, then self-link m_00->m_08 and m_00->m_0C to m_00 and zero
// both m_00->m_04 and m_04. Evidence: callers 0x002E1E19 0x002E30C8;
// callee rowed 0x002E0D66; neighbours share /O1.
class Rva002E0D66
{
public:
	void rva002E0D66(void *head);
};
struct Rva002E15E6Inner
{
	char m_pad[4];
	void *m_04;
	void *m_08;
	void *m_0C;
};
class Rva002E15E6
{
public:
	void rva002E15E6();
private:
	Rva002E15E6Inner *m_00;
	int m_04;
};
void Rva002E15E6::rva002E15E6()
{
	if (m_04 == 0)
		return;
	((Rva002E0D66 *)this)->rva002E0D66(m_00->m_04);
	m_00->m_08 = m_00;
	m_00->m_04 = 0;
	m_00->m_0C = m_00;
	m_04 = 0;
}

// ?Rva002E17A0Copy@@YAPAVRva002E0D93@@PAV1@00@Z @0x002E17A0 54B.
// Array copy via rowed copy-assign: n = end-src (0xD8 records); if n<=0
// return dst; else assign n records advancing src/dst, return final dst.
// Evidence: idiv 0xD8 count plus call rowed 0x002E0D93 op=; caller 0x002E1E9A;
// prev shares /O1.
class Rva002E0D93
{
public:
	Rva002E0D93 &operator=(const Rva002E0D93 &other);
	char m_pad[0xD8];
};
Rva002E0D93 *Rva002E17A0Copy(Rva002E0D93 *src, Rva002E0D93 *srcEnd, Rva002E0D93 *dst)
{
	int n = (int)(srcEnd - src);
	if (n <= 0)
		return dst;
	int i = n;
	do {
		*dst = *src;
		++src;
		++dst;
		--i;
	} while (i != 0);
	return dst;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Rva002E17A0Copy@@YAPAVRva002E0D93@@PAV1@00PADH@Z=?Rva002E17A0Copy@@YAPAVRva002E0D93@@PAV1@00@Z")

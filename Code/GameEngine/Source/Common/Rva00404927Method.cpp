// cl: /MD
// ?rva00404927@Rva00404927@@QAEHPAVRva00404781@@H@Z retail 0x00404927 54B
// Evidence: __thiscall ret 8 takes Rva00404781* plus int; reads m_a[idx] m_b[idx] at +0 +0x50 like Rva00404781; mul by [ecx+8] [ecx+4] sub compare vs [ecx+0x10]*[ecx+0x0C]; callers 0x00404D14 0x0056C1D2
class Rva00404781
{
public:
	float m_a[20]; // +0x00
	float m_b[20]; // +0x50
};
class Rva00404927
{
public:
	int rva00404927(Rva00404781 *p, int idx);
private:
	float m_pad0; // +0x00
	float m_04; // +0x04
	float m_08; // +0x08
	float m_0C; // +0x0C
	float m_10; // +0x10
};

int Rva00404927::rva00404927(Rva00404781 *p, int idx)
{
	float a = p->m_a[idx] * m_08 - p->m_b[idx] * m_04;
	float b = m_10 * m_0C;
	if (a > b)
		return 1;
	return 0;
}

// Complete native 0x00404901..0x00404927 RET8, following RET8 at0x4048FE.
// Semantic donor: BF1 34f59164 Common/S3FloatPredicates.cpp,
// Gen_001de230::bfmeAbove. Target MULSS/SUBSS/COMISS establishes
// second*field08 - first*field04 > field10 and the full int0/1 return.
// The two float arguments and coefficient offsets come from target bytes;
// an application name and common ownership with the indexed sibling above
// are not established. Keep an independent address-owned receiver view.
class Rva00404901Coefficients
{
public:
    int above(float first, float second) const;
private:
    char unknown0[4];
    float field04,field08;
    char unknown0C[4];
    float field10;
};
int Rva00404901Coefficients::above(float first, float second) const
{
    if (second*field08 - first*field04 > field10)
        return 1;
    return 0;
}

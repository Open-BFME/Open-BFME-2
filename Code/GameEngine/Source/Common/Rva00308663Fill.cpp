// cl: /MD
// ?Rva00308663Fill@@YAPAVRva004733E0@@PAV1@IPBV1@@Z, retail 0x00308663, 37B.
// Fill n Rva004733E0 slots via rowed Rva0030CA53Set with a fixed value.
// Evidence: loop calls rowed 0x0030CA53 with (dst, fixed src), dst+=8,
// count--, returns end; caller 0x002828DB in 0x00282870. Honest free-function name.
struct Rva004733E0Obj
{
	int m_00;
	int m_04;
};

class Rva004733E0
{
	int m_00;
	Rva004733E0Obj *m_04;
};

void Rva0030CA53Set(Rva004733E0 *dst, const Rva004733E0 *src);

Rva004733E0 *Rva00308663Fill(Rva004733E0 *dst, unsigned int count, const Rva004733E0 *value)
{
	Rva004733E0 *cur = dst;
	unsigned int n = count;
	if (n > 0)
	{
		do
		{
			Rva0030CA53Set(cur, value);
			cur++;
		} while (--n != 0);
	}
	return cur;
}

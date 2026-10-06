// cl: /MD
//
// ?rva0033A5F4@Rva0033A5F4@@QAEXPAHPAM010@Z @0x0033A5F4 62B
// Five-out-param getter: three ints at +0x5AC/+0x5B0/+0x5B4 and two floats
// at +0x4F8/+0x4FC via x87 fld/fst. Evidence: single caller at 0x000C5A14,
// framed x87 shape. Owning class unproven, hence honest Rva names.

class Rva0033A5F4
{
public:
	void rva0033A5F4(int *o0, float *o1, int *o2, float *o3, int *o4);

private:
	unsigned char m_pad0[0x4F8];
	float m_f0;
	float m_f1;
	unsigned char m_pad1[0x5AC - 0x500];
	int m_i0;
	int m_i1;
	int m_i2;
};

void Rva0033A5F4::rva0033A5F4(int *o0, float *o1, int *o2, float *o3, int *o4)
{
	*o0 = m_i0;
	*o1 = m_f0;
	*o2 = m_i1;
	*o3 = m_f1;
	*o4 = m_i2;
}

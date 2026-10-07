// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva004EABB9@Rva004EABB9@@QAE_NXZ, retail 0x004EABB9, 14 bytes.
// Returns 1 when dwords at +0x34 and +0x3C are both zero.
// Evidence: xor-cmp-jne-cmp-jne-inc shape, caller at 0x004E9DF0.
// ?rva004EABC7@Rva004EABB9@@QAEHXZ, retail 0x004EABC7, 35 bytes.
// Returns 1 when dwords at +0x34 and +0x3C are both 4 and rowed predicate 0x004E9378 is true.

class Rva004E9378
{
public:
	bool rva004E9378();
};

class Rva004EABB9
{
public:
	bool rva004EABB9();
	int rva004EABC7();
private:
	unsigned char pad[0x14];
	Rva004E9378 *m_14;
	unsigned char pad18[0x34 - 0x18];
	int f34;
	unsigned char pad38[0x3C - 0x38];
	int f3C;
};

bool Rva004EABB9::rva004EABB9()
{
	return f34 == 0 && f3C == 0;
}

int Rva004EABB9::rva004EABC7()
{
	if (f34 == 4 && f3C == 4 && m_14 != 0)
	{
		if (m_14->rva004E9378())
			return 1;
	}
	return 0;
}


// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva00319610@Rva00319610@@QAEXXZ @0x00319610 61B
// Unlock-lane void thiscall: gets Ret* via rowed-pin 0x00318C32,
// early-out on null, skips middle checks when pin 0x0031912E is false,
// else requires Ret+0x13C == this+0x54 and rowed 0x003F02E4 true,
// then forwards this+0x20 ScienceType to rowed 0x003F2739.
// Evidence: retail push esi/edi with this in esi and Ret in edi,
// test edi plus test al plus cmp 13C/54 plus rowed predicate,
// caller 0x002B3D4A passes inner-array element as this.
enum ScienceType
{
	SCIENCE_DUMMY = 0
};

class Rva00318C32Ret
{
public:
	char m_pad[0x13C];
	int m_13C;
};

class Rva00318C79Owner
{
public:
	Rva00318C32Ret *rva00318C32();
};

class Rva0031912E
{
public:
	int rva0031912E();
};

class Rva003F02E4
{
public:
	bool rva003F02E4();
};

class Rva003F2739
{
public:
	void rva003F2739(ScienceType v);
};

class Rva00319610
{
public:
	void rva00319610();
private:
	char m_pad00[0x20];
	ScienceType m_20;
	char m_pad24[0x54 - 0x24];
	int m_54;
};

void Rva00319610::rva00319610()
{
	Rva00318C32Ret *p = ((Rva00318C79Owner *)this)->rva00318C32();
	if (p == 0)
		return;
	if ((unsigned char)((Rva0031912E *)this)->rva0031912E() != 0)
	{
		if (*(int *)((char *)p + 0x13C) != m_54)
			return;
		if (!((Rva003F02E4 *)p)->rva003F02E4())
			return;
	}
	((Rva003F2739 *)p)->rva003F2739(m_20);
}

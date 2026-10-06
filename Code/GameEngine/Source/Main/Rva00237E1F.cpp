// cl: /EHsc

// 0x00237E1F 9B: combines two dwords at +0/+4 as (m00<<16)|m04.
// Evidence: leaf, caller 0x0004953C in 2249B FUN_00449271, no callees,
// thiscall, returns int in eax, prev flags fit.

class Rva00237E1F
{
public:
	int rva00237E1F();

private:
	int m_00;
	int m_04;
};

int Rva00237E1F::rva00237E1F()
{
	return (m_00 << 16) | m_04;
}

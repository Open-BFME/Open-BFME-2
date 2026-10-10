// ?rva000B2361@Rva000B2361@@QAEPAHH@Z
// cl: /O1 /DNDEBUG /MD
// Retail 0x000B2361, 31 bytes: maps an index 0/1/2 to the address of one of
// three consecutive dwords at +4/+8/+0xC; any other index yields the first.
// Owner class and field meanings are address-derived and unknown.
class Rva000B2361
{
public:
	int *rva000B2361(int which);
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

int *Rva000B2361::rva000B2361(int which)
{
	switch (which)
	{
	case 0:
		return &m_04;
	case 1:
		return &m_08;
	case 2:
		return &m_0C;
	default:
		return &m_04;
	}
}

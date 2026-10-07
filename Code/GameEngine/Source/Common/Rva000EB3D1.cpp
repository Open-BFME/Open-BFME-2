// cl: /O1 /DNDEBUG /MD
// ?rva000EB3D1@Rva000EB3D1@@QAEXXZ @0x000EB3D1 62B.
// Signed count at +0x44540. Each 0xE8 record at +0x600 calls
// thiscall 0x000EB2EF with the index when dword +0 is non-negative
// and dword +0x88 is non-zero.

struct Rva000EB3D1Elem
{
	int m_key;
	char m_pad[0x84];
	int m_slot;
	char m_tail[0x5C];
};

class Rva000EB3D1
{
public:
	void rva000EB2EF(int index);
	void rva000EB3D1();

	char m_pad[0x600];
	Rva000EB3D1Elem m_elem[1199];
	char m_mid[0xA8];
	int m_count;
};

void Rva000EB3D1::rva000EB3D1()
{
	for (int index = 0; index < m_count; ++index)
	{
		if (m_elem[index].m_key >= 0 && m_elem[index].m_slot != 0)
			rva000EB2EF(index);
	}
}

// cl: /O1 /DNDEBUG /MD
// ?rva000E7B04@Rva000E7B04@@QAEXXZ @0x000E7B04 59B.
// Signed count at +0x4FB58. Each 0xA0 record at +0x1998 calls
// thiscall 0x000E7A40 with the index when dword +0 is non-negative
// and dword +0x44 is non-zero.

struct Rva000E7B04Elem
{
	int m_key;
	char m_pad[0x40];
	int m_slot;
	char m_tail[0x58];
};

class Rva000E7B04
{
public:
	void rva000E7A40(int index);
	void rva000E7B04();

	char m_pad[0x1998];
	Rva000E7B04Elem m_elem[1999];
	char m_mid[0x60];
	int m_count;
};

void Rva000E7B04::rva000E7B04()
{
	for (int index = 0; index < m_count; ++index)
	{
		if (m_elem[index].m_key >= 0 && m_elem[index].m_slot != 0)
			rva000E7A40(index);
	}
}

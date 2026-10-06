// cl: /DNDEBUG /MD
// ?rva005DBBA5@Rva005DBBA5@@QAEHG@Z 0x005DBBA5 28B
// Bounds-checked dword lookup at +0x718 or -1.
// Evidence: caller 0x5A6F5A; unblocks 0x5A6EF2.
class Rva005DBBA5
{
	char m_pad[0x718];
	int m_arr[8];
public:
	int rva005DBBA5(unsigned short idx);
};

int Rva005DBBA5::rva005DBBA5(unsigned short idx)
{
	if (idx >= 8)
		return -1;
	return m_arr[idx];
}

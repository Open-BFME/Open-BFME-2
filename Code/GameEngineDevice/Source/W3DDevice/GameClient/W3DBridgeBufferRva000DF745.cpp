// cl: /O1 /DNDEBUG /MD
// ?rva000DF745@W3DBridgeBuffer@@QAEXHH@Z @0x000DF745 49B.
// Calls rowed 0x000DD878 with the first arg, then 0x000DF52C with the
// second when byte +0xD7B6 is set or dword +0xC is zero. Clears +0xD7B5.

class W3DBridgeBuffer
{
public:
	void rva000DD878(int value);
	void rva000DF52C(int value);
	void rva000DF745(int first, int second);

	char m_pad[0xC];
	int m_c;
	char m_pad10[0xD7B5 - 0x10];
	unsigned char m_d7b5;
	unsigned char m_d7b6;
};

void W3DBridgeBuffer::rva000DF745(int first, int second)
{
	rva000DD878(first);
	if (m_d7b6 != 0 || m_c == 0)
		rva000DF52C(second);
	m_d7b5 = 0;
}

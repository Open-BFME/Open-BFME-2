// cl: /MD
// ?rva003B24C7@Rva003B24C7@@QAEX_N@Z 0x003B24C7 20B
// Evidence: bool setter storing flag at +0; when false zeroes dword at +4
// and byte at +1 reusing the parameter register; callers 0x00207557.
typedef bool Bool;

class Rva003B24C7
{
	Bool m_flag;
	unsigned char m_b;
	char m_pad[2];
	int m_val;

public:
	void rva003B24C7(Bool val);
};

void Rva003B24C7::rva003B24C7(Bool val)
{
	m_flag = val;
	if (!val) {
		m_val = 0;
		m_b = 0;
	}
}

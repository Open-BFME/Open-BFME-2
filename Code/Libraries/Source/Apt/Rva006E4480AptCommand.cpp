// cl: /MD /O2 /arch:SSE
// ?rva006E4480@Rva006E34D0@@QAEXHHEH@Z at 0x006E4480 (98B). The same receiver calls rowed Rva006E34D0::rva006E34D0; retail writes records at +0x7C/+0x8C for IDs 0x1F5/0x1F6.
class Rva006E34D0
{
public:
	void rva006E34D0(int value);
	void rva006E4480(int first, int second, unsigned char flag, int eventId);

private:
	char pad00[0x3c];
	int m_count;
	int *m_arr;
	char pad44[0x7c - 0x44];
	int m_7c;
	int m_80;
	unsigned char m_84;
	char pad85[7];
	int m_8c;
	int m_90;
	unsigned char m_94;
	char pad95[0xac - 0x95];
	int m_cap;
};

void Rva006E34D0::rva006E4480(int first, int second, unsigned char flag, int eventId)
{
	if (eventId == 0x1f5)
	{
		m_7c = first;
		m_80 = second;
		m_84 = flag;
	}
	else if (eventId == 0x1f6)
	{
		m_8c = first;
		m_90 = second;
		m_94 = flag;
	}
	int packed = eventId;
	packed <<= 15;
	packed |= flag;
	packed <<= 2;
	packed |= 1;
	rva006E34D0(packed);
}

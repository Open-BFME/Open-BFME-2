// cl: /O1 /arch:SSE /G7 /MD
// ?rva001EB0B9@Rva001EB0B9@@QAEEXZ @0x001EB0B9 17B
// Evidence: unlock; ptr at +0x10 null-check then byte at +0xC2; caller 0x0041B054.
struct Rva001EB0B9Inner
{
	char m_pad00[0xC2];
	unsigned char m_flagC2;
};

class Rva001EB0B9
{
public:
	unsigned char rva001EB0B9();
private:
	char m_pad00[0x10];
	Rva001EB0B9Inner *m_ptr10;
};

unsigned char Rva001EB0B9::rva001EB0B9()
{
	if (m_ptr10)
		return m_ptr10->m_flagC2;
	return 0;
}

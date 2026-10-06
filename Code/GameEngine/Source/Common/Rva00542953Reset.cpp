// cl: /MD /Oi-
// ?rva00542953@Rva00542953@@QAEXPADHHHH@Z @0x00542953 31B
// Reset parser state: flush pending byte via 0x005427F1 then clear +0x1C/+0x28 and copy 5 dwords of args to +0x00. Evidence: retail bytes chain lane plus neighbours Rva005426DBDecode and Rva00542806Init same +0x20/+0x24 layout and rep movsd 5 with ret 0x14.
class Rva005427F1
{
public:
	void rva005427F1();
};

struct Rva00542953Args
{
	char *a1;
	int a2;
	int a3;
	int a4;
	int a5;
};

class Rva00542953
{
public:
	void rva00542953(char *a1, int a2, int a3, int a4, int a5);
private:
	Rva00542953Args m_args;
	int m_14;
	int m_18;
	int m_1c;
	char *m_20;
	unsigned char m_24;
	char m_pad25[3];
	int m_28;
};

void Rva00542953::rva00542953(char *a1, int a2, int a3, int a4, int a5)
{
	((Rva005427F1 *)this)->rva005427F1();
	m_1c = 0;
	m_28 = 0;
	m_args = *(Rva00542953Args *)&a1;
}

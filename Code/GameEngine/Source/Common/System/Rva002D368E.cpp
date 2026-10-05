// cl: /O1
// ?rva002D368E@Rva002D368E@@QAEXXZ retail 0x002D368E 32B. Dual-subobject reset via mid pointer.
// Evidence: callees rowed 0x00528FD9 reset and 0x00528273 clear; callers 0x0031BF64 0x0053E4F1; neighbours 0x002D3627 0x002D36C3 same /O1.
class Rva00528FD9Owner
{
public:
	void reset();
private:
	int m_pad;
};

class Rva00528273
{
public:
	void rva00528273();
private:
	int m_pad;
};

struct Rva002D368EMid
{
	char m_pad[0x8C];
	Rva00528FD9Owner m_8C;
	Rva00528273 m_90;
};

class Rva002D368E
{
public:
	void rva002D368E();
private:
	char m_pad[0x10];
	Rva002D368EMid *m_10;
};

void Rva002D368E::rva002D368E()
{
	m_10->m_8C.reset();
	m_10->m_90.rva00528273();
}

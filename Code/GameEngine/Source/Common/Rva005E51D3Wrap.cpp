// cl: /O1 /DNDEBUG /MD
// ?rva005E51D3@Rva005E51D3@@QAEXXZ @0x005E51D3 31B lea-call-push-call.
// Same shape as twins 0x005E3E41/0x005E4389 but first is empty 0x00B3FD0.
// Address-derived.
class Rva005E51D3Inner
{
public:
	int m_pad0;
	int m_4;
};

class Rva000B3FD0Empty
{
public:
	void rva000B3FD0Empty();
};

class Rva005E50E1
{
public:
	void rva005E50E1(int a);
};

class Rva005E51D3
{
public:
	void rva005E51D3();
};

void Rva005E51D3::rva005E51D3()
{
	unsigned char *th = (unsigned char *)this;
	Rva005E51D3Inner **ppOuter = (Rva005E51D3Inner **)(th - 0x14);
	Rva005E51D3Inner *pOuter = *ppOuter;
	int inner4 = pOuter->m_4;
	Rva000B3FD0Empty *pFirst = (Rva000B3FD0Empty *)(inner4 + (int)th - 0x14);
	pFirst->rva000B3FD0Empty();
	int arg = *(int *)(th - 0x0C);
	Rva005E50E1 *pSecond = *(Rva005E50E1 **)(th - 0x10);
	pSecond->rva005E50E1(arg);
}

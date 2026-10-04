// cl: /O1 /MD
// ?rva003EFE3E@Rva003EFE3E@@QAEXH@Z, retail 0x003EFE3E, 37 bytes.
// Store int at +0x140, if global g_009FE1C8->m_268 non-null call its
// Rva003EF13E::rva003EF08B with this as int (pin takes int). Evidence: rowed
// pin 0x003EF08B, callers 0x0057DC8D 0x0057DCC6 0x0057DD25, prev/next /O1 /MD.
class Rva003EF13E
{
public:
	void rva003EF08B(int value);
};

class Rva0021294A
{
public:
	char m_pad[0x268];
	Rva003EF13E *m_268;
};

extern Rva0021294A *g_009FE1C8;

class Rva003EFE3E
{
public:
	void rva003EFE3E(int value);
private:
	char m_pad[0x140];
	int m_140;
};

void Rva003EFE3E::rva003EFE3E(int value)
{
	m_140 = value;
	Rva003EF13E *obj = g_009FE1C8->m_268;
	if (!obj)
		return;
	obj->rva003EF08B((int)this);
}

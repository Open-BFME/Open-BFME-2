// cl: /O1 /MD /EHsc
// ??1Rva005E9625@@UAE@XZ, RVA 0x005E9625, 53 bytes.
// Dtor via base 0x005FA393 plus member 0x005FA874 at +0xC; novtable suppresses vptr store.
// Evidence: callees rowed in Rva005FA874Clear.cpp and Rva005FA393Dtor.cpp; neighbours 0x005E95E9 0x005E9742 share /O1 /MD; callers 0x005E96DF 0x005E9705 0x005E971F.
struct Rva005FA874
{
	void rva005FA874();
};
struct Rva005FA393
{
	virtual ~Rva005FA393();
};
class __declspec(novtable) Rva005E9625 : public Rva005FA393
{
public:
	~Rva005E9625();
private:
	char m_pad[8]; // +4..+0xB over base 4B to place m_c at +0xC
	Rva005FA874 m_c; // +0xC
};
Rva005E9625::~Rva005E9625()
{
	m_c.rva005FA874();
}

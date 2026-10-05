// ??1Rva005E80FD@@UAE@XZ
// partial score=0.9 date=2026-10-05
// ??1Rva005E80FD@@UAE@XZ
// cl: /O1 /MD /EHsc
//
// ??1Rva005E80FD@@UAE@XZ, retail 0x005E80FD 134B: virtual dtor (slot 0 of vtable 0x00C77F54)
// with three vptrs (+0x00 +0x08 +0x0C), two CreateAHeroData erases via 0x002B7250 (+0x18/+0x1C),
// vector dtor at +0x24 via 0x005E8005, clear at +0x20 via 0x005E7FC8, then base 0x005F7750.
//
// Evidence: pin name; caller deleting dtor 0x005E8240; callees __EH_prolog 0x00629188
// rva002B7250Erase 0x002B7250 (twice) Rva005E8005 0x005E8005 clear 0x005E7FC8 base 0x005F7750;
// vtable immediates g_00C77F54 g_00C77F44 g_00C77F34 g_00BC6F34.
extern const void *const g_00C77F54[];
extern const void *const g_00C77F44[];
extern const void *const g_00C77F34[];
extern const void *const g_00BC6F34[];
class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};
class Rva005E8005
{
public:
	~Rva005E8005();
};
class Rva005E7FC8
{
public:
	void clear();
};
class Rva005F7750
{
public:
	virtual ~Rva005F7750();
};
class Rva005E80FD : public Rva005F7750
{
public:
	virtual ~Rva005E80FD();
private:
	char m_pad04[0x04];
	void *m_sec08;
	void *m_sec0C;
	unsigned char m_pad10[0x18 - 0x10];
	void *m_mem18;
	void *m_mem1C;
	void *m_mem20;
	void *m_mem24;
};
struct Rva002B7250Wrap
{
	Rva002B7250 m_erase;
};
// ??1Rva005E80FD@@UAE@XZ present-unmatched
Rva005E80FD::~Rva005E80FD()
{
	*(const void **)this = g_00C77F54;
	void *sec08 = (char *)this + 8;
	void *sec0C = (char *)this + 0x0C;
	*(const void **)sec08 = g_00C77F44;
	*(const void **)sec0C = g_00C77F34;
	int four = 4;
	((Rva002B7250 *)((char *)m_mem1C + four))->rva002B7250((CreateAHeroData *)sec0C);
	((Rva002B7250 *)((char *)m_mem18 + 8))->rva002B7250((CreateAHeroData *)sec08);
	((Rva005E8005 *)((char *)this + 0x24))->~Rva005E8005();
	((Rva005E7FC8 *)((char *)this + 0x20))->clear();
	*(const void **)sec0C = g_00BC6F34;
	*(const void **)sec08 = g_00C77F44;
	Rva005F7750::~Rva005F7750();
}

// cl: /DNDEBUG /MD /EHsc /Ob2
//
// ??0Rva0055B52E@@QAE@IPBURva0055B52ESrc@@@Z, retail 0x0055b52e, 145 bytes. Banked partial (score 0.93) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Ctor via rowed base 0x0055BCD2 plus member 0x0055B32B plus 8x getValue fill plus rowed 0x0055B39C.
// Evidence: thiscall 2 args ret 8; calls rowed ??0Rva0055BCD2@@QAE@I@Z 0x0055BCD2 and ??0Rva0055B32B@@QAE@XZ 0x0055B32B and ?getValue@GameClientRandomVariable@@QBEMXZ 0x002341A1 and ?computeAlphaRate@Rva0055B39C@@QAEXXZ 0x0055B39C; vtable VA 0x00C1D11C plus member VA 0x0081D10C plus s_slot3E4first; caller 0x003AC905; neighbours 0x0055B44D 0x0055B5BF same FXParticleSystem.
class Rva0055BCD2
{
public:
	Rva0055BCD2(unsigned int a);
	virtual ~Rva0055BCD2();
private:
	char m_pad[8];
};

struct Rva0055B32BKey
{
	float m_value;
	unsigned int m_frame;
};

class Rva0055B32B
{
public:
	Rva0055B32B();
	virtual ~Rva0055B32B();
public:
	Rva0055B32BKey m_keys[8];
};

class GameClientRandomVariable
{
public:
	float getValue() const;
	int m_type;
	float m_low;
	float m_high;
};

class Rva0055B39C
{
public:
	void computeAlphaRate();
};

// The retail table at RVA 0x0081D11C: 6 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003ADFB2@@UAEPAXI@Z")();
void __identifier("?updateAlpha@Rva0055B39C@@QAEXXZ")();
int __cdecl _purecall(void);
void __identifier("?xfer@Rva0055B3D9@@UAEXPAVXfer@@@Z")();
void __identifier("?rva0055B417@Rva0055B417@@QBE_NH@Z")();
void __identifier("?get@Rva0008BB58FloatField@@QBEMXZ")();
}
extern const void *const g_00C1D11C[6] = {
	(const void *)&__identifier("??_GRva003ADFB2@@UAEPAXI@Z"), // slot 0 0x003AE270
	(const void *)&__identifier("?updateAlpha@Rva0055B39C@@QAEXXZ"), // slot 1 0x0055B489
	(const void *)&__identifier("_purecall"), // slot 2 0x0003B810
	(const void *)&__identifier("?xfer@Rva0055B3D9@@UAEXPAVXfer@@@Z"), // slot 3 0x0055B3D9
	(const void *)&__identifier("?rva0055B417@Rva0055B417@@QBE_NH@Z"), // slot 4 0x0055B417
	(const void *)&__identifier("?get@Rva0008BB58FloatField@@QBEMXZ"), // slot 5 0x0008BB58
};
extern "C" char s_slot3E4first;

struct Rva0055B52ESrcElem
{
	GameClientRandomVariable m_var;
	unsigned int m_frame;
};

struct Rva0055B52ESrc
{
	char m_pad[0x20];
	Rva0055B52ESrcElem m_elems[8];
};

class __declspec(novtable) Rva0055B52E : public Rva0055BCD2
{
public:
	Rva0055B52E(unsigned int a, const Rva0055B52ESrc *src);
	~Rva0055B52E();
private:
	Rva0055B32B m_member;
	float m_time;
	float m_result;
	unsigned int m_index;
};

Rva0055B52E::Rva0055B52E(unsigned int a, const Rva0055B52ESrc *src)
	: Rva0055BCD2(a)
{
	*(const void **)&m_member = (const void *)"HZz";
	*(const void **)this = g_00C1D11C;
	*(void **)((char *)this + 8) = (void *)&s_slot3E4first;
	unsigned int *zDst = &m_member.m_keys[0].m_frame;
	const unsigned int *aSrc = &src->m_elems[0].m_frame;
	unsigned int count = 8;
	do {
		*(float *)(zDst - 1) = ((const GameClientRandomVariable *)(aSrc - 3))->getValue();
		*zDst = *aSrc;
		aSrc += 4;
		zDst += 2;
	} while (--count != 0);
	m_time = m_member.m_keys[0].m_value;
	m_index = 1;
	((Rva0055B39C *)this)->computeAlphaRate();
}

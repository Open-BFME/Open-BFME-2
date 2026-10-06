// cl: /DNDEBUG /MD /EHsc /Ob2
//
// ??0Rva0055B52E@@QAE@IPBURva0055B52ESrc@@@Z, retail 0x0055b52e, 145 bytes. Banked partial (score 0.93) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Ctor via rowed base 0x0055BCD2 plus member 0x0055B32B plus 8x getValue fill plus rowed 0x0055B39C.
// Evidence: thiscall 2 args ret 8; calls rowed ??0Rva0055BCD2@@QAE@I@Z 0x0055BCD2 and ??0Rva0055B32B@@QAE@XZ 0x0055B32B and ?getValue@GameClientRandomVariable@@QBEMXZ 0x002341A1 and ?rva0055B39C@Rva0055B39C@@QAEXXZ 0x0055B39C; vtable VA 0x00C1D11C plus member VA 0x0081D10C plus s_slot3E4first; caller 0x003AC905; neighbours 0x0055B44D 0x0055B5BF same FXParticleSystem.
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
	void rva0055B39C();
};

extern const void *const g_00C1D11C[];
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
	unsigned int n = 8;
	do {
		*(float *)(zDst - 1) = ((const GameClientRandomVariable *)(aSrc - 3))->getValue();
		*zDst = *aSrc;
		aSrc += 4;
		zDst += 2;
	} while (--n != 0);
	m_time = m_member.m_keys[0].m_value;
	m_index = 1;
	((Rva0055B39C *)this)->rva0055B39C();
}

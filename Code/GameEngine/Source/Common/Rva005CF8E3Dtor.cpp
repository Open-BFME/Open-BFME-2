// cl: /O1 /MD /EHsc
// ??1Rva005CF8E3@@UAE@XZ @0x005CF8E3 48B via member 0x0057417E at +8 plus vtable 0x00875290
// Evidence: LINK BONUS 86B; deleting dtor 0x005CFCB8 calls it; caller ??1Rva005D078B 0x005D07CE; lea ecx [esi+8] call pinned ??1Rva0057417E@@QAE@XZ; mov [esi] vtable; precedent Rva005E9FC1Dtor 0x005EA224 same member same size.
extern const void *const g_00C75290[];

class Rva0057417E
{
public:
	~Rva0057417E();
private:
	unsigned long m_time;
	bool m_flag;
};

struct Rva005CF8E3Base
{
	virtual ~Rva005CF8E3Base();
	void *m_04;
};

// ??1Rva005CF8E3Base@@UAE@XZ present-unmatched
inline Rva005CF8E3Base::~Rva005CF8E3Base()
{
	*(const void **)this = g_00C75290;
}

class __declspec(novtable) Rva005CF8E3 : public Rva005CF8E3Base
{
public:
	virtual ~Rva005CF8E3();
private:
	Rva0057417E m_08;
};

Rva005CF8E3::~Rva005CF8E3()
{
}

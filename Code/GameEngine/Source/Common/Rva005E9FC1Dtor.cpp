// cl: /O1 /MD /EHsc
// ??1Rva005E9FC1@@UAE@XZ retail 0x005EA224 48 bytes.
// Dtor destroys member at +8 via pinned 0x0057417E then restores base vtable 0x008780F4.
// Evidence: slot-0 deleting dtor at 0x005EA208 calls this body; lea ecx [esi+8] call 0x0057417E pinned ??1Rva0057417E@@QAE@XZ; mov [esi] 0x008780F4; layout from rowed ctor 0x005E9FC1 in Rva005E9FC1Ctor.cpp.
extern const void *const g_00C780F4[];

class Rva0057417E
{
public:
	~Rva0057417E();
private:
	unsigned long m_time;
	bool m_flag;
};

struct Rva005E9FC1Base
{
	virtual ~Rva005E9FC1Base();
	void *m_04;
};

// ??1Rva005E9FC1Base@@UAE@XZ present-unmatched
inline Rva005E9FC1Base::~Rva005E9FC1Base()
{
	*(const void **)this = g_00C780F4;
}

class __declspec(novtable) Rva005E9FC1 : public Rva005E9FC1Base
{
public:
	virtual ~Rva005E9FC1();
private:
	Rva0057417E m_08;
};

Rva005E9FC1::~Rva005E9FC1()
{
}

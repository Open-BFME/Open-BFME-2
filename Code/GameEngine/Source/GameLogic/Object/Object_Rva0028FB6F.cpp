// cl: /DNDEBUG /MD /GX-
// ?rva0028FB6F@Object@@QAEXPAX@Z, retail 0x0028FB6F, 79 bytes.
// Object status-mask consumer: takes an opaque param whose Helper lives at
// +0x250, fetches a mask through Helper vtable slot 44 (0xB0) with a 16B
// stack temp plus this plus 0, feeds it to rowed Object::Rva0028CDEB, then
// clears +0x439 bit0 and zeroes +0x274/+0x27C. Evidence: thiscall ret 4;
// virtual [eax+0xB0] with (temp,this,0); pin ?Rva0028CDEB@Object@@QAEXPAUObjectStatusMask@@@Z;
// 23B caller passes own +0x274 then destroys; frameless esi save.
struct ObjectStatusMask;

struct Param
{
	char m_pad[0x250];
	class Helper *m_helper;
};

struct Temp16
{
	unsigned char m_data[0x10];
};

class Helper
{
public:
	virtual void *d00(); virtual void *d01(); virtual void *d02(); virtual void *d03();
	virtual void *d04(); virtual void *d05(); virtual void *d06(); virtual void *d07();
	virtual void *d08(); virtual void *d09(); virtual void *d10(); virtual void *d11();
	virtual void *d12(); virtual void *d13(); virtual void *d14(); virtual void *d15();
	virtual void *d16(); virtual void *d17(); virtual void *d18(); virtual void *d19();
	virtual void *d20(); virtual void *d21(); virtual void *d22(); virtual void *d23();
	virtual void *d24(); virtual void *d25(); virtual void *d26(); virtual void *d27();
	virtual void *d28(); virtual void *d29(); virtual void *d30(); virtual void *d31();
	virtual void *d32(); virtual void *d33(); virtual void *d34(); virtual void *d35();
	virtual void *d36(); virtual void *d37(); virtual void *d38(); virtual void *d39();
	virtual void *d40(); virtual void *d41(); virtual void *d42(); virtual void *d43();
	virtual struct ObjectStatusMask *getMask(void *temp, class Object *obj, int zero);
};

class Object
{
public:
	void rva0028FB6F(void *param);
	void Rva0028CDEB(struct ObjectStatusMask *mask);
private:
	char m_pad00[0x274];
	void *m_274;
	char m_pad278[0x27C - 0x278];
	void *m_27C;
	char m_pad280[0x439 - 0x280];
	unsigned char m_439;
};

void Object::rva0028FB6F(void *param)
{
	Helper *helper = (param != 0) ? ((Param *)param)->m_helper : 0;
	if (helper != 0) {
		Temp16 temp;
		struct ObjectStatusMask *mask = helper->getMask(&temp, this, 0);
		Rva0028CDEB(mask);
	}
	m_439 &= (unsigned char)0xFE;
	m_274 = 0;
	m_27C = 0;
}

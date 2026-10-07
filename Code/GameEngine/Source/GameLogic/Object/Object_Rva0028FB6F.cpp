// cl: /DNDEBUG /MD /GX-
// ?rva0028FB6F@Object@@QAEXPAX@Z, retail 0x0028FB6F, 79 bytes.
// Object status-mask consumer: takes an opaque param whose Helper lives at
// +0x250, fetches a 16B result through Helper vtable slot 44 (0xB0),
// and passes it with false to the rowed Object::rva0028CDEB. The boolean
// is pushed before the virtual call but belongs to the outer setter.
// Clears +0x439 bit0 and zeroes +0x274/+0x27C. Evidence: thiscall ret 4;
// native setter 0x28CDEB consumes mask and bool (RET8); module identity unproven.
// 23B caller passes own +0x274 then destroys; frameless esi save.
class Rva00346BC0
{
public:
	unsigned int m_words[4];
};

class Object;

struct Param
{
	char m_pad[0x250];
	class Helper *m_helper;
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
	virtual Rva00346BC0 getMask(Object *obj);
};

class Object
{
public:
	void rva0028FB6F(void *param);
	void rva0028CDEB(const Rva00346BC0 &mask, bool set);
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
		rva0028CDEB(helper->getMask(this), false);
	}
	m_439 &= (unsigned char)0xFE;
	m_274 = 0;
	m_27C = 0;
}

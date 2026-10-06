// cl: /MD
// ?rva005F6A30@Rva005F6A30@@QAEXXZ retail 0x005F6A30 20 bytes.
// Evidence: leaf lane conditional virtual slot 0x08 on member +4 with outer this as arg plus byte clear +0x18 plus caller 0x005F6A90.
// Model: __thiscall method over member pointer at +4 cleaned via virtual slot 2 taking outer plus flag at +0x18.
class Rva005F6A30Member
{
public:
	virtual void m0();
	virtual void m1();
	virtual void m2(void *outer);
};

class Rva005F6A30
{
public:
	virtual ~Rva005F6A30();
	void rva005F6A30();
private:
	Rva005F6A30Member *m_ptr;
	unsigned char _pad[16];
	bool m_flag;
};

void Rva005F6A30::rva005F6A30()
{
	m_flag = false;
	if (m_ptr == 0)
		return;
	m_ptr->m2(this);
}

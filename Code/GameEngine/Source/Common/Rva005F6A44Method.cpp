// cl: /MD
// ?rva005F6A44@Rva005F6A44@@QAEXXZ retail 0x005F6A44 20 bytes.
// Evidence: leaf lane conditional virtual slot 0x0C on member +4 with outer this as arg plus byte set +0x18 plus caller 0x005F6A98; twin of rowed 0x005F6A30 which clears the flag and calls slot 0x08.
class Rva005F6A44Member
{
public:
	virtual void m0();
	virtual void m1();
	virtual void m2();
	virtual void m3(void *outer);
};

class Rva005F6A44
{
public:
	virtual ~Rva005F6A44();
	void rva005F6A44();
private:
	Rva005F6A44Member *m_ptr;
	unsigned char _pad[16];
	bool m_flag;
};

void Rva005F6A44::rva005F6A44()
{
	m_flag = true;
	if (m_ptr == 0)
		return;
	m_ptr->m3(this);
}

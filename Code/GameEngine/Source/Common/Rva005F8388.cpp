// cl: /MD
// ?rva005F8388@Rva005F8388@@QAEXXZ @0x005F8388 33B
// Evidence: chain lane, calls rowed 0x00577966 tail; no caller/vtable, honest Rva name.
class Virt005F8388Helper
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual bool v15(void *a, void *b);
};

class Rva00577936
{
public:
	virtual void rva00577966();
};

class Rva005F8388
{
public:
	void rva005F8388();
private:
	unsigned char m_00[8];
	Virt005F8388Helper *m_08;
	unsigned char m_0C[0xC];
	unsigned char m_18;
};

void Rva005F8388::rva005F8388()
{
	if (!m_08->v15(m_0C, &m_18))
		return;
	return ((Rva00577936 *)this)->Rva00577936::rva00577966();
}

// cl: /MD
// ?rva004E6273@Rva004E6273@@QAEXXZ @ 0x004E6273 (34B): guarded virtual call through +0x10 target slot 0x38 with (m_index m_other 1 1). Early-out when target null or index negative. Unblocks 0x004E63DB thunk which does mov ecx-[ecx] then jmp here. Caller is jmp at 0x004E63DD.
struct Rva004E6273Target
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void meth(int a, int b, int c, int d);
};
struct Rva004E6273
{
	char m_lead[0x10];
	Rva004E6273Target *m_ptr;
	int m_index;
	int m_other;
	void rva004E6273();
};
void Rva004E6273::rva004E6273()
{
	if (m_ptr == 0)
		return;
	int idx = m_index;
	if (idx < 0)
		return;
	m_ptr->meth(idx, m_other, 1, 1);
}

class Rva004E63DB
{
public:
	void rva004E63DB();
private:
	Rva004E6273 *m_ptr;
};

void Rva004E63DB::rva004E63DB()
{
	m_ptr->rva004E6273();
}

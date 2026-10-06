// cl: /MD
// ?rva0056B970@Rva0056B970@@QAEXI@Z @0x0056B970 20B:
// Rva0056B970::rva0056B970 early-outs unless byte at +0x5d of ptr at +0xac,
// then tail-calls virtual 0x1c forwarding arg. Caller 0x003FDE50.
// Vtable slot 0x1c member 0xac from retail.
struct Rva0056B970Ac
{
	char m_pad[0x5D];
	unsigned char m_flag;
};
class Rva0056B970
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1cfunc(unsigned int arg);
private:
	char m_pad2[0xAC - 4];
	Rva0056B970Ac *m_ac;
public:
	void rva0056B970(unsigned int arg);
};
void Rva0056B970::rva0056B970(unsigned int arg)
{
	if (m_ac->m_flag == 0)
		return;
	v1cfunc(arg);
}

// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002D3389@Rva002D3389@@QAEXPAX@Z retail 0x002D3389 22 bytes. Owning-pointer
// setter at +0 that deletes the old value via rowed operator delete 0x0002FD60
// when the new pointer differs. Evidence: callers 0x002D37AA and 0x002D49DD pass
// a fresh operator-new result; same /O1 as neighbours 0x002D337F and 0x002D342A.

void __cdecl operator delete(void *p);

class Rva002D3389
{
public:
	void rva002D3389(void *p);
private:
	void *m_ptr;
};

void Rva002D3389::rva002D3389(void *p)
{
	void *old = m_ptr;
	if (p != old)
	{
		m_ptr = p;
		operator delete(old);
	}
}

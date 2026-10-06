// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002B2F49@Rva002B2F49@@QAEPAXI@Z @0x002B2F49 40B
// Conditional release plus conditional delete: if holder at +0 is present
// release its embedded TargetRef at +0xAC via rowed 0x0007DEEF, then if
// flag&1 delete this via rowed 0x0002FD60 and return this. Evidence:
// callers pass flag; ret 4 with eax=this; neighbours are /O1.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
void __cdecl operator delete(void *p);

struct Rva002B2F49Inner
{
	char m_pad[0xAC];
	TargetRef00217D4C m_ref;
};

class Rva002B2F49
{
public:
	void *rva002B2F49(unsigned int flag);

private:
	Rva002B2F49Inner *m_ptr;
};

void *Rva002B2F49::rva002B2F49(unsigned int flag)
{
	if (m_ptr)
		ReleaseTreeHintRef00217D4C(&m_ptr->m_ref);
	if (flag & 1)
		::operator delete(this);
	return this;
}

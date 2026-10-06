// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva000B2D4D@Rva000B2D4D@@QAEXHH@Z @0x000B2D4D 17B:
// Null-guarded delegate to +0x10 target slot 3 (void,int,int): if (!m_ptr)
// return; return m_ptr->target(a,b) for tail jmp. Callers 0x000BC954
// 0x000BCCE5. Owner unproven honest Rva.
struct ITarget000B2D4D {
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void target(int a, int b);
};
struct Rva000B2D4D {
	char pad[0x10];
	ITarget000B2D4D *m_ptr;
	void rva000B2D4D(int a, int b);
};
void Rva000B2D4D::rva000B2D4D(int a, int b)
{
	if (!m_ptr)
		return;
	return m_ptr->target(a, b);
}

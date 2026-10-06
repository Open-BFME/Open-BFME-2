// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva000514EB@Rva000514EB@@QAEXXZ @0x000514EB 16B
// Guarded decrement at +0x684. Evidence: __thiscall via ecx plus no
// stack args plus ret; lea plus test plus jbe plus dec plus store;
// 3 callers plus 3 unblocks; name stays address-derived.
class Rva000514EB
{
public:
	void rva000514EB();
	void rva000514FB();

private:
	char m_pad[0x684];
	unsigned m_count684;
	unsigned m_count688; // +0x688
};

void Rva000514EB::rva000514EB()
{
	unsigned *p = (unsigned *)((char *)this + 0x684);
	if (*p <= 0u)
		return;
	--(*p);
}

void Rva000514EB::rva000514FB()
{
	unsigned *p = (unsigned *)((char *)this + 0x688);
	if (*p <= 0u)
		return;
	--(*p);
}

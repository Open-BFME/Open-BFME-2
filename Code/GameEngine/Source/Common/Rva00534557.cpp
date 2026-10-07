// cl: /MD /EHsc /Oy- /Os
// ?rva00534557@Rva00534557@@QAEXPBH@Z @0x00534557 42B
// Banked attempt reverse/attempts/0x00534557.cpp, re-verified exact against the current ledger
// (its callees have since been rowed or pinned); landed unchanged by the
// banked-attempt sweep. Identity and evidence: see reverse/re_attempts.log.
// ?rva00534557@Rva00534557@@QAEXPBH@Z, retail 0x00534557, 42 bytes.
// Converts the two input dwords through helper 0x0053442A, inserts the
// resulting 8-byte pair at the front through rowed 0x00357DF8, then sets byte
// +0x10. The rowed helper's BfmeSpecialPowerTimer8 reference is used only as
// its existing 8-byte ABI view; target type names and pair meaning are unknown.

struct BfmeSpecialPowerTimer8;

class Rva00357DF8
{
public:
	void rva00357DF8(const BfmeSpecialPowerTimer8 &record);
};

struct Rva00534557EmptyBase
{
};

struct Rva00534557Record : Rva00534557EmptyBase
{
	int values[2];
	Rva00534557Record() {}
};

Rva00534557Record rva0053442A(const int *source);

class Rva00534557
{
public:
	void rva00534557(const int *source);
};

void Rva00534557::rva00534557(const int *source)
{
	Rva00534557Record record = rva0053442A(source);
	((Rva00357DF8 *)this)->rva00357DF8(
		*(const BfmeSpecialPowerTimer8 *)&record);
	((unsigned char *)this)[0x10] = 1;
}

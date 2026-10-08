// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry whose
// shape needs /O1 /G7 (imul by a constant), batch AO. Classes and methods
// are address-derived and model only what each body touches.

typedef int Int;

// 0x0058AD9F (42 tables): five times the Int at VA 0x00DBA4E4.
extern Int g_Va00DBA4E4;
class Rva0058AD9F
{
public:
	Int rva0058AD9F();
};
Int Rva0058AD9F::rva0058AD9F()
{
	return g_Va00DBA4E4 * 5;
}


// Retail global spelled differently by the unit that defines it (same
// address in reverse/data_ledger.csv); bind this unit's name to it.
#pragma comment(linker, "/alternatename:?g_rva0058AD9FBase@@3HA=?g_Va00DBA4E4@@3HA")

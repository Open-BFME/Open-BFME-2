// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
// ??0Rva00538E22@@QAE@H@Z, retail 0x00538E22, 28 bytes.
// Ctor: vector<BfmeE16> at +0 plus int at +0xc. Calls rowed _Vector_base ctor 0x00211E58 then stores arg.
// Evidence: retail lea [ebp+0xb] allocator temp plus mov [esi+0xc] plus ret 4 plus returns this.
#include <vector>

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

struct Rva00538E22
{
	_STL::vector<BfmeE16> m_vec;
	int m_val;
	Rva00538E22(int v);
};

Rva00538E22::Rva00538E22(int v) : m_vec(), m_val(v)
{
}

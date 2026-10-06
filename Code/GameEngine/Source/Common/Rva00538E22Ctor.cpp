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

// The range-erase callee used by 0x00538ED1 is already rowed for this 16-byte
// element view. Its true payload identity is not established by the call.
struct Elem003AF9E0
{
	virtual ~Elem003AF9E0();
	char m_body[0x0C];
	Elem003AF9E0();
	Elem003AF9E0(const Elem003AF9E0 &);
	Elem003AF9E0 &operator=(const Elem003AF9E0 &);
};

struct Rva00538E22
{
	_STL::vector<BfmeE16> m_vec;
	int m_val;
	Rva00538E22(int v);
	void rva00538ED1(int value);
	void rva00538D3B(int value);
};

Rva00538E22::Rva00538E22(int v) : m_vec(), m_val(v)
{
}

// The 36-byte target checks this vector's begin/finish, erases the full range
// through the rowed 0x00319B97 specialization when nonempty, then calls
// 0x00538D3B with the same this and original 32-bit argument. This class view
// is tied to the constructor at 0x00538E22 by the shared +0 vector and +0x0C
// member accessed by its helper; the original method and payload types remain
// unknown. The local element spelling selects the existing range-erase body.
// ?rva00538ED1@Rva00538E22@@QAEXH@Z
void Rva00538E22::rva00538ED1(int value)
{
	_STL::vector<Elem003AF9E0> &records =
		*reinterpret_cast<_STL::vector<Elem003AF9E0> *>(&m_vec);
	Elem003AF9E0 *first = records.begin();
	Elem003AF9E0 *last = records.end();
	if (first != last) {
		records.erase(first, last);
		rva00538D3B(value);
	}
}

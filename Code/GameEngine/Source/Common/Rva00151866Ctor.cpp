// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva001517DE@@QAE@XZ at 0x00151866 (48B). Ctor storing vtable 0x007D3AA8,
// nulls +4/+8/+0x24, constructs +0x0C via rowed ObjectCreationList ctor
// 0x001F81BF plus +0x18 vector<BfmeE16> via rowed Vector_base 0x00211E58.
// Caller 0x001518C3 deleting dtor proves ctor. Layout mirrors dtor TU with
// OCL plus BfmeE16 vector tail.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class ObjectCreationList
{
public:
	ObjectCreationList();
private:
	char m_pad[0x0C];
};

class Rva001517DE
{
public:
	Rva001517DE();
	virtual ~Rva001517DE();
private:
	void *m_comPtr; // +4
	void *m_holder; // +8
	ObjectCreationList m_oct; // +0x0C
	_STL::vector<BfmeE16> m_vec; // +0x18
	int m_24; // +0x24
};

Rva001517DE::Rva001517DE()
	: m_comPtr(0), m_holder(0), m_24(0)
{
}

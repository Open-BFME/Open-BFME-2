// cl: /MD
// stlport
// ??0Rva0026F419@@QAE@XZ @0x0026F419 44B
// ctor: baseConstruct via inlined Rva0026F419Base, vtable 0x007FABB8, zero
// +0x0C/+0x10/+0x14, then BfmeE16 Vector_base at +0x18.
// Evidence: leaf lane; callees baseConstruct 0x001B4E63 and Vector_base
// 0x00211E58 both rowed; caller 0x0022E79C; vtable image 0x007FABB8 in
// reverse/data_xrefs.tsv written from 0x0026F419 and 0x0026F445.
// Precedent Rva00421242Ctor.cpp.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

class __declspec(novtable) Rva0026F419Base
{
public:
	Rva0026F419Base() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual void unused();
	char m_flag;
	int m_value;
};

class Rva0026F419 : public Rva0026F419Base
{
public:
	Rva0026F419();
protected:
	virtual ~Rva0026F419();
private:
	int m_0C;
	int m_10;
	unsigned char m_14;
	char _pad14[3];
	_STL::vector<BfmeE16> m_18;
};

Rva0026F419::Rva0026F419()
	: m_0C(0)
	, m_10(0)
	, m_14(0)
	, m_18()
{
}
// cl: /DNDEBUG /MD
// stlport
// ??0Rva0043D16F@@QAE@XZ @0x0043D16F 36B
// Ctor with vtable 0x0083D7E8 at +0, int at +4 cleared via and-0, BfmeE16
// vector at +8 via rowed Vector_base ctor 0x00211E58, int at +0x14 cleared.
// Layout mirrors the Rva0043D3A8Clear TU (vptr+int+vector+int). Evidence:
// packet disasm with rowed callee, caller 0x0043D686, prev/next rows.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva0043D16F
{
public:
	Rva0043D16F();
	virtual void keep() {}
private:
	int m_04; // +0x04 cleared
	_STL::vector<struct BfmeE16> m_vec; // +0x08
	int m_14; // +0x14 cleared
};

Rva0043D16F::Rva0043D16F()
	: m_04(0), m_14(0)
{
}

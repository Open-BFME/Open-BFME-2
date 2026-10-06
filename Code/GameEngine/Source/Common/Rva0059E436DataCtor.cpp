// cl: /MD
// stlport
// ??0Rva0059E436Data@@QAE@XZ @0x0059E3BE 32B: default ctor with vector at +4 and int zero at +0x10.
// Evidence: vtable 0x00C70FC8, rowed _Vector_base<BfmeE16> 0x00211E58, caller 0x0059E456 in Rva0059E436Parse.
#include <vector>
struct BfmeE16 { float x; float y; float z; float w; };
class Rva0059E436Data
{
public:
	Rva0059E436Data();
	virtual ~Rva0059E436Data();
private:
	_STL::vector<BfmeE16> m_04;
	int m_10;
};

Rva0059E436Data::Rva0059E436Data()
{
	m_10 = 0;
}

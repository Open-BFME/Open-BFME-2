// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0041E4A3@@QAE@XZ @0x0041E4A3 33B: opaque ctor over 0xC base plus vector at +0xC.
// Evidence: calls rowed base 0x001B4E63 (twin-pinned as SubsystemInterface ctor)
// and rowed Vector_base BfmeE16 0x00211E58; vtable 0x0083AEA8 stored at +0 (gate DIR32).
// Same 33B shape as Rva0022DE6B 0x0022DE6B; owner identity unproven, honest Rva name.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
class SubsystemInterface
{
public:
	SubsystemInterface() throw();
	virtual ~SubsystemInterface();
private:
	char m_pad[8];
};

class Rva0041E4A3 : public SubsystemInterface
{
public:
	Rva0041E4A3();
protected:
	virtual ~Rva0041E4A3();
private:
	_STL::vector<BfmeE16> m_vec;
};

Rva0041E4A3::Rva0041E4A3()
	: SubsystemInterface()
{
}

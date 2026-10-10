// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0022DE6B@@QAE@XZ @0x0022DE6B 33B: opaque ctor over 0xC base plus vector at +0xC.
// Evidence: calls rowed base 0x001B4E63 (twin-pinned as SubsystemInterface ctor)
// and rowed Vector_base BfmeE16 0x00211E58; vtable 0x007E7698 stored at +0 (gate DIR32).
// Prev 0x0022DBC6 (MapMetaData dtor) and next 0x00232920 share no TU; new file beside
// MapMetaDataCopy.cpp copies its // cl: line. BfmeE16 is the 16B stand-in from
// stlport_vector_e16_o1; owner identity unproven, honest Rva name.
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

class Rva0022DE6B : public SubsystemInterface
{
public:
	Rva0022DE6B();
protected:
	virtual ~Rva0022DE6B();
private:
	_STL::vector<BfmeE16> m_vec;
};

Rva0022DE6B::Rva0022DE6B()
	: SubsystemInterface()
{
}

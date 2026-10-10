// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHsc /Ob2 /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
#include <map>
#include "ascii_string.h"
class NamedTimerInfo;
typedef _STL::map<AsciiString,NamedTimerInfo *> EmptyMapView;
// ??1Rva00359290@@UAE@XZ @0x00359290 85B.
// Virtual scalar dtor (vptr 0xC15398): vptr store, three member-dtor calls
// in reverse order through the rowed Rva00358D62/Rva00358E6A bodies, then
// the rowed SubsystemInterface dtor. No new pins; the base is an opaque
// 0xC TU-local stand-in.
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

private:
	char m_pad[0xC - 4];
};

// Constructor storage view only: native folds every empty-map construction
// to existing33C432. The actual key/value instantiations remain unknown.
class Rva00358D62 : public EmptyMapView {
public: __forceinline Rva00358D62():EmptyMapView(){} ~Rva00358D62();
};

// Constructor storage view only: native folds every empty-map construction
// to existing33C432. The actual key/value instantiations remain unknown.
class Rva00358E6A : public EmptyMapView {
public: __forceinline Rva00358E6A():EmptyMapView(){} ~Rva00358E6A();
};

class Rva00359290 : public SubsystemInterface
{
public:
	Rva00359290();
	virtual ~Rva00359290();

private:
	Rva00358E6A m_m0C;
	Rva00358E6A m_m18;
	Rva00358D62 m_m24;
};

Rva00359290::~Rva00359290()
{
}

// Native35973D constructor, same dispatch and reverse destructor family.
Rva00359290::Rva00359290() {}

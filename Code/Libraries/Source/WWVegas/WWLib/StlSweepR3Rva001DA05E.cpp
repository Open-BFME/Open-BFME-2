// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /I. /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <vendor/stlport/stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>


struct Rva001DA05ERecord
{
public:
	Rva001DA05ERecord();
	Rva001DA05ERecord(const Rva001DA05ERecord&);
	~Rva001DA05ERecord();
	Rva001DA05ERecord&operator=(const Rva001DA05ERecord&);
	char bytes[8]; // +0x00
};
namespace _STL {template<> void _Construct<Rva001DA05ERecord,Rva001DA05ERecord>(Rva001DA05ERecord*,const Rva001DA05ERecord&);}


// Instantiate the recovered member; retain only its required template dependencies.
template _STL::vector<Rva001DA05ERecord, _STL::allocator<Rva001DA05ERecord> > & _STL::vector<Rva001DA05ERecord, _STL::allocator<Rva001DA05ERecord> >::operator=(_STL::vector<Rva001DA05ERecord, _STL::allocator<Rva001DA05ERecord> > const &);

// Target operator= calls allocate/copy 1D9C9F -> 1D9B3C -> placement copy
// 1D9B0F; copy dispatcher 255CFA -> 254D65 invokes assignment 1D9990.
// Cleanup is range 32C0CA, calling the string destructor 48BA39 at offset0.
// All loops advance 8. Bind the cdecl construction and ECX-based lifetime/
// assignment operations to their rowed owners, retaining the opaque view.
#pragma comment(linker, "/alternatename:??$_Construct@URva001DA05ERecord@@U1@@_STL@@YAXPAURva001DA05ERecord@@ABU1@@Z=?Rva001D9B0FConstruct@@YAXPAXPBX@Z")
#pragma comment(linker, "/alternatename:??1Rva001DA05ERecord@@QAE@XZ=??1AsciiString@@QAE@XZ")
#pragma comment(linker, "/alternatename:??4Rva001DA05ERecord@@QAEAAU0@ABU0@@Z=??4FXBoneInfo@@QAEAAU0@ABU0@@Z")

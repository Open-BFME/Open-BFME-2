// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0FXShaderParameterBinder@@QAE@PAX@Z, retail 0x00154058, 73 bytes.
// Constructor of the holder whose destructor is rowed at 0x00153D16
// (Rva00153D16Dtor.cpp): it zeroes the COM pointer at +0, builds a
// vector<BfmeE16> at +4 through the rowed _Vector_base ctor 0x00211E58, zeroes
// the pointer at +0x10 and then hands the argument to the holder's set-surface
// method at 0x00153F08 (336B, pinned). Identity: WorldBuilder's
// fxshaderparameterbinder.cpp:27 is FXShaderParameterBinder's constructor
// (asserts the effect) handing it to FXShaderParameterBinder::Init, and the
// layout (effect +0, vector +4, parsing data +0x10) is the binder's. The 0x00154370 SSE
// sibling needs /G7 /arch:SSE and lives in its own TU (Rva00154370Cluster.cpp)
// because /O1 changes that body by one byte.

#include <vector>

#include "../../../Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

enum ScienceType
{
    SCIENCE_INVALID = 0
};

struct Rva001531E6Target;

class FXShaderParameterBinder
{
public:
    void PopDynamicSetStack();
    void PushDynamicSetStack(const char *name);
    void PushDynamicSetStack(ScienceType value);
    FXShaderParameterBinder(void *surface);
    void Init(struct ID3DXEffect *surface);
    void *m_ptr;
    _STL::vector<BfmeE16> m_vec;
    Rva001531E6Target *m_ParsingData;
};

FXShaderParameterBinder::FXShaderParameterBinder(void *surface)
	: m_ptr(0), m_vec(_STL::allocator<BfmeE16>()), m_ParsingData(0)
{
	if (surface)
		Init((struct ID3DXEffect *)surface);
}

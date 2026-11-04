// cl: /DNDEBUG /MD
//
// Retail 0x000729F4, 20 bytes: default constructor of the reference-counted
// rendering-method forwarder whose vtable 0x00BC6540 holds the matched
// RenderingMethodDelegate slot bodies (VslotSmallBodiesC.cpp; slots #2-#6 and #9 forward
// to the object at +8). Ghidra-unlisted, no caller (the body sits between
// W3DShroudMaterialPassClass::UnInstall_Materials 0x000729EB and slot #2).
//
// Shape: RefCountClass base (NumRefs = 1 at +4, vptr at +0), then the +8
// forwarding target built by its holder's inline constructor. Modelling the
// target as a member object -- as FXShaderSetup's +8 shader-asset handle is
// (fxshadersetup.cpp, 0x001525FB has the same three-store prologue) -- keeps
// retail's +4, vptr, +8 store order; a plain pointer initializer is hoisted.

#include "../../../Libraries/Source/WWVegas/WWLib/RefCountData.h"
inline RefCountClass::~RefCountClass() {}

class Rva00072A08Inner;

class Rva00072A08Target
{
public:
	Rva00072A08Target() : m_target(0) {}

private:
	Rva00072A08Inner *m_target;
};

// WorldBuilder FXShader::RenderingMethodDelegate (slot bodies Begin_Pass..End_Rendering, vtable leads).
class FXShader
{
public:
	class RenderingMethodDelegate;
};

class FXShader::RenderingMethodDelegate : public RefCountClass
{
public:
	RenderingMethodDelegate();

	virtual bool rva00072A08(int a0, int a1);

protected:
	virtual ~RenderingMethodDelegate();

private:
	Rva00072A08Target m_08;
};

FXShader::RenderingMethodDelegate::RenderingMethodDelegate()
{
}

// Retail vftable 0x00BC6540: slot 1 is the deleting dtor 0x00072FA9 (calls the dtor at 0x00072AED); slot 2 is the row at 0x00072A08.
#pragma comment(linker, "/alternatename:??1RenderingMethodDelegate@FXShader@@MAE@XZ=??1Rva0072AED@@UAE@XZ")
#pragma comment(linker, "/alternatename:?rva00072A08@RenderingMethodDelegate@FXShader@@UAE_NHH@Z=?rva00072A08@RenderingMethodDelegate@FXShader@@QAE_NHH@Z")

// cl: /Ireference/shims/bfme2renderobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?Init@BoxRenderObjClass@@SAXXZ @ 0x00174E20 (205B).
// Dedicated TU: boxrobj.cpp cannot take another row. Same headers as the
// landed ctor TUs. BFME1 uses NEW_REF (pool); BFME2 retail uses plain global
// operator new (pinned @0x2FDA0), so plain ::new here (proven Clone pattern).
// File-statics share the home TU's retail addresses by name (clean_list
// precedent). All 8 callees already matched; no pins needed.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#include "rendobj.h"
#include "boxrobj.h"
#include "vertmaterial.h"

static VertexMaterialClass * _BoxMaterial = NULL;
static ShaderClass _BoxShader;

// ?Init@BoxRenderObjClass@@SAXXZ
void BoxRenderObjClass::Init(void)
{
	_BoxMaterial = ::new VertexMaterialClass();
	_BoxMaterial->Set_Ambient(0, 0, 0);
	_BoxMaterial->Set_Diffuse(0, 0, 0);
	_BoxMaterial->Set_Specular(0, 0, 0);
	_BoxMaterial->Set_Emissive(1, 1, 1);
	_BoxMaterial->Set_Opacity(1.0f);
	_BoxMaterial->Set_Shininess(0.0f);

	_BoxShader = ShaderClass::_PresetAlphaSolidShader;

	IsInitted = true;
}

// ?Shutdown@BoxRenderObjClass@@SAXXZ @ 0x00174EF0 (38B). Donor reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/boxrobj.cpp Shutdown; caller Do_Onetime_Device_Dependent_Shutdowns @0x001215F0; prev Init @0x00174E20 same TU.
void BoxRenderObjClass::Shutdown(void)
{
	REF_PTR_RELEASE(_BoxMaterial);
	IsInitted = false;
}

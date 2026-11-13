// cl: /Ireference/shims/bfmecamera /MD /EHsc /Ireference/open-bfme-1/Code/GameEngineDevice/Source/W3DDevice/GameClient
// Open-BFME: the 20-byte filter constructor at retail 0x0013EA00 under its
// address-derived name; ShroudTexture::getFilter's fallback filter calls it.
// The real body is TextureFilterClass::TextureFilterClass(MipCountType) in
// Code/Libraries/Source/WWVegas/WW3D2/texturefilter.cpp, rowed as its ICF
// alias; the stage-state body that lived here is TextureFilterClass::Apply.

#include "../../../../GameEngine/Include/Common/Gen_00920A20.h"

Gen_00920A20::Gen_00920A20(int mode)
{
	int *p = (int *)this;
	p[3] = 0;
	p[4] = 0;
	int v = (mode != 1 ? 4 : 0);
	p[0] = 4;
	p[1] = 4;
	p[2] = v;
}

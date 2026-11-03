// cl: /Ireference/shims/bfmestages /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil
// ?AdjustTextureSize@DX8Wrapper@@SAXAAI0@Z @0x0011E670 81B.
// Target facts: retail clamps two dims to next-pow2 capped by CurrentCaps
// MaxTextureWidth/Height at +0x60/+0x64; the body sits in dx8wrapper.cpp's run
// between rows 0x0011E630 and 0x0011E6D0 (both Zero Hour DX8Wrapper methods); its
// callers are W3DVideoBuffer::allocate, W3DShroud::init and W3DTaint::init.
// Donor facts: BFME 1 has the same 81B body at 0x009056F0, also inside its
// dxwrapper.cpp run; BFME 1's EA evidence (ea_evidence.csv) gives it file
// Libraries/Source/WWVegas/WW3D2/dxwrapper.cpp (route wb1: the WorldBuilder
// partner references that path) and name DXWrapper::AdjustTextureSize (route
// chain, aligned). BFME's DXWrapper is spelled DX8Wrapper in this tree, as in
// BFME 1's ledger. Zero Hour's three-argument TextureLoader::Validate_Texture_Size
// (textureloader.cpp) is the same idea and is what the callers' donor text names.
struct D3DCapsPrefix
{
	unsigned char unmodelled_0[0x58];
	unsigned long MaxTextureWidth;
	unsigned long MaxTextureHeight;
};

class DX8Caps
{
public:
	const D3DCapsPrefix &Get_DX8_Caps() const { return Caps; }

private:
	int dword_0;
	int dword_4;
	D3DCapsPrefix Caps;
};

#include "DX8WrapperClass.h"


static unsigned ClampedPowerOfTwo009056F0(unsigned dimension, unsigned maximum)
{
	unsigned result = 1;
	while (result < dimension) {
		result <<= 1;
	}
	return (result < maximum) ? result : maximum;
}

void DX8Wrapper::AdjustTextureSize(unsigned &width, unsigned &height)
{
	const DX8Caps *caps = DX8Wrapper::Get_Current_Caps();
	if (caps == 0) {
		return;
	}
	const D3DCapsPrefix &dx8caps = caps->Get_DX8_Caps();
	width = ClampedPowerOfTwo009056F0(width, dx8caps.MaxTextureWidth);
	height = ClampedPowerOfTwo009056F0(height, dx8caps.MaxTextureHeight);
}

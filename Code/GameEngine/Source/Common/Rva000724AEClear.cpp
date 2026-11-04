// cl: /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?rva000724AE@Rva000724AE@@QAEXXZ, RVA 0x000724AE, 25B. Triple clear: call
// rowed cleanup@Rva00739C70 on +0x00 then clear@BfmeResetTextureRef on +0x08
// then tail-jump to rva000723AC@W3DRadarResetSurface on +0x0c. Evidence:
// chain from just-landed 0x723AC; callers at 0x7259D/0x7262D/0x72697 pass
// W3DVideoBuffer+0x2c; layout matches Rva00739C70State 0x14-byte shape in
// W3DVideoBufferCtorBfme.cpp (+8 texture ref +0xc surface +0x10 flags).
class Rva00739C70
{
public:
	void cleanup();
private:
	int m_00;
	int m_04;
};
#include "../../../Libraries/Source/WWVegas/WW3D2/BfmeResetTextureRef.h"
class W3DRadarResetSurface
{
public:
	void rva000723AC();
private:
	void *m_surface;
};
class Rva000724AE
{
public:
	void rva000724AE();
	bool rva000724C7();
	void *rva000724D7(int *pitchOut);
	bool rva000725BC(unsigned textureWidth,unsigned textureHeight,unsigned width,unsigned height,unsigned format,bool surfaceOnly);
	int m_00; // +0x00
	int m_04; // +0x04
	void *m_08; // +0x08
	void *m_0c; // +0x0C
	unsigned int m_flags; // +0x10
};
void Rva000724AE::rva000724AE()
{
	reinterpret_cast<Rva00739C70 *>(this)->cleanup();
	reinterpret_cast<BfmeResetTextureRef *>(&m_08)->clear();
	reinterpret_cast<W3DRadarResetSurface *>(&m_0c)->rva000723AC();
}

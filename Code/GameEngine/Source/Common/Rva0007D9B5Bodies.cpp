// cl: /DNDEBUG /MD C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// Dump range 1 small pair (0x0007D9B5 26B, 0x0007D9CF 29B). Boundaries are
// ret-4 terminated extents verified from retail bytes via the tools.
// Honest address-derived names; only bytes, ABIs and displacements carry
// identity. Both call the rowed W3DShadowMapManager::UpdateShadowCamera at
// 0x0007C8AE; the first also assigns its arg to the +0x04 member through the
// rowed CameraClass::operator= at 0x00135010.

#include "../../../Libraries/Source/WWVegas/WW3D2/CameraClass.h"

class W3DShadowMapManager
{
public:
	void UpdateShadowCamera();
};

class Rva0007D9B5Host
{
public:
	void rva0007D9B5(int x);
	void rva0007D9CF(const int *p);

	void *m_00;
	CameraClass *m_04; // +0x04
	int m_08; // +0x08
	int m_0C; // +0x0C
	int m_10; // +0x10
};

void Rva0007D9B5Host::rva0007D9B5(int x)
{
	*m_04 = *(const CameraClass *)x;
	((W3DShadowMapManager *)this)->UpdateShadowCamera();
}

void Rva0007D9B5Host::rva0007D9CF(const int *p)
{
	m_08 = p[0];
	m_0C = p[1];
	m_10 = p[2];
	((W3DShadowMapManager *)this)->UpdateShadowCamera();
}

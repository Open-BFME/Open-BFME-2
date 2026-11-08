// cl: /DNDEBUG /EHsc /MD -ICode/Libraries/Source/WWVegas/WW3D2 -ICode/Libraries/Source/WWVegas/WWLib -ICode/Libraries/Source/WWVegas/WWMath -ICode/Libraries/Source/WWVegas/WWSaveLoad -ICode/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil -Ireference/shims/sweep
//
// ?rva00108DBC@W3DProjectedShadowManager@@QAE_NXZ @0x00108DBC 108B. Init method allocating
// Rva00108A0B at +0x24C via rowed new and CameraClass(0x3FC) at +0x20,
// returning true. Caller at 0x0009A29A. Honest address name.
class HashableClass;

#include "../../../Libraries/Source/WWVegas/WWLib/HashableClass.h"

class Rva00108A0B
{
public:
	Rva00108A0B();
private:
	HashTableClass *m_a;
	HashTableClass *m_b;
};

#include "../../../Libraries/Source/WWVegas/WW3D2/CameraClass.h"

class W3DProjectedShadowManager
{
public:
	bool rva00108DBC();
private:
	char m_pad00[0x20];
	CameraClass *m_cam;
	char m_pad24[0x24C - 0x24];
	Rva00108A0B *m_tbl;
};

bool W3DProjectedShadowManager::rva00108DBC()
{
	m_tbl = new Rva00108A0B();
	m_cam = new CameraClass();
	return true;
}

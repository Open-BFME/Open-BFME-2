// ??0RTS2DScene@@QAE@XZ
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// Retail 0x0006F9D6, 154 bytes (EH). "RTS2DScene" is the setName string;
// donor is Zero Hour's RTS2DScene::RTS2DScene (W3DScene.cpp): setName,
// m_status = NEW_REF(W3DStatusCircle), Add_Render_Object(m_status).
// Bases follow the RTS3DScene ctor: matched SimpleSceneClass ctor 0x142960,
// SubsystemInterface at +0x108. W3DStatusCircle is the 0xE8-byte object
// built by the matched ctor at 0x8E54F. BFME 2 zeroes m_camera (+0x118)
// after the publish.
#include <new>
#include <string.h>
#include "ascii_string.h"

class RenderObjClass;

#include "../../../../Libraries/Source/WWVegas/WW3D2/SimpleSceneClass.h"

#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

class W3DStatusCircle
{
public:
	W3DStatusCircle();
	char m_storage[0xE8];
};

class CameraClass;

class RTS2DScene : public SimpleSceneClass, public SubsystemInterface
{
public:
	RTS2DScene();
	virtual ~RTS2DScene();
protected:
	RenderObjClass *m_status;
	CameraClass *m_camera;
};

RTS2DScene::RTS2DScene()
{
	setName("RTS2DScene");
	m_status = (RenderObjClass *)new W3DStatusCircle();
	Add_Render_Object(m_status);
	m_camera = 0;
}

// The ctor's second vftable (0x00BC6264) slot 0 is this-adjusting (-0x108) into the deleting dtor 0x0006F24A, which calls the dtor at 0x0006ED6F.
#pragma comment(linker, "/alternatename:??1RTS2DScene@@UAE@XZ=??1Rva006ED6F@@UAE@XZ")

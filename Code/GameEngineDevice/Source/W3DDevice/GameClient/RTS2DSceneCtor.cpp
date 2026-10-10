// ??0RTS2DScene@@QAE@XZ
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Retail 0x0006F9D6, 154 bytes (EH). "RTS2DScene" is the setName string;
// donor is Zero Hour's RTS2DScene::RTS2DScene (W3DScene.cpp): setName,
// m_status = NEW_REF(W3DStatusCircle), Add_Render_Object(m_status).
// Bases follow the RTS3DScene ctor: matched SimpleSceneClass ctor 0x142960,
// SubsystemInterface at +0x108. W3DStatusCircle is the 0xE8-byte object
// built by the matched ctor at 0x8E54F. BFME 2 zeroes m_camera (+0x118)
// after the publish.
#include "ascii_string.h"

typedef unsigned int size_t;
void *operator new(size_t size);
void operator delete(void *p);

class RenderObjClass;

class SimpleSceneClass
{
public:
	SimpleSceneClass();
	virtual ~SimpleSceneClass();
	virtual void Add_Render_Object(RenderObjClass *obj);
	char m_pad004[0x108 - 0x04];
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	void setName(AsciiString name);
private:
	char m_padAfterVptr[4];
	AsciiString m_name;
};

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

// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ??1Rva006ED6F@@UAE@XZ retail 0x0006ED6F 116B
// MI dtor: own vftables at +0 (SimpleSceneClass part) and +0x108
// (SubsystemInterface part). Removes the held render object from the scene
// with a direct SimpleSceneClass::Remove_Render_Object (rowed 0x00141860),
// releases and clears the ref at +0x114, then the rowed base dtors
// ??1SubsystemInterface@@UAE@XZ 0x001B4E74 and ??1SimpleSceneClass@@UAE@XZ
// 0x00141DF0.
#include "../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"

class SimpleSceneClass
{
public:
	virtual ~SimpleSceneClass();
	virtual void Remove_Render_Object(RenderObjClass *obj);
private:
	char m_pad04[0x108 - 0x04];
};

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class Rva006ED6F : public SimpleSceneClass, public SubsystemInterface
{
public:
	virtual ~Rva006ED6F();
private:
	RenderObjClass *m_object; // +0x114
};

Rva006ED6F::~Rva006ED6F()
{
	SimpleSceneClass::Remove_Render_Object(m_object);
	if (m_object)
	{
		m_object->Release_Ref();
		m_object = 0;
	}
}

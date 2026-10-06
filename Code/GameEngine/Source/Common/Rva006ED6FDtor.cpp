// cl: /DNDEBUG /MD /EHsc
// ??1Rva006ED6F@@UAE@XZ retail 0x0006ED6F 116B
// MI dtor: own vftables at +0 (SimpleSceneClass part) and +0x108
// (GameEngineDeletingBase part). Removes the held render object from the scene
// with a direct SimpleSceneClass::Remove_Render_Object (rowed 0x00141860),
// releases and clears the ref at +0x114, then the rowed base dtors
// ??1GameEngineDeletingBase@@UAE@XZ 0x001B4E74 and ??1SimpleSceneClass@@UAE@XZ
// 0x00141DF0.
class RenderObjClass
{
public:
	virtual void Delete_This();
	void Release_Ref()
	{
		if (--m_numRefs == 0)
			Delete_This();
	}
private:
	int m_numRefs;
};

class SimpleSceneClass
{
public:
	virtual ~SimpleSceneClass();
	virtual void Remove_Render_Object(RenderObjClass *obj);
private:
	char m_pad04[0x108 - 0x04];
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[8];
};

class Rva006ED6F : public SimpleSceneClass, public GameEngineDeletingBase
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

// cl: /DNDEBUG /MD
// ?Notify_Added@BaseHeightMapRenderObjClass@@UAEXPAVSceneClass@@@Z retail
// 0x00068477 29B. Zero Hour's BaseHeightMap.cpp override: the base
// RenderObjClass::Notify_Added (rowed 0x0013BCD0), then registers the terrain
// for frame updates through SceneClass slot 0x38 with ON_FRAME_UPDATE (0).
// It fills the Notify_Added slot of two RenderObjClass-derived vftables (rdata
// 0x007C5E18 and 0x007CE7F0, the first beside a __purecall, i.e. the abstract
// base and its terrain subclass) and sits in the BaseHeightMap range right
// after the rowed BaseHeightMapRenderObjClass::rva0006846A. A ParticleBuffer
// unit's identical body placed it in a library /O1 sweep.

class RenderObjClass;

class SceneClass
{
public:
	enum RegType
	{
		ON_FRAME_UPDATE = 0
	};

	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13();
	virtual void Register( RenderObjClass *obj, RegType for_what );
};

class RenderObjClass
{
public:
	virtual void Notify_Added( SceneClass *scene );
};

class BaseHeightMapRenderObjClass : public RenderObjClass
{
public:
	virtual void Notify_Added( SceneClass *scene );
};

void BaseHeightMapRenderObjClass::Notify_Added( SceneClass *scene )
{
	RenderObjClass::Notify_Added( scene );
	scene->Register( this, SceneClass::ON_FRAME_UPDATE );
}

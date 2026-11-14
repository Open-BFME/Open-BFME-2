// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep

typedef bool Bool;

#include "ascii_string.h"

class DrawableModule
{
	protected:
	virtual ~DrawableModule();
};

class DrawableModuleLayoutBase : public DrawableModule
{
	protected:
	virtual ~DrawableModuleLayoutBase() {}

private:
	void *m_moduleData;
	void *m_drawable;
};

enum ShadowType { SHADOW_NONE = 0 };
class FXList;

class DebrisDrawInterface
{
public:
	virtual void setModelName(AsciiString name, int color, ShadowType type) = 0;
	virtual void setAnimNames(AsciiString initial, AsciiString flying, AsciiString final, const FXList *finalFX) = 0;
};

#include "../../../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"

class SceneClass
{
public:
	virtual void sceneSlot0();
	virtual void sceneSlot1();
	virtual void sceneSlot2();
	virtual void Remove_Render_Object(RenderObjClass *object);
};

#include "../../../../../../GameEngine/Include/Common/Gen0003AC38.h"

// The scene the debris render object leaves is W3DDisplay's 3D scene.
class RTS3DScene : public SceneClass
{
};

#include "../../../../../Include/W3DDevice/GameClient/W3DDisplayClass.h"
class W3DShadowManager; extern W3DShadowManager *TheW3DShadowManager;
// g_shadowManager: VA 0xde5dfc (zero-filled .bss).
class W3DShadowManager; extern W3DShadowManager *TheW3DShadowManager;

class W3DDebrisDraw : public DrawableModuleLayoutBase,
	public DebrisDrawInterface
{
	protected:
	virtual ~W3DDebrisDraw();
public:
	virtual void setModelName(AsciiString name, int color, ShadowType type);
	virtual void setAnimNames(AsciiString initial, AsciiString flying, AsciiString final, const FXList *finalFX);

private:
	AsciiString m_modelName;
	int m_modelColor;
	AsciiString m_animInitial;
	AsciiString m_animFlying;
	AsciiString m_animFinal;
	RenderObjClass *m_renderObject;
	RenderObjClass *m_anims[3];
	void *m_fxFinal;
	int m_state;
	int m_frames;
	Bool m_finalStop;
	void *m_shadow;
};

// ??1W3DDebrisDraw@@MAE@XZ
W3DDebrisDraw::~W3DDebrisDraw()
{
	register int zero = 0;
	if ((void *)(*(Gen0003AC38 * *)&TheW3DShadowManager) != (void *)zero)
	{
		void *shadow = m_shadow;
		if (shadow != (void *)zero)
		{
			(*(Gen0003AC38 * *)&TheW3DShadowManager)->handle(shadow);
			*(volatile int *)&m_shadow = zero;
		}
	}
	RenderObjClass *renderObject = m_renderObject;
	if (renderObject != (RenderObjClass *)zero)
	{
		W3DDisplay::m_3DScene->Remove_Render_Object(renderObject);
		if (m_renderObject != (RenderObjClass *)zero)
		{
			m_renderObject->Release_Ref();
			*(volatile int *)&m_renderObject = zero;
		}
		*(volatile int *)&m_renderObject = zero;
	}
	for (int i = 0; i < 3; ++i)
	{
		if (m_anims[i] != (RenderObjClass *)zero)
		{
			m_anims[i]->Release_Ref();
			*(volatile int *)&m_anims[i] = zero;
		}
		*(volatile int *)&m_anims[i] = zero;
	}
}

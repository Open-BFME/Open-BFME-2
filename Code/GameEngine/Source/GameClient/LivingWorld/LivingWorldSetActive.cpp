// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/moduledata
//
// ?rva002BF391@LivingWorld@@UAEX_N@Z retail 0x002BF391..0x002BF4F3 (354 bytes,
// ret 4). Slot 10 of the LivingWorld vtable 0x007FE508 (the constructor
// 0x002C0120 stores it; WB D26090 is the debug twin, called through slot 10
// by the derived product override 0x0009DB5A). Target evidence: a cleared
// state first runs the LivingWorldManager's rowed 0x002110DF(0); only a
// change of the +0x18 state continues and stores it. Activation turns the
// global data's +0x62 shadow flag into +0x60 (resetting the W3D shadow
// manager's +8 word), appends message 0x3EC with a true boolean, then runs
// TheInGameUI slot 68 and TheControlBar slot 10. Deactivation runs this
// object's slot 20 with 0 and reloads the +0x62/+0x60 flags from the game LOD
// manager's current static entry (index +0x1768, 0x4C-byte entries, bytes
// +0xE and +0xC), dropping +0x60 when both are set. Both paths then hide the
// radar override source (rowed 0x002D337F, a thiscall on its global), store
// "active and not +0x19" into TheGameLogic+0x125, drive TheAudio slots 20 and
// 17 while active, run the manager's rowed 0x00213BBE/0x00213C30 and the empty
// bool member 0x0047A69C with the rowed 0x002BE7BB result, and finally
// broadcast slot 1 of the +4 listener list (vcall thunk 0x005CB260) with this.
// Field and slot meanings beyond those accesses are unresolved; the shadow
// and LOD flag reading follows Zero Hour's GlobalData/StaticGameLODInfo
// (structural inference only).
#include "Common/Snapshot.h"

#define LW391_SLOTS4(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3();
#define LW391_SLOTS16(p) LW391_SLOTS4(p##0) LW391_SLOTS4(p##1) LW391_SLOTS4(p##2) LW391_SLOTS4(p##3)

class Rva002BF33DListener
{
public:
	virtual void notify(void *);
	virtual void notifyStateChanged(void *);
};

class Rva002BF33DList
{
public:
	void forEach(void (Rva002BF33DListener::*notify)(void *), void *arg);
private:
	Rva002BF33DListener **m_begin;
	Rva002BF33DListener **m_end;
	Rva002BF33DListener **m_capacity;
	unsigned int m_index;
};

class LivingWorld : public Rva002BF33DList, public Snapshot
{
public:
	virtual ~LivingWorld();
protected:
	virtual void loadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
public:
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void rva002BF391(bool active);	// slot 10
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20(bool value);
private:
	int m_14;
	bool m_18;
	bool m_19;
};

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
class Rva00211589 { public: void rva002110DF(int value); };
class Rva00213A85 { public: void rva00213BBE(); void rva00213C30(); };
// 0x0047A69C is the ICF-folded empty `ret 4` body; its rowed bool spelling.
class AIGroup { public: void setMineClearingDetail(bool value); };

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct LivingWorldGlobalDataView
{
	unsigned char m_pad[0x60];
	bool m_useShadowVolumes;
	bool m_61;
	bool m_useShadowMapping;
};

class W3DShadowManager;
extern W3DShadowManager *TheW3DShadowManager;
struct LivingWorldShadowManagerView
{
	void *m_vtbl;
	int m_04;
	int m_stencilShadowMask;
};

struct LivingWorldStaticLODInfo
{
	unsigned char m_pad[0xC];
	bool m_shadowVolumes;
	bool m_0D;
	bool m_shadowMapping;
	unsigned char m_tail[0x4C - 0xF];
};
class GameLODManager;
extern GameLODManager *TheGameLODManager;
struct LivingWorldLODManagerView
{
	LivingWorldStaticLODInfo m_staticInfo[1];
	unsigned char m_pad[0x1768 - 0x4C];
	int m_staticLevel;
};

class GameMessage { public: void appendBooleanArgument(bool value); };
class MessageStream;
extern class MessageStream *TheMessageStream;
class LivingWorldMessageStreamView
{
public:
	LW391_SLOTS16(s0)
	virtual void s100();
	virtual void s101();
	virtual GameMessage *appendMessage(int type);	// slot 18
};

class InGameUI;
extern InGameUI *TheInGameUI;
class LivingWorldInGameUIView
{
public:
	LW391_SLOTS16(s0) LW391_SLOTS16(s1) LW391_SLOTS16(s2) LW391_SLOTS16(s3)
	LW391_SLOTS4(s40)
	virtual void slot68();
};

class ControlBar;
extern ControlBar *TheControlBar;
class LivingWorldControlBarView
{
public:
	LW391_SLOTS4(s0) LW391_SLOTS4(s1)
	virtual void s20();
	virtual void s21();
	virtual void slot10();
};

class AudioManager;
extern AudioManager *TheAudio;
class LivingWorldAudioView
{
public:
	LW391_SLOTS16(s0)
	virtual void slot16();
	virtual void slot17(int a, int b, int c);
	virtual void slot18();
	virtual void slot19();
	virtual void slot20(int value);
};

class RadarWindowOverrideSource { public: void rva002D337F(); };
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;

class GameLogic;
extern GameLogic *TheGameLogic;
class Rva002BE7BB { public: bool rva002BE7BB(); };
struct LivingWorldGameLogicView
{
	unsigned char m_pad[0x125];
	bool m_125;
};

void LivingWorld::rva002BF391(bool active)
{
	if (!active)
		((Rva00211589 *)TheLivingWorldManager)->rva002110DF(0);
	if (active == m_18)
		return;
	m_18 = active;
	if (active)
	{
		if (((LivingWorldGlobalDataView *)TheWritableGlobalData)->m_useShadowMapping)
		{
			((LivingWorldGlobalDataView *)TheWritableGlobalData)->m_useShadowMapping = false;
			((LivingWorldGlobalDataView *)TheWritableGlobalData)->m_useShadowVolumes = true;
			((LivingWorldShadowManagerView *)TheW3DShadowManager)->m_stencilShadowMask = -1;
		}
		GameMessage *msg = ((LivingWorldMessageStreamView *)TheMessageStream)->appendMessage(0x3EC);
		msg->appendBooleanArgument(true);
		((LivingWorldInGameUIView *)TheInGameUI)->slot68();
		((LivingWorldControlBarView *)TheControlBar)->slot10();
	}
	else
	{
		slot20(false);
		int level = ((LivingWorldLODManagerView *)TheGameLODManager)->m_staticLevel;
		((LivingWorldGlobalDataView *)TheWritableGlobalData)->m_useShadowMapping =
			((LivingWorldLODManagerView *)TheGameLODManager)->m_staticInfo[level].m_shadowMapping;
		((LivingWorldGlobalDataView *)TheWritableGlobalData)->m_useShadowVolumes =
			((LivingWorldLODManagerView *)TheGameLODManager)->m_staticInfo[level].m_shadowVolumes;
		LivingWorldGlobalDataView *data = (LivingWorldGlobalDataView *)TheWritableGlobalData;
		if (data->m_useShadowMapping && data->m_useShadowVolumes)
			data->m_useShadowVolumes = false;
	}
	theRadarWindowOverrideSource->rva002D337F();
	((LivingWorldGameLogicView *)TheGameLogic)->m_125 = (m_18 && !m_19) ? true : false;
	if (TheAudio && m_18)
	{
		((LivingWorldAudioView *)TheAudio)->slot20(1);
		((LivingWorldAudioView *)TheAudio)->slot17(0x3F, 6, 0);
	}
	if (TheLivingWorldManager)
	{
		if (m_18)
			((Rva00213A85 *)TheLivingWorldManager)->rva00213BBE();
		else
			((Rva00213A85 *)TheLivingWorldManager)->rva00213C30();
		((AIGroup *)TheLivingWorldManager)->setMineClearingDetail(((Rva002BE7BB *)TheGameLogic)->rva002BE7BB());
	}
	forEach(&Rva002BF33DListener::notifyStateChanged, this);
}

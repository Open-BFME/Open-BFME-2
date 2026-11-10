// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// dxsdk
// platformsdk
//
// ?Customized_Render@Rva0009AA0F@@MAEXAAVRenderInfoClass@@@Z, retail
// 0x0009C9DE..0x0009CD9B (957 bytes, EH, ret 4).
//
// Slot 23 of vftable 0x007C8900 (??_7Rva0009AA0F@@6B@, installed by the
// rowed ctor 0x0009AA0F): the SimpleSceneClass layout around it is
// SceneClass::Render (slot 22, protected), Pre_Render_Processing (24) and
// SimpleSceneClass::Post_Render_Processing (25), so this is the scene's
// Customized_Render override. It is not a slot of vftable 0x007C89C8.
//
// Body (read from retail): Visibility_Check (slot 27) on the camera; every
// object of the update list (multi-list head +0x78) gets its per-frame
// update (slot 13); lights 0-3 are cleared (rowed Set_Light); when the
// render info carries no light environment a function-local static one
// (0x00DE5E50 behind guard 0x00DE6078; ctor 0x0013F410, empty dtor pinned
// at 0x0069E440) is reset to the scene ambient at +0x08 (rowed 0x0013F620
// under its existing name), fed every light of the list at +0x90 (rowed
// Add_Light), updated with the camera transform (rowed Pre_Render_Update)
// and installed; the render states change through the inlined
// DX8Wrapper::Set_DX8_Render_State (ZFUNC LESSEQUAL / ZWRITEENABLE off /
// ZENABLE on), every visible object of the list at +0xF0 renders (slots 96
// and 12), WW3D::Flush runs, the states return (ZWRITEENABLE on / ZFUNC
// ALWAYS) and the shadow manager, the display's +0x2C object, the army line
// pass 0x0009C983 and the particle system manager finish the frame.
// PIN: 0x001173F0 is rowed as ?rva001173f0@@YAXXZ but retail passes it the
// render info (push / call / pop): it is WW3D::Flush(RenderInfoClass &)
//   ?Flush@WW3D@@SAXAAVRenderInfoClass@@@Z -> 0x001173F0

#include <d3d9.h>

typedef int Int;

// The device keeps its D3D8 type name but is a Direct3D 9 device
// (SetRenderState, vtable slot 57). The wrapper's state parameter is the
// DWORD its decorations carry (?Get_DX8_Render_State_Value_Name@...KI@Z).
struct IDirect3DDevice8;

#include "wwstring.h"
class PersistFactoryClass;
class ChunkSaveClass;
class ChunkLoadClass;
#include "../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"

struct _D3DLIGHT8;

extern unsigned number_of_DX8_calls; void rva001173f0(unsigned int);

class WW3D
{
public:
	static bool Is_Snapshot_Activated(void) { return SnapshotActivated; }
	static void Flush(class RenderInfoClass &rinfo);
private:
	static bool SnapshotActivated;
};

class DX8Wrapper
{
public:
	static void Set_Light(unsigned index, const _D3DLIGHT8 *light);
	static void Apply_Render_State_Changes(void);
	static void Get_DX8_Render_State_Value_Name(StringClass &name, unsigned long state, unsigned value);

	static __forceinline void Set_DX8_Render_State(unsigned long state, unsigned value)
	{
		if (RenderStates[state] == value) return;
		if (WW3D::Is_Snapshot_Activated()) {
			StringClass value_name(0, true);
			Get_DX8_Render_State_Value_Name(value_name, state, value);
		}
		RenderStates[state] = value;
		reinterpret_cast<IDirect3DDevice9 *>(D3DDevice)->SetRenderState((D3DRENDERSTATETYPE)state, value);
		number_of_DX8_calls++;
		render_state_changes++;
	}

protected:
	static IDirect3DDevice8 *D3DDevice;
	static unsigned RenderStates[256];
	static unsigned render_state_changes;
};


#include "../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"

#include "../../../Libraries/Source/WWVegas/WW3D2/CameraClass.h"

class LightEnvironmentClass;

#define __PLACEMENT_VEC_NEW_INLINE  // always.h defines array placement-new itself
#include "../../../Libraries/Source/WWVegas/WW3D2/RenderInfoClass.h"







#include "../../../Libraries/Source/WWVegas/WW3D2/LightClass.h"



class BfmeVecHF;
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/Gen_0094AC70.h"

class LightEnvironmentClass
{
public:
	LightEnvironmentClass();
	__forceinline void Reset(const Vector3 &object_center, const Vector3 &scene_ambient)
	{
		reinterpret_cast<Gen_0094AC70 *>(this)->bfmeSetPair(
			reinterpret_cast<const BfmeVecHF *>(&object_center),
			reinterpret_cast<const BfmeVecHF *>(&scene_ambient));
	}
	~LightEnvironmentClass();
	void Add_Light(const LightClass &light);
	void Pre_Render_Update(const Matrix3D &camera_tm);
private:
	char m_data[0x228];
};

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DShadowManager.h"
extern W3DShadowManager *TheW3DShadowManager;

class Rva0009A361
{
public:
	void rva0009A361(Int rinfo);
};

class Rva0009C983
{
public:
	void rva0009C983(Int rinfo);
};

class DisplayPass
{
public:
#define G(n) virtual void v##n();
	G(00) G(01) G(02) G(03) G(04) G(05) G(06) G(07) G(08) G(09) G(10)
	G(11) G(12) G(13) G(14) G(15) G(16) G(17) G(18) G(19) G(20) G(21)
#undef G
	virtual void begin(CameraClass *camera); // 22
	virtual void end(void); // 23
};

class Display
{
public:
	char m_pad00[0x2C];
	DisplayPass *m_2C; // +0x2C
};
extern Display *TheDisplay;

#include "../../Include/GameClient/ParticleSys.h"
extern ParticleSystemManager *TheParticleSystemManager;

class Rva0009AA0F
{
public:
#define G(n) virtual void v##n();
	G(00) G(01) G(02) G(03) G(04) G(05) G(06) G(07) G(08) G(09) G(10)
	G(11) G(12) G(13) G(14) G(15) G(16) G(17) G(18) G(19) G(20) G(21)
	G(22)
#undef G
protected:
	virtual void Customized_Render(RenderInfoClass &rinfo); // 23
public:
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void Visibility_Check(CameraClass *camera); // 27

private:
	int m_04;
	Vector3 m_ambientLight; // +0x08
	char m_pad14[0x74 - 0x14];
	RefRenderObjListClass UpdateList; // +0x74
	RefRenderObjListClass LightList; // +0x8C
	char m_padA4[0xEC - 0xA4];
	RefRenderObjListClass RenderList; // +0xEC
};

void Rva0009AA0F::Customized_Render(RenderInfoClass &rinfo)
{
	Visibility_Check(&rinfo.Camera);

	RefRenderObjListIterator it(&UpdateList);
	for (it.First(); !it.Is_Done(); it.Next())
		it.Peek_Obj()->On_Frame_Update();

	DX8Wrapper::Set_Light(0, 0);
	DX8Wrapper::Set_Light(1, 0);
	DX8Wrapper::Set_Light(2, 0);
	DX8Wrapper::Set_Light(3, 0);

	if (!rinfo.light_environment) {
		static LightEnvironmentClass lenv;
		lenv.Reset(Vector3(0, 0, 0), m_ambientLight);
		for (it.First(&LightList); !it.Is_Done(); it.Next())
			lenv.Add_Light(*(LightClass *)it.Peek_Obj());
		lenv.Pre_Render_Update(rinfo.Camera.Get_Transform());
		rinfo.light_environment = &lenv;
	}

	DX8Wrapper::Apply_Render_State_Changes();
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZWRITEENABLE, FALSE);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZENABLE, D3DZB_TRUE);

	for (it.First(&RenderList); !it.Is_Done(); it.Next()) {
		RenderObjClass *robj = it.Peek_Obj();
		if (robj->Is_Really_Visible())
			robj->Render(rinfo);
	}

	rva001173f0(reinterpret_cast<unsigned int>(&rinfo));
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZWRITEENABLE, TRUE);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	TheW3DShadowManager->queueShadows(true);
	reinterpret_cast<Rva0009A361 *>(TheW3DShadowManager)->rva0009A361((Int)&rinfo);
	TheDisplay->m_2C->begin(&rinfo.Camera);
	TheDisplay->m_2C->end();
	reinterpret_cast<Rva0009C983 *>(this)->rva0009C983((Int)&rinfo);
	TheParticleSystemManager->queueParticleRender();
	TheParticleSystemManager->doParticles(rinfo);
}

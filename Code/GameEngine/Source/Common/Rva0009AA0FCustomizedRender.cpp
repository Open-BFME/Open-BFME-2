// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
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

typedef unsigned long DWORD;
typedef long HRESULT;
typedef DWORD D3DRENDERSTATETYPE;
typedef int Int;

struct IDirect3DDevice8
{
#define G(n) virtual void __stdcall s##n() = 0;
	G(00) G(01) G(02) G(03) G(04) G(05) G(06) G(07) G(08) G(09)
	G(10) G(11) G(12) G(13) G(14) G(15) G(16) G(17) G(18) G(19)
	G(20) G(21) G(22) G(23) G(24) G(25) G(26) G(27) G(28) G(29)
	G(30) G(31) G(32) G(33) G(34) G(35) G(36) G(37) G(38) G(39)
	G(40) G(41) G(42) G(43) G(44) G(45) G(46) G(47) G(48) G(49)
	G(50) G(51) G(52) G(53) G(54) G(55) G(56)
#undef G
	virtual HRESULT __stdcall SetRenderState(D3DRENDERSTATETYPE state, DWORD value) = 0; // 57
};

class StringClass
{
public:
	StringClass(int initial_len = 0, bool hint_temporary = false);
	~StringClass() { Free_String(); }
private:
	char *m_Buffer;
	void Free_String();
};

struct _D3DLIGHT8;

extern unsigned number_of_DX8_calls;

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
	static void Get_DX8_Render_State_Value_Name(StringClass &name, D3DRENDERSTATETYPE state, unsigned value);

	static __forceinline void Set_DX8_Render_State(D3DRENDERSTATETYPE state, unsigned value)
	{
		if (RenderStates[state] == value) return;
		if (WW3D::Is_Snapshot_Activated()) {
			StringClass value_name(0, true);
			Get_DX8_Render_State_Value_Name(value_name, state, value);
		}
		RenderStates[state] = value;
		D3DDevice->SetRenderState(state, value);
		number_of_DX8_calls++;
		render_state_changes++;
	}

protected:
	static IDirect3DDevice8 *D3DDevice;
	static unsigned RenderStates[256];
	static unsigned render_state_changes;
};

class Vector3
{
public:
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X, Y, Z;
};

class Matrix3D
{
public:
	float Row[3][4];
};

class CameraClass
{
public:
#define G(n) virtual void v##n();
	G(00) G(01) G(02) G(03) G(04) G(05) G(06) G(07) G(08) G(09)
	G(10) G(11) G(12) G(13) G(14) G(15) G(16) G(17) G(18) G(19)
#undef G
	virtual void Validate_Transform(void) const; // 20
	const Matrix3D &Get_Transform(void) const { Validate_Transform(); return Transform; }
private:
	char m_pad04[0x18 - 0x04];
	Matrix3D Transform; // +0x18
};

class LightEnvironmentClass;

class RenderInfoClass
{
public:
	CameraClass &Camera;
	char m_pad04[0x28 - 0x04];
	LightEnvironmentClass *light_environment; // +0x28
};

class RefCountClassView
{
public:
	virtual void rc00();
	int NumRefs;
};

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();
	void *ListNode;
};

struct MultiListNodeClass
{
	MultiListNodeClass *Prev;
	MultiListNodeClass *Next;
	MultiListNodeClass *NextList;
	MultiListObjectClass *Object;
};

class GenericMultiListClass
{
public:
	virtual ~GenericMultiListClass();
	MultiListNodeClass Head;
	int m_extra;
};

class GenericMultiListIterator
{
public:
	GenericMultiListIterator(GenericMultiListClass *list) { First(list); }
	void First(GenericMultiListClass *list) { List = list; CurNode = List->Head.Next; }
	void First(void) { CurNode = List->Head.Next; }
	void Next(void) { CurNode = CurNode->Next; }
	bool Is_Done(void) { return (CurNode == &(List->Head)); }
protected:
	MultiListObjectClass *Current_Object(void) { return CurNode->Object; }
	GenericMultiListClass *List;
	MultiListNodeClass *CurNode;
};

class RenderObjClass : public RefCountClassView, public MultiListObjectClass
{
public:
#define G(n) virtual void v##n();
	G(01) G(02) G(03) G(04) G(05) G(06) G(07) G(08) G(09) G(10) G(11)
#undef G
	virtual void Render(RenderInfoClass &rinfo); // 12
	virtual void On_Frame_Update(void); // 13
#define G(n) virtual void v##n();
	G(14) G(15) G(16) G(17) G(18) G(19) G(20) G(21) G(22) G(23) G(24)
	G(25) G(26) G(27) G(28) G(29) G(30) G(31) G(32) G(33) G(34) G(35)
	G(36) G(37) G(38) G(39) G(40) G(41) G(42) G(43) G(44) G(45) G(46)
	G(47) G(48) G(49) G(50) G(51) G(52) G(53) G(54) G(55) G(56) G(57)
	G(58) G(59) G(60) G(61) G(62) G(63) G(64) G(65) G(66) G(67) G(68)
	G(69) G(70) G(71) G(72) G(73) G(74) G(75) G(76) G(77) G(78) G(79)
	G(80) G(81) G(82) G(83) G(84) G(85) G(86) G(87) G(88) G(89) G(90)
	G(91) G(92) G(93) G(94) G(95)
#undef G
	virtual int Is_Really_Visible(void); // 96
};

class LightClass : public RenderObjClass
{
};

class RefRenderObjListIterator : public GenericMultiListIterator
{
public:
	RefRenderObjListIterator(GenericMultiListClass *list) : GenericMultiListIterator(list) {}
	RenderObjClass *Peek_Obj(void) { return ((RenderObjClass *)Current_Object()); }
};


class BfmeVecHF;
class Gen_0094AC70
{
public:
	void bfmeSetPair(const BfmeVecHF *center, const BfmeVecHF *ambient);
};

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

class W3DShadowManager
{
public:
	void queueShadows(bool state) { m_isShadowScene = state; }
private:
	bool m_isShadowScene;
};
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

class ParticleSystemManager
{
public:
#define G(n) virtual void v##n();
	G(00) G(01) G(02) G(03) G(04) G(05) G(06) G(07) G(08) G(09) G(10)
	G(11) G(12) G(13) G(14) G(15)
#undef G
	virtual void doParticles(RenderInfoClass &rinfo); // 16
	virtual void v17();
	virtual void queueParticleRender(void); // 18
};
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
	GenericMultiListClass UpdateList; // +0x74
	GenericMultiListClass LightList; // +0x8C
	char m_padA4[0xEC - 0xA4];
	GenericMultiListClass RenderList; // +0xEC
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
	DX8Wrapper::Set_DX8_Render_State(23, 4);
	DX8Wrapper::Set_DX8_Render_State(14, 0);
	DX8Wrapper::Set_DX8_Render_State(7, 1);

	for (it.First(&RenderList); !it.Is_Done(); it.Next()) {
		RenderObjClass *robj = it.Peek_Obj();
		if (robj->Is_Really_Visible())
			robj->Render(rinfo);
	}

	WW3D::Flush(rinfo);
	DX8Wrapper::Set_DX8_Render_State(14, 1);
	DX8Wrapper::Set_DX8_Render_State(23, 8);

	TheW3DShadowManager->queueShadows(true);
	reinterpret_cast<Rva0009A361 *>(TheW3DShadowManager)->rva0009A361((Int)&rinfo);
	TheDisplay->m_2C->begin(&rinfo.Camera);
	TheDisplay->m_2C->end();
	reinterpret_cast<Rva0009C983 *>(this)->rva0009C983((Int)&rinfo);
	TheParticleSystemManager->queueParticleRender();
	TheParticleSystemManager->doParticles(rinfo);
}

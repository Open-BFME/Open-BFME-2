// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// BFME1 donor 2f243e26d44a74a48ef0ccfe9b543874e6567883,
// game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp
// setShroudTex; ZH same function supplies the shroud projection purpose.
// Native 00076C14..00077392 (1918B, cdecl int stage -> int) independently
// establishes owning texture binding and the eight identical stage states,
// followed by inverse view, origin translation, texture scaling and upload.
// The donor supplies the name; target terrain shroud/map fields3878/37C0,
// cell sizes10/14, texture dimensions20/24 and float origins2C/30 are byte-proven.
// Existing DX8Wrapper render_state baseDEE5D8 holds transposed view+22C;
// GetView/Matrix4 transpose comes from the verified SAS camera consumer.
// The address-derived7671F constructor remains the sole64B storage owner.
// Device slots67/44 and snapshot/counter/cache globals are read from retail;
// source data spellings retain existing ledger owners rather than new pins.
// D3DX stdcall thunks are identified independently by the PE import directory.
// Copy the SDK matrix multiply's real return-by-value temporaries: force-inline
// emits both D3DX calls and native64B copies; an ordinary inline left a call.
// Snapshot StringClass has its real4B buffer and matched constructor/teardown.
class Vector4
{
public:
	__forceinline Vector4() {}
	__forceinline Vector4(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }
	float &operator[](int i) { return (&X)[i]; }
	const float &operator[](int i) const { return (&X)[i]; }
	__forceinline Vector4 &operator=(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }
	__forceinline void Set(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }

	float X;
	float Y;
	float Z;
	float W;
};

class Matrix4
{
public:
	__forceinline Matrix4() {}
	__forceinline Matrix4(const Matrix4 &m)
	{
		Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; Row[3] = m.Row[3];
	}
	__forceinline explicit Matrix4(bool identity)
	{
		if (identity)
			Make_Identity();
	}
	__forceinline Matrix4(const Vector4 &r0, const Vector4 &r1, const Vector4 &r2, const Vector4 &r3)
	{
		Init(r0, r1, r2, r3);
	}
	__forceinline void Init(const Vector4 &r0, const Vector4 &r1, const Vector4 &r2, const Vector4 &r3)
	{
		Row[0] = r0; Row[1] = r1; Row[2] = r2; Row[3] = r3;
	}
	__forceinline void Make_Identity()
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
		Row[3].Set(0.0f, 0.0f, 0.0f, 1.0f);
	}
	__forceinline Matrix4 Transpose() const
	{
		return Matrix4(
			Vector4(Row[0][0], Row[1][0], Row[2][0], Row[3][0]),
			Vector4(Row[0][1], Row[1][1], Row[2][1], Row[3][1]),
			Vector4(Row[0][2], Row[1][2], Row[2][2], Row[3][2]),
			Vector4(Row[0][3], Row[1][3], Row[2][3], Row[3][3]));
	}
	__forceinline Matrix4 &operator=(const Matrix4 &m)
	{
		Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; Row[3] = m.Row[3];
		return *this;
	}
	static void Multiply(const Matrix4 &a, const Matrix4 &b, Matrix4 *res);

protected:
	Vector4 Row[4];
};

// The 0x40-byte matrix the setters build (rowed ctor 0x0007671F).
class Rva0007671F : public Matrix4
{
public:
	Rva0007671F();
};


struct D3DXMATRIX;
extern "C" D3DXMATRIX *__stdcall D3DXMatrixMultiply(D3DXMATRIX*,const D3DXMATRIX*,const D3DXMATRIX*);
struct D3DXMATRIX {float m[4][4]; D3DXMATRIX() {} __forceinline D3DXMATRIX operator*(const D3DXMATRIX &other)const {D3DXMATRIX result; D3DXMatrixMultiply(&result,this,&other);return result;} };
extern "C" D3DXMATRIX *__stdcall D3DXMatrixInverse(D3DXMATRIX*,float*,const D3DXMATRIX*);
extern "C" D3DXMATRIX *__stdcall D3DXMatrixMultiply(D3DXMATRIX*,const D3DXMATRIX*,const D3DXMATRIX*);
extern "C" D3DXMATRIX *__stdcall D3DXMatrixTranslation(D3DXMATRIX*,float,float,float);
extern "C" D3DXMATRIX *__stdcall D3DXMatrixScaling(D3DXMATRIX*,float,float,float);
class StringClass {public: StringClass(int,bool); ~StringClass(){Free_String();} private: void Free_String(); char *buffer;};
class WW3D {public: static bool Is_Snapshot_Activated(){return SnapshotActivated;} private: static bool SnapshotActivated;};
class TextureBaseClass {public:void Release_Ref();}; class TextureClass:public TextureBaseClass{};
template<class T>class RefCountPtr {public:T *ptr; ~RefCountPtr(){if(ptr)ptr->Release_Ref();}};
class RvaTextureHandleView:public RefCountPtr<TextureClass>{};
class Rva00072B3A {public: RvaTextureHandleView rva00072B3A()const; char pad[0x10];float cellWidth,cellHeight;char pad18[8];int textureWidth,textureHeight;char pad28[4];float drawOriginX,drawOriginY;};
class BaseHeightMapRenderObjClass {public:char pad[0x37C0];void *map;char pad37C4[0xB4];Rva00072B3A *shroud;};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
class TextureBaseClass;
void __cdecl BoxSetTexture(unsigned,TextureBaseClass *&);
static __forceinline void BindTexture(unsigned stage,const RvaTextureHandleView &handle){BoxSetTexture(stage,reinterpret_cast<TextureBaseClass *&>(const_cast<RvaTextureHandleView&>(handle)));}
struct IDirect3DDevice8 {virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual long __stdcall SetTransform(unsigned,const void *);
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual void slot58();
virtual void slot59();
virtual void slot60();
virtual void slot61();
virtual void slot62();
virtual void slot63();
virtual void slot64();
virtual void slot65();
virtual void slot66();
virtual long __stdcall SetTextureStageState(unsigned,unsigned long,unsigned);
};
extern unsigned number_of_DX8_calls;
struct RenderStateStruct {char pad[0x1EC];Matrix4 world,view;};
class DX8Wrapper {
public:
 static void Get_DX8_Texture_Stage_State_Value_Name(StringClass&,unsigned long,unsigned);
 static __forceinline void Set_DX8_Texture_Stage_State(unsigned stage,unsigned long state,unsigned value) {
  if(stage>=16){D3DDevice->SetTextureStageState(stage,state,value);++number_of_DX8_calls;return;}
  if(TextureStageStates[stage][state]==value)return;
  if(WW3D::Is_Snapshot_Activated()){StringClass valueName(0,true);Get_DX8_Texture_Stage_State_Value_Name(valueName,state,value);}
  TextureStageStates[stage][state]=value; D3DDevice->SetTextureStageState(stage,state,value); ++number_of_DX8_calls;++texture_stage_state_changes;
 }
 static __forceinline void GetView(Matrix4 &m) {if(render_state_changed&(1<<19))m.Make_Identity();else m=render_state.view.Transpose();}
 static __forceinline void SetMatrix(unsigned state,const D3DXMATRIX &m){++matrix_changes; D3DDevice->SetTransform(state,&m);++number_of_DX8_calls;}
protected:
 static IDirect3DDevice8 *D3DDevice; static unsigned TextureStageStates[16][32]; static unsigned texture_stage_state_changes,matrix_changes;
 static RenderStateStruct render_state;static unsigned render_state_changed;
};
class W3DShaderManager{public:static int setShroudTex(int);};
int W3DShaderManager::setShroudTex(int stage) {
 Rva00072B3A *shroud;
 if((shroud=TheTerrainRenderObject->shroud)!=0){
  BindTexture(stage,shroud->rva00072B3A());
  DX8Wrapper::Set_DX8_Texture_Stage_State(stage,11,131072);
  DX8Wrapper::Set_DX8_Texture_Stage_State(stage,24,2);
  DX8Wrapper::Set_DX8_Texture_Stage_State(stage,2,2);
  DX8Wrapper::Set_DX8_Texture_Stage_State(stage,3,1);
  DX8Wrapper::Set_DX8_Texture_Stage_State(stage,5,2);
  DX8Wrapper::Set_DX8_Texture_Stage_State(stage,6,1);
  DX8Wrapper::Set_DX8_Texture_Stage_State(stage,1,4);
  DX8Wrapper::Set_DX8_Texture_Stage_State(stage,4,3);

  D3DXMATRIX inv;float det; Rva0007671F curView;DX8Wrapper::GetView(curView); static_cast<Matrix4&>(curView)=curView.Transpose();
  D3DXMatrixInverse(&inv,&det,reinterpret_cast<D3DXMATRIX*>(&curView));
  D3DXMATRIX scale,offset;
  float xoffset=0,yoffset=0,width=shroud->cellWidth,height=shroud->cellHeight;
  if(TheTerrainRenderObject->map){xoffset=width-shroud->drawOriginX;yoffset=height-shroud->drawOriginY;}
  D3DXMatrixTranslation(&offset,xoffset,yoffset,0);
  width=1.0f/(width*shroud->textureWidth);height=1.0f/(height*shroud->textureHeight);
  D3DXMatrixScaling(&scale,width,height,1);
  *((D3DXMATRIX*)&curView)=(inv*offset)*scale;
  DX8Wrapper::SetMatrix(16+stage,*((D3DXMATRIX*)&curView));
  return 1;
 }
 return 0;
}

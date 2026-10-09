// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native 14A710..14A87C. Original method name unknown.
// Target model C4->descriptor94 tests B8/108 before modifying render state.
// Light environment C8, RGB314, virtual scalar slot25, and globals are target facts.
// Reference x87 Convert_Color is from BFME1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d dx8wrapper.h;
// it changes the rounding-control word, beyond ordinary C++ cast codegen.
struct Vector3 {float X,Y,Z; Vector3(){} Vector3(const Vector3& v):X(v.X),Y(v.Y),Z(v.Z){} };
class LightEnvironmentClass;
class DX8Wrapper {public:static void Set_Light_Environment(LightEnvironmentClass*);static bool FogEnable;static unsigned long FogColor;};
extern int g_rva009f36ac,g_rva009f36b0,G00DEDA78;
struct Rva00174753ReleaseView { virtual void *releaseInstance(unsigned)=0; unsigned unmodelled04; float scalar08; };
// Target nullable context with one observed scalar at +8; original type unknown.
extern Rva00174753ReleaseView *g_gapFillerAuxiliarySource;
struct Rva0014A710Inner {unsigned char prefix[0xb8];int flagB8;unsigned char pad[0x108-0xbc];int flag108;};
struct Rva0014A710Model {unsigned char prefix[0x94];Rva0014A710Inner* inner;};
class BFME2RenderObjInheritedDataView {public:void *Get_Inherited_Render_Data();};
class Rva0014A710 {
public:
 virtual void slot0();
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
 virtual float slot25();
 void prepare();
private:
 unsigned char prefix[0xc4-4];Rva0014A710Model* model;LightEnvironmentClass* light;unsigned char between[0x314-0xcc];Vector3 color;
};
__forceinline void Pack_Ambient_Color(const Vector3& color,float alpha)
{
    const float scale = 255.0f;
    unsigned int col = 0;

    __asm
    {
        sub esp,20                // a, r, g, b and saved FPU control word
        fwait
        fstcw [esp+16]            // save caller control word
        mov eax,[esp+16]
        mov edi,eax
        and eax,~(1024|2048)      // clear rounding-control bits
        or eax,(1024|2048)        // select truncation
        sub edi,eax
        jz skip
        mov [esp],eax
        fldcw [esp]
skip:
        mov esi,dword ptr color
        fld dword ptr[scale]
        fld dword ptr[esi]
        fld dword ptr[esi+4]
        fld dword ptr[esi+8]
        fld dword ptr[alpha]
        fld st(4)
        fmul st(4),st
        fmul st(3),st
        fmul st(2),st
        fmulp st(1),st
        fistp dword ptr[esp+0]
        fistp dword ptr[esp+4]
        fistp dword ptr[esp+8]
        fistp dword ptr[esp+12]
        mov ecx,[esp]
        mov eax,[esp+4]
        mov edx,[esp+8]
        mov ebx,[esp+12]
        shl ecx,24
        shl ebx,16
        shl edx,8
        or eax,ecx
        or eax,ebx
        or eax,edx
        fstp st(0)
        cmp edi,0
        je not_changed
        fwait
        fldcw [esp+16]            // restore caller control word
not_changed:
        add esp,20
        mov col,eax
    }
    DX8Wrapper::FogColor = col;
}

void Rva0014A710::prepare() {
 if(!model)return;
 if(!model->inner->flagB8 && !model->inner->flag108)return;
 if(light)DX8Wrapper::Set_Light_Environment(light);
 g_rva009f36ac=DX8Wrapper::FogColor;
 if(DX8Wrapper::FogEnable) {Vector3 c(color);Pack_Ambient_Color(c,0.f);}
 if(g_gapFillerAuxiliarySource)g_gapFillerAuxiliarySource->scalar08=slot25();
 g_rva009f36b0=G00DEDA78;
 G00DEDA78=(int)reinterpret_cast<BFME2RenderObjInheritedDataView*>(this)->Get_Inherited_Render_Data();
}

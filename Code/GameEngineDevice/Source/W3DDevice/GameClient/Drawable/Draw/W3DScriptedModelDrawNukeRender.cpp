// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Native B3348..B348C thiscall RET4; model constructor C0DD8 and
// destructor C79C9 establish the50/58/5C/81 fields and drawable8.
// WB931790 is the matching teardown; ZH W3DModelDraw::nukeCurrentRender
// guides shadow releases and optional transform copy. BFME2 guards DirectX
// and removes through scene slot3 only when render slot123 says in-scene.
// Render view only declares observed virtual slots0/20/123; unused slots
// carry no recovered signature claim. Target matrix18 and count4 are proven
// by native accesses. Forced inline matrix/vector assignment supplies the
// complete twelve-word copies in both branches. Original method name unknown.
#include "../../../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"
class Matrix3D {public:Vector4 row[3];__forceinline Matrix3D&operator=(const Matrix3D&o){row[0]=o.row[0];row[1]=o.row[1];row[2]=o.row[2];return *this;}};
class Drawable {public:const Matrix3D*getTransformMatrix()const;};
void BFME_DX8_Thread_Lock();bool BFME_DX8_Thread_Assert();
class DX8Scope {public:DX8Scope(){BFME_DX8_Thread_Lock();}~DX8Scope(){BFME_DX8_Thread_Assert();}};
class RenderView {public:virtual void Delete_This();
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
virtual void Validate_Transform()const;
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
virtual void slot44();
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
virtual void slot67();
virtual void slot68();
virtual void slot69();
virtual void slot70();
virtual void slot71();
virtual void slot72();
virtual void slot73();
virtual void slot74();
virtual void slot75();
virtual void slot76();
virtual void slot77();
virtual void slot78();
virtual void slot79();
virtual void slot80();
virtual void slot81();
virtual void slot82();
virtual void slot83();
virtual void slot84();
virtual void slot85();
virtual void slot86();
virtual void slot87();
virtual void slot88();
virtual void slot89();
virtual void slot90();
virtual void slot91();
virtual void slot92();
virtual void slot93();
virtual void slot94();
virtual void slot95();
virtual void slot96();
virtual void slot97();
virtual void slot98();
virtual void slot99();
virtual void slot100();
virtual void slot101();
virtual void slot102();
virtual void slot103();
virtual void slot104();
virtual void slot105();
virtual void slot106();
virtual void slot107();
virtual void slot108();
virtual void slot109();
virtual void slot110();
virtual void slot111();
virtual void slot112();
virtual void slot113();
virtual void slot114();
virtual void slot115();
virtual void slot116();
virtual void slot117();
virtual void slot118();
virtual void slot119();
virtual void slot120();
virtual void slot121();
virtual void slot122();
virtual bool Is_In_Scene();
int refs;char pad[0x18-8];Matrix3D transform;
const Matrix3D&Get_Transform()const{Validate_Transform();return transform;}
void Release_Ref(){if(--refs==0)Delete_This();}};
class RTS3DScene {public:virtual void s0();virtual void s1();virtual void s2();virtual void Remove_Render_Object(RenderView*);};class W3DDisplay {public:static RTS3DScene*m_3DScene;};
class ShadowView {public:virtual void s0();virtual void s1();virtual void release();};
class Rva000B3348 {public:void rva000B3348(Matrix3D*);private:char pad0[8];Drawable*drawable;char pad1[0x50-0xC];RenderView*render;int word54;ShadowView*shadow,*decal;char pad2[0x81-0x60];bool paused;};
void Rva000B3348::rva000B3348(Matrix3D*out){paused=false;if(shadow)shadow->release();shadow=0;if(decal)decal->release();decal=0;
if(render){DX8Scope lock;if(out)*out=render->Get_Transform();if(render->Is_In_Scene()){RTS3DScene*scene=W3DDisplay::m_3DScene;scene->Remove_Render_Object(render);}if(render){render->Release_Ref();render=0;}render=0;}
else if(out){*out=*drawable->getTransformMatrix();}}

// ?rva000B348E@Rva000B348E@@QAEX_N@Z retail 0x000B348E, 74 bytes RET4: the
// render-slot provider refresh this unit's 0xB3348 body belongs to. The
// secondary-base pointer at this-8 supplies the +0x6A guard flag; retail
// computes the boolean through its byte branch, then sets/clears bit 4 of the
// provider slot-120 word and hands it to slot 121 with a 1. The volatile read
// of the by-value parameter is what keeps the branchful guard. Identity
// address-derived; provider slot signatures from the two call offsets.
class Rva000B348EProvider
{
public:
	virtual void vslot000(); virtual void vslot001(); virtual void vslot002(); virtual void vslot003();
	virtual void vslot004(); virtual void vslot005(); virtual void vslot006(); virtual void vslot007();
	virtual void vslot008(); virtual void vslot009(); virtual void vslot010(); virtual void vslot011();
	virtual void vslot012(); virtual void vslot013(); virtual void vslot014(); virtual void vslot015();
	virtual void vslot016(); virtual void vslot017(); virtual void vslot018(); virtual void vslot019();
	virtual void vslot020(); virtual void vslot021(); virtual void vslot022(); virtual void vslot023();
	virtual void vslot024(); virtual void vslot025(); virtual void vslot026(); virtual void vslot027();
	virtual void vslot028(); virtual void vslot029(); virtual void vslot030(); virtual void vslot031();
	virtual void vslot032(); virtual void vslot033(); virtual void vslot034(); virtual void vslot035();
	virtual void vslot036(); virtual void vslot037(); virtual void vslot038(); virtual void vslot039();
	virtual void vslot040(); virtual void vslot041(); virtual void vslot042(); virtual void vslot043();
	virtual void vslot044(); virtual void vslot045(); virtual void vslot046(); virtual void vslot047();
	virtual void vslot048(); virtual void vslot049(); virtual void vslot050(); virtual void vslot051();
	virtual void vslot052(); virtual void vslot053(); virtual void vslot054(); virtual void vslot055();
	virtual void vslot056(); virtual void vslot057(); virtual void vslot058(); virtual void vslot059();
	virtual void vslot060(); virtual void vslot061(); virtual void vslot062(); virtual void vslot063();
	virtual void vslot064(); virtual void vslot065(); virtual void vslot066(); virtual void vslot067();
	virtual void vslot068(); virtual void vslot069(); virtual void vslot070(); virtual void vslot071();
	virtual void vslot072(); virtual void vslot073(); virtual void vslot074(); virtual void vslot075();
	virtual void vslot076(); virtual void vslot077(); virtual void vslot078(); virtual void vslot079();
	virtual void vslot080(); virtual void vslot081(); virtual void vslot082(); virtual void vslot083();
	virtual void vslot084(); virtual void vslot085(); virtual void vslot086(); virtual void vslot087();
	virtual void vslot088(); virtual void vslot089(); virtual void vslot090(); virtual void vslot091();
	virtual void vslot092(); virtual void vslot093(); virtual void vslot094(); virtual void vslot095();
	virtual void vslot096(); virtual void vslot097(); virtual void vslot098(); virtual void vslot099();
	virtual void vslot100(); virtual void vslot101(); virtual void vslot102(); virtual void vslot103();
	virtual void vslot104(); virtual void vslot105(); virtual void vslot106(); virtual void vslot107();
	virtual void vslot108(); virtual void vslot109(); virtual void vslot110(); virtual void vslot111();
	virtual void vslot112(); virtual void vslot113(); virtual void vslot114(); virtual void vslot115();
	virtual void vslot116(); virtual void vslot117(); virtual void vslot118(); virtual void vslot119();
	virtual unsigned int vslot120();
	virtual void vslot121(unsigned int v, int w);
};

class Rva000B348EO
{
public:
	char p[0x6A];
	bool f;
};

class Rva000B348E
{
public:
	void rva000B348E(bool b);
private:
	char a[0x44];
	Rva000B348EProvider *m;
	char c[0x208 - 0x48];
	int d;
};

void Rva000B348E::rva000B348E(bool b)
{
	Rva000B348EO *o = *(Rva000B348EO **)((char *)this - 8);
	bool u;
	if (o->f)
		u = false;
	else
		u = *(volatile bool *)&b;
	d = u;
	if (!m)
		return;
	unsigned int v = m->vslot120();
	if (u)
		v |= 4;
	else
		v &= ~4u;
	m->vslot121(v, 1);
}

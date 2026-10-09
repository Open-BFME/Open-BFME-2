// stlport
// cl: /O1 /MD /arch:SSE /G7 /EHsc /Ireference/shims/bfme2_ascii
// Native1FC49D..1FC701 (612B), reference source and native caller/callee evidence.
// Existing target vtable and136B destructor supply Rva001FC0F1 owner;
// recovered base1F4B63 supplies88B receiver prefix; heap caller1FCC73
// independently allocates C0B. BF1 ParticleConstructor.cpp at2f243e26d
// supplies model-name/asset-list/render/debug semantic guide, while target
// additionally supplies animation-name/tree setup and tail94 forwarding.
// Slot projections preserve only observed dispatch; original class name unknown.
#define _STLP_USE_STATIC_LIB
#include <set>
#include "ascii_string.h"
struct Vec12
{
	float x;
	float y;
	float z;
};
class Rva001F376E
{
public:
	Rva001F376E();
	virtual ~Rva001F376E();
	float m_04;
	float m_08;
	float m_0c;
	Vec12 m_10;
	Vec12 m_1c;
	Vec12 m_28;
	int m_34;
	unsigned char m_38;
	char m_pad39[3];
};
class BfmeParticleSystemHandle {public:~BfmeParticleSystemHandle()throw();};
class ParticleSystem;
ParticleSystem *Make001FCBD7();
class RvaSmartPtr12
{
public:
  ParticleSystem *operator->()const{return m_ptr?(ParticleSystem*)m_ptr:Make001FCBD7();}
 RvaSmartPtr12() { m_ptr = 0; m_pad04 = 0; m_pad08 = 0; }
  RvaSmartPtr12(const RvaSmartPtr12 &that);
  RvaSmartPtr12 &operator=(const RvaSmartPtr12 &that);
 ~RvaSmartPtr12() throw() {if(m_ptr)((BfmeParticleSystemHandle*)this)->BfmeParticleSystemHandle::~BfmeParticleSystemHandle();}
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};
class ClientFrameSubsystem
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30();
	virtual int s31();
};
extern ClientFrameSubsystem *TheGameClient;
class ParticleSystem;
class Rva001F4C67;
class HelperA4
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5(Rva001F4C67 *p);
};
class ParticleSystem
{
public:
	char m_pad00[0x7c];
	int m_7c;
	char m_pad80[0x24];
	HelperA4 *m_a4;
};
extern ParticleSystem *Make001FCBD7();
class ParticleSystemManager;
extern ParticleSystemManager *TheParticleSystemManager;
struct Node001F416C
{
	char m_pad[0x6c];
	Node001F416C *m_prev;
	Node001F416C *m_next;
	char m_gap;
	unsigned char m_flag;
};
class Rva001F416C
{
public:
	void rva001F416C(Node001F416C *node, int slot);
	char m_pad0[0x10];
	Node001F416C *m_arr1[7];
	Node001F416C *m_arr2[9];
	int m_count;
};
class Rva001F4C67 : public Rva001F376E
{
public:
	Rva001F4C67(const RvaSmartPtr12 &a, const Rva001F376E &b);
	RvaSmartPtr12 m_smart;
	Vec12 m_48;
	int m_54;
	int m_58;
	int m_5c;
	unsigned char m_60;
	char m_pad61[3];
	int m_64;
	int m_68;
	void *m_6c;
	void *m_70;
	unsigned char m_74;
	unsigned char m_75;
	char m_pad76[2];
	RvaSmartPtr12 m_78;
	int m_84;
};
struct Rva001408C0Target;
typedef _STL::set<Rva001408C0Target*,_STL::less<Rva001408C0Target*>,_STL::allocator<Rva001408C0Target*> > AssetSet621;
struct AssetList00208F90 {AssetSet621 prototypes;unsigned pad;bool changed;AssetList00208F90():pad(0),changed(true){} AssetList00208F90&operator<<(const AsciiString&);};
void bfmeMergeReceiverKeys(int);
class Rva001FC0A0 {public:Rva001FC0A0();char unknown[0x2C];};
class Rva001FC0B6 {public:~Rva001FC0B6();};
struct ParticleTail621 {Rva001FC0A0 contents;~ParticleTail621(){((Rva001FC0B6*)this)->Rva001FC0B6::~Rva001FC0B6();}};
class Rva001FC42D {public:void rva001FC42D(void*,void*);};
class RenderObjClass;
class HTreeClass;
RenderObjClass*Create_Render_Obj(const char*);
HTreeClass*Rva0014CF5F_GetAnimTree(const char*);
void rva0010E4F6(void*,bool);
class ParticleModelModule621 {public:virtual void v00();virtual void v04();virtual void v08();virtual void v0C();virtual void v10();virtual AsciiString modelName();virtual void v18();virtual int modelValue();};
struct ParticleSystemModel621 {char unknown00[0xC];int kind;char unknown10[0x1B4];ParticleModelModule621*module;};
class RenderView621 {public:
virtual void v000();
virtual void v001();
virtual void v002();
virtual void v003();
virtual void v004();
virtual void v005();
virtual void v006();
virtual void v007();
virtual void v008();
virtual void v009();
virtual void v00A();
virtual void v00B();
virtual void v00C();
virtual void v00D();
virtual void v00E();
virtual void v00F();
virtual void v010();
virtual void v011();
virtual void v012();
virtual void v013();
virtual void v014();
virtual void v015();
virtual void v016();
virtual void v017();
virtual void v018();
virtual void v019();
virtual void v01A();
virtual void v01B();
virtual void v01C();
virtual void v01D();
virtual void v01E();
virtual void v01F();
virtual void v020();
virtual void v021();
virtual void v022();
virtual void v023();
virtual void v024();
virtual void v025();
virtual void v026();
virtual void v027();
virtual void v028();
virtual void v029();
virtual void v02A();
virtual void v02B();
virtual void v02C();
virtual void animate(HTreeClass*,float,int);
virtual void v02E();
virtual void v02F();
virtual void v030();
virtual void v031();
virtual void v032();
virtual void v033();
virtual void v034();
virtual void v035();
virtual void v036();
virtual void v037();
virtual void v038();
virtual void v039();
virtual void v03A();
virtual void v03B();
virtual void v03C();
virtual void v03D();
virtual void v03E();
virtual void v03F();
virtual void v040();
virtual void v041();
virtual void v042();
virtual void v043();
virtual void v044();
virtual void v045();
virtual void v046();
virtual void v047();
virtual void v048();
virtual void v049();
virtual void v04A();
virtual void v04B();
virtual void v04C();
virtual void v04D();
virtual void v04E();
virtual void v04F();
virtual void v050();
virtual void v051();
virtual void v052();
virtual void v053();
virtual void v054();
virtual void v055();
virtual void v056();
virtual void v057();
virtual void v058();
virtual void v059();
virtual void v05A();
virtual void v05B();
virtual void v05C();
virtual void v05D();
virtual void v05E();
virtual void v05F();
virtual void v060();
virtual void v061();
virtual void v062();
virtual void v063();
virtual void v064();
virtual void enabled(int);};

class RefTree621 {public:virtual void destroy();int refs;};
class RTS3DScene {public:virtual void v00();virtual void v04();virtual void add(RenderObjClass*);};
class W3DDisplay {public:static RTS3DScene*m_3DScene;};
class Debug {public:
virtual void debug0();
virtual void debug1();
virtual void debug2();
virtual void debug3();
virtual void debug4();
virtual void debug5();
virtual void debug6();
virtual void debug7();
virtual void debug8();
virtual void debug9();
virtual void debug10();
virtual void debug11();
virtual void debug12();
virtual void debug13();
virtual Debug*message(const char*);
virtual void debug15();
virtual void debug16();
virtual void debug17();
virtual void debug18();
virtual void finish(int);
};
class DebugManager621 {public:
virtual void f0();
virtual void f1();
virtual void f2();
virtual void f3();
virtual void f4();
virtual void f5();
virtual void f6();
virtual void f7();
virtual void f8();
virtual void f9();
virtual void f10();
virtual void f11();
virtual void f12();
virtual void f13();
virtual void f14();
virtual void f15();
virtual void f16();
virtual void f17();
virtual void f18();
virtual void f19();
virtual void f20();
virtual void f21();
virtual void f22();
virtual void f23();
virtual void beginReport();
virtual void f25();
virtual void f26();
virtual Debug*startReport(int,int,int);
};
extern Debug *theDebug;
bool bfmeRva000387C0();void _bfme_debugRecordCallsite(int);
template<class T>Debug&operator<<(Debug&,const StringBase<T>&);
class Rva001FC0F1:public Rva001F4C67 {public:Rva001FC0F1(const RvaSmartPtr12&,const Rva001F376E&);virtual ~Rva001FC0F1();unsigned particleID;RenderObjClass*render;HTreeClass*animation;ParticleTail621 tail;};
Rva001FC0F1::Rva001FC0F1(const RvaSmartPtr12&system,const Rva001F376E&info)
 :Rva001F4C67(system,info),render(0),animation(0)
{
 particleID=0;
 if(((ParticleSystemModel621*)system.operator->())->kind==2){
  AsciiString name=((ParticleSystemModel621*)system.operator->())->module->modelName();
  if(!name.isEmpty()) {
   for(int i=4;i;--i)name.removeLastChar();
   AssetList00208F90 assets;assets<<name;bfmeMergeReceiverKeys((int)&assets);
   render=Create_Render_Obj(name.str());
   m_5c=((ParticleSystemModel621*)system.operator->())->module->modelValue();
   if(render){
    AsciiString animName;animName.format("%s.%s",name.str(),name.str());
    if(animation){RefTree621*p=(RefTree621*)animation;if(--p->refs==0)p->destroy();animation=0;}
    animation=Rva0014CF5F_GetAnimTree(animName.str());
    if(animation)((RenderView621*)render)->animate(animation,0.0f,1);
    ((RenderView621*)render)->enabled(1);
    rva0010E4F6(render,false);W3DDisplay::m_3DScene->add(render);
   }else if(bfmeRva000387C0()){
    _bfme_debugRecordCallsite(1);((DebugManager621*)theDebug)->beginReport();
    (*((DebugManager621*)theDebug)->startReport(0,0,0)->message("Particle system: could not create render object named '")<<*(StringBase<char>*)&name).message("'")->finish(2);
   }
  }
 }
 ((Rva001FC42D*)&tail)->rva001FC42D(this,m_smart.m_ptr);
}

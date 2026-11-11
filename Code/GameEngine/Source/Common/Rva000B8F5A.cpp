// cl: /ICode/Libraries/Include /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// String-slot cluster around 0x000B82F9. Members carry a flag byte, a raw
// name pointer and AsciiString slots; destruction of by-value AsciiString
// parameters emits the shared releaseBuffer worker (0x00036410) through the
// shim destructor, and slot fills go through StringBase::set (0x000366F0)
// via AsciiString::operator= (the operator= inline schedules the member-add
// ahead of the argument push where a direct set call does not).
// Class and member names are address-derived. Probe 0xB82F9 is verified;
// sibling 0xB83A7 follows the record110 string through the same counted probe.
// The adjacent transition BF9FC and condition replacement BFB76 share this
// existing owner view and compiler settings; their target method names remain
// unresolved. No original identity is inferred from a matching instruction shape.

#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include <string.h>
template<> bool StringBase<char>::isEmpty() const;

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/Rva000B4BED.h"

class Matrix3D;struct Coord3D;class Object;
#include "../../Include/Common/Rva000BFDFE.h"
class ModelConditionFlags;
#include "../../Include/GameClient/Drawable.h"
class FXList {public:static void doFXObj(const FXList*,const Object*,const Object*);static void doFXPos(const FXList*,const Coord3D*,const Matrix3D*,float,const Coord3D*);};
struct AnimationStateBF9FC {char pad00[0x68];const FXList*fx68;char pad6C[0x9C-0x6C];bool repeat9C;};
class ModelConditionFlags {public:bool rva000B3EB3()const;bool test(unsigned bit)const{return ((bits[bit>>5]>>(bit&31))&1)!=0;}unsigned bits[19];};
class WeaponTemplateSetHead {public:WeaponTemplateSetHead(const WeaponTemplateSetHead&);void rva000B3ED3(const WeaponTemplateSetHead&);unsigned bits[19];};
class Rva000B6253 {public:Rva000B6253*rva000B6253(int,unsigned,unsigned,unsigned,unsigned,unsigned);unsigned bits[19];};
#include "../../Include/Common/Rva000B4B23.h"
#include "../../Include/GameClient/ParticleSystemClass.h"
ParticleSystem*Make001FCBD7();
#include "../../Include/Common/RvaSmartPtr12.h"
namespace _STL {struct _Rb_tree_node_base {int color;
 _Rb_tree_node_base*parent,*left,*right;};
 template<class T>struct _Rb_global {static _Rb_tree_node_base*_M_increment(_Rb_tree_node_base*);};}
struct ModelChildNode { _STL::_Rb_tree_node_base links;unsigned id;};
class GameClient;extern GameClient*TheGameClient;
class GameClientBFB76View {public:virtual void s00();
 virtual void s01();
 virtual void s02();
 virtual void s03();
 virtual void s04();
 virtual void s05();
 virtual void s06();
 virtual void s07();
 virtual void s08();
 virtual void s09();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15(); virtual Drawable*getDrawable(unsigned);};
// Secondary condition interface begins at primary +10. Field suffixes below
// retain primary offsets used by the already verified BF9FC view; actual
// secondary accesses are those offsets minus10. Only accessed fields are modeled.
class Rva000BFB76Interface {public:virtual void rva000BFB76(const ModelConditionFlags&,bool,int);
 char pad04[4];AnimationStateBF9FC*m_18;
 RvaSmartPtr12 particle1C;char pad28[0x48-0x28];bool flag48;char pad49[0x68-0x49];
 void *begin68,*end6C,*cap70,*begin74,*end78,*cap7C;
 bool hide80;char pad81[0xA8-0x81];_STL::_Rb_tree_node_base*childrenA8;void*enabledAC;char padB0[0xB8-0xB0];unsigned syncB8;
 void*frozenBC;char padC0[0x17C-0xC0];ModelConditionFlags conditions17C;bool flag1C8,flag1C9;
 char pad1CA;bool transition1CB;void*next1CC;char pad1D0[0x25C-0x1D0];bool flag25C;
 char pad25D[0x28C-0x25D];bool m_flag28C;
};
struct Rva000BFB76Data {char pad00[0xBC];ModelConditionFlags ignored;char pad108[0x137-0x108];bool compare137;char pad138[0x15F-0x138];bool frozen15F;};

class Rva000BF9FCHeader {public:virtual void h00();
 virtual void h01();
 virtual void h02();
 virtual void h03();
 virtual void h04();
 virtual void h05();
 virtual void h06();
 virtual void h07();
 virtual void h08();
 virtual void h09();
 virtual void h10();
 virtual void h11();
 virtual void h12();
 virtual void h13();
 virtual void h14();
 virtual void h15();
 virtual void h16();
 virtual void h17();
 virtual void h18();
 virtual void h19();
 virtual void h20();
 virtual void h21();
 virtual void h22();
 virtual void h23();
 virtual void h24();
 virtual void h25();
 virtual void h26();
 virtual void h27();
 virtual void h28();
 virtual void h29();
 virtual void h30();
 virtual void h31();
 virtual void h32();
 virtual void h33();
 virtual void h34();
 virtual void h35();
 virtual void h36();
 virtual void h37();
 virtual void h38();
 virtual void h39();
 virtual void h40();
 virtual void h41();
 virtual void h42();
 virtual void h43();
 virtual void h44();
 virtual void h45();
 virtual void h46();
 virtual void h47();
 virtual void h48();
 virtual void h49();
 virtual void h50();
 virtual void h51();
 virtual void h52();
 virtual void h53();
 virtual void h54();
 virtual void h55();
 virtual void h56();
 virtual void h57();
 virtual void h58();
 virtual void h59();
 virtual void h60();
 virtual void h61();
 virtual void h62();
 virtual void h63();
 virtual void applyInfo(void*,bool,void*);
 void*data;
 Drawable*drawable;};
class Rva000BF9FCModelInterface {public:
virtual void v00();
 virtual void v01();
 virtual void v02();
 virtual void v03();
 virtual void v04();
 virtual void v05();
 virtual void v06();
 virtual void v07();
 virtual void v08();
 virtual void v09();
 virtual void v10();
 virtual void v11();
 virtual void v12();
 virtual void v13();
 virtual void v14();
 virtual void v15();
 virtual void v16();
 virtual void v17();
 virtual void v18();
 virtual void v19();
 virtual void v20();
 virtual void v21();
 virtual void v22();
 virtual void v23();
 virtual void v24();
 virtual void v25();
 virtual void v26();
 virtual void v27();
 virtual void v28();
 virtual void refresh();};
struct Rva000B8F5AOuter:public Rva000BF9FCHeader,public Rva000BF9FCModelInterface,public Rva000BFB76Interface
{
 bool rva000BF9FC(void *entry,bool force,int options);
 void adjustAnimation(void*,float,bool,bool,bool);
 void rva000BFB51(float);

};


struct MatrixView367 {float row[3][4];};
struct ObjectView367 {char pad00[8];MatrixView367 transform08;Coord3D position38;};
struct BarrelView367 {int recoil00,fx04,muzzle08;char pad0C[0x3C-0x0C];};
struct BarrelVector367 {BarrelView367*begin,*end,*capacity;};
struct StateView367 {char pad00[0xAC];BarrelVector367 barrels[3];char padD0[0xF4-0xD0];unsigned char validF4;};
struct RecoilView367 {int state;float value04,value08;};
struct RecoilVector367 {RecoilView367*begin,*end,*capacity;};
struct DataView367 {char pad00[0x54];float initial54;};
#include "../../Include/Common/Rva000B304B.h"
class RenderView367 {public:virtual void v000();virtual void v001();virtual void v002();virtual void v003();
virtual void v004();virtual void v005();virtual void v006();virtual void v007();
virtual void v008();virtual void v009();virtual void v010();virtual void v011();
virtual void v012();virtual void v013();virtual void v014();virtual void v015();
virtual void v016();virtual void v017();virtual void v018();virtual void v019();
virtual void v020();virtual void v021();virtual void v022();virtual void v023();
virtual void v024();virtual void v025();virtual void v026();virtual void v027();
virtual void v028();virtual void v029();virtual void v030();virtual void v031();
virtual void v032();virtual void v033();virtual void v034();virtual void v035();
virtual void v036();virtual void v037();virtual void v038();virtual void v039();
virtual void v040();virtual void v041();virtual void v042();virtual void v043();
virtual void v044();virtual void v045();virtual void v046();virtual void v047();
virtual void v048();virtual void v049();virtual void v050();virtual MatrixView367 bone(int);
virtual void v052();virtual void v053();virtual void v054();virtual void v055();
virtual void v056();virtual void v057();virtual void v058();virtual void v059();
virtual void v060();virtual void v061();virtual void v062();virtual void v063();
virtual void v064();virtual void v065();virtual void v066();virtual void v067();
virtual void v068();virtual void v069();virtual void v070();virtual void v071();
virtual void v072();virtual void v073();virtual void v074();virtual void v075();
virtual void v076();virtual void v077();virtual void v078();virtual void v079();
virtual void v080();virtual void v081();virtual void v082();virtual void v083();
virtual void v084();virtual void v085();virtual void v086();virtual void v087();
virtual void v088();virtual void v089();virtual void v090();virtual void v091();
virtual void v092();virtual void v093();virtual void v094();virtual void v095();
virtual void v096();virtual void v097();virtual void v098();virtual void v099();
virtual int hidden();
};

struct Rva000C144AEntry
{
	void *m_ptr00;
	float f04,f08,f0C;int mode10,direction14;bool active18;char pad19[3];
};

struct Rva000C14BDTarget
{
	virtual void v00();
	virtual void v01();
	virtual const char *v02();
	virtual void *v03();
	virtual void v04();
	virtual int v05();
};

class W3DScriptedModelDraw
{
public:
	bool handleWeaponFireFX(int,int,const FXList*,float,const Coord3D*);
	void getPlayingAnimationFrameRanges(int i,float *first,float *second);
	AsciiString getPlayingAnimationName(int i);
	void rva000B8F5A(char *a, AsciiString b);
	void rva000BFD77();
	void rva000BFD9F();
	int rva000C144A();
	int rva000B82F9();
	int rva000B83A7();
	void *getPlayingAnimationNameKey(int i);
	int rva000B5766(int slot);
	bool rva000B82C2(int index, struct CameraMarker *out);

private:
	char m_pad00[0x0C];
	void *m_ptr0C;
	char m_pad10[0x44-0x10];RenderView367*render44;char m_pad48[0x94-0x48];
	bool m_94;
	char m_pad95[0x98 - 0x95];
	char *m_98;
	char m_pad9C[0xA8 - 0x9C];
	AsciiString m_A8;
	char m_padAC[0xBC-0xAC];RecoilVector367 recoilBC[3];char m_padE0[0x104-0xE0];
	Rva000C144AEntry m_entries104[3];
	char m_pad158[0x1BF - 0x158];
	bool m_useState1C0;			// +0x1BF
	StateView367 *m_state1C0;		// +0x1C0
	char m_pad1C4[0x254 - 0x1C4];
	AsciiString m_name254;
	char m_pad258[0x280 - 0x258];
	bool m_flag280;
};

// ?rva000B8F5A@W3DScriptedModelDraw@@QAEXPADVAsciiString@@@Z @0x000B8F5A 71B
void W3DScriptedModelDraw::rva000B8F5A(char *a, AsciiString b)
{
	m_98 = a;
	m_94 = false;
	m_A8 = b;
}

// ?rva000BFB51@Rva000B8F5AOuter@@QAEXM@Z @0x000BFB51 37B
// Refill setter: when the +0x18 entry is live, clears the +0x28C flag first
// and refills through the outer 0xBEE25 body with (entry, value, 0, 1, 1).
void Rva000B8F5AOuter::rva000BFB51(float value)
{
	void *entry = m_18;
	if (entry != 0)
	{
		m_flag28C = false;
		adjustAnimation(entry, value, 0, 1, 1);
	}
}

// ?rva000BFD77@W3DScriptedModelDraw@@QAEXXZ @0x000BFD77 40B
// Table-probe refill: looks the +0x0C entry up in the outer table; on a hit
// raises the +0x280 flag first and refills through the outer 0xBF9FC body.
void W3DScriptedModelDraw::rva000BFD77()
{
	void *e = (*(Rva000B4BED **)((char *)this - 8))->rva000B4C9D(m_ptr0C);
	if (e != 0)
	{
		m_flag280 = true;
		((Rva000B8F5AOuter *)((char *)this - 12))->rva000BF9FC(e, 1, 0);
	}
}

// ?rva000BFD9F@W3DScriptedModelDraw@@QAEXXZ @0x000BFD9F 40B
// Twin of 0xBFD77 through the get-next sibling probe (0xB4CBE).
void W3DScriptedModelDraw::rva000BFD9F()
{
	void *e = (*(Rva000B4BED **)((char *)this - 8))->rva000B4CBE(m_ptr0C);
	if (e != 0)
	{
		m_flag280 = true;
		((Rva000B8F5AOuter *)((char *)this - 12))->rva000BF9FC(e, 1, 0);
	}
}

// ?rva000C144A@W3DScriptedModelDraw@@QAEHXZ @0x000C144A 35B
// Leading-live counter: runs the outer 0xC0386 probe, then counts the
// leading non-null +0x104 entries (3 x 0x1C, testing the first pointer).
int W3DScriptedModelDraw::rva000C144A()
{
	((Rva000BFDFE *)((char *)this - 12))->rva000C0386();
	unsigned n = 0;
	Rva000C144AEntry *e = m_entries104;
	do
	{
		if (e->m_ptr00 == 0)
			break;
		n++;
		e++;
	} while (n < 3);
	return n;
}

// ?getPlayingAnimationNameKey@W3DScriptedModelDraw@@QAEPAXH@Z @0x000C14BD 56B
// Indexed entry fetch: runs the outer 0xC0386 probe, bounds-checks the
// index against the 3 x 0x1C +0x104 entries, and returns the entry target's
// slot-3 virtual (or null when out of range or empty).
void *W3DScriptedModelDraw::getPlayingAnimationNameKey(int i)
{
	((Rva000BFDFE *)((char *)this - 12))->rva000C0386();
	if (i < 0 || (unsigned)i >= 3)
		return 0;
	Rva000C144AEntry *e = &m_entries104[i];
	// Volatile view: retail tests the slot in memory (cmp [eax],0) and
	// reloads it for the call instead of forwarding one load.
	Rva000C144AEntry volatile *ve = e;
	if (ve->m_ptr00 == 0)
		return 0;
	return ((Rva000C14BDTarget *)ve->m_ptr00)->v03();
}

// ?getPlayingAnimationName@W3DScriptedModelDraw@@QAE?AVAsciiString@@H@Z @0x000C146D 80B
// Returns a string by value: runs the outer 0xC0386 probe; when the index hits
// a live +0x104 entry, builds it from the entry target's slot-2 text (0x37BA0),
// otherwise returns an empty string. The return-object flag at [ebp-4] is the
// by-value return; indexing the entry twice keeps retail's test-then-reload.
// WorldBuilder W3DScriptedModelDraw::getPlayingAnimationName, WB VA 0x00930240 (align lead, score 2; ret 8 with the hidden result).
AsciiString W3DScriptedModelDraw::getPlayingAnimationName(int i)
{
	((Rva000BFDFE *)((char *)this - 12))->rva000C0386();
	if (i >= 0 && (unsigned)i < 3)
	{
		if (m_entries104[i].m_ptr00 != 0)
			return AsciiString(((Rva000C14BDTarget *)m_entries104[i].m_ptr00)->v02());
	}
	return AsciiString();
}

// TargetB82F9 establishes secondary view(-C), outer slot49, state(-8)
// string10C and override254. Provider slot32 returns a counted handle;
// slot5 yields a32-bit result and only the zero result releases its handle.
// Original class and result semantic names remain unresolved.
class ProbeHandleB83A7 {
public:
    virtual void Delete_This();
    virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4();
    virtual int probe();
    int refs;
    void Release_Ref() { if(--refs==0) Delete_This(); }
};
class ProbeProviderB83A7 {
public:
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual ProbeHandleB83A7 *find(const char *, bool);
};
class ProbeOuterB83A7 {
public:
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual void s48();
    virtual ProbeProviderB83A7 *get();
};
struct ProbeStateB83A7 {
    char unknown[0x10C];
    AsciiString name10C,name110;
};

// ?rva000B82F9@W3DScriptedModelDraw@@QAEHXZ
int W3DScriptedModelDraw::rva000B82F9()
{
    ProbeProviderB83A7 *provider=reinterpret_cast<ProbeOuterB83A7 *>((char *)this-12)->get();
    int result=0;
    if(provider) {
        AsciiString name;
        if(!reinterpret_cast<const StringBase<char> *>(&m_name254)->isEmpty()) name=m_name254;
        else name=(*reinterpret_cast<ProbeStateB83A7 **>((char *)this-8))->name10C;
        ProbeHandleB83A7 *handle=provider->find(name.str(),false);
        if(handle) { result=handle->probe(); if(!result) handle->Release_Ref(); }
    }
    return result;
}

// ?rva000B83A7@W3DScriptedModelDraw@@QAEHXZ
// Retail B83A7..B8440 uses the same secondary receiver and probe slots as
// B82F9 but always selects state+110. Reassigning the typed address view
// preserves the native source pointer in ESI. The result role is unproven.
int W3DScriptedModelDraw::rva000B83A7()
{
    ProbeProviderB83A7 *provider=reinterpret_cast<ProbeOuterB83A7 *>((char *)this-12)->get();
    int result=0;
    if(provider) {
        AsciiString name;
        const ProbeStateB83A7 *state = reinterpret_cast<const ProbeStateB83A7 *>(this);
        state = *reinterpret_cast<ProbeStateB83A7 *const *>((const char *)state - 8);
        name = state->name110;
        ProbeHandleB83A7 *handle=provider->find(name.str(),false);
        if(handle) { result=handle->probe(); if(!result) handle->Release_Ref(); }
    }
    return result;
}

extern int g_bfmeDisplayAnimationSyncClock;
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/Rva000BC9B1.h"
class Rva000B2EB5 {public:float rva000B2EB5();};
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/Rva000B9A0E.h"
// Full nativeBF9FC..BFB51 RET12: WB931DE0 animation-state transition.
// Reference W3DModelDraw state/animation sequence is semantic context only;
// target owns added state callbacks, effects, tick synchronization and vectors.
bool Rva000B8F5AOuter::rva000BF9FC(void*entry,bool force,int options){
 AnimationStateBF9FC*next=(AnimationStateBF9FC*)entry;
 if(m_18==next){
  if(m_18 && m_18->repeat9C && force)m_18=next;
  else if(force)refresh();else return false;
 }
 unsigned now=(unsigned)g_bfmeDisplayAnimationSyncClock;
 if(now>syncB8)flag25C=false;
 syncB8=now;
 if(!(drawable->m_status&8))flag48=true;
 ((Rva000BC9B1*)this)->rva000BC9B1(true);
 AnimationStateBF9FC*previous=m_18;
 float fraction=((Rva000B2EB5*)this)->rva000B2EB5();
 m_18=next;
 adjustAnimation(previous,fraction,0,0,(bool&)options);
 if(previous!=m_18){
  if(previous)((Rva000B9A0E*)previous)->rva000B9A0E(drawable->m_object,2,0);
  if(m_18)((Rva000B9A0E*)m_18)->rva000B9A0E(drawable->m_object,1,0);
 }
 if(m_18!=next)return true;
 if(next && next->fx68){
  Drawable*draw=drawable;
  if(draw->m_object)FXList::doFXObj(next->fx68,draw->m_object,0);
  else FXList::doFXPos(next->fx68,draw->getPosition(),draw->getTransformMatrix(),0.0f,0);
 }
 if((begin74!=end78 && flag1C9)||(begin68!=end6C && flag1C8))refresh();
 return true;
}

// Retail BFB76..BFD77: complete 513-byte RET12 body. Secondary interface receiver +10;
// WB935790 supplies native child propagation, condition comparison, particle
// teardown and transition arguments. BF1 W3DModelDraw replacement is semantic
// context; this target method's original name is unresolved.
void Rva000BFB76Interface::rva000BFB76(const ModelConditionFlags&conditions,bool force,int options){
 Rva000BFB76Data*data=*(Rva000BFB76Data**)((char*)this-0xC);
 if(data->frozen15F && frozenBC)return;
 const ModelConditionFlags&ignored=data->ignored;
 if(ignored.rva000B3EB3() && enabledAC){
  WeaponTemplateSetHead set=*(const WeaponTemplateSetHead*)&conditions;
  set.rva000B3ED3(*(const WeaponTemplateSetHead*)&ignored);
  WeaponTemplateSetHead clear=*(const WeaponTemplateSetHead*)&conditions;
  for(unsigned i=0;i<19;++i)clear.bits[i]=~clear.bits[i];
  clear.rva000B3ED3(*(const WeaponTemplateSetHead*)&ignored);
  for(_STL::_Rb_tree_node_base*node=childrenA8->left;node!=childrenA8;node=_STL::_Rb_global<bool>::_M_increment(node)){
   Drawable*child=((GameClientBFB76View*)TheGameClient)->getDrawable(((ModelChildNode*)node)->id);
   if(child)child->rva002761F3((const int*)&clear,(const int*)&set);
  }
 }
 void*info=((Rva000B4B23*)*(void**)((char*)this-0xC))->rva000B4B23(conditions);
 bool change=force;
 if(!change && data->compare137){
  Rva000B6253 mask;mask.rva000B6253(0,3,4,5,7,8);
  WeaponTemplateSetHead old=*(const WeaponTemplateSetHead*)&conditions17C;
  for(unsigned i=0;i<76;i+=4)*(unsigned*)((char*)&old+i)&=*(unsigned*)((char*)&mask+i);
  WeaponTemplateSetHead next=*(const WeaponTemplateSetHead*)&conditions;
  for(unsigned i=0;i<76;i+=4)*(unsigned*)((char*)&next+i)&=*(unsigned*)((char*)&mask+i);
  if(memcmp(&next,&old,sizeof(next)))change=true;
 }
 conditions17C=conditions;
 hide80=!(conditions.bits[0]&(1u<<7));
 void*state=((Rva000B4BED*)*(void**)((char*)this-0xC))->rva000B4BED(&conditions);
 if(transition1CB && m_18 && state==next1CC)state=m_18;
 else {transition1CB=false;next1CC=0;}
 if(!conditions.test(239) && *(ParticleSystem*volatile*)&particle1C.field00){
  particle1C->destroy();
  if(particle1C.field00){particle1C.rva0004CBC0();particle1C.field00=0;}
 }
 if(info)((Rva000B8F5AOuter*)((char*)this-0x10))->applyInfo(info,change,state);
 if(state){m_flag28C=false;((Rva000B8F5AOuter*)((char*)this-0x10))->rva000BF9FC(state,force,options);}
}

// Native C15F1..C1788 complete407B RET12, WB930BA0 named frame ranges.
// Secondary+C receiver and three1C records are independently shared with
// existing indexed getters and native B5D7F blending. Field roles inferred
// only from accesses: mode10, direction14, active18; no full record identity.
struct Rva000C15F1Range {float first,second;};
// WorldBuilder W3DScriptedModelDraw::getPlayingAnimationFrameRanges, WB VA 0x00930BA0 (align lead, score 1.8; ret 0xC); vtable 0x007CBBB4 slot beside getPlayingAnimationName/NameKey.
void W3DScriptedModelDraw::getPlayingAnimationFrameRanges(int i,float*first,float*second){
 ((Rva000BFDFE*)((char*)this-12))->rva000C0386();
 if(i<0 || (unsigned)i>=3 || !m_entries104[i].m_ptr00){
  first[0]=0.0f;first[1]=0.0f;
  *(Rva000C15F1Range*)second=*(const Rva000C15F1Range*)first;return;
 }
 W3DScriptedModelDraw*slot=(W3DScriptedModelDraw*)((char*)this+i*0x1C);
 if(slot->m_entries104[0].active18){
  switch(slot->m_entries104[0].mode10){
  case 1:
   first[0]=slot->m_entries104[0].f08;
   first[1]=(float)((Rva000C14BDTarget*)slot->m_entries104[0].m_ptr00)->v05();
   second[0]=-0.00001f;second[1]=slot->m_entries104[0].f04;return;
  case 3:
   if(m_entries104[i].direction14==1){
    if(slot->m_entries104[0].f08>slot->m_entries104[0].f04){first[0]=slot->m_entries104[0].f08;first[1]=0.0f;}
    else{first[0]=-0.00001f;first[1]=slot->m_entries104[0].f04;}
   }else{
    if(slot->m_entries104[0].f04>slot->m_entries104[0].f08){
     first[0]=slot->m_entries104[0].f08;
     first[1]=(float)((Rva000C14BDTarget*)slot->m_entries104[0].m_ptr00)->v05()-1.0f;
    }else{
     first[0]=(float)((Rva000C14BDTarget*)slot->m_entries104[0].m_ptr00)->v05()-0.99999f;
     first[1]=slot->m_entries104[0].f04;
    }
   }
   second[0]=0.0f;second[1]=0.0f;return;
  case 5:
   first[0]=slot->m_entries104[0].f08;first[1]=0.0f;
   second[0]=(float)((Rva000C14BDTarget*)slot->m_entries104[0].m_ptr00)->v05();
   second[1]=slot->m_entries104[0].f04;return;
  }
 }
 first[0]=slot->m_entries104[0].f08;first[1]=slot->m_entries104[0].f04;
 second[0]=0.0f;second[1]=0.0f;
}

// Target B57A7..B5916 full367 RET14 and WB9416C0 named weapon FX;
// ZH handleWeaponFireFX provides bone/hidden-object/recoil semantics.
// Target five arguments, secondary+C receiver, record3C and validF4,
// Native accesses establish offsets, the five-argument ABI and latched state.
// Record roles and subsystem identity are supported by WB and the donor;
// local view names retain uncertainty about original target types.
// Slot51 passes a return buffer and bone index in retail; the donor returns
// a matrix reference, so its return convention is not copied here.
// WorldBuilder W3DScriptedModelDraw::handleWeaponFireFX, WB VA 0x009416C0 (callgraph lead, score 1; ret 0x14; FXList::doFXPos callees).
bool W3DScriptedModelDraw::handleWeaponFireFX(int slot,int barrel,const FXList*fx,float speed,const Coord3D*victim){
 StateView367*state=(StateView367*)m_ptr0C;
 if(!state || !(state->validF4&8))return false;
 const BarrelVector367&vec=state->barrels[slot];
 if(vec.begin==vec.end)return false;
 bool handled=false;
 if(barrel<0 || (unsigned)barrel>(unsigned)(vec.end-vec.begin))barrel=0;
 const BarrelView367&info=vec.begin[barrel];
 if(fx && info.fx04 && render44){
  ObjectView367*object=(ObjectView367*)(*(Drawable**)((char*)this-4))->m_object;
  if(render44->hidden() && object){
   Coord3D position=object->position38;
   FXList::doFXPos(fx,&position,(const Matrix3D*)&object->transform08,speed,victim);
  }else{
   MatrixView367 matrix=render44->bone(info.fx04);
   Coord3D position;
   position.x=matrix.row[0][3];position.y=matrix.row[1][3];position.z=matrix.row[2][3];
   FXList::doFXPos(fx,&position,(const Matrix3D*)&matrix,speed,victim);
  }
  handled=true;
 }
 if(info.recoil00 || info.muzzle08){
  RecoilView367&recoil=recoilBC[slot].begin[barrel];
  if(!recoil.state){
   recoil.state=1;
   recoil.value08=(*(DataView367**)((char*)this-8))->initial54;
   if(info.muzzle08)((Rva000B304B*)&info)->setMuzzleFlashHidden(render44,false);
  }
 }
 return handled;
}

// ?rva000B5766@W3DScriptedModelDraw@@QAEHH@Z, retail 0x000B5766 (65 bytes, RET 4), slot 23 of the
// table 0x007CC588 beside handleWeaponFireFX: the barrel count of the given slot in the active
// state record (the +0x1C0 override while the +0x1BF flag is set, else +0x0C), or zero
// when there is no record or its +0xF4 bit 3 is clear.
int W3DScriptedModelDraw::rva000B5766(int slot)
{
	const StateView367 *state = m_useState1C0 ? m_state1C0 : (const StateView367 *)m_ptr0C;
	if (state && (state->validF4 & 8))
	{
		const BarrelVector367 &vec = state->barrels[slot];
		return vec.end - vec.begin;
	}
	return 0;
}

// ?rva000B82C2@W3DScriptedModelDraw@@QAE_NHPAUCameraMarker@@@Z, retail 0x000B82C2 (55 bytes, RET 8),
// table 0x007CC588 neighbour of the probe slots: copies entry [index] of the module data's
// 8-byte marker vector (+0x11C of the record at this-8) into out through the rowed
// CameraMarker::operator=, false when index is outside the vector.
struct CameraMarker
{
	CameraMarker &operator=(const CameraMarker &that);
	int m_00;
	int m_04;
};
struct MarkerVectorB82C2
{
	CameraMarker *begin;
	CameraMarker *end;
	CameraMarker *capacity;
	int size() const { return end - begin; }
	const CameraMarker &operator[](int i) const { return begin[i]; }
};
struct MarkerDataB82C2
{
	char unknown[0x11C];
	MarkerVectorB82C2 markers;
};

bool W3DScriptedModelDraw::rva000B82C2(int index, CameraMarker *out)
{
	const MarkerDataB82C2 *data = *reinterpret_cast<MarkerDataB82C2 *const *>((char *)this - 8);
	if (index >= 0 && index < data->markers.size())
	{
		*out = data->markers[index];
		return true;
	}
	return false;
}

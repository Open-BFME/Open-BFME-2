// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfme2_vector3 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// ?rva00275598@Drawable@@QAEXXZ, retail 0x00275598..0x0027566B (211 bytes):
// the Drawable's tint-status refresh (Zero Hour's updateDrawable block that
// compares m_tintStatus with m_prevTintStatus), in its BFME 2 form. When the
// status at +0x120 differs from the previous one at +0x124, the +0x8C tint
// envelope is created on demand (rowed constructor 0x00271826). Status bit 2
// -- or bit 1 when neither bit 3 nor bit 0 is set -- plays the global tint
// setting's colour (+0x30) with its attack/decay frames (+0x48/+0x4C), scaled
// by its +0x58 factor when the setting's mode test holds (rowed 0x0027000E),
// held indefinitely (rowed TintEnvelope::play); bits 3 or 0 instead put the
// envelope in state 2. The previous status then takes the current one.
// WorldBuilder's twin (0x00CA5060) is unnamed.

#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "vector3.h"
#include "../Common/GameLogicObjectLookupView.h"
class Drawable;
class Matrix3D;
// TU-scoped coordinate operations from the BF1 update donor; canonical layout.
struct DrawablePosition:Coord3D {
 void sub(const Coord3D *v){x-=v->x;y-=v->y;z-=v->z;}
 void scale(float value){x*=value;y*=value;z*=value;}
 void add(const Coord3D *v){x+=v->x;y+=v->y;z+=v->z;}
};
class Thing {public:virtual void slot0();Drawable *getDrawable() const;void setTransformMatrix(const Matrix3D *);};
class Object:public Thing {public:Object *rva002931F5(bool);
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79) V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87) V(88) V(89) V(90) V(91) V(92) V(93) V(94) V(95) V(96) V(97) V(98) V(99)
#undef V
 virtual const Coord3D *rva0028D4E0(Coord3D *,Coord3D *);
 const Matrix3D *getTransformMatrix() const {return reinterpret_cast<const Matrix3D *>(reinterpret_cast<const char *>(this)+8);}
 char pad04[0x438-4];unsigned char status438;
};
class Rva00271C8A {public:void rva00271C8A(const int *,const int *);};
class Rva00271A80 {
public:
	void rva00271A80(float x);
private:
	char m_pad[0xE4];
	bool m_enable;
	char m_padE5[3];
	int m_min;
	int m_max;
	int m_cur;
	float m_input;
};
void Rva00271A80::rva00271A80(float x)
{
	m_cur = 0;
	m_input = x;
	if (!m_enable)
		return;
	if (x <= 0.0f)
		m_cur = m_min;
	else if (x >= 1.0f)
		m_cur = m_max;
	else
		m_cur = (int)((m_max - m_min) * x + m_min);
}


class GameEngine {friend class Drawable;private:bool rva00225D38();};
extern GameEngine *TheGameEngine;
extern GameLogic *TheGameLogic;
class DrawableClientSlots {
public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28)
#undef V
 virtual void destroyDrawable(Drawable *);
 virtual void slot30();virtual unsigned getFrame();
};
class GameClient;
extern GameClient *TheGameClient;
int g_00DFEB98 = 0; // Native flash interval storage, initialized by 0x007ADEF6.
class DrawableConditionInterface {public:virtual void replaceModelConditionState(const int *,int,int);};
class DrawableUpdateModule {
public:
 virtual void slot0();
#define V(n) virtual void slot##n();
 V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10)
#undef V
 virtual bool isPaused();virtual void clientUpdate();
};
class DrawableDrawSlots {
public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20) V(21)
#undef V
 virtual void setTerrainDecalOpacity(float);
#define V(n) virtual void slot##n();
 V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34) V(35)
#undef V
 virtual void reactToUnpause();
};
template<class T> __forceinline const T& drawableMin(const T&a,const T&b){return a<b?a:b;}
template<class T> __forceinline const T& drawableMax(const T&a,const T&b){return a<b?b:a;}

class Rva002716Holder { public:void rva00271547(); };
extern int g_009BA4E8;
float Sin(float);
// Target reads the stored1/30-second value at VA DBA508; its original
// linkage/name is unknown. A local data owner preserves the measured read.
float opacityLogicStepSeconds=0.03333333507180214f;

struct RGBColor
{
	float red;
	float green;
	float blue;
 void setFromInt(int);
};

class Rva00271826
{
public:
	Rva00271826() throw();
	char m_pad00[0x38];
	unsigned char m_38;
	char m_pad39[3];float m_3C,m_40;char m_pad44[0x50-0x44];
 void setPulse(float first,float second){m_3C=first;m_40=second;}
};

class TintEnvelope
{
public:
 void play(const RGBColor *peak, unsigned int attackFrames, unsigned int decayFrames, unsigned int sustainAtPeak);
 void rva002719A7(float first, float second);
 void update();
private:
 void setDecayFrames(unsigned int frames);
 void setAttackFrames(unsigned int frames);
 enum EnvelopeStates { ENVELOPE_STATE_REST, ENVELOPE_STATE_ATTACK, ENVELOPE_STATE_DECAY, ENVELOPE_STATE_SUSTAIN };
 void *m_vtable;
 Vector3 m_attackRate;
 Vector3 m_decayRate;
 Vector3 m_peakColor;
 Vector3 m_currentColor;
 unsigned int m_sustainCounter;
 signed char m_envState;
 bool m_affect;
 char m_pad3A[2];
 float m_3C;
 float m_40;
};

class Rva0027000E
{
public:
	bool rva0027000E();
};

class Rva0027070CGlobal
{ public:
	unsigned char m_pad00[0x30];
	RGBColor m_color30;						// +0x30
	unsigned char m_pad3C[0x48 - 0x3C];
	int m_attack48;							// +0x48
	int m_decay4C;							// +0x4C
	unsigned char m_pad50[0x58 - 0x50];
	float m_scale58;						// +0x58
};

extern Rva0027070CGlobal *g_00DFE1E4;

void *operator new(unsigned int s) throw();

// Target DBB6A8/DBB6C0 float triples; original data names remain unresolved.
RGBColor disabledTintColor={-0.5f,-0.5f,-0.5f};
RGBColor timedTintColor={0.5f,-0.5f,-0.5f};
class Drawable
{
public:
	void rva00275598();
 void rva0027566B();
 void rva00272DBB(Object *);
 void rva00272870(int);
 void rva0027541E(const RGBColor *,unsigned,unsigned,unsigned);
 void rva0027292F(const Coord3D *,const Coord3D *);
 void fadeIn(unsigned);
 void setDrawableHidden(bool hidden);
 __forceinline DrawableDrawSlots **getDrawModules(){return draw14C;}
 void setTransformMatrix(const Matrix3D *m){reinterpret_cast<Thing *>(this)->setTransformMatrix(m);}

    void rva00272DEE();
private:
	__forceinline void playTint(Rva0027070CGlobal *setting, bool scaled)
	{
		int attack = setting->m_attack48;
		int decay = setting->m_decay4C;
		RGBColor color = setting->m_color30;
		if (scaled)
		{
			float scale = setting->m_scale58;
			attack = (int)(attack * scale);
			decay = (int)(decay * scale);
		}
		((TintEnvelope *)m_envelope8C)->play(&color, attack, decay, (unsigned int)-2);
	}
 unsigned char pad00[0x64];Rva00271826 *selection64,*color68;
 RGBColor custom6C;unsigned attack78,decay7C,sustain80;
 float affect84,affect88;
 Rva00271826 *m_envelope8C;
 unsigned char pad90[0xa8-0x90];int decalTypeA8;unsigned padAC;
 float explicitB0;
 float m_B4,m_B8,m_BC,m_C0,m_C4,m_C8,m_CC,m_D0;unsigned m_D4;
 unsigned padD8;float decalFadeDC,decalOpacityE0;
 unsigned char opacityEnabledE4;unsigned char padE5[3];
 int minE8,maxEC,curF0;float inputF4,incrementF8;
 Object *m_objectFC;
 unsigned char pad100[0x118-0x100];unsigned tint118,prev11C;
 unsigned m_tintStatus120,m_prevTintStatus124;
 int fade128;unsigned elapsed12C,duration130,then134;
 unsigned char pad138[0x14c-0x138];DrawableDrawSlots **draw14C;
 DrawableUpdateModule **updates150;
 unsigned pad154;DrawableConditionInterface **conditionBegin158,**conditionEnd15C;
 unsigned pad160,m_164;int flash168;unsigned flashColor16C;
 unsigned char pad170[0x258-0x170];int condition258[19],clear2A4[19],set2F0[19];
 unsigned char pad33C[0x350-0x33c];unsigned expires350;
 unsigned char pad354[0x37c-0x354];unsigned fadeLast37C,decalLast380;
 unsigned char pad384[0x3a9-0x384];bool copied3A9;
 unsigned char pad3AA[0x43c-0x3aa];unsigned char decalPosition43C,hidden43D,m_43E;
 unsigned char pad43F[2];bool pause441,wasPaused442,dirty443;

};

// Exact TintEnvelope attack/decay/play moved here before their caller.
// MSVC observes preserved EDX and XMM4; forward declarations alone erase
// those clobber facts and shift the entire update body.
typedef float Real;
typedef unsigned int UnsignedInt;
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
const Real FADE_RATE_EPSILON = 0.001f;

void TintEnvelope::setAttackFrames(UnsignedInt frames) 
{
	TintEnvelope *self = this;

	Real recipFrames = 1.0f / (Real)MAX(1,frames);
	self->m_attackRate.Set( self->m_currentColor );
	Vector3::Subtract( self->m_peakColor, self->m_attackRate, &self->m_attackRate);
	Vector3 rateScale; rateScale.Set(recipFrames, recipFrames, recipFrames);
	self->m_attackRate.Scale(rateScale);
}


void TintEnvelope::setDecayFrames( UnsignedInt frames )
{
	TintEnvelope *self = this;

	Real recipFrames = ( -1.0f ) / (Real)MAX(1,frames);
	self->m_decayRate.Set( self->m_peakColor );
	Vector3 rateScale; rateScale.Set(recipFrames, recipFrames, recipFrames);
	self->m_decayRate.Scale(rateScale);
}

void TintEnvelope::play(const RGBColor *peak, UnsignedInt atackFrames, UnsignedInt decayFrames, UnsignedInt sustainAtPeak )    
{
	TintEnvelope *self = this;

	Vector3 peakColor; peakColor.Set(peak->red, peak->green, peak->blue);
	self->m_peakColor = peakColor;

	setAttackFrames( atackFrames );
	setDecayFrames( decayFrames );

	self->m_envState = ENVELOPE_STATE_ATTACK;
	self->m_sustainCounter = sustainAtPeak;
	self->m_affect = true;

	Vector3 delta;
	Vector3::Subtract(self->m_currentColor, self->m_peakColor, &delta);

	if ( delta.Length() <= FADE_RATE_EPSILON ) // we are practically already at this color
		self->m_envState = ENVELOPE_STATE_SUSTAIN;

}


void Drawable::rva00275598()
{
	if (m_prevTintStatus124 != m_tintStatus120)
	{
		if (m_envelope8C == 0)
			m_envelope8C = new Rva00271826;
		Rva0027070CGlobal *setting = g_00DFE1E4;
		bool scaled = reinterpret_cast<Rva0027000E *>(setting)->rva0027000E();
		unsigned int status = m_tintStatus120;
		if (status & 4)
			playTint(setting, scaled);
		else if (status & 8)
			m_envelope8C->m_38 = 2;
		else if (status & 1)
			m_envelope8C->m_38 = 2;
		else if (status & 2)
			playTint(setting, scaled);
	}
	m_prevTintStatus124 = m_tintStatus120;
}

// BFME2 native272DEE..272FB6: inherit parent's effective stealth look,
// otherwise update pulse/transition opacity. ZH imitateStealthLook and
// setEffectiveOpacity establish the subsystem purpose; new pulse/transition
// equations, offsets and comparisons below are independently target facts.
void Drawable::rva00272DEE() {
 Object *parent=m_objectFC?m_objectFC->rva002931F5(false):0;
 if(parent && m_objectFC!=parent) {
  Drawable *other=parent->getDrawable();
  if(!other)return;
  m_B4=other->m_B4;
  unsigned char old=m_43E;
  m_43E=other->m_43E;
  m_164=other->m_164;
  if(old!=m_43E)reinterpret_cast<Rva002716Holder *>(this)->rva00271547();
 }else if(m_B8!=m_BC) {
  float pulse=m_C4+m_C8*Sin(m_CC);
  float blend=(g_009BA4E8*m_C0-m_D4)/(g_009BA4E8*m_C0);
  if(m_D4>0)--m_D4;
  m_B4=pulse*blend+m_D0*(1.0f-blend);
  m_CC+=(opacityLogicStepSeconds/m_C0)*3.1415927410125732f;
 }else if((float)(m_B8==m_BC)==1.0f && m_B4<1.0f) {
  float blend=(g_009BA4E8*m_C0-m_D4)/(g_009BA4E8*m_C0);
  if(m_D4>0)--m_D4;
  m_B4=m_D0*(1.0f-blend)+blend;
 }
}

// Native27566B..275D9F1844B. BF1 readonly9cbfb551 DrawableUpdateDrawable
// and ZH updateDrawable supply the lifecycle,
// fade/decal/expiry/flash/envelope semantics; BFME2 condition flags, pause gating,
// realtime deltas, extra tint states and position/normal forwarding are
// independently read from the retail body and its callers/providers.
void Drawable::rva0027566B() {
 unsigned now=TheGameLogic->getFrame();
 Object *obj=m_objectFC;
 if(TheGameEngine->rva00225D38() && dirty443) {
  Rva00271C8A *condition=reinterpret_cast<Rva00271C8A *>(condition258);
  condition->rva00271C8A(clear2A4,set2F0);
  DrawableConditionInterface **end=conditionEnd15C;
  for(DrawableConditionInterface **p=conditionBegin158;p!=end;++p)
   (*p)->replaceModelConditionState(reinterpret_cast<const int *>(condition),0,0);
  dirty443=false;
 }
 rva00272DBB(obj);
 if(pause441) {
  if(obj && !copied3A9) {setTransformMatrix(obj->getTransformMatrix());copied3A9=true;}
  for(DrawableUpdateModule **p=updates150;p && *p;++p)(*p)->clientUpdate();
  wasPaused442=true;
 }else {
  for(DrawableUpdateModule **p=updates150;p && *p;++p)if(!(*p)->isPaused())(*p)->clientUpdate();
  bool &wasPaused=wasPaused442;
  if(wasPaused) {
   wasPaused=false;
   DrawableDrawSlots **p=getDrawModules();
   while(*p) {(*p)->reactToUnpause();++p;}
  }
 }
 if(fade128!=0) {
  unsigned currentFrame=reinterpret_cast<DrawableClientSlots *>(TheGameClient)->getFrame();
  unsigned delta=currentFrame-fadeLast37C;
  fadeLast37C=currentFrame;
  elapsed12C=drawableMin(elapsed12C+delta,duration130);
  if(fade128<3) {
   unsigned numerator=fade128==1?elapsed12C:duration130-elapsed12C;
   double value=(float)numerator;
   value=duration130==0?(fade128==1?1.0:0.0):value/(float)duration130;
   float opacity=(float)value;
   explicitB0=opacity;
   if(elapsed12C>=duration130)fade128=0;
   if(!hidden43D && opacity*255.0f<1.0f)setDrawableHidden(true);
   else if(hidden43D)setDrawableHidden(false);
  }else if(duration130==elapsed12C) {
   setDrawableHidden(fade128==4);
   if(fade128==5)fadeIn(then134);
  }
 }
 if(opacityEnabledE4) {
  inputF4+=incrementF8;
  if(inputF4<0.0f)inputF4=0.0f;
  if(inputF4>1.0f)inputF4=1.0f;
  reinterpret_cast<Rva00271A80 *>(this)->rva00271A80(inputF4);
 }
 if(decalTypeA8!=7) {
  DrawableDrawSlots **dm=getDrawModules();
  if(*dm) {
   if(decalFadeDC!=0.0f) {
    unsigned frame=reinterpret_cast<DrawableClientSlots *>(TheGameClient)->getFrame();
    int delta=frame-decalLast380,one=1;
    const int &steps=drawableMax(delta,one);
    decalLast380=frame;
    (*dm)->setTerrainDecalOpacity(decalOpacityE0);
    decalOpacityE0+=steps*decalFadeDC;
   }
   if(decalFadeDC<0.0f && decalOpacityE0<=0.0f) {
    decalFadeDC=0.0f;decalOpacityE0=0.0f;rva00272870(7);
   }else if(decalFadeDC>0.0f && decalOpacityE0>=1.0f) {
    decalOpacityE0=1.0f;decalFadeDC=0.0f;(*dm)->setTerrainDecalOpacity(decalOpacityE0);
   }
  }
 }else decalOpacityE0=0.0f;
 if(expires350!=0 && now>=expires350) {
  reinterpret_cast<DrawableClientSlots *>(TheGameClient)->destroyDrawable(this);return;
 }
 if(flash168>0 && reinterpret_cast<DrawableClientSlots *>(TheGameClient)->getFrame()%g_00DFEB98==0) {
  RGBColor color;color.setFromInt(flashColor16C);rva0027541E(&color,4,0,0);--flash168;
 }
 if(prev11C!=tint118) {
  if(tint118&1) {
   if(!color68)color68=new Rva00271826;
   reinterpret_cast<TintEnvelope *>(color68)->play(&disabledTintColor,30,30,-2);
   color68->setPulse(0.0f,0.0f);
  }else if(tint118&8) {
   if(!color68)color68=new Rva00271826;
   reinterpret_cast<TintEnvelope *>(color68)->play(&timedTintColor,30,30,300);
   color68->setPulse(0.25f,0.05f);tint118=0;prev11C=0;
  }else if(tint118&16) {
   if(!color68)color68=new Rva00271826;
   reinterpret_cast<TintEnvelope *>(color68)->play(&timedTintColor,30,30,9999);
   color68->setPulse(0.0f,0.0f);tint118=0;prev11C=0;
  }else if(tint118&32) {
   if(!color68)color68=new Rva00271826;
   reinterpret_cast<TintEnvelope *>(color68)->play(&custom6C,attack78,decay7C,sustain80);
   color68->setPulse(affect84,affect88);tint118=0;prev11C=0;
   custom6C.setFromInt(-1);attack78=0;decay7C=0;sustain80=0;affect84=0.0f;affect88=0.0f;
  }else {
   if(!color68)color68=new Rva00271826;
   color68->m_38=2;
  }
 }
 prev11C=tint118;
 if(obj && !(obj->status438&1))tint118&=~2u;
 if(color68)reinterpret_cast<TintEnvelope *>(color68)->update();
 if(selection64)reinterpret_cast<TintEnvelope *>(selection64)->update();
 rva00272DEE();
 if(obj) {
  if(decalPosition43C) {
   Coord3D normal;
   Coord3D position;
   rva0027292F(obj->Object::rva0028D4E0(&position,&normal),&normal);
  }else {
   Object *parent=obj->rva002931F5(true);
   if(parent) {
    Drawable *other=parent->getDrawable();
    if(other && other->decalPosition43C) {
     DrawablePosition direction,position;
     parent->Object::rva0028D4E0(&direction,0);
     obj->Object::rva0028D4E0(&position,0);
     direction.sub(&position);
     if(direction.x*direction.x+direction.y*direction.y+direction.z*direction.z>0.01f) {
      direction.Normalize();
      direction.scale(10.0f);
      position.add(&direction);
     }
     Coord3D normal;
     rva0027292F(&position,&normal);
    }
   }
  }
 }
}

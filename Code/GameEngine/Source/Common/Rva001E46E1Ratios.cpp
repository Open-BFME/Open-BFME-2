// cl: /O1 /G7 /arch:SSE /ICode/Libraries/Include /DNDEBUG /MD /Oi-
// Float getters of one object-module class whose shared worker is the
// unrowed 356-byte 0x001E46E1 (pinned by address from these call sites; it
// reads the Object's +0x254 and +0x258 and calls the rowed check at
// 0x001E468F). Layout facts from the bodies: module data at +4 holding
// unsigned counts at +0x44 and +0x50; floats at +0x30, +0x34, +0x40 and a
// cached value at +0x5C stamped with a frame at +0x60, compared against
// TheGameLogic's frame (+0x40).
//   0x001E4845  worker / count44, capped at +0x30
//   0x001E488A  worker / count50, capped at +0x34
//   0x001E48CF  cached +0x5C unless its frame is stale, else the worker
//   0x001E543F  whether +0x40 exceeds a quarter of the worker
//   0x001E53D8  step +0x40 toward a limit by the +0x30-capped ratio, then
//               clamp it to [0, worker]
// Retail compares with fcompi, which MSVC 7.1 emits only under /arch:SSE.
// Class and member names are unknown, hence address-derived.
#include "Lib/Coord3D.h"
class Object;
class GameLogic;
extern GameLogic *TheGameLogic;
extern float g_secondsPerLogicFrame;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
class Rva001E468F;
struct Rva001E46E1FrameView
{
	char m_pad00[0x40];
	unsigned int m_frame;
};
struct Rva001E46E1Data
{
	char m_pad00[0x18];
	float m_18;
	char m_pad1C[0x24-0x1C];
	float m_24;
	char m_pad28[0x44 - 0x28];
	unsigned int m_44;
	float m_48;
	float m_4C;
	unsigned int m_50;
	char m_pad54[0xEC - 0x54];
	unsigned char m_ec;
	char m_padED[0x104 - 0xED];
	float m_104;
	unsigned char m_108;
	unsigned char m_109;
	char m_pad10A[0x14C - 0x10A];
	float m_14C;
};
class Rva001E46E1
{
public:
	float rva001E46E1(Object *obj);
    bool rva001E5F1D(Object*,const Coord3D*,float*);
	void rva001E546B(Object *obj);
	float rva001E3F4D(Object *obj,int condition);
	float rva001E4845(Object *obj);
	float rva001E488A(Object *obj);
	bool rva001E543F(Object *obj);
	float rva001E48CF(Object *obj);
	void rva001E53D8(float limit, Object *obj);
	void *m_00;
	const Rva001E46E1Data *m_data;
	char m_pad08[0x24 - 8];
	float m_24;
	float m_28;
	float m_2c;
	float m_30;
	float m_34;
	char m_pad38[0x40 - 0x38];
	float m_40;
	char m_pad44[4];
	float m_48;
	char m_pad4C[0x5C - 0x4C];
	float m_5C;
	unsigned int m_60;
	char m_pad64[0xA0-0x64];
	float m_A0,m_A4;
};
class Obj254V
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual int s08();
};
class Rva00368C7A { public: unsigned char rva00368271(); };
struct Obj258Holder
{
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
	virtual void s49();
	virtual void s50();
	virtual void s51();
	virtual void s52();
	virtual void s53();
	virtual void s54();
	virtual void s55();
	virtual void s56();
	virtual void s57();
	virtual void s58();
	virtual void s59();
	virtual void s60();
	virtual void s61();
	virtual void s62();
	virtual void s63();
	virtual void s64();
	virtual void s65();
	virtual void s66();
	virtual void s67();
	virtual void s68();
	virtual void s69();
	virtual void s70();
	virtual void s71();
	virtual void s72();
	virtual void s73();
	virtual void s74();
	virtual void s75();
	virtual void s76();
	virtual void s77();
	virtual void s78();
	virtual void s79();
	virtual void s80();
	virtual void s81();
	virtual void s82();
	virtual void s83();
	virtual void s84();
	virtual void s85();
	virtual void s86();
	virtual void s87();
	virtual void s88();
	virtual void s89();
	virtual void s90();
	virtual void s91();
	virtual void s92();
	virtual void s93();
	virtual void s94();
	virtual void s95();
	virtual void s96();
	virtual void s97();
	virtual Rva00368C7A *query001E546B();
	char m_pad[0x1F8-4];
	float m_1F8;
};
struct Rva001E546BFlags {
    unsigned m_bits[19];
    __forceinline unsigned test(unsigned i)const {return m_bits[i>>5] & (1u<<(i&31));}
    __forceinline void set(unsigned i){m_bits[i>>5]|=1u<<(i&31);}
    __forceinline void reset(unsigned i){m_bits[i>>5]&=~(1u<<(i&31));}
};
class Thing { public: float getHeightAboveTerrainOrWater()const; void setOrientation(float); };
class Rva0030A92C { public: void rva0030A92C(float); };
extern "C" double __cdecl sin(double);
float normalizeAngle(float);
float GetGameLogicRandomValueReal(float,float,char*,int);
class Object : public Thing
{
public:
	float rva0028B842() const;
    int rva0028B511() const;
    void rva001E431E(const int*);
    void rva001E42F2(const int*);
	bool rva0028C15E(int attr, float *val, int a, int b);
	void rva0028AE6D();
	__forceinline int getID()const {return m_id74;}
	char m_pad00[0x38];
	float m_38;
	float m_3C;
	float m_40,m_44;
	char m_pad48[0x74-0x48];
	int m_id74;
	char m_pad78[0xBC-0x78];
	float m_BC;
	char m_padC0[0x10C-0xC0];
	Rva001E546BFlags m_flags10C;
	char m_pad158[0x250-0x158];
	void *m_250;
	Obj254V *m_254;
	Obj258Holder *m_258;
};
class GlobalData
{
public:
	char m_pad[0xB3C];
	int m_b3c;
};
class TerrainLogic
{
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
	virtual bool s19(float x, float y, float *a, float *b, unsigned char *out);
};
class Rva001E468F
{
public:
	bool rva001E468F(Object *obj);
};
float Rva001E46E1::rva001E4845(Object *obj)
{
	float value = rva001E46E1(obj) / (float)m_data->m_44;
	if (value > m_30)
		value = m_30;
	return value;
}
float Rva001E46E1::rva001E488A(Object *obj)
{
	float value = rva001E46E1(obj) / (float)m_data->m_50;
	if (value > m_34)
		value = m_34;
	return value;
}
bool Rva001E46E1::rva001E543F(Object *obj)
{
	float current = m_40;
	return current > rva001E46E1(obj) * 0.25f;
}
float Rva001E46E1::rva001E48CF(Object *obj)
{
	if (m_60 < ((const Rva001E46E1FrameView *)TheGameLogic)->m_frame)
		return rva001E46E1(obj);
	return m_5C;
}

static inline float bfmeClamp(float value, float lo, float hi)
{
	if (value < lo)
		return lo;
	if (value > hi)
		return hi;
	return value;
}

void Rva001E46E1::rva001E53D8(float limit, Object *obj)
{
	if (limit > m_40) {
		m_40 += rva001E4845(obj);
		if (m_40 > limit)
			m_40 = limit;
	} else {
		m_40 = limit;
	}
	float cap = rva001E46E1(obj);
	m_40 = bfmeClamp(m_40, 0.0f, cap);
}
float Rva001E46E1::rva001E46E1(Object *obj)
{
	int cmpVal = obj->m_254->s08();
	float scale = obj->m_258->m_1F8;
	int gv = TheWritableGlobalData->m_b3c;
	float f;
	if (cmpVal >= gv && m_data->m_109 == 0)
		f = m_data->m_24 * g_secondsPerLogicFrame * scale;
	else if (((Rva001E468F *)this)->rva001E468F(obj))
		f = m_data->m_104 * g_secondsPerLogicFrame * scale;
	else
		f = g_secondsPerLogicFrame * scale;
	if (f > m_28)
		f = m_28;
	if (m_data->m_ec != 0)
		f *= obj->rva0028B842();
	float tmp = 0.0f;
	if (obj->rva0028C15E(8, &tmp, 0, 1))
		f = tmp * f;
	if (m_data->m_14C != 1.0f) {
		unsigned char flag = 0;
		if (TheTerrainLogic->s19(obj->m_38, obj->m_3C, 0, 0, &flag) && flag != 0)
			f = m_data->m_14C * f;
	}
	if (m_2c != -1.0f) {
		if (m_2c > f)
			goto done2c;
		f = m_2c;
	}
done2c:
	return f;
}

// Target 0x001E3F4D..0x001E3FAD (RET8). Native caller 0x001E558A uses
// this same locomotor receiver and the object's body-condition result.
// BFME1 LocomotorRva001B5A30.cpp at 9cbfb551fe20dae985f91f2319d8997287b6a705
// establishes the lift-limit role; target offsets/calls above establish the
// local layout. Original method name remains unknown. Keeping the square
// in each branch reproduces retail's shared square then memory multiplies.
float Rva001E46E1::rva001E3F4D(Object *obj,int condition)
{
    float scale=obj->m_258->m_1F8;
    float result;
    if (condition < TheWritableGlobalData->m_b3c)
        result=(g_secondsPerLogicFrame*g_secondsPerLogicFrame)*m_data->m_48;
    else
        result=(g_secondsPerLogicFrame*g_secondsPerLogicFrame)*m_data->m_4C;
    result*=scale;
    if (result > m_24) result=m_24;
    return result;
}

// BFME1 LocomotorVerticalUpdateRva001B80D0.cpp at 9cbfb551fe20dae985f91f2319d8997287b6a705
// supplies the vertical bobbing/jitter semantics. Native 0x001E546B..0x001E56DC
// proves Object BC/74/254/258, AI slot188, template18 and mover48/A0/A4.
// Target's model-condition bits are 72/103/155 at byte115/118/11F; donor
// offsets and bit numbers differ. Original class/method names remain unproven.
void Rva001E46E1::rva001E546B(Object *obj)
{
    if(!obj) return;
    float amplitude=obj->m_BC; amplitude*=0.5f;
    if(m_data->m_18>1.0f) amplitude=m_data->m_18*amplitude;
    Obj258Holder *ai=obj->m_258;
    if(!ai) return;
    Rva00368C7A *heightView=ai->query001E546B();
    if(!heightView) return;
    Obj254V *body=obj->m_254;
    if(!body) return;
    float baseline=m_48;
    float wave=(float)sin((int)(((const Rva001E46E1FrameView*)TheGameLogic)->m_frame+obj->getID())*0.1f);
    wave*=amplitude;
    wave*=0.2f;
    float desired=wave+baseline;
    float current=obj->getHeightAboveTerrainOrWater();
    bool outside=desired+amplitude*0.2f>current || desired*1.5f<current;
    if(heightView->rva00368271() | outside) m_A0+=desired-current;
    float cap=rva001E3F4D(obj,body->s08());
    m_A0*=0.25f;
    if(m_A0>cap) m_A0=cap;
    else if(m_A0< -cap) m_A0=-cap;
    if(m_A0>0.3f) {
        if(obj->m_flags10C.test(72) || !obj->m_flags10C.test(103)) {
            obj->m_flags10C.reset(72);
            obj->m_flags10C.set(103);
            obj->rva0028AE6D();
        }
    } else {
        if(obj->m_flags10C.test(103)) {
            obj->m_flags10C.reset(103);
            obj->rva0028AE6D();
        }
    }
    ((Rva0030A92C*)obj)->rva0030A92C(obj->m_40+m_A0);
    if(obj->m_flags10C.test(155)) {
        obj->m_flags10C.reset(155);
        obj->rva0028AE6D();
    }
    m_A4+=GetGameLogicRandomValueReal(-0.06283185631036758f,0.06283185631036758f,
        "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Locomotor.cpp",1831);
    if(m_A4>0.06283185631036758f) m_A4=0.06283185631036758f;
    if(m_A4< -0.06283185631036758f) m_A4=-0.06283185631036758f;
    float angle=obj->m_44+m_A4;
    float normalized=normalizeAngle(angle);
    obj->setOrientation(normalized);
}

class Rva001E4912 { public:
    Rva001E4912 *rva001E4912(int,unsigned,unsigned);
    unsigned m_bits[19];
};
class AI;
extern AI *TheAI;
struct Rva001E5F1DData { char pad[0x98]; float m_98; };
struct Rva001E5F1DAI { char pad[0x18]; const Rva001E5F1DData *m_data; };

// Native callers 0x001E7F5C/0x001E7FA5 set ECX to the locomotor and
// pass an Object, copied three-float position, and float output. RET12 proves
// the stack shape; this is unused in the body. Terrain slot4C supplies the
// height pair; TheAI data+98 is only a target-observed threshold, not a
// recovered field name. Bits239/240 are Object word7 at +128.
// Scope both 4C-byte masks separately so MSVC reuses their stack storage.
bool Rva001E46E1::rva001E5F1D(Object *obj,const Coord3D *pos,float *ground)
{
    float height=0.0f;
    if(obj->rva0028B511()==1 && TheTerrainLogic->s19(pos->x,pos->y,&height,ground,0)) {
        const float &limit=((Rva001E5F1DAI*)TheAI)->m_data->m_98;
        float depth=height-*ground;
        if(depth>limit*0.25f) {
            if(depth>limit) {
                Rva001E4912 flags;
                obj->rva001E431E((const int*)flags.rva001E4912(0,240,239));
            } else {
                if(obj->m_flags10C.test(240) || !obj->m_flags10C.test(239)) {
                    obj->m_flags10C.reset(240);
                    obj->m_flags10C.set(239);
                    obj->rva0028AE6D();
                }
            }
            return true;
        }
    }
    { Rva001E4912 flags;
    obj->rva001E42F2((const int*)flags.rva001E4912(0,240,239));
    }
    return false;
}

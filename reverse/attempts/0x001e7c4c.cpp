// ?rva001E7C4C@Rva001E7C4C@@QAEXPAVObject@@IMM@Z
// partial score=0.8758880937 date=2026-10-10
// cl: /G7 /arch:SSE /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: x87 float-forwarding twins at 0x1E7C2B/0x1E9045 (33B
// each). Each forwards (a,b,c,d) with this to its callee (0x1E7053 /
// 0x1E8C1B). Only c/d travel via fld/fstp into two push-ecx temps; a/b are
// dword-pushed directly, so the first two params are int-sized and the last
// two are float. Address-derived names; callee types unproven (pins).

class Rva001E7053
{
public:
	void rva001E7053(int a, int b, float c, float d);
};
class Rva001E8C1B
{
public:
	void rva001E8C1B(int a, int b, float c, float d);
};
class Rva001E7C2B
{
public:
	void rva001E7C2B(int a, int b, float c, float d);
};
class Rva001E9045
{
public:
	void rva001E9045(int a, int b, float c, float d);
};

// ?rva001E7C2B@Rva001E7C2B@@QAEXHHMM@Z
void Rva001E7C2B::rva001E7C2B(int a, int b, float c, float d)
{
	((Rva001E7053 *)this)->rva001E7053(a, b, c, d);
}

// ?rva001E9045@Rva001E9045@@QAEXHHMM@Z
void Rva001E9045::rva001E9045(int a, int b, float c, float d)
{
	((Rva001E8C1B *)this)->rva001E8C1B(a, b, c, d);
}

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
struct HoverFlags { unsigned prefix:5;unsigned overWater:1;unsigned tail:26; };
struct HoverObjectView {char pad[0x38];float x,y;char pad40[0x118-0x40];unsigned modelFlags;};
class Object {public:void rva0028AE6D();};
class TerrainLogic {public:
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
virtual bool isUnderwater(float,float,void*,void*,void*);
};
extern TerrainLogic *TheTerrainLogic;
class Rva001E7C4C {public:void rva001E7C4C(Object*,unsigned,float,float);private:char pad[0x44];unsigned flags;};
void Rva001E7C4C::rva001E7C4C(Object *obj,unsigned goal,float onPath,float speed){
 ((Rva001E7053*)this)->rva001E7053((int)obj,goal,onPath,speed);
 HoverObjectView *view=(HoverObjectView*)obj;
 float x=view->x,y=view->y;
 if(TheTerrainLogic->isUnderwater(x,y,0,0,0)){
  if(!((unsigned char)(flags>>5)&1)){flags|=0x20;
   if(!(view->modelFlags&0x20)){_ReadWriteBarrier();view->modelFlags|=0x20;obj->rva0028AE6D();}
  }
 }else{
  if(((unsigned char)(flags>>5)&1)){flags&=~0x20;
   if(view->modelFlags&0x20){_ReadWriteBarrier();view->modelFlags&=~0x20;obj->rva0028AE6D();}
  }
 }
}

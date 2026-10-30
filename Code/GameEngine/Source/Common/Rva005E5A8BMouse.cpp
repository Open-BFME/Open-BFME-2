// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG
// Target 5E5A8B149B / 5E5B2098B / 5E5B82117B are complete entries;
// old false-boundary notes are contradicted by their real prologues and RETs.
// Native dispatcher5E5B82 and WB15FF760 parse GameMessage3 point and1B region.
// Existing PlanRetreats OnMouseLeftClick131B is a clean source shape guide
// for the same 12-byte picker RAII and point copy. Here target accesses prove
// viewer8 contextC selector-enabled30 held38 dirty3C blocked40.
// Owned selector ctor5E5A38 and reset7B5CB9F3 plus existing checked picker
// pin5CBB4A establish the lifetime and calls. Original UI owner/method names
// remain unresolved; callback and field labels are structural descriptions.
#include "../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../Libraries/Include/Lib/IRegion2D.h"
union GameMessageArgumentType { int integer;ICoord2D point;IRegion2D region; };
class GameMessage { public: const GameMessageArgumentType*getArgument(int)const;char prefix[0x10];int type; };
class Rva0005CB9F3DwordImmSetter { public:void apply(); };
class Rva005E5A38 { public:Rva005E5A38(int);__forceinline ~Rva005E5A38(){((Rva0005CB9F3DwordImmSetter*)this)->apply();} private:unsigned storage[3]; };
class Rva00574815 { public:void rva005CBB4A(int,int,int); };
class Rva005CBB4A { public:void rva005CBB4A(void*,int,int); }; // rowed 0x005CBB4A
class Callback { public:virtual void s00();virtual void s01();virtual void s02();virtual void s03();virtual void s04(); };
struct Context { char pad[0x1c];int value; };
class Rva000AD6F4
{
public:
	void clear();
};
class Rva005E5A8B { public:int OnMouseLeftClick(const IRegion2D&,int);int OnMouseMove(const ICoord2D&,int);int handleMessage(GameMessage*); private:
 char pad[8];int viewer;Context*context;char pad10[0x20];void*enabled;char pad34[4];Callback*callback;bool dirty;char pad3d[3];int blocked;
};
int Rva005E5A8B::OnMouseLeftClick(const IRegion2D&region2D,int modifiers){
 if(region2D.hi.x-region2D.lo.x<=0 && region2D.hi.y-region2D.lo.y<=0 && enabled){
 Rva005E5A38 selector((int)this);
 ICoord2D point;point.x=region2D.lo.x;point.y=region2D.lo.y;
 ((Rva005CBB4A*)&selector)->rva005CBB4A((void*)viewer,(int)&point,context->value);
 Callback* picked=callback;
 if(picked){picked->s04();return 1;}
 }return 0;
}
int Rva005E5A8B::OnMouseMove(const ICoord2D&point,int modifiers){
 dirty=true;
 if(enabled){Rva005E5A38 selector((int)this);((Rva005CBB4A*)&selector)->rva005CBB4A((void*)viewer,(int)&point,context->value);}
 else ((Rva000AD6F4*)&callback)->clear();
 return 0;
}
int Rva005E5A8B::handleMessage(GameMessage*msg){
 if(blocked)return 0;
 switch(msg->type){
 case 3:{ICoord2D point=msg->getArgument(0)->point;return OnMouseMove(point,msg->getArgument(1)->integer);}
 case 0x1b:return OnMouseLeftClick(msg->getArgument(0)->region,msg->getArgument(1)->integer);
 default:return 0;
 }
}

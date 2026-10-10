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
struct ICoord2D { int x,y; };
struct IRegion2D { ICoord2D lo,hi; };
union GameMessageArgumentType { int integer;ICoord2D point;IRegion2D region; };
class GameMessage { public: const GameMessageArgumentType*getArgument(int)const;char prefix[0x10];int type; };
class Rva0005CB9F3DwordImmSetter { public:void apply(); };
class Rva005E5A38 { public:Rva005E5A38(int);__forceinline ~Rva005E5A38(){((Rva0005CB9F3DwordImmSetter*)this)->apply();} private:unsigned storage[3]; };
class Rva00574815 { public:void rva005CBB4A(int,int,int); };
class Callback { public:virtual void s00();virtual void s01();virtual void s02();virtual void s03();virtual void s04(); };
struct Context { char pad[0x1c];int value; };
class Rva000AD6F4 { public:void clear(); };
class Rva005E5A8B { public:int rva005E5A8B(const IRegion2D&,int);int rva005E5B20(const ICoord2D&,int);int rva005E5B82(GameMessage*); private:
 char pad[8];int viewer;Context*context;char pad10[0x20];void*enabled;char pad34[4];Callback*callback;bool dirty;char pad3d[3];int blocked;
};
int Rva005E5A8B::rva005E5A8B(const IRegion2D&r,int modifiers){
 if(r.hi.x-r.lo.x<=0 && r.hi.y-r.lo.y<=0 && enabled){
 Rva005E5A38 selector((int)this);
 ICoord2D point;point.x=r.lo.x;point.y=r.lo.y;
 ((Rva00574815*)&selector)->rva005CBB4A(viewer,(int)&point,context->value);
 Callback* picked=callback;
 if(picked){picked->s04();return 1;}
 }return 0;
}
int Rva005E5A8B::rva005E5B20(const ICoord2D&point,int modifiers){
 dirty=true;
 if(enabled){Rva005E5A38 selector((int)this);((Rva00574815*)&selector)->rva005CBB4A(viewer,(int)&point,context->value);}
 else ((Rva000AD6F4*)&callback)->clear();
 return 0;
}
int Rva005E5A8B::rva005E5B82(GameMessage*msg){
 if(blocked)return 0;
 switch(msg->type){
 case 3:{ICoord2D point=msg->getArgument(0)->point;return rva005E5B20(point,msg->getArgument(1)->integer);}
 case 0x1b:return rva005E5A8B(msg->getArgument(0)->region,msg->getArgument(1)->integer);
 default:return 0;
 }
}

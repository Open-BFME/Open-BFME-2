// cl: /O1 /G7 /MD /EHsc
// Native0042C0DB..0042C145106B cursor/position handler and
// Native0042C145..0042C1B7114B GameMessage dispatch into that handler.
// Mouse identity/current cursor4FA4 and virtual setter4C agree with the
// existing sibling42C7B1. Owner1C accepts the decoded two-word point.
// mode24==3 selects cursor2; other modes delegate34 via slot3 or the
// owned constant-minus-one RAMFile::write fold, then clamp cursor to1..55.
// The caller delegates via slot2; result1 consumes the message, type3 uses
// arguments0/1 as point/value, other types return whether type is111.
// The two five-byte forwarder definitions are whole native byte twins of
// existing owners; their concrete delegate class identity remains unknown.
// Target-derived layouts and address-derived class/method names.
struct Rva0042C083Param {int x,y;};
union GameMessageArgumentType {Rva0042C083Param position;int integer;};
class GameMessage {public:const GameMessageArgumentType*getArgument(int)const;char unknown0[0x10];int type;};
class Rva005E6817Mid {public:int fwd(GameMessage*);};
class Rva0042C083 {public:void rva0042C083(const Rva0042C083Param*);};
class RAMFile {public:virtual int write(const void*,int);};
class Mouse {public:
 virtual void m0();virtual void m1();virtual void m2();virtual void m3();virtual void m4();
 virtual void m5();virtual void m6();virtual void m7();virtual void m8();virtual void m9();
 virtual void m10();virtual void m11();virtual void m12();virtual void m13();virtual void m14();
 virtual void m15();virtual void m16();virtual void m17();virtual void m18();virtual void m19(int);
 char unknown4[0x4FA0];int cursor;
};
extern Mouse*TheMouse;
class Rva0042C0DBDelegate {public:
 virtual void slot0();virtual void slot1();virtual int slot2(GameMessage*);virtual int slot3(const Rva0042C083Param*,int);
 __declspec(noinline) int invokeMessage(GameMessage*);__declspec(noinline) int invokePoint(const Rva0042C083Param*,int);
};
int Rva0042C0DBDelegate::invokeMessage(GameMessage*m){return slot2(m);}
int Rva0042C0DBDelegate::invokePoint(const Rva0042C083Param*p,int value){return slot3(p,value);}
class Rva0042C145 {public:
 int rva0042C0DB(const Rva0042C083Param*,int);
 int rva0042C145(GameMessage*);
 char unknown0[0x1C];Rva0042C083*position;char unknown20[4];int mode;char unknown28[0xC];Rva0042C0DBDelegate*delegate;
};
int Rva0042C145::rva0042C0DB(const Rva0042C083Param*p,int value){
 if(TheMouse){
  int cursor;
  switch(mode){
   default:
    if(delegate)cursor=delegate->invokePoint(p,value);
    else cursor=((RAMFile*)((char*)this+0xC))->RAMFile::write(p,value);
    if(cursor<1||cursor>=0x38)cursor=2;
    break;
   case 3:cursor=2;break;
  }
  if(cursor!=TheMouse->cursor)TheMouse->m19(cursor);
 }
 position->rva0042C083(p);
 return 0;
}
int Rva0042C145::rva0042C145(GameMessage*m){
 if(mode!=3){
  int result;
  if(delegate)result=delegate->invokeMessage(m);
  else result=((Rva005E6817Mid*)((char*)this+0xC))->fwd(m);
  if(result==1)return result;
 }
 int type=m->type;
 if(type!=3)return type==0x6F;
 Rva0042C083Param point=m->getArgument(0)->position;
 return rva0042C0DB(&point,m->getArgument(1)->integer);
}

// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// Primary guide: BF1f989 game/GameEngine/Source/Common/
// Rva00465770MovieProperties.cpp. The same five parameter names and message
// purpose survive. Target369B WB144C980 AptMovieGameWindow::MovieInit proves
// callback ABI (unused name, query, window), last-frame string at26C rather
// than donor268, and manager slot58 rather than donor53. Native four-word
// message owns a one-pointer counted reference, not donor's raw callback.
// Existing holder23E8D8, assignment2174A4 and message destructor56D76B
// supply exact target lifetimes; _CallOnLastFrame is independently owned123B.
// A named char result, as in donor, retains native CMP AL,BL rather than TEST.
// Original class/static member spelling remains unasserted by neutral owner.
#include "ascii_string.h"
class GameWindow;
void _CallOnLastFrame(GameWindow*);
struct FunctorWrapperHead{void*vtable;unsigned refs;};
struct TargetRef00217D4C;void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
class Rva0023E8D8 {public:Rva0023E8D8():m_ptr(0){}Rva0023E8D8(void*);FunctorWrapperHead*m_ptr;};
class AptCommandMap;template<class T>class AptRef;
template<>class AptRef<AptCommandMap>:public Rva0023E8D8 {
public:
 AptRef(){}AptRef(void(__cdecl*f)(GameWindow*)):Rva0023E8D8(&f){}
 AptRef&operator=(const AptRef&);
 __forceinline ~AptRef(){if(m_ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)m_ptr);}
};
class Rva0056D76B {
public:
 Rva0056D76B():flags(0),window(0){}~Rva0056D76B();
 AsciiString movieName;unsigned flags;AptRef<AptCommandMap>callback;GameWindow*window;
};
class GameWindowManager{
public:
#define V(n) virtual void slot##n();
V(0)V(1)V(2)V(3)V(4)V(5)V(6)V(7)V(8)V(9)V(10)V(11)V(12)V(13)V(14)V(15)V(16)V(17)V(18)V(19)V(20)V(21)V(22)V(23)V(24)V(25)V(26)V(27)V(28)V(29)V(30)V(31)V(32)V(33)V(34)V(35)V(36)V(37)V(38)V(39)V(40)V(41)V(42)V(43)V(44)V(45)V(46)V(47)V(48)V(49)V(50)V(51)V(52)V(53)V(54)V(55)V(56)V(57)
#undef V
virtual int winSendSystemMsg(GameWindow*,unsigned int,unsigned int,Rva0056D76B*);
};
extern GameWindowManager*TheWindowManager;
bool Rva004128F0GetParam(const char*,const char*,AsciiString&);
void Rva0056D7A4(const char*,const char*query,GameWindow*window){
 if(!window)return;
 AsciiString param;
 Rva0056D76B msg;
 char found=Rva004128F0GetParam(query,"_MovieName",param);if(found!=0){
  msg.movieName=param.str();
  Rva004128F0GetParam(query,"_Loop",param);if(((const StringBase<char>*)&param)->find('t'))msg.flags|=4;
  Rva004128F0GetParam(query,"_UseAlpha",param);if(((const StringBase<char>*)&param)->find('t'))msg.flags|=0x40;
  Rva004128F0GetParam(query,"_HoldLastFrame",param);if(((const StringBase<char>*)&param)->find('t'))msg.flags|=0x80;
  if(Rva004128F0GetParam(query,"_CallOnLastFrame",param)){
   *(AsciiString*)((char*)window+0x26C)=param;
   msg.callback=AptRef<AptCommandMap>(_CallOnLastFrame);msg.window=window;
  }
  TheWindowManager->winSendSystemMsg(window,0x1D,1000,&msg);
 }
}

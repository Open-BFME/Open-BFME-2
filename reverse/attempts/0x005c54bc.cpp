// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAE_NPAVAnimateWindow@@@Z
// partial score=0.95 date=2026-10-10
// cl: /O1 /arch:SSE /G6 /Oy- /MD /ICode/Libraries/Include/Lib
// Reference: BF1 f98983a7d / GeneralsMD ProcessAnimateWindowSlideFromLeft.
// Target boundary 0x005C54BC..0x005C55A5; offsets and ordering are retail facts.
// Constructor 0x005C52CE installs vtable 0xC7486C and slot 4 is
// reverseAnimateWindow, which proves the target virtual method.
// Existing getVel at 0x005C5046 has an 8-byte hidden output and ret 4.
struct Coord2D;
struct RvaLeftVelocity { float x,y; };
struct ICoord2D { int x,y; };
class GameWindow { public: int winSetPosition(int,int); };
class AnimateWindow {
public:
 Coord2D getVel();
 void setVel(RvaLeftVelocity value) { m_velocity=value; }
 void *vptr; unsigned delay; ICoord2D start,end,current,rest;
 GameWindow *window; RvaLeftVelocity m_velocity;
 unsigned startTime,endTime; int animType; bool needsFinish,finished;
};
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
class ProcessAnimateWindowSlideFromLeft {
public:
 virtual ~ProcessAnimateWindowSlideFromLeft();
 virtual void initAnimateWindow(AnimateWindow*);
 virtual void initReverseAnimateWindow(AnimateWindow*,unsigned);
 virtual bool updateAnimateWindow(AnimateWindow*);
 virtual bool reverseAnimateWindow(AnimateWindow*);
 virtual void setMaxDuration(unsigned);
 RvaLeftVelocity maxVel; int slowThreshold; float slowRatio,speedRatio;
};
struct RvaLeftReverseVelocity {
 RvaLeftReverseVelocity() {}
 RvaLeftReverseVelocity(const RvaLeftReverseVelocity &v):x(v.x),y(v.y) {}
 float x,y;
};
bool ProcessAnimateWindowSlideFromLeft::reverseAnimateWindow(AnimateWindow *a)
{
 if(!a) return true;
 if(a->finished) return true;
 unsigned startTime=a->startTime;
 if(timeGetTime()<startTime) return false;
 GameWindow *win=a->window;
 if(!win) return true;
 ICoord2D cur=a->current;
 RvaLeftReverseVelocity vel;
 ICoord2D start=a->start;
 typedef void (AnimateWindow::*VelocityOutput)(RvaLeftReverseVelocity*);
 (a->*reinterpret_cast<VelocityOutput>(&AnimateWindow::getVel))(&vel);
 cur.x+=(int)vel.x;
 if(cur.x<start.x) {
  cur.x=start.x;
  a->finished=true;
  win->winSetPosition(cur.x,cur.y);
  return true;
 }
 win->winSetPosition(cur.x,cur.y);
 a->current=cur;
 start=a->end;
 float slowedX;
 if(start.x-cur.x<=slowThreshold) slowedX=speedRatio*vel.x;
 else slowedX=-maxVel.x;
 if(slowedX < -maxVel.x) slowedX=-maxVel.x;
 RvaLeftVelocity slowedVel;
 slowedVel.x=slowedX;
 slowedVel.y=vel.y;
 a->setVel(slowedVel);
 return false;
}
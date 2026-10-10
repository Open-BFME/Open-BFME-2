// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromTop@@UAE_NPAVAnimateWindow@@@Z
// partial score=0.999 date=2026-10-10
// cl: /O1 /arch:SSE /G6 /Oy- /MD /ICode/Libraries/Include/Lib
struct Coord2D;
struct RvaTopVelocity { float x,y; };
struct ICoord2D { int x,y; };
class GameWindow { public: int winSetPosition(int,int); };
class AnimateWindow {
public:
 Coord2D getVel();
 void setVel(RvaTopVelocity value) { m_velocity=value; }
 void *vptr; unsigned delay; ICoord2D start,end,current,rest;
 GameWindow *window; RvaTopVelocity m_velocity;
 unsigned startTime,endTime; int animType; bool needsFinish,finished;
};
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
class ProcessAnimateWindowSlideFromTop {
public:
 virtual ~ProcessAnimateWindowSlideFromTop();
 virtual void initAnimateWindow(AnimateWindow*);
 virtual void initReverseAnimateWindow(AnimateWindow*,unsigned);
 virtual bool updateAnimateWindow(AnimateWindow*);
 virtual bool reverseAnimateWindow(AnimateWindow*);
 virtual void setMaxDuration(unsigned);
 RvaTopVelocity maxVel; int slowThreshold; float slowRatio,speedRatio;
};
struct RvaTopReverseVelocity {
 RvaTopReverseVelocity() {}
 RvaTopReverseVelocity(const RvaTopReverseVelocity &v):x(v.x),y(v.y) {}
 float x,y;
};
bool ProcessAnimateWindowSlideFromTop::reverseAnimateWindow(AnimateWindow *a)
{
 if(!a) return true;
 if(a->finished) return true;
 unsigned startTime=a->startTime;
 if(timeGetTime()<startTime) return false;
 GameWindow *win=a->window;
 if(!win) return true;
 ICoord2D cur=a->current;
 RvaTopReverseVelocity vel;
 ICoord2D start=a->start;
 typedef void (AnimateWindow::*VelocityOutput)(RvaTopReverseVelocity*);
 (a->*reinterpret_cast<VelocityOutput>(&AnimateWindow::getVel))(&vel);
 cur.y+=(int)vel.y;
 if(cur.y<start.y) {
  cur.y=start.y;
  a->finished=true;
  win->winSetPosition(cur.x,cur.y);
  return true;
 }
 win->winSetPosition(cur.x,cur.y);
 a->current=cur;
 start=a->end;
 float slowedY;
 if(start.y-cur.y<=slowThreshold) slowedY=speedRatio*vel.y;
 else slowedY=-maxVel.y;
 if(slowedY>-maxVel.y) slowedY=-maxVel.y;
 RvaTopReverseVelocity copied(vel);
 copied.y=slowedY;
 a->setVel(*reinterpret_cast<RvaTopVelocity*>(&copied));
 return false;
}
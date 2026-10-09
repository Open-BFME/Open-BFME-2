// cl: /O1 /arch:SSE /G6 /Oy- /MD /ICode/Libraries/Include/Lib
// Reference: BF1 f98983a7d / GeneralsMD ProcessAnimateWindowSlideFromLeft.
// Target boundary 0x005C53DD..0x005C54BC; offsets and ordering are retail facts.
// Matched ctor0x005C52CE installs C7486C; slots3/4 prove Left update/reverse.
// Existing getVel at 0x005C5046 has an 8-byte hidden output and ret 4.
// Keep its struct-return declaration incomplete; use a typed output view below
// rather than inventing copy traits for the canonical Coord2D class.
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
bool ProcessAnimateWindowSlideFromLeft::updateAnimateWindow(AnimateWindow *a)
{
 if(!a) return true;
 if(a->finished) return true;
 unsigned startTime=a->startTime;
 if(timeGetTime()<startTime) return false;
 GameWindow *win=a->window;
 if(!win) return true;
 ICoord2D cur=a->current;
 union { ICoord2D position; RvaLeftVelocity velocity; } scratch;
 scratch.position.y=a->end.y;
 int endX=a->end.x;
 typedef void (AnimateWindow::*VelocityOutput)(RvaLeftVelocity*);
 (a->*reinterpret_cast<VelocityOutput>(&AnimateWindow::getVel))(&scratch.velocity);
 cur.x+=(int)scratch.velocity.x;
 if(cur.x>endX) {
  cur.x=endX;
  a->finished=true; return true;
 }
 win->winSetPosition(cur.x,cur.y);
 a->current=cur;
 float &x=scratch.velocity.x;
 if(endX-cur.x<=slowThreshold) *(volatile float *)&x=slowRatio*x;
 if(1.0f>x) *(volatile float *)&x=1.0f;
 RvaLeftVelocity outgoing;
 outgoing.x=x; outgoing.y=scratch.velocity.y;
 a->setVel(outgoing);
 return false;
}

// cl: /O1 /arch:SSE /G6 /Oy- /MD /ICode/Libraries/Include/Lib
// Reference: BF1 f98983a7d / GeneralsMD ProcessAnimateWindowSlideFromTop.
// Target boundary 0x005C6106..0x005C61EE; offsets and ordering are retail facts.
// Constructor5C55A5 and C74884 slot3 prove the target virtual method.
// Existing getVel at 0x005C5046 has an 8-byte hidden output and ret 4.
// Keep its struct-return declaration incomplete; use a typed output view below
// rather than inventing copy traits for the canonical Coord2D class.
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
bool ProcessAnimateWindowSlideFromTop::updateAnimateWindow(AnimateWindow *a)
{
 if(!a) return true;
 if(a->finished) return true;
 unsigned startTime=a->startTime;
 if(timeGetTime()<startTime) return false;
 GameWindow *win=a->window;
 if(!win) return true;
 // The endpoint scratch is dead when the helper writes its velocity result.
 union { ICoord2D position; RvaTopVelocity output; } cur;
 cur.position=a->current;
 union { ICoord2D position; RvaTopVelocity velocity; } scratch;
 scratch.position.x=a->end.x;
 int endY=a->end.y;
 typedef void (AnimateWindow::*VelocityOutput)(RvaTopVelocity*);
 (a->*reinterpret_cast<VelocityOutput>(&AnimateWindow::getVel))(&scratch.velocity);
 cur.position.y+=(int)scratch.velocity.y;
 if(cur.position.y>endY) {
  cur.position.y=endY;
  win->winSetPosition(cur.position.x,cur.position.y);
  a->finished=true; return true;
 }
 win->winSetPosition(cur.position.x,cur.position.y);
 a->current=cur.position;
 float &y=scratch.velocity.y;
 if(endY-cur.position.y<=slowThreshold) *(volatile float *)&y=slowRatio*y;
 if(1.0f>y) *(volatile float *)&y=1.0f;
 cur.output.x=scratch.velocity.x;
 cur.output.y=y;
 a->setVel(cur.output);
 return false;
}

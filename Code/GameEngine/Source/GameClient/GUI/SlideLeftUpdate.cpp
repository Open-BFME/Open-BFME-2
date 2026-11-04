// cl: /O1 /arch:SSE /G6 /Oy- /MD /ICode/Libraries/Include/Lib
#include <windows.h>
// Reference: BF1 f98983a7d / GeneralsMD ProcessAnimateWindowSlideFromLeft.
// Target boundary 0x005C53DD..0x005C54BC; offsets and ordering are retail facts.
// Matched ctor0x005C52CE installs C7486C; slots3/4 prove Left update/reverse.
// Existing getVel at 0x005C5046 has an 8-byte hidden output and ret 4.
// The typed output view below preserves the verified hidden-result call
// and stack layout.
#include "../../../../Libraries/Include/Lib/Coord2D.h"
struct RvaLeftVelocity { float x,y; };
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
class GameWindow { public: int winSetPosition(int,int); };
class AnimateWindow {
public:
 Coord2D getVel();
 void setVel(RvaLeftVelocity value) { m_velocity=value; }
 void *vptr; unsigned delay; ICoord2D start,end,current,rest;
 GameWindow *window; RvaLeftVelocity m_velocity;
 unsigned startTime,endTime; int animType; bool needsFinish,finished;
};

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
bool ProcessAnimateWindowSlideFromLeft::updateAnimateWindow(AnimateWindow *animWin)
{
 if(!animWin) return true;
 if(animWin->finished) return true;
 unsigned startTime=animWin->startTime;
 if(timeGetTime()<startTime) return false;
 GameWindow *win=animWin->window;
 if(!win) return true;
 ICoord2D cur=animWin->current;
 union { ICoord2D position; RvaLeftVelocity velocity; } scratch;
 scratch.position.y=animWin->end.y;
 int endX=animWin->end.x;
 typedef void (AnimateWindow::*VelocityOutput)(RvaLeftVelocity*);
 (animWin->*reinterpret_cast<VelocityOutput>(&AnimateWindow::getVel))(&scratch.velocity);
 cur.x+=(int)scratch.velocity.x;
 if(cur.x>endX) {
  cur.x=endX;
  animWin->finished=true; return true;
 }
 win->winSetPosition(cur.x,cur.y);
 animWin->current=cur;
 float &x=scratch.velocity.x;
 if(endX-cur.x<=slowThreshold) *(volatile float *)&x=slowRatio*x;
 if(1.0f>x) *(volatile float *)&x=1.0f;
 RvaLeftVelocity outgoing;
 outgoing.x=x; outgoing.y=scratch.velocity.y;
 animWin->setVel(outgoing);
 return false;
}

// Retail 0x005C54BC (233 B, ret 4): Left reverse, directly after the update above. X mirror of
// the TopFast reverse (SlideTopUpdate.cpp) with GeneralsMD's clamp (vel.x < -maxVel.x); closed by
// the same two equal-arm schedule levers: the finish-branch winSetPosition duplicated on curX and
// the slowed value selected as (curX ? v*speedRatio : v*speedRatio).
bool ProcessAnimateWindowSlideFromLeft::reverseAnimateWindow(AnimateWindow *animWin)
{
 if(!animWin) return true;
 if(animWin->finished) return true;
 unsigned startTime=animWin->startTime;
 if(timeGetTime()<startTime) return false;
 GameWindow *win=animWin->window;
 if(!win) return true;
 union { ICoord2D position; RvaLeftVelocity velocity; } scratch;
 ICoord2D startPos=animWin->start;
 int curX=animWin->current.x;
 int curY=animWin->current.y;
 typedef void (AnimateWindow::*VelocityOutput)(RvaLeftVelocity*);
 (animWin->*reinterpret_cast<VelocityOutput>(&AnimateWindow::getVel))(&scratch.velocity);
 curX+=(int)scratch.velocity.x;
 if(curX<startPos.x) {
  animWin->finished=true;
  if (curX) { win->winSetPosition(startPos.x,curY); } else { win->winSetPosition(startPos.x,curY); }
  return true;
 }
 win->winSetPosition(curX,curY);
 animWin->current.x=curX; animWin->current.y=curY;
 ICoord2D endPos=animWin->end;
 float slowed;
 if(endPos.x-curX<=slowThreshold)
  slowed=(curX ? (scratch.velocity.x*speedRatio) : (scratch.velocity.x*speedRatio));
 else
  slowed=-maxVel.x;
 if(slowed<-maxVel.x)
  slowed=-maxVel.x;
 RvaLeftVelocity out;
 out.x=slowed;
 out.y=scratch.velocity.y;
 animWin->setVel(out);
 return false;
}

// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// The drawer owns the background pass below (519B at 0x0010500F) and this
// text pass. Vtable 0x007CF800 independently puts background at slot 1
// and the deleting destructor at slot 5.
//
// ?rva00105216@Rva00104DB0@@QAEXH@Z retail 0x00105216..0x001052F9
// (227 bytes RET 4). The window drawer's text pass in the shape of Zero
// Hour's W3DGameWindow::drawText(Color): a pending rebuild flag (+0xD5) or
// a new colour (+0xD0) marks the text dirty; when dirty or when the
// position flag (+0xD4) is set the +0x04 Render2DSentenceClass (layout from
// the rowed dtor 0x00104DB0) is rebuilt: rowed Reset_Polys 0x00154EC0 and
// Set_Location 0x00154EF0 and pinned Draw_Sentence 0x00155B00 draw a black
// outline (TheWindowManager slot 70 winMakeColor 0 0 0 255) one pixel off
// the +0xC8/+0xCC text position and then the text in the current colour;
// the position flag is cleared. The rowed render 0x00155AD0 always runs.
// It sits between the drawer's draw slot 0x0010500F and initBorders in the
// W3DGameWindow.cpp region. Class identity is address-derived.

typedef int Int;
typedef int Color;
typedef unsigned char UnsignedByte;
class Image;

#include "../../../../../../reference/shims/wwmath/Vector2.h"

#include "../../../../../Libraries/Source/WWVegas/WW3D2/Render2DSentenceClass.h"

class GameWindowManager;
extern GameWindowManager *TheWindowManager;

class Rva00105216ManagerView
{
public:
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V10(1) V10(2) V10(3) V10(4) V10(5)
 V(60) V(61) V(62) V(63) V(64) V(65)
 virtual void winDrawImage(const Image *,Int,Int,Int,Int,Color);
 virtual void winFillRect(Color,float,Int,Int,Int,Int);
 virtual void winOpenRect(Color,float,Int,Int,Int,Int);
 V(69)
#undef V10
#undef V
	virtual Color winMakeColor(UnsignedByte red, UnsignedByte green, UnsignedByte blue, UnsignedByte alpha); // slot 70
};

class Image;
class GameWindow {
public:
 Int winGetScreenPosition(Int *,Int *);
 Int winGetSize(Int *,Int *);
 unsigned int winGetStatus();
 char unknown00[0x48];
 const Image *enabledImage; Color enabledColor,enabledBorder;
 char unknown54[0xb4-0x54];
 const Image *disabledImage; Color disabledColor,disabledBorder;
 char unknownC0[0x120-0xc0];
 const Image *hiliteImage; Color hiliteColor,hiliteBorder;
};
struct Rva0010500FDrawData {
 char unknown00[8]; unsigned int state;
 char unknown0c[0x17c-0xc]; Int imageOffsetX,imageOffsetY;
 char unknown184[0x1a4-0x184]; void *videoBuffer;
};
class Display; extern Display *TheDisplay;
class Rva0010500FDisplayView {
public:
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
 V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
 V10(1) V10(2) V10(3) V10(4) V10(5)
 V(60) V(61) V(62) V(63) V(64)
#undef V10
#undef V
 virtual void drawVideoBuffer(void *,float,float,float,float,Color);
};
#include "../../../../../Libraries/Include/Lib/ICoord2D.h"
class Rva00104DB0
{
public:
	virtual void drawBorder(GameWindow *);                       // slot 0
 virtual void rva0010500F(GameWindow *,Rva0010500FDrawData *); // slot 1
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual ~Rva00104DB0();                                    // slot 5
	void rva00105216(Color color);

private:
	Render2DSentenceClass m_textRenderer; // +0x04
	Int m_textPosX;                       // +0xC8
	Int m_textPosY;                       // +0xCC
	Color m_currTextColor;                // +0xD0
	bool m_newTextPos;                    // +0xD4
	bool m_needPolyDraw;                  // +0xD5
};


// Native 10500F..105216, RET8: slot 1 of the drawer vtable at 0x7CF800.
// ZH W3DGameWinDefaultDraw is the semantic guide. BFME2 calls the pass as a
// drawer member with window/data supplied explicitly; the receiver is unused.
// Native proves image/color triplets48/B4/120, data state08 and offsets17C/180,
// video1A4, window-manager slots66..68 and display video slot65.
void Rva00104DB0::rva0010500F(GameWindow *window,Rva0010500FDrawData *instData)
{
 float borderWidth=1.0f;
 ICoord2D origin,size;
 window->winGetScreenPosition(&origin.x,&origin.y);
 window->winGetSize(&size.x,&size.y);
 if(window->winGetStatus() & 0x80) {
  const Image *image;
  if(!(window->winGetStatus() & 8)) image=window->disabledImage;
  else if(instData->state & 2) image=window->hiliteImage;
  else image=window->enabledImage;
  if(image) {
   ICoord2D start,end;
   start.x=origin.x+instData->imageOffsetX;
   start.y=origin.y+instData->imageOffsetY;
   end.x=start.x+size.x;end.y=start.y+size.y;
   ((Rva00105216ManagerView *)TheWindowManager)->winDrawImage(image,start.x,start.y,end.x,end.y,-1);
  }
 } else {
  Color color,borderColor;
  if(!(window->winGetStatus() & 8)) {color=window->disabledColor;borderColor=window->disabledBorder;}
  else if(instData->state & 2) {color=window->hiliteColor;borderColor=window->hiliteBorder;}
  else {color=window->enabledColor;borderColor=window->enabledBorder;}
  if(borderColor!=0x00ffffff)
   ((Rva00105216ManagerView *)TheWindowManager)->winOpenRect(borderColor,borderWidth,origin.x,origin.y,origin.x+size.x,origin.y+size.y);
  if(color!=0x00ffffff)
   ((Rva00105216ManagerView *)TheWindowManager)->winFillRect(color,borderWidth,origin.x+borderWidth,origin.y+borderWidth,origin.x+size.x-borderWidth,origin.y+size.y-borderWidth);
 }
 if(instData->videoBuffer) {
  ICoord2D pos,size;
  window->winGetScreenPosition(&pos.x,&pos.y);
  window->winGetSize(&size.x,&size.y);
  ((Rva0010500FDisplayView *)TheDisplay)->drawVideoBuffer(instData->videoBuffer,pos.x,pos.y,pos.x+size.x,pos.y+size.y,-1);
 }
}

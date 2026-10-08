// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Vector2 comes from BFME1 donor9cbfb551fe20 game/WWVegas/WWMath/vector2.h.
// This reference supplies only its established8B vector operations; native
// timeline structure and formulas are independently established below.
#include "vector2.h"
// Local consuming series view: retail calls count at slot0 and float value
// at slot4. The original series and graph class names remain unknown.
class TimelineSeries {public:virtual int count()=0;virtual float value(int)=0;};
class Rva0051E354 {
public:
 Vector2 rva0051E354(TimelineSeries*,int);
 void rva0051E664(TimelineSeries*,int,class Image*);
 void rva0051E511(TimelineSeries*,float,float,unsigned long);
 float baseline()const{return y+height;}
 float x,y,width,height;int frames;float maximum;
};
// WB13DBFE0 is unnamed. Native5_1E354..5_1E3A3 whole79B returns8B Vector2
// through the hidden output pointer, RET12 for output/series/index. Native
// fields establish x/y/width/height at0/4/8/C, frames10 and maximum14. The
// baseline accessor preserves the float lifetime across the virtual call.
Vector2 Rva0051E354::rva0051E354(TimelineSeries*series,int index) {
 return Vector2(float(index+1)/float(frames)*width+x,baseline()-series->value(index)*(height/maximum));
}

class Image {public:char beforeDimensions[0x24];int width,height;};
class Rva0051E664ScaleView {
public:
 virtual void slot00()=0;virtual void slot04()=0;virtual void slot08()=0;virtual void slot0C()=0;
 virtual void slot10()=0;virtual void slot14()=0;virtual void slot18()=0;virtual void slot1C()=0;
 virtual void slot20()=0;virtual void slot24()=0;virtual void slot28()=0;virtual void slot2C()=0;
 virtual void slot30()=0;virtual void slot34()=0;virtual void slot38()=0;
 virtual const Vector2&scale()=0;
};
extern class BfmeAptWindowManager*g_bfmeAptWindowManager;
class W3DDisplay {public:void rva0004D6B3(Image*,float,float,float,float,int,int);};
extern class Display*TheDisplay;
// WB13DBCF0 AptTimeLine.cpp510 contains this unnamed image-marker body;
// its Vector2::Scale debug lead is not an original name for the function.
// Native5_1E664..5_1E716 whole178B measures Image24/28 and centers the scaled
// marker on the graph point. Apt scale slot3C and full rowed Display draw
// provider4D6B3 bind the two globals; native itself omits the WB begin/end.
void Rva0051E354::rva0051E664(TimelineSeries*series,int index,Image*image) {
 if(!image)return;
 Vector2 point=rva0051E354(series,index);
 Vector2 dimensions(float(image->width),float(image->height));
 dimensions.Scale(reinterpret_cast<Rva0051E664ScaleView*>(g_bfmeAptWindowManager)->scale());
 reinterpret_cast<W3DDisplay*>(TheDisplay)->rva0004D6B3(image,point.X-dimensions.X/2.0f,point.Y-dimensions.Y/2.0f,point.X+dimensions.X/2.0f,point.Y+dimensions.Y/2.0f,-1,2);
}

class Render2DClass {
public:unsigned shader;char beforeFlag[0x48-4];bool flag;
 void Add_Line(const Vector2&,const Vector2&,float,unsigned long);
};
class Rva0011A040Target {public:void rva0011A040();};
// Consuming Display view: native slot17C supplies the Render2D batch. All
// other slots are intentionally unnamed; the actual Display global keeps
// its established type and is cast only at this virtual interface.
class Rva0051E511DisplayView {
public:
 virtual void slot00()=0;
 virtual void slot01()=0;
 virtual void slot02()=0;
 virtual void slot03()=0;
 virtual void slot04()=0;
 virtual void slot05()=0;
 virtual void slot06()=0;
 virtual void slot07()=0;
 virtual void slot08()=0;
 virtual void slot09()=0;
 virtual void slot10()=0;
 virtual void slot11()=0;
 virtual void slot12()=0;
 virtual void slot13()=0;
 virtual void slot14()=0;
 virtual void slot15()=0;
 virtual void slot16()=0;
 virtual void slot17()=0;
 virtual void slot18()=0;
 virtual void slot19()=0;
 virtual void slot20()=0;
 virtual void slot21()=0;
 virtual void slot22()=0;
 virtual void slot23()=0;
 virtual void slot24()=0;
 virtual void slot25()=0;
 virtual void slot26()=0;
 virtual void slot27()=0;
 virtual void slot28()=0;
 virtual void slot29()=0;
 virtual void slot30()=0;
 virtual void slot31()=0;
 virtual void slot32()=0;
 virtual void slot33()=0;
 virtual void slot34()=0;
 virtual void slot35()=0;
 virtual void slot36()=0;
 virtual void slot37()=0;
 virtual void slot38()=0;
 virtual void slot39()=0;
 virtual void slot40()=0;
 virtual void slot41()=0;
 virtual void slot42()=0;
 virtual void slot43()=0;
 virtual void slot44()=0;
 virtual void slot45()=0;
 virtual void slot46()=0;
 virtual void slot47()=0;
 virtual void slot48()=0;
 virtual void slot49()=0;
 virtual void slot50()=0;
 virtual void slot51()=0;
 virtual void slot52()=0;
 virtual void slot53()=0;
 virtual void slot54()=0;
 virtual void slot55()=0;
 virtual void slot56()=0;
 virtual void slot57()=0;
 virtual void slot58()=0;
 virtual void slot59()=0;
 virtual void slot60()=0;
 virtual void slot61()=0;
 virtual void slot62()=0;
 virtual void slot63()=0;
 virtual void slot64()=0;
 virtual void slot65()=0;
 virtual void slot66()=0;
 virtual void slot67()=0;
 virtual void slot68()=0;
 virtual void slot69()=0;
 virtual void slot70()=0;
 virtual void slot71()=0;
 virtual void slot72()=0;
 virtual void slot73()=0;
 virtual void slot74()=0;
 virtual void slot75()=0;
 virtual void slot76()=0;
 virtual void slot77()=0;
 virtual void slot78()=0;
 virtual void slot79()=0;
 virtual void slot80()=0;
 virtual void slot81()=0;
 virtual void slot82()=0;
 virtual void slot83()=0;
 virtual void slot84()=0;
 virtual void slot85()=0;
 virtual void slot86()=0;
 virtual void slot87()=0;
 virtual void slot88()=0;
 virtual void slot89()=0;
 virtual void slot90()=0;
 virtual void slot91()=0;
 virtual void slot92()=0;
 virtual void slot93()=0;
 virtual void slot94()=0;
 virtual Render2DClass*renderer()=0;
};
// WB debug max selects one of two integer lvalues; a reference-returning
// maximum preserves their lifetimes and the native LEA selection.
inline const int&timelineMaximum(const int&a,const int&b){return a<b?b:a;}
// WB13DBAA0 AptTimeLine.cpp455 is unnamed; retail5_1E511..5_1E664 whole339B
// samples this same24B graph, clamps to the available series frames and
// sends lines through the established Add_Line and flush bindings. Native
// flushes after1001 pending segments, restores shader0 and clears flag48.
void Rva0051E354::rva0051E511(TimelineSeries*series,float step,float lineWidth,unsigned long color) {
 Render2DClass*render=reinterpret_cast<Rva0051E511DisplayView*>(TheDisplay)->renderer();
 if(!render)return;
 render->flag=false;
 unsigned previousShader=render->shader;
 render->shader=2;
 int pending=0;
 Vector2 previous(x-step,-1.0f);
 bool last=false;
 while(previous.X<x+width) {
  if(last)break;
  Vector2 next;
  next.X=previous.X+step;
  int frame=int((float(frames)/width)*(next.X-x));
  int zero=0;
  int index=timelineMaximum(frame,zero);
  if(index>=series->count()) {index=series->count()-1;last=true;}
  next.Y=rva0051E354(series,index).Y;
  if(previous.Y>0.0f) {
   render->Add_Line(previous,next,lineWidth,color);
   if(++pending>1000) {
    reinterpret_cast<Rva0011A040Target*>(render)->rva0011A040();
    pending=0;
   }
  }
  previous=next;
 }
 if(pending>0)reinterpret_cast<Rva0011A040Target*>(render)->rva0011A040();
 render->shader=previousShader;
}

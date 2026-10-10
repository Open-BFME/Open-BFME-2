// ?method_005C9311@Rva005C847BRecord@@QAEXHHM@Z
// partial score=0.9327098321342925 date=2026-10-10
// stlport
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
#include <vector>
extern "C" __declspec(dllimport) double __cdecl ceil(double);
struct FloatPair{FloatPair(){}FloatPair(float a,float b):x(a),y(b){}FloatPair(const FloatPair&p):x(p.x),y(p.y){}~FloatPair(){}float x,y;};
class Rva005C8176{public:void*rva005C8176(FloatPair);};
struct GridScaleView{char unknown[0x10];float scale;};
class LargeGroupAudioSoundKeyPair{public:int getGrid(int);char unknown[0x3c];GridScaleView*scale;};
struct GridRadiusView{char unknown[0x10];float radius;};
class TargetObj005C8DBF{public:void method_005C902A(float);};
struct PrereqUnitRec{union{unsigned m_data[3];float m_float[3];};~PrereqUnitRec(){}};
struct AudioCellVector:public _STL::vector<PrereqUnitRec>{using _STL::vector<PrereqUnitRec>::_M_start;using _STL::vector<PrereqUnitRec>::_M_finish;};
struct Rva005C847BRecord{float x,y;unsigned active;char unknown[0x2c];AudioCellVector entries;unsigned flags;void method_005C9311(int,int,float);};
void Rva005C847BRecord::method_005C9311(int a,int b,float weight){
 float spacing=((LargeGroupAudioSoundKeyPair*)b)->scale->scale;
 float width=((GridRadiusView*)a)->radius;
 int count=(int)(ceil((double)width/spacing)+1.1);
 FloatPair corner;corner.x=x-width*.5f;corner.y=y-width*.5f;
 for(int gridIndex=0;gridIndex<4;++gridIndex){
  Rva005C8176*grid=(Rva005C8176*)((LargeGroupAudioSoundKeyPair*)b)->getGrid(gridIndex);
  unsigned previous=entries.size();
  for(int i=0;i<count;++i){
   float px=(float)i*spacing;
   for(int j=0;j<count;++j){
    float py=(float)j*spacing;
    float offsetX=px;bool boundary=false;
    if(offsetX>width){offsetX=width;boundary=true;}
    if(py>width){py=width;boundary=true;}
    FloatPair point;point.x=corner.x+offsetX;point.y=corner.y+py;
    TargetObj005C8DBF*cell=(TargetObj005C8DBF*)grid->rva005C8176(point);
    if(cell){
     if(boundary){
      unsigned k=previous;bool found=false;
      while(!found){if(k>=entries.size())break;if(entries[k].m_data[0]==(unsigned)cell)found=true;++k;}
      if(found)continue;
     }
     {
      PrereqUnitRec record;record.m_data[0]=(unsigned)cell;record.m_data[1]=(unsigned)b;record.m_float[2]=weight;
      entries.push_back(record);
      if(active)cell->method_005C902A(weight);
     }
    }
   }
  }
 }
}

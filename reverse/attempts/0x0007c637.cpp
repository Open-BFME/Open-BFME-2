// ?Rva0007C637@@YA_NAAV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@0M@Z
// partial score=0.88 date=2026-10-09
// cl: /O1 /Og /Oi /arch:SSE /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// Native shadow map helper 0007C637..0007C8AE. WorldBuilder7EF110 embeds
// BuildCovexHull2D (sic), with point de-duplication and a stable orientation
// test after sorting the three indices. No equivalent ZH subsystem body was
// found; Vector2 subtraction, length and perp-dot source provide math semantics.
#include <vector>
#include <algorithm>
#define _OPERATOR_NEW_DEFINED_
#include "wwmath.h"
struct BfmeE8 {float X,Y;};
struct BfmePod8 {int a[2];};
class ModuleData;
namespace _STL {
template<> __declspec(noinline) void vector<BfmeE8>::push_back(const BfmeE8 &);
template<> __declspec(noinline) BfmePod8 *vector<BfmePod8>::erase(BfmePod8 *,BfmePod8 *);
template<> __declspec(noinline) void vector<const ModuleData *>::push_back(const ModuleData *const &);
template<> int *find<int *,int>(int *,int *,const int &);
}
struct Rva0007B734Item {char m_pad[8];};
typedef bool (__cdecl *Rva0007B734Pred)(const Rva0007B734Item *,const Rva0007B734Item *);
Rva0007B734Item *Rva0007B734Find(Rva0007B734Item *,Rva0007B734Item *,Rva0007B734Pred);
bool Rva0007B701Cmp(const BfmeE8 &,const BfmeE8 &);
static inline void ClearPoints(std::vector<BfmeE8> &v) {
 std::vector<BfmePod8> &p=*(std::vector<BfmePod8> *)&v;
 p.erase(p.begin(),p.end());
}
static inline void PushIndex(std::vector<int> &v,const int &i) {
 ((std::vector<const ModuleData *> *)&v)->push_back(*(const ModuleData *const *)&i);
}
static inline float PointDistance(const BfmeE8 &a,const BfmeE8 &b) {
 float x=a.X-b.X,y=a.Y-b.Y;
 float sum=x*x+y*y;
 return WWMath::Sqrt(sum);
}
static inline float Perp(const BfmeE8 &a,const BfmeE8 &b,const BfmeE8 &c) {
 float x1=b.X-a.X,y1=b.Y-a.Y;
 float x2=c.X-a.X,y2=c.Y-a.Y;
 return y1*x2-x1*y2;
}
bool Rva0007C637(std::vector<BfmeE8> &input,std::vector<BfmeE8> &output,float epsilon)
{
 ClearPoints(output);
 std::vector<BfmeE8> points;
 unsigned i;
 for(i=0;i<input.size();++i) {
  unsigned j, size=points.size();
  for(j=0;j<size;++j)
   if(PointDistance(points[j],input[i])<epsilon) break;
  if(j==size) points.push_back(input[i]);
 }
 unsigned count=points.size();
 if(count<3) return false;
 std::vector<int> hull;
 int start=(BfmeE8 *)Rva0007B734Find((Rva0007B734Item *)points.begin(),(Rva0007B734Item *)points.end(),(Rva0007B734Pred)Rva0007B701Cmp)-points.begin();
 PushIndex(hull,start);
 for(;;) {
  int current=hull.back();
  for(i=0;i<count;++i) {
   if(i==current) continue;
   unsigned j;
   for(j=0;j<count;++j) {
    if(j==i || j==current) continue;
    int a=current,b=i,c=j;
    bool flip=false;
    if(a>b){std::swap(a,b);flip=true;}
    if(b>c){std::swap(b,c);flip=!flip;}
    if(a>b){std::swap(a,b);flip=!flip;}
    float side=Perp(points[a],points[b],points[c]);
    if(flip ? side>epsilon : side<-epsilon) break;
   }
   if(j==count) break;
  }
  if(std::find(hull.begin(),hull.end(),(const int &)i)!=hull.end()) break;
  PushIndex(hull,(const int &)i);
 }
 ClearPoints(output);
 for(int *p=hull.begin();p!=hull.end();++p) output.push_back(points[*p]);
 return true;
}

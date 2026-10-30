// cl: /O1 /Og /Oi /arch:SSE /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /D_CRTIMP= /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// Native shadow map helper 0007C637..0007C8AE. WorldBuilder7EF110 embeds
// BuildCovexHull2D (sic), with point de-duplication and a stable orientation
// test after sorting the three indices. No equivalent ZH subsystem body was
// found; Vector2 subtraction, length and perp-dot source provide math semantics.
#include <vector>
#include <algorithm>
#define _OPERATOR_NEW_DEFINED_
#include "wwmath.h"
// LINK: max<unsigned> stays inline in _M_insert_overflow as in the retail
// copies; its .debug$F-only copy is suppressed with dllimport forceinline.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int const & max<unsigned int>(unsigned int const &__a, unsigned int const &__b) { return __a < __b ? __b : __a; } }
struct BfmeE8 {float X,Y; BfmeE8(){} BfmeE8(float x,float y):X(x),Y(y){}};
void Rva00030830FreeAllocation(void*);
namespace _STL {template<> inline void allocator<BfmeE8>::deallocate(BfmeE8*p,size_t)const{if(p)Rva00030830FreeAllocation(p);}template<> inline void allocator<int>::deallocate(int*p,size_t)const{if(p)Rva00030830FreeAllocation(p);}}
struct BfmePod8 {int a[2];};
class ModuleData;
namespace _STL {
template<> inline __declspec(noinline) void vector<BfmeE8>::push_back(const BfmeE8&v){if(_M_finish!=_M_end_of_storage._M_data){_Construct(_M_finish,v);++_M_finish;}else _M_insert_overflow(_M_finish,v,_IsPODType(),1UL,true);}
template<> __declspec(noinline) BfmePod8 *vector<BfmePod8>::erase(BfmePod8 *,BfmePod8 *);
template<> inline __declspec(noinline) void vector<const ModuleData *>::push_back(const ModuleData *const &v){if(_M_finish!=_M_end_of_storage._M_data){_Construct(_M_finish,v);++_M_finish;}else _M_insert_overflow(_M_finish,v,__true_type(),1UL,true);}
template<> int *find<int *,int>(int *,int *,const int &);
}
struct Rva0007B734Item {char m_pad[8];};
typedef bool (__cdecl *Rva0007B734Pred)(const Rva0007B734Item *,const Rva0007B734Item *);
Rva0007B734Item *Rva0007B734Find(Rva0007B734Item *,Rva0007B734Item *,Rva0007B734Pred);
bool Rva0007B701Cmp(const BfmeE8 &,const BfmeE8 &);
static inline void ClearPoints(std::vector<BfmeE8> &points) {
 std::vector<BfmePod8> &p=*(std::vector<BfmePod8> *)&points;
 p.erase(p.begin(),p.end());
}
static inline void PushIndex(std::vector<int> &indices,const int &i) {
 ((std::vector<const ModuleData *> *)&indices)->push_back(*(const ModuleData *const *)&i);
}
static inline float PointDistance(const BfmeE8 &from,const BfmeE8 &to) {
 float y=from.Y-to.Y,x=from.X-to.X;
 float sum=x*x+y*y;
 return WWMath::Sqrt(sum);
}
static inline BfmeE8 operator-(const BfmeE8 &a,const BfmeE8 &b) {
 return BfmeE8(a.X-b.X,a.Y-b.Y);
}
static inline float Perp_Dot_Product(const BfmeE8 &a,const BfmeE8 &b) {
 return a.X*-b.Y+a.Y*b.X;
}
__declspec(noinline) inline bool Rva0007C637(std::vector<BfmeE8> &input,std::vector<BfmeE8> &output,float epsilon)
{
 ClearPoints(output);
 std::vector<BfmeE8> points;
 {
 for(int n=0;n<input.size();++n) {
  unsigned j;
  for(j=0;j<points.size();++j)
   if(PointDistance(points[j],input[n])<epsilon) break;
  if(j==points.size()) points.push_back(input[n]);
 }
 }
 unsigned count=points.size();
 if(count<3) return false;
 std::vector<int> hull;

 PushIndex(hull,((BfmeE8 *)Rva0007B734Find((Rva0007B734Item *)points.begin(),(Rva0007B734Item *)points.end(),(Rva0007B734Pred)Rva0007B701Cmp)-points.begin()));
 for(;;) {
  int i;
  int current=hull.back();
  for(i=0;i<count;++i) {
   if(i==current) continue;
   unsigned j;
   for(j=0;j<count;++j) {
    if(j==i || j==current) continue;
    int a=current,b=i,c=j;
    bool flip=false;
    if(a>b){int t=a;a=b;b=t;flip=!flip;}
    if(b>c){int t=b;b=c;c=t;flip=!flip;}
    if(a>b){int t=a;a=b;b=t;flip=!flip;}
    BfmeE8 e1=points[b]-points[a];
    BfmeE8 e2=points[c]-points[a];
    if(flip){if(Perp_Dot_Product(e1,e2)>epsilon)break;}
    else{if(Perp_Dot_Product(e1,e2)< -epsilon)break;}
   }
   if(j==count) break;
  }
  if(std::find(hull.begin(),hull.end(),i)!=hull.end()) break;
  PushIndex(hull,(const int &)i);
 }
 ClearPoints(output);
 for(int *p=hull.begin();p!=hull.end();++p) output.push_back(points[*p]);
 return true;
}
// Select-any: W3DShadowMapManagerUpdateShadowCamera.cpp compiles an identical copy; the anchor keeps the rowed body emitted.
// ?bfmeAnchorRva0007C637 absent-from-retail
void bfmeAnchorRva0007C637(std::vector<BfmeE8> &input,std::vector<BfmeE8> &output,float epsilon) { Rva0007C637(input,output,epsilon); }

// cl: /O1 /G7 /arch:SSE /MD /EHsc /Oi
// Partial reconstruction of native RVA00312118, 2860 bytes, WB00EADCE0.
// WB exposes an inline Catmull-Rom calculation, not an imported D3DX call.
// Target +2C/+30 vector holds 184-byte records; +38 total length, +54 last position.
// Algorithm follows WB and independently decoded retail; owner/method names unknown.
// Neighbor 00312EDA uses the same vector; no application class identity asserted.
// Retail four-term polynomial and float Length2; matched helper 00311638 corroborates copy shape.
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <math.h>
// ----------------------------------------------------------------------------
// Sqrt
// ----------------------------------------------------------------------------
__forceinline float rva00312118Sqrt(float val) {
 float retval;
 __asm { fld [val] }
 __asm { fsqrt }
 __asm { fstp [retval] }
 return retval;
}
namespace {
struct Rva00312118Point {float x,y,z;};
extern "C" Rva00312118Point * __stdcall rva0062AFC8D3DXVec3CatmullRom(Rva00312118Point *,const Rva00312118Point *,const Rva00312118Point *,const Rva00312118Point *,const Rva00312118Point *,float);
struct Rva00312118Vector {
 float x,y,z;
 Rva00312118Vector() {}
 Rva00312118Vector(const Rva00312118Point &point):x(point.x),y(point.y),z(point.z){}
 Rva00312118Vector(float a,float b,float c):x(a),y(b),z(c){}
 Rva00312118Vector(const Rva00312118Vector &other):x(other.x),y(other.y),z(other.z){}
 __forceinline float length2() const { float squared=x*x; squared+=z*z; squared+=y*y; return squared; }
 __forceinline float length() const { return rva00312118Sqrt(length2()); }
};
__forceinline Rva00312118Vector operator+(const Rva00312118Vector &a,const Rva00312118Vector &b) {return Rva00312118Vector(a.x+b.x,a.y+b.y,a.z+b.z);}
__forceinline Rva00312118Vector operator-(const Rva00312118Vector &a,const Rva00312118Vector &b) {return Rva00312118Vector(a.x-b.x,a.y-b.y,a.z-b.z);}
__forceinline Rva00312118Vector operator-(const Rva00312118Vector &a) {return Rva00312118Vector(-a.x,-a.y,-a.z);}
__forceinline Rva00312118Vector operator*(const Rva00312118Vector &a,float k) {return Rva00312118Vector(a.x*k,a.y*k,a.z*k);}
__forceinline Rva00312118Vector operator*(float k,const Rva00312118Vector &a) {return Rva00312118Vector(a.x*k,a.y*k,a.z*k);}
__forceinline Rva00312118Point *rva00312118Interpolate(Rva00312118Point *out,const Rva00312118Point *pa,const Rva00312118Point *pb,const Rva00312118Point *pc,const Rva00312118Point *pd,float t,bool imported) {
 if(imported) return rva0062AFC8D3DXVec3CatmullRom(out,pa,pb,pc,pd,t);
 float tSquared=t*t;
 float tCubed=t*tSquared;
 Rva00312118Vector a=*pa,b=*pb,c=*pc,d=*pd;
 Rva00312118Vector term0=2.0f*b;
 Rva00312118Vector term1=(c-a)*t;
 Rva00312118Vector term2=(2.0f*a-5.0f*b+4.0f*c-d)*tSquared;
 Rva00312118Vector term3=(3.0f*b-a-3.0f*c+d)*tCubed;
 Rva00312118Vector v=(term0+term1+term2+term3)*0.5f;
 out->x=v.x; out->y=v.y; out->z=v.z;
 return out;
}
struct Rva00312118Record {
 float length;
 float distances[10];
 Rva00312118Point samples[10];
 Rva00312118Point position;
 unsigned trailing[2];
};
}

class Rva00312C95 {
 char prefix[0x2c];
 _STL::vector<Rva00312118Record> records;
 float total;
 char reserved[0x18];
 Rva00312118Point last;
public:
 void rva00312118();
};
void Rva00312C95::rva00312118() {
 int count=records.size()-3;
 for(int i=0;i<count;++i) {
  records[i].length=0;
  Rva00312118Point previous;
  rva00312118Interpolate(&previous,&records[i].position,&records[i+1].position,&records[i+2].position,&records[i+3].position,0.0f,false);
  for(int j=0;j<10;++j) {
   float t=(j+1)*0.1f;
   Rva00312118Point point;
   rva00312118Interpolate(&point,&records[i].position,&records[i+1].position,&records[i+2].position,&records[i+3].position,t,false);
   float distance=(Rva00312118Vector(point)-Rva00312118Vector(previous)).length();
   records[i].length+=distance;
   records[i].distances[j]=distance;
   records[i].samples[j]=point;
   previous=point;
  }
  total+=records[i].length;
 }
 last=records[records.size()-2].position;
}

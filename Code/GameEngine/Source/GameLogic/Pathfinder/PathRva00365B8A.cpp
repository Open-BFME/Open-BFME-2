// cl: /Os /arch:SSE /ICode/Libraries/Include /DNDEBUG /MD /EHsc
// Path::rva00365B8A, native 365B8A..365DF0 (614B); WB F21F60 vector arithmetic; ZH Vector3 copy,
// constructors and operations guide inline shape. This 3-float local
// adapter uses retail's rowed Coord3D::normalize ABI, preserving its layout.
#include "Lib/Coord3D.h"
#include <math.h>
inline float Coord3D::length() const {return (float)sqrt(x*x+y*y+z*z);}
inline void Coord3D::normalize(){float len=length();if(len!=0.0f){float scale=1.0f/len;x*=scale;y*=scale;z*=scale;}}
class Object;
#include "../../../Include/GameLogic/PathNode.h"
#include "../../../Include/Common/DirectionOptions.h"
struct PathWorkingCoord {
 float x,y,z;
 __forceinline PathWorkingCoord(){} __forceinline PathWorkingCoord(float a,float b,float c):x(a),y(b),z(c){}
 __forceinline PathWorkingCoord(const Coord3D &p):x(p.x),y(p.y),z(p.z){}
 __forceinline PathWorkingCoord(const PathWorkingCoord &pathWorkingCoord):x(pathWorkingCoord.x),y(pathWorkingCoord.y),z(pathWorkingCoord.z){}
 __forceinline ~PathWorkingCoord(){}
 __forceinline void scale(float s){x*=s;y*=s;z*=s;}
 __forceinline void add(const PathWorkingCoord &pathWorkingCoord){x+=pathWorkingCoord.x;y+=pathWorkingCoord.y;z+=pathWorkingCoord.z;}
 __forceinline void subtract(const Coord3D &p){x-=p.x;y-=p.y;z-=p.z;}
 __forceinline void normalize(){((Coord3D *)this)->normalize();}
 __forceinline const Coord3D *coord()const{return (const Coord3D *)this;}
};
#include "../../../Include/GameLogic/PathfindPath.h"
void Path::rva00365B8A(Object *obj,PathNode *start,PathNode *end,const Coord3D *input,float radius)
{
 PathWorkingCoord reverse(*input);reverse.scale(-1.0f);
 PathWorkingCoord direction(end->m_pos);direction.subtract(start->m_pos);direction.normalize();
 DirectionOptions options;options.flag0=false;options.flag1=false;options.value4=radius;options.flag8=true;
 float angle=3.14159265358979323846f;
 float cross=reverse.x*direction.y-direction.x*reverse.y;
 bool positive=cross>0.0f;
 PathWorkingCoord middle(reverse);middle.add(direction);middle.scale(radius*0.5f);
 PathWorkingCoord side(-direction.y-reverse.y,direction.x+reverse.x,0.0f);side.normalize();
 if(positive)side.scale(-1.0f);
 side.scale(radius*2.0f);
 PathWorkingCoord saved(end->m_pos);
 PathWorkingCoord target(start->m_pos);target.add(side);target.add(middle);
 end->m_pos=*target.coord();
 rva00365309(obj,start,reverse.coord(),&options,0xffff,angle,0);
 end->m_pos=*saved.coord();side.scale(-1.0f);
 rva00365309(obj,start,side.coord(),&options,0xffff,angle,0);
}

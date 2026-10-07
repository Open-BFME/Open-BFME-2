// ?rva002829BD@Rva002829BD@@QAEXPBVModuleData@@PAX@Z
// partial score=0.88920056 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD
struct Coord3DBase {float x,y,z;};
struct Coord3D:Coord3DBase {
 Coord3D(){} Coord3D(float a,float b,float c){x=a;y=b;z=c;}
 Coord3D(const Coord3D&v){x=v.x;y=v.y;z=v.z;}
 float length()const;void normalize();
 Coord3D operator-(const Coord3D&v)const{return Coord3D(x-v.x,y-v.y,z-v.z);}
 Coord3D operator+(const Coord3D&v)const{return Coord3D(x+v.x,y+v.y,z+v.z);}
 Coord3D operator*(float s)const{return Coord3D(x*s,y*s,z*s);}
 Coord3D operator-()const{Coord3D r;r.x=0.f-x;r.y=0.f-y;r.z=0.f-z;return r;}
};
Coord3D operator*(float s,const Coord3D&v){return Coord3D(s*v.x,s*v.y,s*v.z);}
class ModuleData;
namespace _STL {
 template<class T>class allocator{};
 template<class T,class A=allocator<T> >class vector {public:void push_back(const T&);private:T*first,*last,*cap;};
}
class Rva004DFA43 {public:bool rva004DFA43(void*,void*);};
class Rva002829BD {public:void rva002829BD(const ModuleData*,void*);private:char flag[4];float radius;Coord3D center;float padding;char unknown18[4];_STL::vector<const ModuleData*> elements;};
void Rva002829BD::rva002829BD(const ModuleData*item,void*fn){
 float extra=padding;
 void**v=(void**)&elements;
 if(v[0]==v[1]){
  radius=padding;center=*reinterpret_cast<Coord3D*(__cdecl*)(const ModuleData*)>(fn)(item);
 }else if(!((Rva004DFA43*)this)->rva004DFA43((void*)item,fn)){
  Coord3D old=center;
  Coord3D p=*reinterpret_cast<Coord3D*(__cdecl*)(const ModuleData*)>(fn)(item); Coord3D delta=old-p;
  float dist=delta.length();delta.normalize();
  Coord3D inverse=-delta;
  Coord3D edge=old+delta*radius;
  float grown=(radius+dist+extra)*0.5f;
  center=edge+grown*inverse;
  radius=grown;
 }
 elements.push_back(item);
}

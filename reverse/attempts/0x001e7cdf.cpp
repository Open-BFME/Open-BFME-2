// ?rva001E7CDF@Rva001E7CDF@@QAEXPAVObject@@@Z
// partial score=0.99 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /MD
struct Coord3D { float x,y,z; };
class Thing { public: bool isAboveTerrain() const; };
class Object;
int __cdecl Rva001E3896Check(float);
extern "C" float __cdecl atan2f(float,float);
float Cos(float); float Sin(float);
struct Rva001E3F08Arg;
class Rva001E3F08 { public: float rva001E3F08(Rva001E3F08Arg *); };
class Rva001E7C2B { public: void rva001e7c2b(unsigned,unsigned,float,float); };
class Rva001E4073 { public: float rva001E4073(Object *,float *); };
struct WingsObjectView { char gap[0x38]; Coord3D position; float angle; float getOrientation() const { return angle; } const Coord3D *getPosition() const { return &position; } };
struct WingsTemplateView { char gap[0x64]; float radius; };
class Rva001E7CDF {
public:
 void rva001E7CDF(Object *);
 void *unknown0; WingsTemplateView *parameters; Coord3D maintainPos;
 char unknown14[0x44-0x14]; unsigned flags;
};
void Rva001E7CDF::rva001E7CDF(Object *obj) {
 if(((Thing *)obj)->isAboveTerrain()) {
  flags|=0x10;
  float radius=parameters->radius;
  if(radius==0.0f) radius=((Rva001E4073 *)this)->rva001E4073(obj,0);
  WingsObjectView *object=(WingsObjectView *)obj;
  float dx=maintainPos.x-object->getPosition()->x;
  float dy=maintainPos.y-object->getPosition()->y;
  float angle=((unsigned char)Rva001E3896Check(dx) && (unsigned char)Rva001E3896Check(dy)) ? object->getOrientation() : atan2f(dy,dx);
  float aimDir=(3.14159265358979323846f-3.14159265358979323846f/8);
  if(radius<0) { radius=-radius;aimDir=-aimDir; }
  angle+=aimDir;
  Coord3D desired; desired.x=maintainPos.x; desired.y=maintainPos.y; desired.z=maintainPos.z;
  desired.x+=Cos(angle)*radius;
  desired.y+=Sin(angle)*radius;
  ((Rva001E7C2B *)this)->rva001e7c2b((unsigned)obj,(unsigned)&desired,0,((Rva001E3F08 *)this)->rva001E3F08((Rva001E3F08Arg *)obj));
 }
}


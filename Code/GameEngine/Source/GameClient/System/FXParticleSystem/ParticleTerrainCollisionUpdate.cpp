// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /ICode/Libraries/Include /Ireference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
#include "Lib/Coord3D.h"
#include "matrix3d.h"
float __cdecl atan2f(float,float);
class FXList {public:static void doFXPos(const FXList*,const Coord3D*,const Matrix3D*,float,const Coord3D*);};
class CollisionTerrainView {public:virtual void f0();virtual void f1();virtual void f2();virtual void f3();virtual void f4();virtual void f5();virtual float height(float,float,void*);};
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
struct CollisionParticleView {char unknown[0x10];Coord3D velocity;Coord3D position;char unknown28[0x2C];unsigned lifetime;};
class Rva00564743 {public:void rva00564743();char unknown00[4];CollisionParticleView*particle;char unknown08[4];bool kill;char unknown0D[7];float height;const FXList*fx;bool rotate;char unknown1D[3];bool active;};
// Target564743..5648FE: one-shot ground collision FX and optional lifetime=1.
// ZH Matrix3D identity/Rotate_Z source supplies the rotation implementation;
// target supplies particle +4, flags C/1C/20, height14 and FX18.
void Rva00564743::rva00564743(){
 if(!active||!fx)return;
 if(!(particle->position.z<=((CollisionTerrainView*)TheTerrainLogic)->height(particle->position.x,particle->position.y,0)))return;
 Matrix3D matrix(true);
 if(rotate)matrix.Rotate_Z(atan2f(particle->velocity.y,particle->velocity.x));
 const Coord3D *source=&particle->position;
 Coord3D position;position.x=source->x;position.y=source->y;position.z=source->z+height;
 FXList::doFXPos(fx,&position,&matrix,0.0f,0);
 active=false;
 if(kill)particle->lifetime=1;
}

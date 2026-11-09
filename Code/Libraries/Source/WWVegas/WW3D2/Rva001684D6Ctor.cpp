// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2renderobj /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
#define BFME_RO_DTOR_DECL_ONLY
#include "rendobj.h"
#include "simplevec.h"
// bfme link decl-only begin
template <> SimpleDynVecClass<Vector3>::~SimpleDynVecClass();
template <> bool SimpleVecClass<Vector3>::Resize(int);
template <> bool SimpleVecClass<Vector3>::Uninitialised_Grow(int);
// bfme link decl-only end
// Native16844F..1684B2 constructs the RenderObj C4 base; points C4;
// float widths D4; renderer settings E4. The same primary/secondary tables
// BD41C8/BD41C4 are independently owned by deleting dtor1684BA and Clone1686EB.
// Set_Points168605 is independently named SimpleStreakLineClass by WB A1A980;
// preserve the existing RVA class owner until its other providers reconcile.
class Rva001683A7 {public:Rva001683A7(int n=0);__forceinline ~Rva001683A7(){((SimpleDynVecClass<float>*)this)->~SimpleDynVecClass<float>();}private:char storage[16];};
class Rva00126314 {public: Rva00126314();~Rva00126314();private:char storage[36];};
class Rva001684D6:public RenderObjClass {
public: Rva001684D6();virtual ~Rva001684D6();virtual Rva001684D6 *Clone() const;virtual void Render(RenderInfoClass&);
// Retail's table 0x00BD41C8.
virtual int Class_ID(void) const;virtual int Get_Num_Polys(void) const;virtual bool Cast_Ray(RayCollisionTestClass&);virtual void Get_Obj_Space_Bounding_Sphere(SphereClass&) const;virtual void Get_Obj_Space_Bounding_Box(AABoxClass&) const;virtual void Prepare_LOD(CameraClass&);virtual float Get_Cost(void) const;virtual int Get_LOD_Count(void) const;
private: SimpleDynVecClass<Vector3> points;Rva001683A7 widths;Rva00126314 renderer;
};
Rva001684D6::Rva001684D6():points(0),widths(0){}

// Target facts for the slots below, retail's table 0x00BD41C8. Slot 3 returns 0x1C. Slot 72 is empty. Slot 76 is the polygon
// count (slot 10) as a float. Slot 81 returns 0. Each body folds with another class's, so these are ICF rows.
int Rva001684D6::Class_ID(void) const { return 0x1C; }
void Rva001684D6::Prepare_LOD(CameraClass&) {}
float Rva001684D6::Get_Cost(void) const { return (float)Get_Num_Polys(); }
int Rva001684D6::Get_LOD_Count(void) const { return 0; }

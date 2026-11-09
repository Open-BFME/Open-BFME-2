// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2renderobj /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Native168527..16859E copies point storageC4 and widthsD4 after a fresh
// RenderObj default construction, then copies the renderer at E4.
// Point storage is SimpleDynVecClass<Vector3>: its copy ctor 0x0015E640
// installs the SimpleVecClass<Vector3>/SimpleDynVecClass<Vector3> vtables
// 0x007C6F44/0x007C6F50.
// This16B view follows the native helper's complete pointer/count stores;
// field use is independently established by WB-named Set_Points168605.
// Primitive copies are nonthrowing; only renderer construction needs state2.
#define BFME_RO_DTOR_DECL_ONLY
#include "rendobj.h"
template<class T>class SimpleVecClass{public:SimpleVecClass(int);SimpleVecClass(const SimpleVecClass&) throw();virtual ~SimpleVecClass() throw();virtual bool Resize(int);virtual bool Uninitialised_Grow(int);protected:T*Vector;int VectorMax;};
template<class T>class SimpleDynVecClass:public SimpleVecClass<T>{public:SimpleDynVecClass(int=0);SimpleDynVecClass(const SimpleDynVecClass&) throw();virtual ~SimpleDynVecClass() throw();virtual bool Resize(int);protected:int ActiveCount;};
class Rva00126350 {public:Rva00126350(const Rva00126350&);};
class TextureClass;
template<class T>class RefCountPtr{public:~RefCountPtr();private:T*ptr;};
class Rva00126314 {public:Rva00126314();__forceinline Rva00126314(const Rva00126314&r){((Rva00126350*)this)->Rva00126350::Rva00126350((const Rva00126350&)r);}__forceinline ~Rva00126314(){((RefCountPtr<TextureClass>*)this)->~RefCountPtr<TextureClass>();}private:char storage[36];};
class Rva001684D6:public RenderObjClass {
public: Rva001684D6();Rva001684D6(const Rva001684D6&);virtual ~Rva001684D6();virtual Rva001684D6 *Clone() const;virtual void Render(RenderInfoClass&);
// Retail's table 0x00BD41C8.
virtual int Class_ID(void) const;virtual int Get_Num_Polys(void) const;virtual bool Cast_Ray(RayCollisionTestClass&);virtual void Get_Obj_Space_Bounding_Sphere(SphereClass&) const;virtual void Get_Obj_Space_Bounding_Box(AABoxClass&) const;virtual void Prepare_LOD(CameraClass&);virtual float Get_Cost(void) const;virtual int Get_LOD_Count(void) const;
private: SimpleDynVecClass<Vector3> points;SimpleDynVecClass<float> widths;Rva00126314 renderer;
};




Rva001684D6::Rva001684D6(const Rva001684D6&r):points(r.points),widths(r.widths),renderer(r.renderer){}

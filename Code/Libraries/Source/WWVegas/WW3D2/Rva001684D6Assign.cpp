// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2renderobj /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Native16859E..168605 is the complete assignment body (RET4). It first
// assigns RenderObjClass then skips member copies on self assignment.
// Point and width storage have three non-vptr words at C4 and D4; renderer
// E4 delegates the independently verified 73-byte assignment126350.
// Point helper identity remains RVA-derived: the canonical Vector3 copy
// owns different vtable relocations. No new callee pins are introduced.
#include "rendobj.h"
template<class T>class SimpleVecClass{public:SimpleVecClass(int);SimpleVecClass(const SimpleVecClass&) throw();virtual ~SimpleVecClass() throw();virtual bool Resize(int);virtual bool Uninitialised_Grow(int);protected:T*Vector;int VectorMax;};
template<class T>class SimpleDynVecClass:public SimpleVecClass<T>{public:SimpleDynVecClass(int=0);SimpleDynVecClass(const SimpleDynVecClass&) throw();virtual ~SimpleDynVecClass() throw();virtual bool Resize(int);protected:int ActiveCount;};
class Rva0015E640{
public:
 __forceinline Rva0015E640(int n=0){((SimpleDynVecClass<Vector3>*)this)->SimpleDynVecClass<Vector3>::SimpleDynVecClass(n);}
 Rva0015E640(const Rva0015E640&) throw();
 __forceinline ~Rva0015E640()throw(){((SimpleDynVecClass<Vector3>*)this)->SimpleDynVecClass<Vector3>::~SimpleDynVecClass<Vector3>();}
__forceinline Rva0015E640&operator=(const Rva0015E640&r){vector=r.vector;capacity=r.capacity;active=r.active;return *this;}
private:void*vt;void*vector;int capacity,active;
};
class Rva00126350 {public:Rva00126350(const Rva00126350&);Rva00126350&operator=(const Rva00126350&);};
class TextureClass;
template<class T>class RefCountPtr{public:~RefCountPtr();private:T*ptr;};
class Rva00126314 {public:Rva00126314();__forceinline Rva00126314&operator=(const Rva00126314&r){*((Rva00126350*)this)=(const Rva00126350&)r;return *this;}__forceinline Rva00126314(const Rva00126314&r){((Rva00126350*)this)->Rva00126350::Rva00126350((const Rva00126350&)r);}__forceinline ~Rva00126314(){((RefCountPtr<TextureClass>*)this)->~RefCountPtr<TextureClass>();}private:char storage[36];};
class Rva001684D6:public RenderObjClass {
public: Rva001684D6();Rva001684D6&operator=(const Rva001684D6&);Rva001684D6(const Rva001684D6&);virtual ~Rva001684D6();virtual Rva001684D6 *Clone() const;virtual void Render(RenderInfoClass&);
private: Rva0015E640 points;SimpleDynVecClass<float> widths;Rva00126314 renderer;
};




Rva001684D6&Rva001684D6::operator=(const Rva001684D6&r){RenderObjClass::operator=(r);if(this!=&r){points=r.points;widths=r.widths;renderer=r.renderer;}return *this;}

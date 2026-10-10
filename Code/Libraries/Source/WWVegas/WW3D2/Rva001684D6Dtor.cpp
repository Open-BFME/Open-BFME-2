// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2renderobj /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
#include "rendobj.h"
template<class T>class SimpleDynVecClass{public:virtual ~SimpleDynVecClass() throw();private:char storage[12];};
// Native1684D6..168527 destroys settingsE4 then widthsD4 then pointsC4
// and finally the RenderObj C4 base. The target omits derived vptr stores,
// as in the already matched StreakLineDestructor.cpp; novtable preserves that.
// Primitive vector cleanup cannot throw; texture release retains EH state2.
// Native16844F..1684B2 constructs the RenderObj C4 base; points C4;
// float widths D4; renderer settings E4. The same primary/secondary tables
// BD41C8/BD41C4 are independently owned by deleting dtor1684BA and Clone1686EB.
// Set_Points168605 is independently named SimpleStreakLineClass by WB A1A980;
// preserve the existing RVA class owner until its other providers reconcile.
class Rva001683A7 {public:Rva001683A7(int n=0);__forceinline ~Rva001683A7() throw(){((SimpleDynVecClass<float>*)this)->SimpleDynVecClass<float>::~SimpleDynVecClass<float>();}private:char storage[16];};
class TextureClass;
template<class T>class RefCountPtr{public:~RefCountPtr();private:T*ptr;};
class Rva00126314 {public:Rva00126314();__forceinline ~Rva00126314(){((RefCountPtr<TextureClass>*)this)->~RefCountPtr<TextureClass>();}private:char storage[36];};
class __declspec(novtable) Rva001684D6:public RenderObjClass {
public: Rva001684D6();virtual ~Rva001684D6();virtual Rva001684D6 *Clone() const;virtual void Render(RenderInfoClass&);
private: SimpleDynVecClass<Vector3> points;Rva001683A7 widths;Rva00126314 renderer;
};


Rva001684D6::~Rva001684D6(){}

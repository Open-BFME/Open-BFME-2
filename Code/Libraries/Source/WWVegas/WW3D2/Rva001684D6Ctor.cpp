// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2renderobj /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
#include "rendobj.h"
#include "simplevec.h"
// Native16844F..1684B2 constructs the RenderObj C4 base; points C4;
// float widths D4; renderer settings E4. The same primary/secondary tables
// BD41C8/BD41C4 are independently owned by deleting dtor1684BA and Clone1686EB.
// Set_Points168605 is independently named SimpleStreakLineClass by WB A1A980;
// preserve the existing RVA class owner until its other providers reconcile.
class Rva001683A7 {public:Rva001683A7(int n=0);__forceinline ~Rva001683A7(){((SimpleDynVecClass<float>*)this)->~SimpleDynVecClass<float>();}private:char storage[16];};
class Rva00126314 {public: Rva00126314();~Rva00126314();private:char storage[36];};
class Rva001684D6:public RenderObjClass {
public: Rva001684D6();virtual ~Rva001684D6();virtual Rva001684D6 *Clone() const;virtual void Render(RenderInfoClass&);
private: SimpleDynVecClass<Vector3> points;Rva001683A7 widths;Rva00126314 renderer;
};
Rva001684D6::Rva001684D6():points(0),widths(0){}

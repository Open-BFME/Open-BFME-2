// ?rva005D0F95@Rva005D0F95@@QAEXXZ
// partial score=0.98 date=2026-10-10
// ?rva005D0F95@Rva005D0F95@@QAEXXZ
// partial score=0.98 date=2026-10-10
// cl: /O1 /G5 /MD /EHsc
class Object;
class Rva00575674 {public:void rva00575674(Object*);};
class Rva005CFEDF {public:Rva005CFEDF(void*);char bytes[12];};
class Rva005D073A {public:Rva005D073A(void*);char bytes[12];};
struct Rva005D0F95Owner {char unknown[0x1C];Rva00575674 state;};
class Rva005D0F95 {public:void rva005D0F95();char unknown[8];bool mode;
 __forceinline Rva005D0F95Owner*owner(){return *(Rva005D0F95Owner**)((char*)this-8);}
};
void Rva005D0F95::rva005D0F95(){
 Object*state;
 if(mode)state=(Object*)new Rva005CFEDF(owner());
 else state=(Object*)new Rva005D073A(owner());
 Rva00575674 *holder=&owner()->state;
 holder->rva00575674(state);
}

// ?rva003FA835@Rva003FA835@@QAE?AUBfmeEventPositionView@@XZ
// partial score=0.9051573263824241 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
// Native3FA835..3FA878 RET4, the whole67B value-returning worker.
// The audio caller2DA1CC already pins this signature and shared12B value.
// Target reads receiver+10 then child+8; virtual slot20 precedes reading
// the three transform translations at24/34/44. Internal type names infer
// storage roles; the original receiver and slot20 spelling are unknown.
#include "Common/BfmeAudioEventPrefix136.h"
class Rva003FA835Model {
public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual void s19();virtual void refresh();
 char pad4[0x20];float x;char pad28[0xc];float y;char pad38[0xc];float z;
};
struct Rva003FA835Details {char pad0[8];Rva003FA835Model*model;};
class Rva003FA835 {
public: BfmeEventPositionView rva003FA835();
private:char pad0[0x10];Rva003FA835Details*details;
};
BfmeEventPositionView Rva003FA835::rva003FA835() {
 Rva003FA835Model*model=details->model;
 float z=0.0f,y=0.0f,x=0.0f;
 if(model){model->refresh();x=model->x;y=model->y;z=model->z;}
 return BfmeEventPositionView(x,y,z);
}

// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Native2D3C5F..2D3CA5 and WB F40800 independently prove reset order.
// The complete outer state type and field meanings remain unknown.
void __cdecl operator delete(void *);
extern "C" void __cdecl _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
class Rva002D3C5F
{
public:
 void reset();
private:
 int at00, at04; bool at08; char at09[3];
 int at0C, at10, at14; float at18; int at1C;
 void *at20, *at24;
};
void Rva002D3C5F::reset()
{
 volatile Rva002D3C5F *prefix = this;
 prefix->at08 = false;
 prefix->at0C = -2; prefix->at10 = -2; prefix->at14 = -2;
 prefix->at18 = 0.0f;
 void *first = prefix->at20; at20 = 0;
 if (first) operator delete(first);
 void *second = at24; at24 = 0;
 operator delete(second);
 _ReadWriteBarrier();
 prefix->at00 = 0; prefix->at04 = 0; prefix->at1C = 0;
}

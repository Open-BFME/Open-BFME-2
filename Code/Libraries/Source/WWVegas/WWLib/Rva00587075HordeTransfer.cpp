// ?rva00587075@HordeMeleeFormation@@UAEXPAVXfer@@@Z
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Native00587075..00587204,399B, is vtable00C6FD90 slot15. The
// checked HordeMeleeFormation type name, reciprocal save/load paths and
// constructor/vtable neighbours prove the class and snapshot-transfer purpose.
// Exact method spelling is not established by WB; retain the address name.
// Record84 constructor00585ADA and assignment00586BC9 establish the field
// offsets below independently. These existing providers use different type
// names: casts project their identical84B storage views, not a claim of native
// inheritance or a new alias. Deque storage starts at+28; its scalar cleanup
// is005858F3, and native calls the existing deque transfer00586231 there.
// Formation layout: held+4, vector+8, flag+14, other+18 (ctor00586D8E).
// Xfer view records only observed virtual slot ABI; no Xfer vtable is emitted.
// WB1474C40 is an unnamed string-matched transfer lead, not recovered source.
// Semantic guide: existing clean record/vector/deque providers and native
// save/load/version/type guard. Complete399B and all relocations verified.
#include <deque>
#include <vector>
#include "ascii_string.h"
struct BfmeE12 { float x,y,z; };
struct OpaqueTriple12 { int a,b,c; };
struct Gen_t_00595870_p12cd {int a,b,c;};
struct BfmeAssignRecord84 {
 int state; BfmeE12 position; OpaqueTriple12 unknown10; bool flag; char pad[3]; int a,b;
 _STL::deque<BfmeE12> path; int tail;
 BfmeAssignRecord84 &operator=(const BfmeAssignRecord84 &);
};
class Rva00585B16 {
public:
 Rva00585B16();
 ~Rva00585B16() {}
 int state; BfmeE12 position; OpaqueTriple12 unknown10; bool flag; char pad[3]; int a,b;
 _STL::deque<BfmeE12> path; int tail;
};
struct XferVersion { unsigned char current,minimum; XferVersion(unsigned char a,unsigned char b):current(a),minimum(b){} };
class Xfer {
public:
 virtual ~Xfer(); virtual bool isLoading(); virtual bool isSaving();
 virtual void slot3(); virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
 virtual Xfer &xferVersion(XferVersion &);
 virtual void slot11();virtual void slot12();virtual void slot13();virtual void slot14();virtual void slot15();virtual void slot16();virtual void slot17();virtual void slot18();virtual void slot19();virtual void slot20();virtual void slot21();virtual void slot22();virtual void slot23();
 virtual Xfer &xferFloat3(BfmeE12 &);
 virtual void slot25();virtual void slot26();
 virtual void xferAsciiString(AsciiString *);
 virtual void slot28();virtual void slot29();virtual void slot30();
 virtual Xfer &xferInt(int &);
 virtual void slot32();virtual void slot33();virtual void slot34();virtual void slot35();
 virtual Xfer &xferBoolean(bool &);
};
Xfer *Rva00586231Xfer(Xfer *,_STL::deque<Gen_t_00595870_p12cd> *);
struct XferException {char *text;int tag;};
extern "C" XferException *__cdecl bfmeFormatText(XferException *,int,const char *,...);
struct _s__ThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *,const _s__ThrowInfo *);
extern int g_guardTargetTypeThrowInfo;
template<class T> struct Rva00584A7DVector {
 T *start,*finish,*limit;
 int size() const {return finish-start;}
 void grow(unsigned int);
};
struct Rva00587057Entry {char storage[0x54];};
class HordeMeleeFormation {
public:
 virtual ~HordeMeleeFormation();
 void *held;
 _STL::vector<BfmeAssignRecord84> entries;
 bool flag;char pad[3];void *other;
 // Slot 15 of the vftable 0x00C6FD90 that the ctor installs: virtual.
 virtual void rva00587075(Xfer *);
};
void HordeMeleeFormation::rva00587075(Xfer *xfer) {
 XferVersion version(1,1); xfer->xferVersion(version);
 AsciiString expected("HordeMeleeFormation");
 AsciiString actual(expected);
 xfer->xferAsciiString(&actual);
 if(actual.compare(expected)!=0) {
  XferException error;
  bfmeFormatText(&error,4,"Xfer data saved by %s is now being loaded by %s",actual.str(),expected.str());
  _CxxThrowException(&error,(const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
  __assume(0);
 }
 xfer->xferBoolean(flag);
 int count=entries.size();
 xfer->xferInt(count);
 if(xfer->isLoading()) ((Rva00584A7DVector<Rva00587057Entry> *)&entries)->grow(count);
 for(int i=0;i<count;++i) {
  Rva00585B16 value;
  if(!xfer->isLoading())
   ((BfmeAssignRecord84 *)&value)->operator=(entries[i]);
  xfer->xferFloat3(value.position);
  xfer->xferBoolean(value.flag);
  if(xfer->isLoading())
   entries[i].operator=(*(BfmeAssignRecord84 *)&value);
  Rva00586231Xfer(xfer,(_STL::deque<Gen_t_00595870_p12cd> *)&value.path);
 }
}

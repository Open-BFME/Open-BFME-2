// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Native318F42..318F64: the vector-like view returned twice by318B83
// must exist and have a nonzero unsigned16-byte record count. Original
// application names remain unknown; WB131AA30 order drain corroborates uses.
// The neutral getter ABI is a complete17B byte/relocation twin of the
// existing getWheelInfo row; that donor name is not asserted for this view.
struct Rva00318F42Record { unsigned char bytes[16]; };
struct Rva00318F42View { Rva00318F42Record *first,*finish,*end; };
struct Rva00318F42Holder { unsigned char pad[0x3C]; Rva00318F42View view; };

struct Rva00538CEFPair {int a,b;};
class Rva00538CEF {public:void rva00538DC1(const Rva00538CEFPair *,int);bool rva00538D17(Rva00538CEFPair *);};
class Rva003195C9Owner {public:void rva003195C9();};
class Rva003197EEListener {public:virtual void notify(void *);virtual void slot04(void *);virtual void slot08(void *);virtual void slot0c(void *);virtual void slot10(void *);};
class Rva003197EEList {public:void forEach(void (Rva003197EEListener::*)(void *),void *);};
class Rva00318F42 {
public:
 __declspec(noinline) Rva00318F42View *rva00318B83() const;
 bool rva00318F42();
 void rva0031986B(const Rva00538CEFPair *,int);
private:
 unsigned char pad[0x88];
 Rva00318F42Holder *holder;
};
Rva00318F42View *Rva00318F42::rva00318B83() const {
 return holder ? &holder->view : 0;
}
bool Rva00318F42::rva00318F42() {
 if(rva00318B83()) { Rva00318F42View *v=rva00318B83(); return (unsigned int)(v->finish-v->first)>0; }
 return false;
}

// Native31986B..3198B8,77B; WB102B1B0 independently preserves the
// getter and unsigned16-byte count, two-word update/copy and listener walk.
// This view preserves the original owner/type uncertainty. The pushed
// compiler vcall thunk is the existing5B slot10 provider at5CB26A;
// listener slot declarations describe only the witnessed dispatch offsets.
void Rva00318F42::rva0031986B(const Rva00538CEFPair *pair,int word){
 Rva00318F42View *v=rva00318B83();
 if(v){int *span=(int*)v;if((unsigned)((span[1]-span[0])>>4)>0){
  ((Rva00538CEF*)v)->rva00538DC1(pair,word);
  ((Rva00538CEF*)v)->rva00538D17((Rva00538CEFPair*)((char*)this+0x3c));
  ((Rva003195C9Owner*)this)->rva003195C9();
  ((Rva003197EEList*)((char*)this+8))->forEach(&Rva003197EEListener::slot10,this);
 }}
}

// Native3190BB..3190E7,44B; WB102C7B0 preserves an output-only
// pair copy: use the last record when present else receiver words44/48.
// The old unowned Boolean pin was unsupported: its fallback leaves AL
// unconstrained and the owned71B caller discards the register result.
// This declaration makes no register-return contract or original type claim.
class Rva003190BBOwner {public:void rva003190BB(int *);};
void Rva003190BBOwner::rva003190BB(int *out){
 Rva00318F42View *v=((Rva00318F42*)this)->rva00318B83();
 if(v){int *span=(int*)v;if((unsigned)((span[1]-span[0])>>4)>0){
  ((Rva00538CEF*)v)->rva00538D17((Rva00538CEFPair*)out);return;
 }}
 out[0]=*(int*)((char*)this+0x44);out[1]=*(int*)((char*)this+0x48);
}

#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
class Xfer;
struct BfmeVectorRecord00319C84 { unsigned int words[4]; };
struct Elem003AF9E0 { unsigned int words[4]; };
namespace _STL {
template<> vector<BfmeVectorRecord00319C84> &vector<BfmeVectorRecord00319C84>::operator=(const vector<BfmeVectorRecord00319C84> &);
template<> vector<Elem003AF9E0>::iterator vector<Elem003AF9E0>::erase(iterator, iterator);
}
void Rva0031A160Xfer(Xfer *xfer, _STL::vector<BfmeVectorRecord00319C84> *records);
struct Rva0031A6DBStatus {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual bool s11();
};
class Xfer {
public:
    struct Version { unsigned char current, minimum; Version(unsigned char a,unsigned char b):current(a),minimum(b){} };
    virtual void slot00();
    virtual bool IsLoading() const;
    virtual bool IsStoring() const;
    virtual bool IsCRC() const;
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual Xfer &XferRawBytes(void *, unsigned int);
    virtual Xfer &xferVersion(Version &);
    virtual void slot11();
    virtual Xfer &xferSnapshot(void *);
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual Xfer &xferCoord2D(void *);
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual Xfer &xferUnicodeString(UnicodeString &);
    virtual Xfer &xferAsciiString(AsciiString &);
    virtual Xfer &xferReal(float &);
    virtual void slot29();
    virtual void slot30();
    virtual Xfer &xferInt(int &);
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual Xfer &xferBool(bool &);
};

class LivingWorldArmy {
public:
    virtual void xfer(Xfer *xfer);
    char pad04[0x18 - 0x04];
    AsciiString name18;
    AsciiString name1C;
    int owner20;
    AsciiString name24;
    AsciiString name28;
    int region2C;
    int value30;
    unsigned int pos34[2];
    unsigned int pos3C[2];
    unsigned int pos44[2];
    int source4C;
    char pad50[4];
    int owner54;
    bool flag58;
    bool flag59;
    char pad5A[2];
    float value5C;
    unsigned int audio60;
    char pad64;
    bool flag65;
    char pad66[2];
    UnicodeString text68;
    UnicodeString text6C;
    int iconSize70;
    bool flag74;
    bool flag75;
    char pad76[2];
    void *summary78;
    _STL::vector<BfmeVectorRecord00319C84> records7C;
    Rva0031A6DBStatus *status88;
    int value8C;
};

// LivingWorldArmy::xfer, native 0031A6DB..0031A8DD RET4: the vtable slot
// after the "LivingWorldArmy" name getter 00319E76 (00C0C838). Version 6;
// fields are transferred in retail order. Records come from the rowed
// 00318B83 view unless loading (else cleared through the rowed 16-byte
// erase), and are transferred by the unrowed 0031A160 unless CRC. TheAudio
// slot 88 transfers the +60 handle. Before version 6 the icon size and the
// two texts are reset; on load the +8C word is cleared. It lives here
// because retail calls the getter twice without reloading ECX, which
// MSVC 7.1 only does when the getter's body is visible in the unit.
class AudioManager;
extern AudioManager *TheAudio;
struct Rva0031A6DBAudio {
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual void s48();
    virtual void s49();
    virtual void s50();
    virtual void s51();
    virtual void s52();
    virtual void s53();
    virtual void s54();
    virtual void s55();
    virtual void s56();
    virtual void s57();
    virtual void s58();
    virtual void s59();
    virtual void s60();
    virtual void s61();
    virtual void s62();
    virtual void s63();
    virtual void s64();
    virtual void s65();
    virtual void s66();
    virtual void s67();
    virtual void s68();
    virtual void s69();
    virtual void s70();
    virtual void s71();
    virtual void s72();
    virtual void s73();
    virtual void s74();
    virtual void s75();
    virtual void s76();
    virtual void s77();
    virtual void s78();
    virtual void s79();
    virtual void s80();
    virtual void s81();
    virtual void s82();
    virtual void s83();
    virtual void s84();
    virtual void s85();
    virtual void s86();
    virtual void s87();
    virtual void xferHandle(Xfer *xfer, unsigned int *handle);
};
struct Rva003EFE82Obj;
int Rva003EFE82Get(Rva003EFE82Obj *xfer, void *value);
void XferLivingWorldArmyID(Xfer *xfer, int *value);
void XferArmyIconSize(Xfer *xfer, int *value);

void LivingWorldArmy::xfer(Xfer *xfer)
{
    Xfer::Version version(1, 6);
    xfer->xferVersion(version);
    XferLivingWorldArmyID(xfer, &owner20);
    xfer->xferAsciiString(name24);
    xfer->xferCoord2D(pos44);
    xfer->xferCoord2D(pos34);
    Rva003EFE82Get((Rva003EFE82Obj *)xfer, &region2C);
    xfer->xferInt(value30);
    xfer->xferCoord2D(pos3C);
    xfer->xferBool(flag59);
    xfer->xferReal(value5C);
    xfer->xferBool(flag74);
    xfer->xferAsciiString(name18);
    if (version.minimum >= 2)
        xfer->xferBool(flag75);
    if (version.minimum >= 3)
        xfer->xferAsciiString(name1C);
    if (version.minimum >= 4)
        xfer->xferBool(flag58);
    xfer->XferRawBytes(&owner54, 4);
    if (!xfer->IsLoading() && ((const Rva00318F42 *)this)->rva00318B83())
        records7C = *(const _STL::vector<BfmeVectorRecord00319C84> *)((const Rva00318F42 *)this)->rva00318B83();
    else {
        _STL::vector<Elem003AF9E0> *view = (_STL::vector<Elem003AF9E0> *)&records7C;
        view->erase(view->begin(), view->end());
    }
    if (!xfer->IsCRC())
        Rva0031A160Xfer(xfer, &records7C);
    xfer->xferSnapshot(summary78);
    ((Rva0031A6DBAudio *)TheAudio)->xferHandle(xfer, &audio60);
    if (version.minimum >= 5) {
        xfer->xferAsciiString(name28);
        xfer->xferCoord2D(&source4C);
    }
    if (!xfer->IsCRC()) {
        if (version.minimum >= 6) {
            if (xfer->IsStoring())
                flag65 = status88 ? status88->s11() : false;
            xfer->xferBool(flag65);
            XferArmyIconSize(xfer, &iconSize70);
            xfer->xferUnicodeString(text68);
            xfer->xferUnicodeString(text6C);
        } else {
            iconSize70 = -1;
            text68 = UnicodeString::TheEmptyString;
            text6C = UnicodeString::TheEmptyString;
        }
    }
    if (xfer->IsLoading())
        value8C = 0;
}

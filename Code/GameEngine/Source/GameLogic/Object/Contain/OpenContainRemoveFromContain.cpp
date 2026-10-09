// cl: /O1 /G7 /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source
// stlport
// BFME1 9cbfb551fe20 OpenContain.cpp removeFromContain is the semantic
// donor; BFME2's wrapper validates through slot58 and processes status bits
// before its private removal helper. WB01194580 carries OpenContain.cpp383
// and the complete diagnostic; native00463509..004635C0 RET8 is183bytes.
// The existing neutral binding keeps the secondary-interface ABI unchanged.
#include <bitset>
#include "debug/debug.h"
bool bfmeRva000387C0();
enum ObjectStatusTypes { OBJECT_STATUS_5=5 };
class Object { public: void setStatus(ObjectStatusTypes,bool); };
class OpenContain { public: void rva00462FB3(Object *,bool); };
struct Rva00463509Flags { _STL::bitset<101> bits; };
template<int N> class Rva00463509Slots:public Rva00463509Slots<N-1> { public: virtual void gap(char (*)[N]); };
template<> class Rva00463509Slots<0> {};
class Rva00463509Slot44:public Rva00463509Slots<44> { public: virtual Rva00463509Flags flags(Object *); };
template<int N> class Rva00463509After45:public Rva00463509After45<N-1> { public: virtual void gap(char (*)[N+45]); };
template<> class Rva00463509After45<0>:public Rva00463509Slot44 {};
class Rva00463509:public Rva00463509After45<13> {
public:
    virtual bool contains(Object *);
    void rva00463509(Object *,bool);
};
// The shared debug prefix supplies the first three operations. This call's
// final diagnostic kind is the native integer2; its enum identity is unknown.
class Rva00463509DebugFinish:public Rva00463509Slots<19> { public: virtual void finish(int); };
void Rva00463509::rva00463509(Object *rider,bool expose)
{
    if (!rider) return;
    if (!contains(rider)) {
        if (bfmeRva000387C0()) {
            Debug::SkipNext(true);
            theDebug->SkipNext();
            Debug &message=theDebug->CrashBegin(0,0,0);
            Debug &finished=message<<"OpenContain::removeFromContain: Trying to remove an object from a container that does not currently contain it.";
            reinterpret_cast<Rva00463509DebugFinish *>(&finished)->finish(2);
        }
        return;
    }
    if (flags(rider).bits.test(1) && !flags(rider).bits.test(61)) rider->setStatus(OBJECT_STATUS_5,false);
    reinterpret_cast<OpenContain *>(reinterpret_cast<char *>(this)-0x20)->rva00462FB3(rider,expose);
}

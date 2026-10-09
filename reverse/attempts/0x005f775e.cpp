// ??0InProgressIconSlot@Impl@BuildQueueDetailsMovieClip@StrategicHUD@@QAE@PAV123@@Z
// partial score=0.9080120464351823 date=2026-10-10
// Native C79790/C797F4 contain thirteen ordinary methods; there is no
// virtual destructor slot. Base destruction is the independently rowed59B
// body at5F6941; its old virtual mangling/provider view needs reconciliation.
// Field layout1C/2C and single-inheritance data are target-proven. Return
// and unused argument types on unowned slot declarations are structural views.
// Direct returned binding with actual copy-aware Rva579E47 holder removes
// old20B excess. Remaining whole967B differences are the prefix/key/binding
// stack-home cycle. No Code/pins/byte credit. Base dtor and image setter
// QA/UA declarations also need provider/consumer reconciliation before link.
// cl: /G7 /arch:SSE /ICode/Libraries/Include/Lib /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include "Coord2D.h"
struct AsciiStringRef {const AsciiString *m_string;};
struct AsciiStringPlusString : AsciiStringRef {AsciiStringRef m_second;};
class Rva000B3F84Pair {public:Rva000B3F84Pair(){} Rva000B3F84Pair *init(const char*);const char *text;int length;};
struct AsciiStringPlusStringText : AsciiStringPlusString {operator AsciiString();Rva000B3F84Pair m_right;};
static __forceinline AsciiStringPlusString operator+(const AsciiString&a,const AsciiString&b) {AsciiStringPlusString r;r.m_string=&a;r.m_second.m_string=&b;return r;}
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString&a,const char*b) {Rva000B3F84Pair p;p.init(b);AsciiStringPlusStringText r;static_cast<AsciiStringPlusString&>(r)=a;r.m_right=p;return r;}
class AptCommandTarget {};
struct DelegateDesc {
 template<class T> DelegateDesc(T*o,void(T::*m)(void*)):object((AptCommandTarget*)o),method(reinterpret_cast<void(AptCommandTarget::*)(void*)>(m)){}
 template<class T> DelegateDesc(T*o,void(T::*m)(const Coord2D*,const Coord2D*,void*,void*)):object((AptCommandTarget*)o),method(reinterpret_cast<void(AptCommandTarget::*)(void*)>(m)){}
 AptCommandTarget *object;void(AptCommandTarget::*method)(void*);
};
class Rva00579E47 {public:Rva00579E47(const DelegateDesc&);Rva00579E47(const Rva00579E47&);~Rva00579E47();void*ptr;};
class AptCommandMap;class AptCustomRender;struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
template<class T> class AptRef:public Rva00579E47 {public:AptRef(DelegateDesc desc):Rva00579E47(desc){}};
class AptCommandMapAdder {public:void AddCommandMap(const AsciiString&,AptRef<AptCommandMap>);__forceinline void AddCommandMapDelegate(const AsciiString&n,DelegateDesc d){AddCommandMap(n,AptRef<AptCommandMap>(d));}char storage[12];};
class AptCustomRenderAdder {public:void AddCustomRender(const AsciiString&,AptRef<AptCustomRender>);__forceinline void AddCustomRenderDelegate(const AsciiString&n,DelegateDesc d){AddCustomRender(n,AptRef<AptCustomRender>(d));}char storage[12];};
class Image;
class Rva005F6941 {public:
 Rva005F6941();~Rva005F6941();
 virtual unsigned char rva004C9990()const;virtual void rva002B230F(void*);
 virtual const Image*rva0030F45F()const;virtual void rva005F6CA8(const Image*);
 virtual const Image*rva001DB0A8()const;virtual void rva005F6D2C(const Image*);
 virtual int rva001DB09D()const;virtual void rva005F74F7(int);
 virtual int rva0057E556()const;virtual void DoSetState(int);
 virtual int rva0030D377()const=0;virtual int rva00091A56()const=0;
 virtual void rva005F7512(int,int)=0;
 void*listener;void*portrait,*typeImage;int quantity,state;bool hovered;
};
namespace StrategicHUD {class BuildQueueDetailsMovieClip {public:class Impl;};}
class StrategicHUD::BuildQueueDetailsMovieClip::Impl {public:char prefix[4];unsigned int level;AsciiString name;char gap[8];AptCommandMapAdder maps;char images[12];AptCustomRenderAdder renders;class QueuedIconSlot;class InProgressIconSlot;};
class StrategicHUD::BuildQueueDetailsMovieClip::Impl::QueuedIconSlot {public:void rva005F688B(void*);void rva005F6892(void*);void rva005F6A90(void*);void rva005F6A98(void*);void rva005F6AA0(void*);void rva005F6AA8(void*);void rva005F6AE8(void*);};
class StrategicHUD::BuildQueueDetailsMovieClip::Impl::InProgressIconSlot :public Rva005F6941 {
public:InProgressIconSlot(Impl*);~InProgressIconSlot();virtual void DoSetState(int);
 virtual void rva005F74F7(int);virtual void rva005F7512(int,int);
 virtual const Image*rva0030F45F()const;virtual void rva005F6CA8(const Image*);
 virtual const Image*rva001DB0A8()const;virtual void rva005F6D2C(const Image*);
 virtual int rva0030D377()const;virtual int rva00091A56()const;
 void rva005F6899(const Coord2D*,const Coord2D*,void*,void*);void SetQuantityString(int);void SetProgressString(int,int);
private:Impl*owner;int total,remaining;bool turnsHover;
};
#define PROGRESS_BIND(TEXT,METHOD) owner->maps.AddCommandMap(prefix+owner->name+TEXT,AptRef<AptCommandMap>(DelegateDesc((QueuedIconSlot*)this,&QueuedIconSlot::METHOD)))
StrategicHUD::BuildQueueDetailsMovieClip::Impl::InProgressIconSlot::InProgressIconSlot(Impl *parent):owner(parent),total(0),remaining(0),turnsHover(false) {
 AsciiString prefix;prefix.format("_level%u.",owner->level);
 PROGRESS_BIND("_OnInProgressIconSlotClicked",rva005F6AE8);
 PROGRESS_BIND("_OnInProgressIconSlotRollOver",rva005F6A98);
 PROGRESS_BIND("_OnInProgressIconSlotRollOut",rva005F6A90);
 PROGRESS_BIND("_OnInProgressIconSlotTurnsRemainingRollOver",rva005F6892);
 PROGRESS_BIND("_OnInProgressIconSlotTurnsRemainingRollOut",rva005F688B);
 PROGRESS_BIND("_OnInProgressIconSlotTypeRollOver",rva005F6AA8);
 PROGRESS_BIND("_OnInProgressIconSlotTypeRollOut",rva005F6AA0);
 owner->renders.AddCustomRender(prefix+owner->name+"_ProgressOverlay",AptRef<AptCustomRender>(DelegateDesc(this,&InProgressIconSlot::rva005F6899)));
 SetQuantityString(quantity);SetProgressString(total,remaining);
}

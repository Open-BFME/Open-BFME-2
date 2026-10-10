// ??0TunnelTracker@@QAE@XZ
// partial score=1.0 date=2026-10-10
// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport
#include <list>
class Object;
namespace _STL {
template<> _List_base<int,allocator<int> >::_List_base(const allocator<int>&);
template<> _List_base<int,allocator<int> >::~_List_base();
}
class Xfer;
class TunnelPrimary {public:virtual ~TunnelPrimary(){} protected:virtual void loadPostProcess()=0;virtual const char *rva004F5617()const=0;virtual void xfer(Xfer*)=0;};
class TunnelCounter {public:TunnelCounter(){} virtual void rva004F5391(bool)=0;};
class TunnelTracker:public TunnelPrimary,public TunnelCounter {
public:TunnelTracker();virtual void rva004F5391(bool);
protected:virtual ~TunnelTracker();virtual void loadPostProcess();virtual const char *rva004F5617()const;virtual void xfer(Xfer*);
private:_STL::list<int> ids;unsigned unknownC;_STL::list<Object*> contained;_STL::list<int> transfer;unsigned unknown18,unknown1C,nemesis,timestamp;
};
TunnelTracker::TunnelTracker(){unknown1C=0;unknown18=0;nemesis=0;timestamp=0;unknownC=0;}

void TunnelTracker::rva004F5391(bool up){if(up)++unknownC;else --unknownC;}
const char *TunnelTracker::rva004F5617()const{return "TunnelTracker";}

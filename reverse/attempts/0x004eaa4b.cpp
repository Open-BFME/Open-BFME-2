// ?DoXferFarmLibrary@AIEconomyBuilder@@SAXPAVXfer@@@Z
// partial score=0.90754 date=2026-10-08
// cl: /O1 /G7 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <new>
class Xfer;
class Rva00596F18 {public:Rva00596F18(void *);virtual ~Rva00596F18();private:unsigned char opaque04[0x74-4];};
struct AIEconomyFarmLibraryStorage {Rva00596F18 **first,**finish,**end;};
class AIEconomyBuilder {public:static AIEconomyFarmLibraryStorage m_farmList;static void DoXferFarmLibrary(Xfer *);};
class ModuleData;
namespace _STL {template<> void vector<const ModuleData *>::push_back(const ModuleData *const &);}
class FarmLibraryXferHead {public:virtual void slot0();virtual bool IsLoading() const;};
template<class Base,int N> class FarmLibraryXferSlots:public FarmLibraryXferSlots<Base,N-1>{public:virtual void gap(Base*,char(*)[N]);};
template<class Base> class FarmLibraryXferSlots<Base,0>:public Base {};
class FarmLibraryXferView:public FarmLibraryXferSlots<FarmLibraryXferHead,28>{public:virtual void transferUnsigned(unsigned &);};
template<int N> class FarmSnapshotSlots:public FarmSnapshotSlots<N-1>{public:virtual void gap(char(*)[N]);};
template<> class FarmSnapshotSlots<0> {};
class FarmSnapshotView:public FarmSnapshotSlots<12>{public:virtual void DoXfer(Xfer*,bool);};
void AIEconomyBuilder::DoXferFarmLibrary(Xfer *xfer) {
 unsigned count=m_farmList.finish-m_farmList.first;
 FarmLibraryXferView *io=reinterpret_cast<FarmLibraryXferView *>(xfer);
 io->transferUnsigned(count);
 if(io->IsLoading()) {
  for(unsigned i=0;i<count;++i) {
   Rva00596F18 *farm=new Rva00596F18(0);
   reinterpret_cast<_STL::vector<const ModuleData*> *>(&m_farmList)->push_back(reinterpret_cast<const ModuleData *const &>(farm));
  }
 }
 Rva00596F18 **last=m_farmList.finish;
 for(Rva00596F18 **i=m_farmList.first;i!=last;++i) {
  reinterpret_cast<FarmSnapshotView *>(*i)->DoXfer(xfer,false);
 }
}

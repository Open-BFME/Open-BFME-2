// ?rva0039D1D0@Rva0039C190@@QAEXI@Z
// partial score=0.8303 date=2026-10-08
// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// Native39D1D0..39D1F1 default resize wrapper; WBFA5240/43B. Correct owned
// PerFrameStats argument now calls the independently recovered96B resize.
// Native keeps this inEDX across ctor39B7FB; this out-of-line declaration
// makes VC7.1 preserve it inESI, producing35B instead of33B. A visible
// constructor must still preserve the correct complete class/vtable and
// canonical Snapshot cleanup; no incorrect ctor body or binding is used.
#include <vector>
#include "Common/Snapshot.h"
struct Rva0039C028Record { Rva0039C028Record(); Rva0039C028Record(const Rva0039C028Record&); ~Rva0039C028Record(); Rva0039C028Record&operator=(const Rva0039C028Record&); private: char bytes[20]; };
namespace _STL { template<>void vector<Rva0039C028Record>::reserve(unsigned int); }
class __declspec(novtable) Rva0039B893 : public Snapshot { public: Rva0039B893(); virtual __forceinline ~Rva0039B893(){}; int field04; float field08; short field0C,field0E,field10; protected: virtual void loadPostProcess();virtual void crc(Xfer*);virtual void xfer(Xfer*); };

struct Rva0039C415Element {unsigned words[5];};
namespace _STL {template<>void vector<Rva0039C415Element>::_M_fill_insert(Rva0039C415Element*,unsigned int,const Rva0039C415Element&);}
class Rva0039C190 {
public:
 Rva0039B893 *rva0039C190(Rva0039B893*,Rva0039B893*);
 void rva0039D170(unsigned int n,Rva0039B893 value);
 void rva0039D1D0(unsigned int n);
 Rva0039B893 *start,*finish,*capacity;
};
void Rva0039C190::rva0039D1D0(unsigned int n){rva0039D170(n,Rva0039B893());}

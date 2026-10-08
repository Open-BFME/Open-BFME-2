// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native598DA2..598E66 is a complete RET4 snapshot-transfer body.
// WB152EC60 is unnamed; named AIBuilder::DoXfer4EC1D9 independently calls
// it on its +38 component. The component's class and original method name
// remain unproved; retain the address name rather than infer them from
// adjacent AIUnitBuilder operations. Native storage is vector<AsciiString>
// at+4C: version1/1 and count precede store/load. Load clears the range via
// rowed51B2CCFC, transfers temporary strings, appends via rowed55B2DBE6,
// and releases each temporary via rowed36410. Real STLport clear supplies
// the same receiver-relative begin/end reads as native; no donor asserted.
#include <vector>
#include "ascii_string.h"
// Retail Version stores minimum/current bytes and has an inline constructor;
// that constructor form also reproduces the independent stack homes in DoXfer.
struct WallVersion
{
    WallVersion(unsigned char min, unsigned char cur) : minimum(min), current(cur) {}
    unsigned char minimum, current;
};
class Xfer{public:virtual~Xfer();virtual bool IsLoading() const;
virtual bool IsStoring() const;
virtual bool IsCRC() const;
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual Xfer &xferVersion(WallVersion *);
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual Xfer &xferCoord3D(struct Coord3D *);
virtual void slot25();
virtual void slot26();
virtual Xfer& xferAsciiString(AsciiString*);
virtual void slot28();
virtual void slot29();
virtual Xfer &xferUnsignedInt(unsigned int *);
virtual Xfer& xferInt(int*);
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual Xfer &xferBool(bool *);
};


namespace _STL {
template<> vector<AsciiString>::iterator vector<AsciiString>::erase(iterator,iterator);
template<> void vector<AsciiString>::push_back(const AsciiString &);
}
class Rva00598DA2 {
public: void rva00598DA2(Xfer *);
private: unsigned char prefix[0x4c]; _STL::vector<AsciiString> values;
};
void Rva00598DA2::rva00598DA2(Xfer *xfer) {
 WallVersion version(1,1);
 xfer->xferVersion(&version);
 unsigned int count=values.size();
 xfer->xferUnsignedInt(&count);
 if(xfer->IsStoring()) {
  _STL::vector<AsciiString>::iterator end=values.end();
  for(_STL::vector<AsciiString>::iterator it=values.begin(); it!=end;++it) xfer->xferAsciiString(it);
 } else if(xfer->IsLoading()) {
  values.clear();
  for(unsigned int i=0;i<count;++i) {
   AsciiString value;
   xfer->xferAsciiString(&value);
   values.push_back(value);
  }
 }
}

// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// WB ED5360 / ED51E0 name ObjectFilter::DoNamesXfer / DoTemplatesXfer.
// Retail 361533..361594 and 360DB9..360E64 prove the two argument pointers,
// Xfer slots7C/6C, vector stride4, and ThingTemplate name at+64. WB preserves
// the otherwise unused ObjectFilter receiver. Pointer/reference spellings are
// a local ABI view; original parameter declarations are not available.
// The six collection offsets are also established by BFME1 ba7ddda7e8f26116's
// ObjectFilterResolveNames.cpp and the existing BFME2 resolver; these bodies
// themselves are reconstructed from retail/WB, not claimed as donor transfers.
#include <vector>
#include "ascii_string.h"
class Xfer{public:virtual~Xfer();virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void slot10();
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
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual Xfer& xferAsciiString(AsciiString*);
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual Xfer& xferInt(int*);
};
namespace _STL {template<>void vector<AsciiString>::push_back(const AsciiString&);}
class ThingTemplate
{
public:
    char opaque00[0x64];
    AsciiString name;
};
class ObjectFilter {public:void DoNamesXfer(Xfer*,_STL::vector<AsciiString>*);void DoTemplatesXfer(Xfer*,_STL::vector<ThingTemplate*>*,_STL::vector<ThingTemplate*>*);};
// ?DoNamesXfer@ObjectFilter@@QAEXPAVXfer@@PAV?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@@Z
void ObjectFilter::DoNamesXfer(Xfer *xfer, _STL::vector<AsciiString> *names)
{
    int count;
    xfer->xferInt(&count);
    AsciiString name;
    for (int i = 0; i < count; ++i)
    {
        xfer->xferAsciiString(&name);
        names->push_back(name);
    }
}

// ?DoTemplatesXfer@ObjectFilter@@QAEXPAVXfer@@PAV?$vector@PAVThingTemplate@@V?$allocator@PAVThingTemplate@@@_STL@@@_STL@@1@Z
void ObjectFilter::DoTemplatesXfer(Xfer *xfer,
                                 _STL::vector<ThingTemplate *> *special,
                                 _STL::vector<ThingTemplate *> *normal)
{
    int count = special->size() + normal->size();
    xfer->xferInt(&count);
    _STL::vector<ThingTemplate *>::iterator it;
    for (it = special->begin(); it != special->end(); ++it)
    {
        AsciiString name("S:");
        name += (*it)->name;
        xfer->xferAsciiString(&name);
    }
    for (it = normal->begin(); it != normal->end(); ++it)
        xfer->xferAsciiString(&(*it)->name);
}

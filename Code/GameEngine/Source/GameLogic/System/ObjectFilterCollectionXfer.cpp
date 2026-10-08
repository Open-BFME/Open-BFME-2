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
// Retail Version stores minimum/current bytes and has an inline constructor;
// that constructor form also reproduces the independent stack homes in DoXfer.
struct FilterVersion
{
    FilterVersion(unsigned char min, unsigned char cur) : minimum(min), current(cur) {}
    unsigned char minimum, current;
};
class Xfer{public:virtual~Xfer();virtual void slot01();
virtual bool IsStoring() const;
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual Xfer &xferVersion(FilterVersion *);
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
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual Xfer &xferBool(bool *);
};
namespace _STL {template<>void vector<AsciiString>::push_back(const AsciiString&);}
class ThingTemplate
{
public:
    char opaque00[0x64];
    AsciiString name;
};
class ObjectFilter
{
public:
    void DoXfer(Xfer *);
    static void rva003611EFResolveNames(ObjectFilter *);
    void DoNamesXfer(Xfer *, _STL::vector<AsciiString> *);
    void DoTemplatesXfer(Xfer *, _STL::vector<ThingTemplate *> *, _STL::vector<ThingTemplate *> *);
    int m_id;
};
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

// Existing verified 218-bit flag provider; only its member ABI is used here.
template<int N> class BitFlags { public: void xfer(Xfer *); };
// Existing constructor/destructor/equality own this nonvirtual 0x94-byte
// interned record. Offset views below come from this retail transfer and are
// consistent with those providers; no new record identity is asserted.
class Rva00360F55
{
public:
    Rva00360F55();
    ~Rva00360F55();
    bool rva00360E64(const Rva00360F55 &);
    char bytes[0x94];
};
int Rva00361790(Rva00360F55*);
extern unsigned char*g_validityBegin;extern unsigned char*g_validityEnd;
// ?DoXfer@ObjectFilter@@QAEXPAVXfer@@@Z
// WB ED5470 names DoXfer; native362255..3623E5 supplies the record fields,
// save/load sequence, conditional version-2 field, and registry scan. The old
// resolver's ObjectFilter spelling denotes the full record: pass that verified
// provider its record view, not the four-byte index wrapper's address.
void ObjectFilter::DoXfer(Xfer *xfer)
{
    FilterVersion version(1, 2);
    xfer->xferVersion(&version);
    Rva00360F55 temp;
    Rva00360F55 *data;
    if (xfer->IsStoring())
    {
        if (m_id == -1)
            m_id = Rva00361790(&Rva00360F55());
        data = reinterpret_cast<Rva00360F55 *>(g_validityBegin) + m_id;
    }
    else
        data = &temp;
    xfer->xferBool(reinterpret_cast<bool *>(data->bytes + 0x88));
    xfer->xferInt(reinterpret_cast<int *>(data->bytes + 0x80));
    reinterpret_cast<BitFlags<218> *>(data->bytes + 0x48)->xfer(xfer);
    reinterpret_cast<BitFlags<218> *>(data->bytes + 0x64)->xfer(xfer);
    xfer->xferInt(reinterpret_cast<int *>(data->bytes + 0x84));
    if (xfer->IsStoring())
    {
        DoTemplatesXfer(xfer,
            reinterpret_cast<_STL::vector<ThingTemplate *> *>(data->bytes + 0x18),
            reinterpret_cast<_STL::vector<ThingTemplate *> *>(data->bytes + 0x30));
        DoTemplatesXfer(xfer,
            reinterpret_cast<_STL::vector<ThingTemplate *> *>(data->bytes + 0x24),
            reinterpret_cast<_STL::vector<ThingTemplate *> *>(data->bytes + 0x3C));
    }
    else
    {
        DoNamesXfer(xfer, reinterpret_cast<_STL::vector<AsciiString> *>(data->bytes));
        DoNamesXfer(xfer, reinterpret_cast<_STL::vector<AsciiString> *>(data->bytes + 0x0C));
        rva003611EFResolveNames(reinterpret_cast<ObjectFilter *>(data));
        int count = (g_validityEnd - g_validityBegin) / (int)sizeof(Rva00360F55);
        for (int i = 0; i < count; ++i)
        {
            if (reinterpret_cast<Rva00360F55 *>(g_validityBegin)[i].rva00360E64(*data))
            {
                m_id = i;
                break;
            }
        }
    }
    if (version.current >= 2)
        xfer->xferInt(reinterpret_cast<int *>(data->bytes + 0x90));
}

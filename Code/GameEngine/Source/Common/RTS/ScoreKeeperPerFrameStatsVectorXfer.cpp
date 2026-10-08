// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Clean BF1 ba7ddda XferMissionObjectiveStateVector/Coord3DVector semantic guide.
// Existing target vtable C1AD6C slot2 returns ScoreKeeper::PerFrameStats and
// slot3 reaches the named39B823 xfer. The address-named record view preserves
// the established constructor/insertion providers, while its canonical
// Snapshot base restores BBB554 on unwind (native base destructor49B47C).
// Its complete destructor is a genuine7B fold, with no unique-byte gain.
// Target39C4F7..39C5E1 proves snapshot transfer slot12, stride20, version1/1,
// reserve39C028, ctor39B7FB and insertion39C27D. The established record
// providers retain their address-derived names.
#include <vector>
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
// Existing reserve provider uses this opaque 20-byte record ABI.
struct Rva0039C028Record
{
    Rva0039C028Record();
    Rva0039C028Record(const Rva0039C028Record &);
    ~Rva0039C028Record();
    Rva0039C028Record &operator=(const Rva0039C028Record &);
private:
    char bytes[20];
};
namespace _STL
{
    template<> void vector<Rva0039C028Record>::reserve(unsigned int);
}

class __declspec(novtable) Rva0039B893 : public Snapshot
{
public:
    Rva0039B893();
    virtual __forceinline ~Rva0039B893() {}
    int field04;
    float field08;
    short field0C, field0E, field10;
protected:
    virtual void loadPostProcess();
    virtual void crc(Xfer *);
    virtual void xfer(Xfer *);
};

class Rva0039C1C3
{
public:
    void rva0039C27D(Rva0039B893 *);
    Rva0039B893 *start, *finish, *end;
};

struct XferVersion
{
    unsigned char minimum, current;
};

class Xfer
{
public:
 virtual ~Xfer();
 virtual void slot01();
 virtual bool IsStoring() const;
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual Xfer &xferVersion(XferVersion *);
 virtual Xfer &xferTypeName(const char *const &);
 virtual Xfer &xferSnapshot(Rva0039B893 *);
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
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual Xfer &xferUnsignedInt(unsigned int *);
};
class XferException
{
public:
    XferException(int, const char *, ...);
    XferException(const XferException &);
    ~XferException();
    char *text;
    int tag;
};

Xfer *Rva0039C4F7XferSnapshotVector(Xfer *xfer, Rva0039C1C3 *vector)
{
    XferVersion version = {1, 1};
    xfer->xferVersion(&version);
    unsigned int count = vector->finish - vector->start;
    xfer->xferTypeName("std::vector").xferUnsignedInt(&count);
    if (xfer->IsStoring())
    {
        Rva0039B893 *end = vector->finish;
        Rva0039B893 *it = vector->start;
        while (it != end)
        {
            xfer->xferSnapshot(it);
            ++it;
        }
    }
    else
    {
        if (vector->start != vector->finish)
            throw XferException(4, "Vector must be empty on load");
        reinterpret_cast<_STL::vector<Rva0039C028Record> *>(vector)->reserve(count);
        Rva0039B893 value;
        while (count != 0)
        {
            --count;
            vector->rva0039C27D(&value);
            xfer->xferSnapshot(vector->finish - 1);
        }
    }
    return xfer;
}

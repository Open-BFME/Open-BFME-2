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

#include "../System/XferVectorTypes.h"
#include "../../../Include/Common/BfmeXfer.h"
#include "../../../Include/Common/XferException.h"

Xfer *Rva0039C4F7XferSnapshotVector(Xfer *xfer, Rva0039C1C3 *vector)
{
    XferVersion version = {1, 1};
    (*xfer == reinterpret_cast<Xfer::Version &>(version));
    unsigned int count = vector->finish - vector->start;
    ((*xfer == "std::vector") == count);
    if (xfer->IsStoring())
    {
        Rva0039B893 *end = vector->finish;
        Rva0039B893 *it = vector->start;
        while (it != end)
        {
            (*xfer == static_cast<Snapshot &>(*it));
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
            (*xfer == static_cast<Snapshot &>(*(vector->finish - 1)));
        }
    }
    return xfer;
}

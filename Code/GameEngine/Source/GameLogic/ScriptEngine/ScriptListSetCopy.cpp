// cl: /O1 /G7 /MD /DNDEBUG /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// BFME2 extends the ZH/BF1 ScriptList linked lists with two record sets.
// WB ScriptSetBase deep-copy algorithm is also used by the verified workers
// 3B7FE0 and 3B825F. Native full constructor extents include both catches:
// 3B872A..3B8802 and 3B8802..3B88DA (216 bytes each).
#include "ascii_string.h"
struct BfmeStringRecord003B3F78
{
    unsigned int word0, word1;
    AsciiString text;
    unsigned char flag;
    unsigned short short0;
    unsigned int word2;
    BfmeStringRecord003B3F78() : word2(0) {}
    BfmeStringRecord003B3F78(const BfmeStringRecord003B3F78 &other);
};
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
class Rva003B32E5;
void rva003B7FE0(Rva003B32E5 *, const Rva003B32E5 *);
void rva003B825F(Rva003B32E5 *, const Rva003B32E5 *);
struct Rva003B675BRecord;
struct Rva00359330Record;
void clearRva003B675BNodes(Rva003B675BRecord *);
void clearRva00359330Nodes(Rva00359330Record *);
struct Rva003B713ERange;
struct Rva003B678ARange;
void destroyRva003B713ERange(Rva003B713ERange *);
void destroyRva003B678ARange(Rva003B678ARange *);
class Rva003B872ASet
{
public:
    Rva003B872ASet(const Rva003B872ASet &other);
private:
    _STL::vector<unsigned int> sorted;
    _STL::vector<BfmeStringRecord003B3F78> records;
    int freeHead;
    int tail;
};
Rva003B872ASet::Rva003B872ASet(const Rva003B872ASet &other)
    : sorted(other.sorted), freeHead(other.freeHead), tail(other.tail)
{
    records.reserve(other.records.size());
    try {
        const BfmeStringRecord003B3F78 *end = other.records.end();
        for (const BfmeStringRecord003B3F78 *p = other.records.begin(); p != end; ++p) {
            BfmeStringRecord003B3F78 copy;
            rva003B7FE0((Rva003B32E5 *)&copy, (const Rva003B32E5 *)p);
            try {
                records.push_back(copy);
            } catch (...) {
                clearRva003B675BNodes((Rva003B675BRecord *)&copy);
                throw;
            }
        }
    } catch (...) {
        destroyRva003B713ERange((Rva003B713ERange *)&records);
        throw;
    }
}

class Rva003B8802Set
{
public:
    Rva003B8802Set(const Rva003B8802Set &other);
private:
    _STL::vector<unsigned int> sorted;
    _STL::vector<BfmeStringRecord003B3F78> records;
    int freeHead;
    int tail;
};
Rva003B8802Set::Rva003B8802Set(const Rva003B8802Set &other)
    : sorted(other.sorted), freeHead(other.freeHead), tail(other.tail)
{
    records.reserve(other.records.size());
    try {
        const BfmeStringRecord003B3F78 *end = other.records.end();
        for (const BfmeStringRecord003B3F78 *p = other.records.begin(); p != end; ++p) {
            BfmeStringRecord003B3F78 copy;
            rva003B825F((Rva003B32E5 *)&copy, (const Rva003B32E5 *)p);
            try {
                records.push_back(copy);
            } catch (...) {
                clearRva00359330Nodes((Rva00359330Record *)&copy);
                throw;
            }
        }
    } catch (...) {
        destroyRva003B678ARange((Rva003B678ARange *)&records);
        throw;
    }
}

#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
class ScriptListBase
{
public:
    ~ScriptListBase();
};
class Rva003525E0Pair
{
public:
    Rva003525E0Pair(const Rva003525E0Pair &other);
    ~Rva003525E0Pair() { ((ScriptListBase *)this)->~ScriptListBase(); }
private:
    void *group;
    void *script;
};
class ScriptList : public Snapshot, public Rva003525E0Pair
{
public:
    ScriptList(const ScriptList &other);
    ~ScriptList();
protected:
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *);
private:
    Rva003B872ASet groups;
    Rva003B8802Set scripts;
};
ScriptList::ScriptList(const ScriptList &other)
    : Snapshot(other), Rva003525E0Pair(*(static_cast<const Rva003525E0Pair *>(&other))),
      groups(other.groups), scripts(other.scripts)
{
}

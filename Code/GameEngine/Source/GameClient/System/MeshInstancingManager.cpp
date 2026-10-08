// stlport
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// MeshInstancingManager subsystem view; the original C++ class/method names
// are unknown, so the destructor address remains its class name.
// Target identity: GameEngine::init names TheMeshInstancingManager and invokes
// ctor 0x0041FCEA on a 0x24-byte allocation. That ctor installs primary vtable
// VA 0x00C3B914 and a secondary interface vtable VA 0x00C3B910 at +0xC, then
// constructs the 20-byte table at +0x10. The secondary base is one pure slot
// (base vtable VA 0x00C1C780); native lookup 0x0041FB69 is its override.
// SubsystemInterface's existing target header supplies its verified 12-byte
// layout and 14 primary virtual slots. Native slots 1/9/10 identify init/reset/
// update; reset and update both target the already-owned RET at RVA 0x000B3FD0.
// Destructor 0x0041FB13..0x0041FB61 (78B) unregisters the interface, destroys
// the table through its real 0x0041FA59 owner, then destroys SubsystemInterface.
// Lookup 0x0041FB69..0x0041FC37 (206B) returns node+8 for the whole name, then
// retries the prefix before the first dot, otherwise returning 1. AsciiString
// key +4 and scalar value +8 are native accesses; STLport's two-word iterator
// is a source-shape inference, independently verified against the full body.
// Reference BFME1 34f59164f6d1efd413c5fd37f4894ec834c3c0fe and ZH sweeps
// supplied no viable named donor for this subsystem. Real C++ reconstruction.

#include "ascii_string.h"
#include <string.h>
#include <hash_map>
typedef _STL::pair<const AsciiString, int> MeshNamePair;
typedef _STL::_Ht_iterator<
    MeshNamePair, _STL::_Nonconst_traits<MeshNamePair>, AsciiString,
    _STL::hash<AsciiString>, _STL::_Select1st<MeshNamePair>,
    _STL::equal_to<AsciiString>, _STL::allocator<MeshNamePair> > MeshNameIterator;
typedef MeshNameIterator::_Node MeshNameNode;
typedef bool Bool;
#include "subsystem_interface.h"
class Rva00056F61 { public: __declspec(nothrow) void *rva00056F61(const AsciiString *); };
class Rva000427195 { public: void rva003A2A41(); };
class Rva0041FA59
{
public:
    Rva0041FA59();
    ~Rva0041FA59();
    MeshNameIterator find(const AsciiString &key)
    {
        return MeshNameIterator(static_cast<MeshNameNode *>(reinterpret_cast<Rva00056F61 *>(this)->rva00056F61(&key)),
            reinterpret_cast<MeshNameIterator::_Hashtable *>(this));
    }
    MeshNameIterator end() { return MeshNameIterator(0,reinterpret_cast<MeshNameIterator::_Hashtable *>(this)); }
private:
    // Twenty-byte table ABI; actual field ownership is defined in MeshInstancingTable.cpp.
    unsigned opaque[5];
};
class MeshInstancingInterfaceView { public: virtual int rva0041FB69(const char *) = 0; };
void Rva0018C0F1Clear();
class Rva0041FB13 : public SubsystemInterface, public MeshInstancingInterfaceView
{
public:
    Rva0041FB13();
    virtual ~Rva0041FB13();
    virtual void init() { reinterpret_cast<Rva000427195 *>(&table)->rva003A2A41(); }
    virtual void reset() {}
    virtual void update() {}
    virtual int rva0041FB69(const char *arg);
private:
    Rva0041FA59 table;
};
Rva0041FB13::~Rva0041FB13() { Rva0018C0F1Clear(); }

int Rva0041FB13::rva0041FB69(const char *arg)
{
    if (!arg)
        return 1;

    MeshNameIterator found = table.find(arg);
    if (found != table.end())
        return found->second;

    char *dot = strchr(arg, '.');
    if (dot) {
        AsciiString prefix(arg, 0, static_cast<int>(dot - arg));
        found = table.find(prefix.str());
        if (found != table.end())
            return found->second;
    }
    return 1;
}

typedef char MeshInstancingSubsystemSize[(sizeof(Rva0041FB13) == 0x24) ? 1 : -1];

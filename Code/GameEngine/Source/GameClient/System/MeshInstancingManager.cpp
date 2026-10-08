// stlport
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// ?rva0041FB69@Rva0041FB69@@UAEHPBD@Z, retail 0x0041FB69..0x0041FC37 (206B).
// Target identity: GameEngine::init names TheMeshInstancingManager and calls
// ctor 0x0041FCEA; that ctor installs primary vtable VA 0x00C3B914 and the
// secondary interface vtable VA 0x00C3B910 at +0xC. Its slot zero is this body.
// The secondary receiver owns the AsciiString-keyed table at +4, corresponding
// to +0x10 in the complete subsystem. The interface's original method name is
// unknown; the address-derived name deliberately preserves that uncertainty.
// Native lookup returns node+8 for the complete name, then retries the prefix
// before the first dot, otherwise returning 1. Node key +4 and value +8 are
// target accesses; STLport's two-word iterator is a source-shape inference.
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
// Existing row 0x00056F61 owns the nonthrowing bucket/key search. This view
// adds only inline iterator packaging; the retained table word reproduces the
// native iterator assignment and does not introduce a new helper pin.
class Rva00056F61
{
public:
    __declspec(nothrow) void *rva00056F61(const AsciiString *key);

    MeshNameIterator find(const AsciiString &key)
    {
        return MeshNameIterator(static_cast<MeshNameNode *>(rva00056F61(&key)),
            reinterpret_cast<MeshNameIterator::_Hashtable *>(this));
    }

    MeshNameIterator end()
    {
        return MeshNameIterator(0,
            reinterpret_cast<MeshNameIterator::_Hashtable *>(this));
    }

private:
    unsigned opaque[5];
};

// Partial view of the secondary interface, rather than the full subsystem.
class Rva0041FB69
{
public:
    virtual int rva0041FB69(const char *arg);

private:
    Rva00056F61 table;
};

int Rva0041FB69::rva0041FB69(const char *arg)
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

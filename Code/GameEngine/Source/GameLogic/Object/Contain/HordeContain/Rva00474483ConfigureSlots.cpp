// cl: /O1 /G7 /arch:SSE /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Native 474483..474517 RET4: definition20C pointer vector, owner270 pointer
// vector, allocate8 {resolved-template,slot}, 474431 position and key0, then
// 2D06CA name lookup on TheThingFactory. The following HordeContain formation
// builder calls this with its definition4 when vector20C is nonempty. Target
// offsets and ownership come from retail; no original member name is asserted.
// vector<>::_M_insert_overflow inlines max(size(), n). Retail never calls
// _STL::max<unsigned> (0x00013740 has no call site), but cl 13.10 still emits
// the template's COMDAT, and under /O1 /G7 it is not retail's blend body. A
// file-static unsigned overload takes the call instead: no external max copy
// (the SubsystemInterface.cpp recipe).
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include "ascii_string.h"
class ThingTemplate;
class ThingFactory;
extern ThingFactory *TheThingFactory;
class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &name); };
struct Rva00474431Pair { int m_00, m_04; };
struct Rva00474483Input { AsciiString name; Rva00474431Pair position; };
struct Rva00474483Definition {
 char opaque00[0x20c];
 _STL::vector<Rva00474483Input *> entries;
};
struct Rva00474483Entry {
 // ?Rva00474483Entry::Rva00474483Entry present-unmatched
 __forceinline Rva00474483Entry() : target(0), slot(-1) {}
 void *target; int slot;
};
class Rva00474431 {
public:
 int rva00474431(const Rva00474431Pair &, int);
 void rva00474483(Rva00474483Definition *);
 char opaque00[0x270];
 _STL::vector<Rva00474483Entry *> entries;
};
void Rva00474431::rva00474483(Rva00474483Definition *definition)
{
 for (unsigned i=0; i<definition->entries.size(); ++i) {
  Rva00474483Entry *entry = new Rva00474483Entry;
  entry->slot = rva00474431(definition->entries[i]->position, 0);
  entry->target = (void *)TheThingFactory->findTemplate(definition->entries[i]->name);
  entries.push_back(entry);
 }
}

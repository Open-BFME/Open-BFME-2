// cl: /Ireference/shims/bfme2_ascii /MD
// ?Rva005D232DGet@@YAPBVImage@@PAURva005D232DIn@@@Z @0x005D232D 40B
// Image lookup sibling of 0x005D2355: +0x28 referent plus 0xC string goes through
// global 0x009FF000 rowed 0x002D06CA then tail-jmps ThingTemplate 0x0033BA46.
// Evidence: rowed 0x002D06CA and 0x0033BA46 callers 0x005CE74C 0x005CF0E2.
#include "ascii_string.h"

class Image;
class Rva002D06CA {
public:
    void *rva002D06CA(const AsciiString *s);
};
extern class ThingFactory *TheThingFactory;

class ThingTemplate {
public:
    const Image *rva0033BA46();
};

struct Rva005D232DHolder {
    char pad[0x0C];
    AsciiString str;
};
struct Rva005D232DIn {
    char pad[0x28];
    void *p28;
};
const Image *Rva005D232DGet(Rva005D232DIn *in);
const Image *Rva005D232DGet(Rva005D232DIn *in)
{
    void *q = in->p28;
    if (q != 0) {
        const AsciiString &s = *(const AsciiString *)((char *)q + 0x0C);
        void *v = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&s);
        if (v != 0)
            return ((ThingTemplate *)v)->rva0033BA46();
    }
    return 0;
}

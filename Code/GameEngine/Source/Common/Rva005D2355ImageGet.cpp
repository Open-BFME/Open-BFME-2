// cl: /Ireference/shims/bfme2_ascii /MD
// ?Rva005D2355Get@@YAPBVImage@@PAURva005D2355In@@@Z @0x005D2355 102B
// Image lookup: non-empty +0x18 string goes through global 0x009FF000 rowed 0x002D06CA
// then tail-jmps ThingTemplate 0x0033BA46 else falls back to LivingWorld find 0x002B51F8
// with id at +0x54 and player +0x40+0x30 string via ImageCollection findImageByName.
// Evidence: rowed isEmpty 0x1E2F twice callers 0x0057754A 0x005CF3D8 0x005E6377 0x005FAE5C.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "ascii_string.h"

class Image;
class ImageCollection {
public:
    const Image *findImageByName(const AsciiString &n);
};
extern class ImageCollection *TheMappedImageCollection;

class Rva002E2903Player {
public:
    char pad[0x40];
    void *p40;
};
struct Rva005D2355Holder {
    char pad[0x30];
    AsciiString str;
};
class Rva002BA8F1Logic {
public:
    Rva002E2903Player *find(int, unsigned int *);
};

class Rva002D06CA {
public:
    void *rva002D06CA(const AsciiString *s);
};
extern class ThingFactory *TheThingFactory;

class ThingTemplate {
public:
    const Image *getButtonImage();
    const Image *rva0033BA46();
};

struct Rva005D2355In {
    char pad00[0x18];
    AsciiString str18;
    char pad1C[0x38];
    int id54;
};
const Image *Rva005D2355Get(Rva005D2355In *in);
const Image *Rva005F031DGet(Rva005D2355In *in);
const Image *Rva005D2355Get(Rva005D2355In *in)
{
    const AsciiString &s = in->str18;
    if (!((const StringBase<char> *)&s)->isEmpty()) {
        void *v = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&s);
        if (v != 0)
            return ((ThingTemplate *)v)->rva0033BA46();
    }
    int id = in->id54;
    Rva002E2903Player *p = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->find(id, 0);
    if (p != 0) {
        Rva005D2355Holder *h = *(Rva005D2355Holder **)((char *)p + 0x40);
        const AsciiString &s2 = *(const AsciiString *)((char *)h + 0x30);
        if (!((const StringBase<char> *)&s2)->isEmpty())
            return TheMappedImageCollection->findImageByName(s2);
    }
    return 0;
}

// ?Rva005F031DGet@@YAPBVImage@@PAURva005D2355In@@@Z @0x005F031D 102B: the same
// lookup ending in the template's rowed ButtonImage resolver 0x0033B580 instead
// of the portrait one; called from 0x005E1B09 and 0x005FF04B.
const Image *Rva005F031DGet(Rva005D2355In *in)
{
    const AsciiString &s = in->str18;
    if (!((const StringBase<char> *)&s)->isEmpty()) {
        void *v = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&s);
        if (v != 0)
            return ((ThingTemplate *)v)->getButtonImage();
    }
    int id = in->id54;
    Rva002E2903Player *p = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->find(id, 0);
    if (p != 0) {
        Rva005D2355Holder *h = *(Rva005D2355Holder **)((char *)p + 0x40);
        const AsciiString &s2 = *(const AsciiString *)((char *)h + 0x30);
        if (!((const StringBase<char> *)&s2)->isEmpty())
            return TheMappedImageCollection->findImageByName(s2);
    }
    return 0;
}

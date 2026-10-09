// ?GetTypeImage@StrategicInGameUI@@YAPBVImage@@PAURva005F002CIn@@@Z @0x005F002C 47B.
// Chain from LivingWorld id find 0x002B51F8: reads id at +0x54 from the input
// then looks up the player and forwards its +0x40+0x20 AsciiString to
// ImageCollection::findImageByName via TheMappedImageCollection.
// TU-local honest-address views; offsets prove operations not original names.
// cl: /MD

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class AsciiString { void *m_data; };
class Image;
class ImageCollection { public: const Image *findImageByName(const AsciiString &n); };
extern ImageCollection *TheMappedImageCollection;
class Rva002E2903Player { public: char pad[0x40]; void *p40; };
struct Rva005F002CHolder { char pad[0x20]; AsciiString str; };
class Rva002BA8F1Logic { public: Rva002E2903Player *find(int, unsigned int *); };

#define TheRva00DFEF10 (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)
struct Rva005F002CIn { char pad[0x54]; int id; };
// WB 0x01615FC0 is StrategicInGameUI::GetTypeImage (asserts at
// StrategicInGameUIGetTypeImage.cpp:233..234): the same +0x54 find(id, 0),
// +0x40 record, +0x20 name and findImageByName as retail.
namespace StrategicInGameUI { const Image *GetTypeImage(Rva005F002CIn *in); }
const Image *StrategicInGameUI::GetTypeImage(Rva005F002CIn *in)
{
    int id = *(int *)((char *)in + 0x54);
    Rva002E2903Player *p = TheRva00DFEF10->find(id, 0);
    if (p)
    {
        Rva005F002CHolder *h = *(Rva005F002CHolder **)((char *)p + 0x40);
        const AsciiString &s = *(const AsciiString *)((char *)h + 0x20);
        return TheMappedImageCollection->findImageByName(s);
    }
    return 0;
}

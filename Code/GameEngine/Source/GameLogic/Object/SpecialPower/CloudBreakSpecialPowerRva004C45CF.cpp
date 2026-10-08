// cl: /MD
// ?Rva004C45CFCreate@@YGXPBUCoord3D@@PBVAsciiString@@@Z @0x004C45CF 82B: free stdcall helper creating object from template name and placing at pos. Evidence: rowed rva002D06CA plus pinned newObject plus rowed setPosition plus g_009FF000 plus caller 0x004C4621 plus neighbours 0x004C4582 0x004C479A.
class AsciiString;
struct Coord3D { float x; float y; float z; };
class Rva002D06CA { public: void *rva002D06CA(const AsciiString *key); };
extern class ThingFactory *TheThingFactory;
void __cdecl ji_006291ae();
class ThingTemplate;
class Team;
struct CreateMask { char m_pad[0x10]; };
class Object;
class ThingFactory { public: Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, bool flag); };
class Thing { public: void setPosition(const Coord3D *pos); };
void __stdcall Rva004C45CFCreate(const Coord3D *pos, const AsciiString *name)
{
    void *tmpl = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(name);
    if (tmpl == 0)
        return;
    CreateMask mask;
    ((void (__cdecl *)(void *, int, unsigned int))&ji_006291ae)(&mask, 0, 0x10);
    Object *obj = ((ThingFactory *)TheThingFactory)->newObject((const ThingTemplate *)tmpl, 0, &mask, false);
    if (obj == 0)
        return;
    ((Thing *)obj)->setPosition(pos);
}

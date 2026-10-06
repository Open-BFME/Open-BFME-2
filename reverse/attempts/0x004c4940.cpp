// ?rva004C4940@Rva004C4940@@QAEPAVObject@@PBUCoord3D@@PBVAsciiString@@@Z
// partial score=0.99 date=2026-10-06
// cl: /O1 /MD
// ?rva004C4940@Rva004C4940@@QAEPAVObject@@PBUCoord3D@@PBVAsciiString@@@Z @0x004C4940 110B: thiscall helper creating object from template name placing at pos and assigning team from holder. Evidence: rowed rva002D06CA plus pinned newObject plus rowed setPosition plus pinned rva00298AE4 plus g_009FF000 plus caller 0x004C49AE plus neighbours.
class AsciiString;
struct Coord3D { float x; float y; float z; };
class Rva002D06CA { public: void *rva002D06CA(const AsciiString *key); };
extern Rva002D06CA *g_009FF000;
void __cdecl ji_006291ae();
class ThingTemplate;
class Team;
struct CreateMask { char m_pad[0x10]; };
class Object;
class ThingFactory { public: Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, bool flag); };
class Thing { public: void setPosition(const Coord3D *pos); };
class Object {
public:
    void setPosition(const Coord3D *pos);
    void rva00298AE4(Team *team);
    char m_pad[0x304];
    Team *m_teamAt304;
};
class Rva004C4940 {
public:
    Object *rva004C4940(const Coord3D *pos, const AsciiString *name);
private:
    char m_pad[8];
    Object *m_obj;
};
// ?rva004C4940@Rva004C4940@@QAEPAVObject@@PBUCoord3D@@PBVAsciiString@@@Z present-unmatched
Object *Rva004C4940::rva004C4940(const Coord3D *pos, const AsciiString *name)
{
    void *tmpl = g_009FF000->rva002D06CA(name);
    if (tmpl == 0)
        return 0;
    CreateMask mask;
    ((void (__cdecl *)(void *, int, unsigned int))&ji_006291ae)(&mask, 0, 0x10);
    Object *obj = ((ThingFactory *)g_009FF000)->newObject((const ThingTemplate *)tmpl, 0, &mask, false);
    if (obj != 0)
    {
        ((Thing *)obj)->setPosition(pos);
        obj->rva00298AE4(m_obj->m_teamAt304);
        return obj;
    }
    return obj;
}

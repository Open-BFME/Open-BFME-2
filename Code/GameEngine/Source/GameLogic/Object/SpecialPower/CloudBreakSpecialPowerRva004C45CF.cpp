// cl: /MD
// ?Rva004C45CFCreate@@YGXPBUCoord3D@@PBVAsciiString@@@Z @0x004C45CF 82B: free stdcall helper creating object from template name and placing at pos. Evidence: rowed rva002D06CA plus pinned newObject plus rowed setPosition plus g_009FF000 plus caller 0x004C4621 plus neighbours 0x004C4582 0x004C479A.
class AsciiString;
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class ThingTemplate;
enum ObjectID; extern class ThingFactory *TheThingFactory;
// memset is msvcr71's, called through its import thunk at 0x006291AE
// rather than expanded inline: <string.h>'s memset with
// #pragma function(memset).
#include <string.h>
#pragma function(memset)
class ThingTemplate;
class Team;
struct CreateMask
{
public:
	unsigned int m_words[4]; // +0x00 +0x00
};
class Object;
class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &name); Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, ObjectID flag); };
#include "../../../Common/Thing/thing.h"
void __stdcall Rva004C45CFCreate(const Coord3D *pos, const AsciiString *name)
{
    void *tmpl = (void *)TheThingFactory->findTemplate(*name);
    if (tmpl == 0)
        return;
    CreateMask mask;
    memset(&mask, 0, 0x10);
    Object *obj = TheThingFactory->newObject((const ThingTemplate *)tmpl, 0, &mask, (ObjectID)0);
    if (obj == 0)
        return;
    ((Thing *)obj)->setPosition(pos);
}

class CloudBreakSpecialPower
{
public:
	void rva004C45CF(const Coord3D *pos, const AsciiString *name);
};

// ICF-folded twin of Rva004C45CFCreate above (same 82 bytes at 0x004C45CF):
// the member spelling ignores its receiver, so its stack frame matches the
// stdcall spelling exactly, including the callee-cleaned return.
void CloudBreakSpecialPower::rva004C45CF(const Coord3D *pos, const AsciiString *name)
{
    void *tmpl = (void *)TheThingFactory->findTemplate(*name);
    if (tmpl == 0)
        return;
    CreateMask mask;
    memset(&mask, 0, 0x10);
    Object *obj = TheThingFactory->newObject((const ThingTemplate *)tmpl, 0, &mask, (ObjectID)0);
    if (obj == 0)
        return;
    ((Thing *)obj)->setPosition(pos);
}

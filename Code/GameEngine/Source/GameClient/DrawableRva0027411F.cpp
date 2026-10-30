// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Native0027411F..00274176, 87B, RET8. Receiver+FC is Object as proved by
// Drawable sibling source; local state+460 and three cdecl(3-word) helpers
// are measured. Original member and output layout remain unknown.
enum ObjectStatusTypes { RvaStatus2 = 2 };
class Object
{
public:
    bool testStatus(ObjectStatusTypes status) const;
};
struct Rva0027411FTemplateView
{
    char unknown00[0x108];
    unsigned char flags;
};
struct Rva0027411FObjectView
{
    void *unknown00;
    Rva0027411FTemplateView *data;
};
void Rva00271CB6(void *state, void *out, float time);
void Rva00271EAD(void *state, void *out, float time);
void Rva002720A4(void *state, void *out, float time);
#include "../../Include/GameClient/DrawableBFME2.h"
void Drawable::rva0027411F(void *out, float time)
{
    Object *owner = m_object;
    if (owner)
    {
        if (owner->testStatus(RvaStatus2))
            Rva00271CB6(((char *)this + 0x460), out, time);
        else if (reinterpret_cast<Rva0027411FObjectView *>(owner)->data->flags & 0x80)
            Rva00271EAD(((char *)this + 0x460), out, time);
        else
            Rva002720A4(((char *)this + 0x460), out, time);
    }
}

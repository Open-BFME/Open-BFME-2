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
class Drawable
{
public:
    void rva0027411F(void *out, float time);
private:
    char unknown00[0xFC];
    Object *object;
    char unknown100[0x460 - 0x100];
    char state;
};
void Drawable::rva0027411F(void *out, float time)
{
    Object *owner = object;
    if (owner)
    {
        if (owner->testStatus(RvaStatus2))
            Rva00271CB6(&state, out, time);
        else if (reinterpret_cast<Rva0027411FObjectView *>(owner)->data->flags & 0x80)
            Rva00271EAD(&state, out, time);
        else
            Rva002720A4(&state, out, time);
    }
}

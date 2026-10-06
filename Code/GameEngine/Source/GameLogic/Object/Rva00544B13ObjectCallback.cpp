// cl: /MD
// Target callback boundary 0x00544B13-0x00544B41, immediately preceding
// the ObjectID refresh body. Its address is passed by that caller to the
// Player iterator at 0x002AB08B with a two-pointer local context.
// Native code proves the object null guard, template+0x111 bit-2 test,
// comparison of object+0x78 with original+0x74, found-pointer write and
// zero/one continuation result. No original callback or flag name is asserted.
// The served ZH Player.cpp lead directs the iterator investigation; these
// target-specific accesses and callback behavior are established independently.
struct Rva00544B13TemplateView { char unknown[0x111]; unsigned char flags111; };
struct Rva00544B13ObjectView {
    char unknown00[4];
    Rva00544B13TemplateView *template04;
    char unknown08[0x74-8];
    int id74;
    int id78;
};
struct Rva00544B13Info { Rva00544B13ObjectView *original; Rva00544B13ObjectView *found; };
int __cdecl Rva00544B13Callback(void *object, void *opaque)
{
    Rva00544B13ObjectView *p = static_cast<Rva00544B13ObjectView *>(object);
    if (p && (p->template04->flags111 & 2)) {
        Rva00544B13Info *info = static_cast<Rva00544B13Info *>(opaque);
        if (p->id78 == info->original->id74) {
            info->found = p;
            return 0;
        }
    }
    return 1;
}

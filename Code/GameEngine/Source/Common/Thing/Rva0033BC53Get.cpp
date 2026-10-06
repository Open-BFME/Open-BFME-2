// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// ?Rva0033BC53Get@@YAPBVImage@@PAVThingTemplate@@PAX@Z @0x0033BC53 23B evidence tail-jmp to rowed ThingTemplate::rva0033BA46 with two null guards callers 0x002946C7 0x0029474F
class Image;
class ThingTemplate
{
public:
    const Image *rva0033BA46();
};

const Image *__cdecl Rva0033BC53Get(ThingTemplate *t, void *u)
{
    if (t == 0 || u == 0)
        return 0;
    return t->rva0033BA46();
}

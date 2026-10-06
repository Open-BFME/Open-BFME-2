// cl: /MD
// ?Rva0045628CDraw@@YGXPAX0H@Z @0x0045628C 52B
// Loops an AsciiString array [start,finish) at +0/+4 of arg1 (stride 4,
// sizeof AsciiString) calling rowed Drawable::rva002724FD 0x002724FD with
// (string, arg3, 1, 0.0f, 0.0f) on Drawable arg2. Proven by retail push 1,
// fstp 0.0 twice, add esi 4 cmp/jne, ret 0xC (3 __stdcall args), and 5
// callers in 0x004562F8. Honest free-function name, __stdcall for ret 0xC.
class AsciiString;
class Drawable {
public:
    void rva002724FD(const AsciiString &s, int a, int b, float c, float d);
};
struct AsciiRange {
    char *m_start;
    char *m_finish;
};
void __stdcall Rva0045628CDraw(void *range, void *drawable, int val)
{
    AsciiRange *r = (AsciiRange *)range;
    Drawable *d = (Drawable *)drawable;
    char *cur = r->m_start;
    while (cur != r->m_finish) {
        d->rva002724FD(*(const AsciiString *)cur, val, 1, 0.0f, 0.0f);
        cur += 4;
    }
}

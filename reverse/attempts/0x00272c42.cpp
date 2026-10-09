// ?rva00272C42@Rva00272C42@@QAEXPBD@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /DNDEBUG /MD
// Retail 0x00272C42..0x00272C5B, a 25-byte RET4 forwarder on the Drawable
// returned by Thing::getDrawable. Native +14C is the pointer to its null-ended
// module array. Forwarding to slot +D4 of its first module is target evidence;
// the original method name and parameter meaning remain unresolved. Caller
// DynamicPortalBehaviour 0x0046129A supplies module-data +138 string bytes.
template <int N> class Rva00272C42Slots : public Rva00272C42Slots<N - 1>
{
public:
    virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00272C42Slots<0> {};
class Rva00272C42Module : public Rva00272C42Slots<53>
{
public:
    virtual void forward(const char *text) = 0;
};
class Rva00272C42
{
public:
    void rva00272C42(const char *text);
private:
    char pad[0x14C];
    Rva00272C42Module **modules;
};
// ?rva00272C42@Rva00272C42@@QAEXPBD@Z present-unmatched
void Rva00272C42::rva00272C42(const char *text)
{
    Rva00272C42Module *module = *modules;
    if (module)
        module->forward(text);
}

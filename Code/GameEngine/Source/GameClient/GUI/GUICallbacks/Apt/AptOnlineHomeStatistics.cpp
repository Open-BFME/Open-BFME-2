// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /Oy-
// Copy extents and source-pointer ABI are target facts; OnlineHome singleton
// identity is inherited from the rowed shell factory and bound callbacks.
// Native Ghidra 005B9717..005B977B, RET0. Six independent 32-byte
// block copies followed by refresh of the online-home singleton.
// Member/global content names remain unknown; target proves storage extents.
struct Rva005B9717Block { unsigned int word[8]; };
extern unsigned int g_Va00E06484, g_Va00E064A4, g_Va00E064C4;
extern unsigned int g_Va00E064E4, g_Va00E06504, g_Va00E06524;
extern int g_Va00E06480;
// Full callee Ghidra 005B95B8..005B9717 is351B RET0, consumes ECX,
// and invokes the rowed online-home ticker helper with three stack words.
// Its application method name remains unknown.
namespace AptOnline { class OnlineHome { public: void rva005B95B8(); }; }
void rva005B9717(const Rva005B9717Block *a, const Rva005B9717Block *b,
 const Rva005B9717Block *c, const Rva005B9717Block *d,
 const Rva005B9717Block *e, const Rva005B9717Block *f)
{
 *reinterpret_cast<Rva005B9717Block *>(&g_Va00E06484) = *a;
 *reinterpret_cast<Rva005B9717Block *>(&g_Va00E064A4) = *b;
 *reinterpret_cast<Rva005B9717Block *>(&g_Va00E064C4) = *c;
 *reinterpret_cast<Rva005B9717Block *>(&g_Va00E064E4) = *d;
 *reinterpret_cast<Rva005B9717Block *>(&g_Va00E06504) = *e;
 *reinterpret_cast<Rva005B9717Block *>(&g_Va00E06524) = *f;
 if (g_Va00E06480) reinterpret_cast<AptOnline::OnlineHome *>(g_Va00E06480)->rva005B95B8();
}

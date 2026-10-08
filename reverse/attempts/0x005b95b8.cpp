// ?rva005B95B8@OnlineHome@AptOnline@@QAEXXZ
// partial score=0.9 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
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

// BF1 9cbfb551 AptOnlineHome.cpp faction-rate section is a semantic lead;
// target uses five independent blocks and displays the remainder as field11.
float rva005B909F(const Rva005B9717Block *,int);
class Rva005B922F { public: void rva005B947D(int,int,int); };
void AptOnline::OnlineHome::rva005B95B8()
{
 int a=(int)(rva005B909F((const Rva005B9717Block *)&g_Va00E06484,3)*100.0f);
 int b=(int)(rva005B909F((const Rva005B9717Block *)&g_Va00E064A4,3)*100.0f);
 int c=(int)(rva005B909F((const Rva005B9717Block *)&g_Va00E064C4,3)*100.0f);
 int d=(int)(rva005B909F((const Rva005B9717Block *)&g_Va00E064E4,3)*100.0f);
 int e=(int)(rva005B909F((const Rva005B9717Block *)&g_Va00E06504,3)*100.0f);
 int f=10000-e-d-c-b-a;
 ((Rva005B922F *)this)->rva005B947D(6,a/100,(a%100)/10);
 ((Rva005B922F *)this)->rva005B947D(7,b/100,(b%100)/10);
 ((Rva005B922F *)this)->rva005B947D(8,c/100,(c%100)/10);
 ((Rva005B922F *)this)->rva005B947D(9,d/100,(d%100)/10);
 ((Rva005B922F *)this)->rva005B947D(10,e/100,(e%100)/10);
 ((Rva005B922F *)this)->rva005B947D(11,f/100,(f%100)/10);
}


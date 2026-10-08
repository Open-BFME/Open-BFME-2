// ?rva005B95B8@OnlineHome@AptOnline@@QAEXXZ
// partial score=0.99 date=2026-10-08
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

// Native 005B909F..005B922F RET0,400B. Seven integer ratios use
// pairs at +0 and +0x10 in the copied32B blocks; the six-bank sum
// is evaluated in reverse bank order. Final normalization returns via x87.
// BF1 9cbfb551 has only dump545DE0(345B), not a clean donor for this body.
// Names of the copied fields and original helper remain unknown.
template<class T> inline const T &onlineHomeMax(const T &a,const T &b)
{ return a<b ? b:a; }
struct OnlineHomeCountPair { int first[4]; int second[4]; };
float Rva005B909FCompute(int *selected,int category)
{
 OnlineHomeCountPair *a=reinterpret_cast<OnlineHomeCountPair *>(&g_Va00E06484);
 OnlineHomeCountPair *b=reinterpret_cast<OnlineHomeCountPair *>(&g_Va00E064A4);
 OnlineHomeCountPair *c=reinterpret_cast<OnlineHomeCountPair *>(&g_Va00E064C4);
 OnlineHomeCountPair *d=reinterpret_cast<OnlineHomeCountPair *>(&g_Va00E064E4);
 OnlineHomeCountPair *e=reinterpret_cast<OnlineHomeCountPair *>(&g_Va00E06504);
 OnlineHomeCountPair *f=reinterpret_cast<OnlineHomeCountPair *>(&g_Va00E06524);
 float ra=float(a->first[category]*100)/float(onlineHomeMax(a->second[category]+a->first[category],1));
 float rb=float(b->first[category]*100)/float(onlineHomeMax(b->second[category]+b->first[category],1));
 float rc=float(c->first[category]*100)/float(onlineHomeMax(c->second[category]+c->first[category],1));
 float rd=float(d->first[category]*100)/float(onlineHomeMax(d->second[category]+d->first[category],1));
 float re=float(e->first[category]*100)/float(onlineHomeMax(e->second[category]+e->first[category],1));
 float rf=float(f->first[category]*100)/float(onlineHomeMax(f->second[category]+f->first[category],1));
 OnlineHomeCountPair *p=reinterpret_cast<OnlineHomeCountPair *>(selected);
 float rs=float(p->first[category]*100)/float(onlineHomeMax(p->second[category]+p->first[category],1));
 return rs/onlineHomeMax(rf+re+rd+rc+rb+ra,1.0f)*100.0f;
}

// Native005B95B8..005B9717 RET0,351B. Five normalized values scaled
// by retail100.0f; the sixth is the residual from10000. No BF1 rounding
// term: native truncates each of five products through __ftol2.
// Same six32B banks copied above; original faction ordering is unknown.
float Rva005B909FCompute(int *selected,int category);
class Rva005B922F { public: void rva005B947D(int index,int a,int b); };
void AptOnline::OnlineHome::rva005B95B8()
{
 int a=int(Rva005B909FCompute(reinterpret_cast<int *>(&g_Va00E06484),3)*100.0f);
 int b=int(Rva005B909FCompute(reinterpret_cast<int *>(&g_Va00E064A4),3)*100.0f);
 int c=int(Rva005B909FCompute(reinterpret_cast<int *>(&g_Va00E064C4),3)*100.0f);
 int d=int(Rva005B909FCompute(reinterpret_cast<int *>(&g_Va00E064E4),3)*100.0f);
 int e=int(Rva005B909FCompute(reinterpret_cast<int *>(&g_Va00E06504),3)*100.0f);
 int f=10000-e-d-c-b-a;
 Rva005B922F *ticker=reinterpret_cast<Rva005B922F *>(this);
 ticker->rva005B947D(6,a/100,(a%100)/10);
 ticker->rva005B947D(7,b/100,(b%100)/10);
 ticker->rva005B947D(8,c/100,(c%100)/10);
 ticker->rva005B947D(9,d/100,(d%100)/10);
 ticker->rva005B947D(10,e/100,(e%100)/10);
 ticker->rva005B947D(11,f/100,(f%100)/10);
}

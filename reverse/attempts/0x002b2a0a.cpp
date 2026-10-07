// ?rva002B2A0A@Rva002B2A0A@@QAEXXZ
// partial score=0.8 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD
// Native Ghidra 002B2A0A..002B2A95 RET0, two measured callees.
// Receiver B0 supplies the index query, B8 its index. DFEF18 is the existing
// singleton. Float argument bits are copied to its 1C/20 words afterwards;
// original method/class identities and those words' interpretation are open.
class Rva0020F27EHost { public: bool rva0020F27E(int index, int argumentWord); };
class Rva002BECCD { public: void rva002BECCD(float x, float y, float z); };
class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;
struct Rva002B2A0APair { float x, y; };
struct Rva002B2A0AVec {
 float x, y, z;
 Rva002B2A0AVec(float a, float b, float c) : x(a), y(b), z(c) {}
 Rva002B2A0AVec(const Rva002B2A0AVec &p) : x(p.x), y(p.y), z(p.z) {}
};
struct Rva002B2A0ATarget { char pad[0x1C]; int x, y; };
inline int rva002B2A0ABits(float f)
{
 union { float value; int word; } bits;
 bits.value = f;
 return bits.word;
}
class Rva002B2A0A
{
public:
 void rva002B2A0A();
private:
 char pad[0xB0];
 Rva0020F27EHost *m_query;
 int m_index;
 int m_B8;
};
void Rva002B2A0A::rva002B2A0A()
{
 Rva002B2A0APair p = {0.0f, 0.0f};
 m_query->rva0020F27E(m_B8, (int)&p);
 if (g_00DFEF18)
 {
  typedef void (Rva002BECCD::*AggregateCall)(Rva002B2A0AVec);
  AggregateCall call = (AggregateCall)&Rva002BECCD::rva002BECCD;
  (((Rva002BECCD *)g_00DFEF18)->*call)(Rva002B2A0AVec(p.x, p.y, 0.0f));
  ((Rva002B2A0ATarget *)g_00DFEF18)->x = rva002B2A0ABits(p.x);
  ((Rva002B2A0ATarget *)g_00DFEF18)->y = rva002B2A0ABits(p.y);
 }
}

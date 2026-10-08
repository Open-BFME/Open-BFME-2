// cl: /O1 /arch:SSE /G7 /EHsc /MD
// Native 0x002B2A0A..0x002B2A95, RET0. Receiver +B0 queries the
// two-component position using +B8, then singleton DFEF18 receives a
// nontrivial pair and an independent zero height at 0x002BECCD.
// The subsequent +1C/+20 writes copy the float representations as words.
// Application field names remain unresolved. LivingWorldLogic association
// follows the surrounding established source family, not a recovered method name.
// A contiguous pair of bit views preserves the native F8/FC stack homes.
// The ordered first word read preserves retail's load before its first store
// and makes MSVC choose the observed ECX receiver/EAX value registers.
class Rva0020F27EHost
{
public:
    bool rva0020F27E(int, int);
};
struct RvaFloatPair
{
    float x, y;
    RvaFloatPair() {}
    RvaFloatPair(const RvaFloatPair &a) { x = a.x; y = a.y; }
    ~RvaFloatPair() {}
};
class Rva002BECCD
{
public:
    void rva002BECCD(RvaFloatPair, float);
};
class Rva002D3627Host
{
public:
    char pad[0x1c];
    unsigned x, y;
    union Bits { float f; unsigned u; };
};
extern Rva002D3627Host *g_00DFEF18;
class LivingWorldLogic
{
public:
    void rva002B2A0A();
private:
    char pad[0xb0];
    Rva0020F27EHost *host;
    char padB4[4];
    int index;
};
void LivingWorldLogic::rva002B2A0A()
{
    RvaFloatPair pos;
    pos.x = 0.0f;
    pos.y = 0.0f;
    host->rva0020F27E(index, (int)&pos);
    if (g_00DFEF18)
    {
        ((Rva002BECCD*)g_00DFEF18)->rva002BECCD(pos, 0.0f);
        Rva002D3627Host::Bits bits[2];
        bits[0].f = pos.x;
        bits[1].f = pos.y;
        g_00DFEF18->x = *(volatile unsigned*)&bits[0].u;
        g_00DFEF18->y = bits[1].u;
    }
}

// cl: /MD
// Disp8 dword mask set/clear: __thiscall members with one stack mask argument:
//
//     mov eax,[esp+4] / or [ecx+<DISP>],eax / ret 4                      (10 B)
//     mov eax,[esp+4] / not eax / and [ecx+<DISP>],eax / ret 4            (12 B)
//
// A dword bitmask at a fixed disp8 displacement from `this` gains (`|= mask`)
// or loses (`&= ~mask`) the bits set in the argument. Both siblings below touch
// +0x4C from the same two unclaimed callers, so they are the set/clear pair of
// one flag word. Identity is not recovered: names are derived from addresses.
//
// ?rva001D9709@Rva001D9709@@QAEXH@Z retail 0x001D9709 12 bytes.
// Evidence: 2 unclaimed callers at 0x004332A2/0x0043344B; neighbours are disp
// lea getter 0x001D96F8 and float setter 0x001D972B.
// ?rva001D96FF@Rva001D96FF@@QAEXH@Z retail 0x001D96FF 10 bytes.
// Evidence: same +0x4C word and same 2 callers at 0x0043329B/0x00433444.
class Rva001D9709
{
public:
	void rva001D9709(int mask);

	char m_lead[0x4C];
	int m_flags4C;
};

void Rva001D9709::rva001D9709(int mask)
{
	m_flags4C &= ~mask;
}

class Rva001D96FF
{
public:
	void rva001D96FF(int mask);

	char m_lead[0x4C];
	int m_flags4C;
};

void Rva001D96FF::rva001D96FF(int mask)
{
	m_flags4C |= mask;
}

// BF1 f98983a7d3 WW3D2/w3d_util_convert_shader.cpp and shader.h are the clean
// clear-and-shift expression guide, compiled /O1 /x87 /G7 in discovery.
// Retail65F73..65F85 lies after rowed65F66 RET4 and before rowed65F85.
// It reads/writes raw receiverword0, clears bit3, ORs the full stackword
// shifted left3, and RET4. All eight image sections contain no direct or
// literal reference to this entry. Shader/DepthMask names and enum limits
// are donor facts; the original concrete owner, result and complete layout
// are not proved by this leaf. The address-owned consumed-word view below
// preserves the complete observed operation for every raw32 input, without
// re-declaring ShaderClass or altering its independently unresolved copies.
class Rva00065F73Word
{
public:
    void set(unsigned int value);
private:
    unsigned int word0;
};
void Rva00065F73Word::set(unsigned int value)
{
    word0 = (word0 & ~8u) | (value << 3);
}

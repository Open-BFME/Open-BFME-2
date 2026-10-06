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

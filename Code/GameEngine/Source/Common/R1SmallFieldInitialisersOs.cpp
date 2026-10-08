// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ?Rva000DFB80@@YAPAVR1DwordPair@@PAV1@HH@Z, retail 0x005E6A11 (18B).
// Ported from Open-BFME-1 Code/GameEngine/Source/Common/R1SmallFieldInitialisers.cpp
// (BFME1 0x000DFB80), recompiled /Os by the bfme1_csweep placement.
//
// Same shape as its BFME 1 twin Rva000BEED0 (retail 0x00219701, in
// R1SmallFieldInitialisers.cpp): two ints stored at +0x00 and +0x04 in
// argument order, the pair returned unchanged. The bodies differ only in
// register allocation, and THAT difference is why this one is a separate TU
// rather than a second definition in its twin's file:
//
//     0x00219701  mov eax,[esp+4] / mov ecx,[esp+8] / mov edx,[esp+0xC]
//                 mov [eax],ecx / mov [eax+4],edx / ret        (batched loads)
//     0x005E6A11  mov eax,[esp+4] / mov ecx,[esp+8]
//                 mov [eax],ecx / mov ecx,[esp+0xC]
//                 mov [eax+4],ecx / ret                        (interleaved)
//
// /Os produces the interleaved schedule and the default BFME 2 optimisation
// produces the batched one, so each address needs its own flag set. Putting
// both in one TU makes the pair fail together: whichever flags the file
// carries, one of the two rows then mismatches.
//
// R1DwordPair is a shape name, not a recovered identity: the two stores at
// +0x00 and +0x04 establish two consecutive dwords and nothing more.

class R1DwordPair
{
public:
	int m_first;
	int m_second;
};

R1DwordPair *Rva000DFB80(R1DwordPair *pair, int first, int second)
{
	pair->m_first = first;
	pair->m_second = second;
	return pair;
}
// Clean BF1 9cbfb551fe Common/MidTwoStoreCtors.cpp supplies two-field
// initialization semantics only; donor constructor/class identity is not
// asserted for these target bodies. Actual native ECX receiver/EAX return,
// complete prior-RET to own-RET extents and accessed offsets are independent.
// 1D976E..1D9781 writes raw word00=all ones, float04=1.0f; target BBB8D8
// literal is independently 0000803F. 4689FA..468A04 writes word00=0,
// word04=all ones. Complete class bounds and field purposes remain unknown.
// Ordinary address-owned initialize methods preserve this uncertainty.
// Fixed-field initializer proof; native names remain unknown.
struct Rva001D976EFields {
    unsigned int word00; float value04;
    Rva001D976EFields *initialize();
};
Rva001D976EFields *Rva001D976EFields::initialize() {
    word00 = ~0u; value04 = 1.0f; return this;
}
struct Rva004689FAFields {
    unsigned int word00; unsigned int word04;
    Rva004689FAFields *initialize();
};
Rva004689FAFields *Rva004689FAFields::initialize() {
    word00 = 0; word04 = ~0u; return this;
}

// BF1 9cbfb551fe Common/Q1ConstantFieldConstructors.cpp is the clean
// zero-field/receiver-return semantic guide only. The target bodies are
// independently RET-bounded: 23DC7F..23DC86 writes dword18=0 after RET23DC7E;
// 85524..8552B writes dword28=0 after RET85523. Incoming ECX is returned in
// EAX. Constructor-versus-reset, owner identity and complete bounds are unknown.
struct Rva0023DC7FFields {
    unsigned char unknown[0x18]; unsigned int word18;
    Rva0023DC7FFields *clear();
};
Rva0023DC7FFields *Rva0023DC7FFields::clear() { word18=0; return this; }
struct Rva00085524Fields {
    unsigned char unknown[0x28]; unsigned int word28;
    Rva00085524Fields *clear();
};
Rva00085524Fields *Rva00085524Fields::clear() { word28=0; return this; }

// BF1 9cbfb551fe Common/RTS/Player_resetOrStartSpecialPowerReadyFrame.cpp
// emits the SpecialPowerReadyTimerType constructor, a two-field initialization
// semantic guide only. The target 2AA3B5..2AA3BF follows RET2AA3B4 and stores
// raw word04=all ones BEFORE word00=zero, returning incoming ECX in EAX.
// Original timer/class identity, constructor-versus-reset and bounds unknown.
struct Rva002AA3B5Fields {
    unsigned int word00, word04;
    Rva002AA3B5Fields *initialize();
};
Rva002AA3B5Fields *Rva002AA3B5Fields::initialize() {
    word04=~0u; word00=0; return this;
}

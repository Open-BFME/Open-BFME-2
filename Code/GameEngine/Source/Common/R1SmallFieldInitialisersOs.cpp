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
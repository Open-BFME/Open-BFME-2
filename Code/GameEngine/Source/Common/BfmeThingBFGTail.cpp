// cl: /O1 /MD /arch:SSE
// ?bfmeTailBFG@BfmeThingBFG@@QAEXXZ @0x0025EF23 206B.
// LINK BONUS body for BfmeConv455.cpp: tail init with exact SSE store order that clean C++ reorders (250 vs 206B with extra global reloads).
// Evidence: jmp tail from bfmeGoBFG in BfmeConv455.cpp plus pins plus retail offsets. Inline asm like siblings BfmeConv1440/1463 for exactness.

extern float g_Va00BBB8D8;
extern float g_00BC4DD8;
extern float g_Va00BC74F0;

class BfmeThingBFG
{
public:
	void bfmeTailBFG();
    void rva0025F3F3();
    void rva0025F30DCallView();
    char m_unmodelled0[0x74];
    char m_flag74;
};

void BfmeThingBFG::bfmeTailBFG()
{
	__asm
	{
		xorps xmm0, xmm0
		movss xmm1, g_Va00BBB8D8
		movss xmm2, g_00BC4DD8
		xor edx, edx
		movss dword ptr [ecx + 0x38], xmm2
		movss xmm2, g_Va00BC74F0
		mov dword ptr [ecx + 0x20], edx
		mov dword ptr [ecx + 0x24], edx
		movss dword ptr [ecx + 0x0C], xmm0
		movss dword ptr [ecx + 0x10], xmm0
		movss dword ptr [ecx + 0x28], xmm0
		mov dword ptr [ecx + 0x58], edx
		mov dword ptr [ecx + 0x5C], edx
		movss dword ptr [ecx + 0x34], xmm1
		movss dword ptr [ecx + 0x3C], xmm1
		mov byte ptr [ecx + 0x75], dl
		movss dword ptr [ecx + 0x48], xmm0
		movss dword ptr [ecx + 0x4C], xmm0
		mov dword ptr [ecx + 0x60], edx
		movss dword ptr [ecx + 0x64], xmm0
		movss dword ptr [ecx + 0x68], xmm0
		movss dword ptr [ecx + 0x6C], xmm2
		movss dword ptr [ecx + 0x70], xmm0
		mov byte ptr [ecx + 0x74], dl
		mov byte ptr [ecx + 0x76], dl
		movss dword ptr [ecx + 0x78], xmm0
		movss dword ptr [ecx + 0x7C], xmm0
		lea eax, [ecx + 0x8C]
		mov byte ptr [ecx + 0x84], dl
		mov dword ptr [ecx + 0x88], edx
		mov dword ptr [eax], edx
		mov dword ptr [eax + 4], edx
		mov dword ptr [eax + 8], edx
		movss dword ptr [ecx + 0x98], xmm0
		movss dword ptr [ecx + 0x9C], xmm1
		movss dword ptr [ecx + 0xA0], xmm1
		movss dword ptr [ecx + 0xA4], xmm1
		movss dword ptr [ecx + 0xA8], xmm1
		movss dword ptr [ecx + 0xAC], xmm0
		movss dword ptr [ecx + 0xB0], xmm0
	}
}

// BFME1 full lead5cc75ddda6455c338a5068307e587a793f96d6b3,
// game/GameEngine/Source/Common/BfmeConv802.cpp. Native Ghidra25F3F3/19 calls
// the existing206-byte tail then rowed CameraMarkerList::clear53 with the same
// ECX receiver, and finally clears byte+74. The donor's second free-call
// declaration is replaced with the witnessed zero-argument thiscall protocol.
// Keeping the actual tail definition visible lets VC7.1 prove ECX survives it;
// earlier isolated trials inserted an extra reload between these two calls.
// The existing BFG view models only this observed byte; owner identity and full
// layout remain unknown. An address-qualified call alias binds the same
// receiver to the existing clear body without a private CameraMarkerList view.
#pragma comment(linker, "/alternatename:?rva0025F30DCallView@BfmeThingBFG@@QAEXXZ=?clear@CameraMarkerList@@QAEXXZ")
void BfmeThingBFG::rva0025F3F3() {
    bfmeTailBFG();
    rva0025F30DCallView();
    m_flag74=0;
}

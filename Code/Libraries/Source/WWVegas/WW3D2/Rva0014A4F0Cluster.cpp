// cl: /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /FIbfme_wwstring_teardown.h /Ireference/shims/wwstring_teardown/bfme /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Rva0014A4F0Cluster: the out-of-line colour pack beside mesh.cpp, retail
// 0x00014A4F0, 177 bytes.
//
// The x87 body is the open-bfme-1 dx8wrapper.h Convert_Color sequence, but
// this copy stores its result into the wrapper's ambient-colour slot (VA
// 0x00DEDA24) instead of returning it in eax, and it keeps the colour pointer
// in the caller's frame slot [ebp+8] rather than folding a Vector3 by value.
// That single tail store is the only difference from the matched /O1 out-of-line
// twin at 0x0006E1C0 (Code/.../DX8ConvertColorVector3O1.cpp): the prologue there
// spills only one callee-save register, this one spills ebx/esi/edi in that
// order, which is what /G7 emits when the callee must survive the epilogue.
//
// Identity evidence is target-side. The scale constant is read from VA
// 0x00BC2900, the same float the 121 other pack sites in this image load; the
// truncation control-word dance and the AARRGGBB or/shl sequence match the
// matched 0x0006E1C0 body byte for byte from 0x14A518 to 0x14A58F. The immediate
// enclosing function at 0x0014A710 (called from 0x00174458 with `mov ecx,[ebx]`,
// a thiscall taking no stack argument) inlines the same sequence from its three
// Vector3s at +0x314/+0x318/+0x31C and then stores its packed colour through the
// same global, so this out-of-line body is that helper lifted for reuse.
#define Matrix4x4 Matrix4
#include "always.h"
#include "winbase_shim.h"
#include "vector3.h"

// Target-derived: the global the packed colour lands in (DX8Wrapper::FogColor
// at VA 0x00DEDA24, via the g_Va alias the ledger defines there), and the
// shared 255.0f scale (g_00BC2900 at VA 0x00BC2900).
extern int g_Va00DEDA24;

// The out-of-line Convert_Color(const Vector3&, float alpha) shape. Only
// [ebp+8] (the colour pointer) is read; the alpha operand comes from the
// zero-initialised [ebp-8] local the caller never writes, which retail proves
// by both x87ps clearing that slot and never storing to it afterwards.
//
// The declaration order is load-bearing: retail's prologue clears [ebp-8] with
// xorps/movss and only then loads the shared scale into [ebp-0xC], so alpha must
// be declared before scale to reproduce that instruction order.
void Pack_Ambient_Color(const Vector3& color)
{
    const float alpha = 0.0f;
    const float scale = 255.0f;
    unsigned int col = 0;

    __asm
    {
        sub esp,20                // a, r, g, b and saved FPU control word
        fwait
        fstcw [esp+16]            // save caller control word
        mov eax,[esp+16]
        mov edi,eax
        and eax,~(1024|2048)      // clear rounding-control bits
        or eax,(1024|2048)        // select truncation
        sub edi,eax
        jz skip
        mov [esp],eax
        fldcw [esp]
skip:
        mov esi,dword ptr color
        fld dword ptr[scale]
        fld dword ptr[esi]
        fld dword ptr[esi+4]
        fld dword ptr[esi+8]
        fld dword ptr[alpha]
        fld st(4)
        fmul st(4),st
        fmul st(3),st
        fmul st(2),st
        fmulp st(1),st
        fistp dword ptr[esp+0]
        fistp dword ptr[esp+4]
        fistp dword ptr[esp+8]
        fistp dword ptr[esp+12]
        mov ecx,[esp]
        mov eax,[esp+4]
        mov edx,[esp+8]
        mov ebx,[esp+12]
        shl ecx,24
        shl ebx,16
        shl edx,8
        or eax,ecx
        or eax,ebx
        or eax,edx
        fstp st(0)
        cmp edi,0
        je not_changed
        fwait
        fldcw [esp+16]            // restore caller control word
not_changed:
        add esp,20
        mov col,eax
    }
    g_Va00DEDA24 = col;
}

// The pointer constant is the emission lever only: it forces this TU to emit
// the inline helper out of line, the same trick DX8ConvertColorVector3O1.cpp
// uses for the returned-value copy. It has no runtime effect.
extern void (*const g_bfmePackAmbientAnchor)(const Vector3&);
void (*const g_bfmePackAmbientAnchor)(const Vector3&) = &Pack_Ambient_Color;
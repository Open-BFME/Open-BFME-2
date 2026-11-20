# Texture TU: canonical surface/holder and GUID provider reconciliation

Root outcome: only the seed SurfaceClass prerequisite was accepted (24/24)
and committed as 7c52b0ebb1. The proposed cursor remains blocked: ordinary
7/7 bytes pass, but native header acceptance and the normal merged-object
link guard both predict 547 -> 0 linked bytes because the canonical default
constructor's existing O2/O1 copies differ. The uncommitted cursor patch was
reverted; its original source again passes 7/7 and LINKS 547 -> 547. No donor
was absorbed and no cursor queue entry was retired. See the independent
provider, actual-retail-constructor and default-profile evidence in
20261120-texture-cursor-canonical-link-blocker.md in this directory.

Private verified proposals only. No production source, header, ledger, Git,
claim or register changes by this agent.

## Root scopes before editing

Keep existing file claims for:
- Code/Libraries/Source/WWVegas/WW3D2/texture.cpp
- Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DMouseCursorSurfaceLevel.cpp

Also claim class:SurfaceClass and class:W3DRadarResetSurface. No header is
modified, and no claim to edit a BFME1 reference/submodule is needed. The two
existing canonical headers remain byte-for-byte unchanged:
Code/Libraries/Source/WWVegas/WW3D2/W3DSurfaceClass.h and
Code/GameEngine/Include/Common/W3DRadarResetSurface.h.

## Two exact source patches

seed-surface.patch isolates the legacy imported SurfaceClass spelling as
BfmeDonorSurfaceClass only while loading the initial legacy include cluster,
then includes the real canonical SurfaceClass. No canonical class is copied,
no member/view/layout is invented. Independent seed24/24 stays matched, and
its complete external-code definition/reference footprint is unchanged.

cursor-holder-guid.patch includes the canonical W3DRadarResetSurface header
instead of its private class. The old inline void*-constructor(NULL) cleared
m_surface. The canonical default constructor also clears m_surface, so those
return expressions become W3DRadarResetSurface(). This is required atomically
with the class adoption: changing expressions alone under the old empty
default constructor would be wrong. Existing seven row bodies stay exact.
The emitted old void*-ctor disappears and the canonical inline zeroing
no-argument ctor appears; all other external code and references are unchanged.

The same cursor patch changes its GUID include to:

    #include <windows.h>
    #if !defined(_GUID_DEFINED) && !defined(GUID_DEFINED)
    #include <guiddef.h>
    #endif

This reads two existing provider guards; it defines neither and adds no build
optin. Standalone uses the existing WWLib windows wrapper then the real SDK
guiddef.h. In the merged context, the existing sweep windows.h already defines
GUID, so the incompatible second SDK definition is unnecessary. There is no
alternate runtime path, fabricated type, suppressed error or fallback value.

## Native evidence

texture-guid-provider-results.json: cursor7/7; native seed+cursor composition31/31.
All objects are explicit private build/agent-melee-bfme2-20261120 outputs.
No production compiler settings changed. Additional -Z7 was used only by the
native class-layout diagnostic, which does not alter production source flags.

guid-provider-native-layouts.json and guid-use-api-contracts.json prove:
- Both full _GUID records are struct16,alignment4, no bases/vptr/methods/statics.
- Data1 unsigned long at0 size4; Data2 unsigned short at4 size2;
  Data3 unsigned short at6 size2; Data4 unsigned char[8] at8 size8.
- Template pointer-to-member binding checks validate the exact field primitive
  types and array bound; compile-time sizeof/alignof/offset checks all pass.
- ISurface8, its COM method graph including QueryInterface(const GUID&,void**),
  TexObject and canonical W3DRadarResetSurface contracts agree between contexts.
- Compiler include tracing records SDK guiddef.h only in the standalone path,
  and sweep windows.h as the sole GUID definition provider in composition.
  Provider file hashes are retained, not inferred from include path spelling.

texture-provider-footprint.json proves no changed/added/removed external code
or undefined references for seed->surface adoption or holder->GUID-provider
selection. _IID_TexSurface remains the same static16-byte datum in original,
canonical-holder, final-cursor and composed objects, with no relocations:
2712c385e53d004f9b3af11ac38c18b5, equal to retail RVA0x008E0AD8.
No data row or new symbol owner was added.

## Native production verification/admission sequence for Root

Apply each complete source patch atomically within its existing file claim;
commit each verified prerequisite separately. The prepared texts were produced
with the native header_adopt_lane.swap for the holder plus the proven zeroing
constructor expressions. Do not run a partial source edit between those steps.

After each atomic prerequisite, run the ordinary source build. Then use the
native canonical-adoption verdict, which also checks dependency/link context
and is the only queue-retirement writer (not run by this private worker):

    python3 tools/header_adopt_lane.py accept --class SurfaceClass --header Code/Libraries/Source/WWVegas/WW3D2/W3DSurfaceClass.h Code/Libraries/Source/WWVegas/WW3D2/texture.cpp
    python3 tools/header_adopt_lane.py accept --class W3DRadarResetSurface --header Code/GameEngine/Include/Common/W3DRadarResetSurface.h Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DMouseCursorSurfaceLevel.cpp

The standalone native adopt --apply transformer alone does not make the extra
NULL-to-zeroing-default source-expression repair; accept is appropriate for
the already validated complete source patch. If the native verdict reports an
unknown/link-loss or other refusal, retain that result and repair the evidenced
prerequisite; do not override it or hand-edit a queue/register.

Finally, rerun ordinary tu_skeleton --merge texture.cpp --dry-run, then the
normal merge only for accepted donors. This31-row seed+cursor composition is
private evidence, not a substitute for native merge/link-guard admission or its
ordinary build and find_declared_unmatched pass.

## The other two donors remain blocked

TextureRvaGetters.cpp supplies six opaque getters of a4B pointer-slot view named
TextureBaseClass, while the seed imports the full polymorphic BFME1 texture
hierarchy. Rva00132B83Finish.cpp depends on a different TextureClass view and
Get_Memory_Size. No new API declarations, header copy, source-path move, pin,
flags or layout claim is justified simply to force these into one class.
The legitimate cursor merge may remove one file; the remaining two donors must
stay with their concrete class/ABI blockers. This work adds no native byte
coverage, memory/crash/runtime proof or complete38-row consolidation claim.

# Xfer header adoption: constructor emission and load dispatch

Inspected `49397dc664` on 2026-10-28 under the `class:Xfer` claim. These
are blocked adoption attempts, not regressions or recovered rows. Every
source trial was restored; the six remaining Xfer header-queue entries,
canonical header, function ledger, pins and source paths are unchanged.
The attempt verdicts are in `reverse/re_attempts.log`.

## FamilyDeletingDtors.cpp

The private class uses `Xfer(EmitVtableTag *)` to emit the rowed scalar
deleting destructor `??_GXfer@@UAEPAXI@Z`, RVA `0x0060C8B1`, 28 bytes.
The canonical header has only the real default constructor.

After replacing the private class with `BfmeXfer.h`, none of scalar
`_STL::_Destroy<Xfer>`, a qualified destructor call or `__vecDelDtor(1)`
emits the required scalar body. VC7.1 rejects `__scalarDelDtor` as an
unrecognized member. An unused inline default constructor does not emit
it either.

An out-of-line `Xfer::Xfer() {}` does emit it: the normal build passes all
11 rows, and all 28 retained external COMDAT byte-and-relocation digests
are unchanged. The tag constructor disappears and the real nine-byte
default constructor appears. Its bytes and relocation match the existing
row at `0x000053DE` in System/Xfer.cpp. That is not sufficient: the paired
ordinary preview reports duplicate `??0Xfer@@QAE@XZ` in both units,
predicting losses of 285 and 2,015 census-linked bytes respectively.
The trial is reverted.

The current TU-map entry for `0x0060C8B1` is displaced, with no approved
destination. Its naming hint is `Code/GameEngine/Source/Common/Xfer.cpp`,
not approval to repoint it to System/Xfer.cpp. A correct emission contract
or separately evidenced TU approval is still required; do not add a
compatibility tag constructor or move the row solely to retire this queue
entry.

## BfmeRva00C7B388Xfer.cpp (XferSaveAsText)

The earlier recorded blocker was loss of inline base construction and
destruction. The existing canonical `BFME_XFER_INLINE_DTOR` option addresses
the destructor portion. This trial replaces the private Xfer definition,
retaining its surrounding inline-depth control, with:

```cpp
#define BFME_XFER_INLINE_DTOR
#pragma inline_depth(0)
#include "../../../Include/Common/BfmeXfer.h"
__forceinline Xfer::Xfer() {}
inline Xfer::~Xfer() {}
#pragma inline_depth()
```

All 36 rows match; all 88 retained external COMDAT digests are unchanged.
It adds the same nine-byte default constructor. The paired preview with
System/Xfer.cpp reports the duplicate constructor, predicting losses of
2,447 and 2,015 census-linked bytes. `header_adopt_lane.py accept` refuses
the predicted loss and leaves the queue intact.

Retaining the original constructor's `__declspec(dllimport)` on the
out-of-class definition instead fails with C2375: it disagrees with the
canonical declaration's linkage. Both trials are reverted. Further work
needs a coherent canonical constructor emission contract as well as the
existing inline-destructor option; do not repeat a destructor-only fix.

## GameStateAutoSave.cpp

The private concrete reader needs five overrides to become concrete with
the canonical interface. A trial declared those overrides, used the typed
operator== transfers, and called canonical BeginBlock/EndBlock/SkipBlock
through the base view. The two data rows pass, but
`getSaveGameInfoFromFile` (`0x002DEEC3`) grows from 497 to 500 bytes.
Retail calls `0x0060C629`, `0x0060C469` and `0x0060C6F6` directly; the trial
dispatches through virtual slots 5, 6 and 7 (`+0x14`, `+0x18`, `+0x1C`).
The parent mismatch also prevents a scoped EH-funclet verification.

The lowercase Xfer-owned block providers in xfer_load.cpp need their
concrete reader identity reconciled before these calls can use the
canonical overrides and preserve retail dispatch. This is a class/provider
prerequisite, not permission to pin a second identity at those addresses.
The source is restored exactly.

## Verification and remaining scope

After restoration, a combined normal build passes 78/78 function rows in
the three trial sources, their two data rows, 48 literals plus five empty
string references, and three named imports. The frozen-source check passes
with FamilyDeletingDtors' original seven unclaimed emitter definitions.
`git diff --exit-code -- Code/ reverse/header_queue.tsv` is clean.

The combined ordinary preview of the three restored sources and Xfer.cpp
reports four of four LINKS, retaining 7,244 authored bytes against index
`41c28839bf` (2026-10-28 11:08). This is a preview, not a new census or a
linked-byte gain. [Object comparisons and restored-source hashes](xfer-header-blockers-20261028-codex.json)
preserve the bounded evidence. Local raw logs are under
`build/xfer-header-20261028-codex/`; the findings above do not depend on
those untracked logs remaining available.

The other queued Xfer sources were not edited. PersistentStorageThread
still needs its concrete reader interface, XferSaveOpen its stream identity,
and xfer_load its block-provider identity and protected transfer state.
The prior shared-obstacle entries remain open.

Before the header work, the default picker served
W3DMouse_releaseD3DCursorTextures.cpp at `0x00098F52`. A paired preview with
the existing Render2DSentenceDrawBFME2.cpp repair makes that consumer LINKS
(121 authored bytes); the provider itself remains blocked on its unproven
Add_Quad copy, as already documented by LINK-132/LINK-133. No mouse change
was necessary, and that scope claim was released.

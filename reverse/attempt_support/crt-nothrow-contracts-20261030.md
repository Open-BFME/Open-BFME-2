CRT header exception contracts, 2026-10-30
========================================

Inputs: BFME2 4bf903241756abcd19dd7a73cf78fc87ca1b6904 and retained
BFME1 1d5131d3f193cdf01a99da66ccd6828639585650. Both trials below use
the normal ./build.sh source verifier. Both sources were restored.

Texture constructor
-------------------

Code/Libraries/Source/WWVegas/WW3D2/Rva00131BE5Ctor.cpp declares the
one-argument operator new with throw(). Replacing that declaration with
the Microsoft <new> header adds `mov byte ptr [ebp-4],2` before allocation
in the 142-byte constructor at 0x00131B57. The real header declares
operator new(size_t) with _THROW1(std::bad_alloc), so this is an exception
contract difference, not a drop-in change. No alternative allocation
overload or ABI substitution was attempted.

AI picker masks
---------------

Code/GameEngine/Source/GameLogic/SkirmishAI/AISpecialPowers/AISpecialPowerPickers.cpp
declares memset with throw(). Replacing it with <string.h> leaves 15 of
16 ordinary code rows byte-exact, but changes the 568-byte
AISpecialPowerCaptureBuilding::shouldActivate at 0x005DA109. It inserts
`mov byte ptr [ebp-4],4` at +0x102; later branches shift by four bytes.
The strict funclet verifier correctly refuses scoped $L1816 because its
same-source parent is not byte-exact. This is not a verifier false reject.

Read-only inspection of the existing compiled object confirms all other
ordinary rows have exact bytes, no masks and no unresolved relocations.
eh_verify.py reports all 12 parent EH graphs EXACT, which alone does not
prove parent code bytes. Marking both the mask's zeroing constructor and
clear() with throw() still fails the strict source check. That trial was
also restored. The pinned Vc7/include/string.h declares memset without an
exception specification; moving a guarantee to an inlined wrapper did not
make this a safe migration.

Retain these local contracts until a clean source change preserves the
full parent and its EH placement. No header-queue retirement, byte gain,
baseline edit or new hatch is claimed.

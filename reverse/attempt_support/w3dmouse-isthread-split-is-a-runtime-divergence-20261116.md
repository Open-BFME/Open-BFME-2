# `isThread` is split across two storages, and nothing writes the shared one

`next_work.py --claim --tier data` serves W3DMouse.cpp as `wrong-name _mutex`
@ 0x009E4B34. Two earlier seats recorded `blocked` on it, both correctly: the
`_mutex` repair itself is done, and what refuses the retirement is a *different*
finding, `duplicate-def _isThread` @ 0x009E4B30.

This note does not repair that. It records what the earlier verdicts and the
data row's own evidence do not say: the split is not a naming compromise, it is
a live behavioural divergence from retail that a complete byte match hides.

## What the objects say

    W3DMouse.obj                 _isThread   STATIC    (sec542 +4648)
    W3DMouseInitW3DAssets.obj    _isThread   EXTERNAL  (sec3 +0)

Two definitions, two storages. The static one does not collide at link time, so
nothing refuses it; it simply means each unit reads a different byte.

## Nothing writes the external one

Every write to `isThread` in the tree is in W3DMouse.cpp, where the variable is
file-static:

    W3DMouse.cpp:760   isThread=TRUE;     (setRedrawMode, entering thread mode)
    W3DMouse.cpp:763   isThread=FALSE;
    W3DMouse.cpp:859   isThread=FALSE;    (reset)

Every read of the *external* one is in W3DMouseInitW3DAssets.cpp:

    :456   if (isThread)
    :540   if (!isThread)
    :795   if (!isThread)
    :803   showTooltip && rva001EDE26() && !isThread

So in a real image all four take the "not the mouse thread" branch
unconditionally, whatever `setRedrawMode` was given. In retail there is one
variable at 0x009E4B30 and these reads see what `setRedrawMode` wrote.

The bytes cannot show this. A `DIR32` to `_isThread` is the same instruction
either way; only the address the linker picks differs. Both units byte-match
today, and the divergence is entirely in which storage the reference binds --
which is exactly, and only, what `data_check` reports.

(`isThread` also appears in ten GameSpy units. Those are `isThreadRunning`
member functions, unrelated; the two W3DMouse units are the only references to
this variable.)

## Why neither spelling can fix it, and what the bytes prove

The data row for 0x009E4B30 already records the constraint: W3DMouse.cpp must
keep its copy file-static because "an external one there reorders
W3DMouse::reset's store". That is the right observation, and it settles the
direction:

> an external definition constrains the store, a file-static does not, and
> retail's order is the **unconstrained** one. So retail's `isThread` had
> internal linkage -- and a unit that reads an internal-linkage variable is the
> same translation unit that writes it.

Retail's `W3DMouse::initW3DAssets` was therefore in the same TU as
`W3DMouse::reset`. `reverse/tu_map.csv` already agrees from other evidence: 12
of W3DMouseInitW3DAssets.cpp's 16 rows are **approved** into
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DMouse.cpp` as their TU.
This is a second, independent witness for that grouping, from linkage rather
than from address order.

That also closes off the spelling repairs, so no later seat should retry them:

- external in W3DMouse.cpp -- reorders `reset`'s store, breaks the byte match
- file-static in both units -- still two storages, still two definitions, and
  the asset unit's reads are still never written
- a shared accessor -- a new out-of-line body retail does not have

The one repair is the TU merge, and that is where the earlier seats left it:
the dry run refuses on `C1083 d3d9.h` in the merged TU and on `adopt_first` of
nine classes (AIUpdateInterface, GameInfo, HotKeyManager, SidesList, ...).

## State of this unit's data debt

`data_check` on the current object reports **one** finding, and it is not either
baselined key:

    duplicate-def  _isThread  0x009E4B30        <- the live one, merge-only
    wrong-name     _mutex        0x009E4B34     <- in the baseline, NOT reported
    wrong-name     _threadMutex  0x009E5DA0     <- in the baseline, NOT reported

Both baselined keys are already fixed. They stay only because
`repair_queue.py retire data` will not retire a line while the scan finds
something new, which is the gate working as designed -- not a false reject.

## Reproducing

    ./build.sh Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DMouse.cpp
    python3 tools/data_check.py Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DMouse.cpp
    grep -rn "isThread[[:space:]]*=" --include=*.cpp Code/     # every write

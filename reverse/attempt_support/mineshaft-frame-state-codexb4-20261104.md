# Mineshaft final frame state trial, 2026-11-04

Inspected revision: `39f4309a09`. Approved destination:
`Code/GameEngine/Source/GameLogic/Object/Behavior/MineshaftPortalBehaviour.cpp`.
Related obstacle: LINK-300. Trial source was restored; no source paths, rows,
hatches, aliases or debt keys changed.

## Hypothesis and trial

Composition emits the complete seed body group before the link-step donor.
The seed's existing `#pragma optimize("", on)` therefore resets the frame
state before the donor is emitted. Merely moving that reset past a
`tu-skeleton` placeholder cannot affect composition: markers are regenerated.

The trial moved the existing framed-method block (starting at
`MineshaftPortalBehaviour::rva00372DFA`) to the seed's end and moved the existing
reset before that block. The late default-frame functions stayed before the
framed block. No pragma was added. This leaves the seed in `/Oy-` state so a
following donor could inherit it.

Sanctioned `./build.sh` passed all 38 code rows, the data row, string and float
checks. `find_declared_unmatched.py` also passed. The current-object link
preview nevertheless changed from 2,881 to zero linking bytes. Blocking changes:

- `_STLP_alloc_proxy<_Rb_tree_node<int> *, ...>::deallocate` differs from the
  first copy in link order.
- `_STLP_alloc_proxy<ScienceType *, ...>::deallocate` likewise differs.
- The signed-key `_M_find<int>` for the map of vectors of int differs from the
  kept copy without retail proof.
- The selected int-tree `erase(iterator)` is no longer retail's definition.

Numerous unreferenced template diagnostics also grew frame prologues. This
supports the existing comment that delayed template instances need the final
reset. Byte-exact rowed functions alone do not validate a frame-scope move.
The planned merge trial was not run after this link refusal.

## Restoration and next check

Restored the exact pre-trial source, then rebuilt it through `./build.sh`:
38/38 code rows and the data row pass, with the declaration check clean.
`link_check.py` again predicts LINKS, 2,881 -> 2,881 bytes. Both previews use
the 2026-11-04 20:47 census index at `f12552d0a7`; no new census is claimed.

A viable composition must keep `/Oy-` for the link-step body AND reset delayed
template emission to the seed's default frame state. Do not repeat the final
`/Oy-` arrangement without addressing those provider bindings. The allocator
specialization, destructor subsystem include, and manager native-vtable
prerequisites remain separate blockers.

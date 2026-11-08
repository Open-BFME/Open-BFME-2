# Module constructors adopt canonical Thing, 2026-11-08

DrawableModuleCtor.cpp and ObjectModuleCtor.cpp remove their five-slot and
three-slot private Thing declarations and include the canonical header.
Their null-preserving access now uses its existing AsDrawable/AsObject
friend helpers. A TU-local force-inline forward declaration preserves the
retail inline call sites, including Thing dispatch offsets +0x10 and +8.
No shared header, class/member identity, compiler flag or source path changes.
The helper declarations do not define a second class or change its access.

All three existing rows and both parent EH graphs pass normal verification;
both files remain unfrozen. header_adopt_lane.py accept passes for each and
retires exactly two Thing rows from header_queue.tsv. Strict preparation
passes for the two modified sources and the native AsObject/iterator owners.
All retained code COMDAT bytes, relocations, flags and selection policies,
named data allocations, external definitions and undefined references remain
equal. Normal paired staged-peer checking passes; ordinary current-object
preview conserves LINKS/226 authored census bytes at d171e84869.

New implicit output is accounted for, not called exact: each TU emits a
framed 34-byte vector-constructor iterator and a framed 20-byte friend
helper outline. These differ from the native iterator at 0x00001423 and
AsObject at 0x00306A5E. They introduce no undefined reference and displace
neither native provider in the cached population with both candidates
overlaid. In census order, ATL's iterator owner and Module_AsObject precede
the candidates. In the real link's default path order (exit_link.py),
AudioSettingsConstructor's iterator and Module_AsObject precede them. These
explicit providers are strictly current and their complete native bytes
and relocations are checked; final-proof.json records hashes, policies,
flags and order. AsDrawable has no provider, external consumer or export in
the cached index, and the candidates add no external reference to it. Its
new outline is not claimed as a recovered native body.

The initial ordinary inline declarations outlined the helpers and failed the
parent bytes. A source-line /Ob2 trial is not an effective flag override;
an explicit private /Ob2 trial also failed. No flag override was admitted.
The local force-inline declarations preserve the existing region flags and
solve both call sites together.

This clears two header-adoption debts only. The provider proof is bounded
to the d171e84869 population and current explicit receipts; broader current
consumer closure, full real-link/runtime validation and retail TU recovery
remain open. The earlier Module consolidation attempt's seed-header slot
failure does not apply to this verified canonical-header adoption, and no
merge or generated pass-test queue is edited.

Published as b38a3024b4; first attempt landed in 50.8 seconds. Required
row/EH/scoped-DIR32 checks pass after rebase. Broader link audit remains
INCONCLUSIVE: index d171e84869 versus outgoing base
195accef7eb242f0247ea449bf48c6d07435daa7; Common/AICowerState_onEnter.cpp
lacks a current receipt. AIBaseBuilder now has a local current receipt, but
this does not change the earlier recorded audits or establish image closure.

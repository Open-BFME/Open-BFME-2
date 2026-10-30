# AssaultTransportAIUpdate composition prerequisite

Base: `1184c0c8e20d`. Scope: the existing AssaultTransportAIUpdate.cpp seed
and the approved pool-key donor; this prerequisite moves no source paths.

## Target facts

Native `0x0048F45C` loads ObjectID at argument +0x74 and stores it at
receiver +0x4C. The constructor at `0x0048F5A3` installs the secondary table
`0x00C4CC88` at complete-object +0x3E4; that table selects this method.
The store therefore reaches complete-object +0x430. These placements are
target evidence, not an inference from the donor's field offsets.

## Donor facts and bounded reconstruction

The official Zero Hour AssaultTransportAIUpdate header declares the
AIUpdateInterface and AssaultTransportAIInterface bases, with beginAssault
in the latter. That source is a structural lead, not a BFME 2 header.
The old seed included that broad header stack and collided with the separate
pool-key definition. The replacement is a TU-local partial view using the
native offsets above. It declares only the slots needed by these bodies;
the full AIUpdateInterface contract, primary slot inventory and complete
AssaultTransportAIUpdate layout remain open. No sizeof claim is made.

## Verification

- `find_declared_unmatched.py` passes before and after; `./build.sh` passes
  both existing seed rows, including string/float/import references.
- `class_layouts.py` places the secondary base at 0x3E4 and the target field
  at 0x430. All three retained external COMDAT fingerprints (beginAssault,
  the existing comparison helper, Object::getID) are unchanged; none added.
- The broad headers previously emitted 549 external COMDATs; the narrowed
  seed emits three. Every one of the 546 removed names has another provider
  in the published index. This is provider-presence evidence, not proof of
  every consumer's selected provider.
- Strict two-source preparation passes 5/5 rows, including the pool-key EH
  funclet mapping ($L306 renumbered to $L310). Ordinary preview retains
  2/2 LINKS, 75 + 79 = 154 authored bytes, against the 2026-10-30 10:11
  index at `12b9e7a7c0`.
- The staged outgoing audit is INCONCLUSIVE: the index predates this base,
  and affected consumer Common/0CreateAHeroManager21FE49.cpp lacks a current
  receipt. Full consumer loss/selection checks remain unverified. Carry the
  removed header providers and their consumers into the next scheduled
  census. No census gain or debt retirement is claimed.
- No seed/pool-key entries occur in the gate, code-identity, data-check,
  header or ms-header registers, hatch register, or data ledgers inspected.
  No protected register, shared header, canonical class or pin is changed.

The supported merge probe must be refreshed against this seed. The remaining
donors still require reconciliation of their private views and declarations;
the mixed-source donors require their own supported splits. The prior blocked
merge record is retained as history, not treated as a new matching regression.

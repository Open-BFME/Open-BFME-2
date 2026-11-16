# Native consumer repairs after alias withdrawal

Measured baseline: authoritative real link 43956924845 at 1ffed447, 29
unresolved symbols, no image. The local repairs below await a new full link.

## String copies

- BfmeConv1399.cpp: row 000B6D4B, 64 bytes, copies StringBase<char> at +0.
- BfmeConv526.cpp: row 004D04FF, 31 bytes, copies StringBase<char> at +4.
- Both retail calls target the rowed constructor at 000365F0; use the existing
  canonical header's BFME_STRINGBASE_PUBLIC_COPY declaration. The containing
  views retain raw storage, offsets and size. MSVC's explicit constructor-call
  syntax starts the string lifetime without adding automatic destruction to
  these footprint views; the canonical header already uses this idiom.
- Rejected placement-new trial emitted null tests and EH code absent from the
  target; reverted completely before verification.
- Official build: 2/2. EH: no graphs, no missing objects. Scoped link_check
  with StringBaseNarrowCopySet.cpp: 3/3 clean, provider 197 bytes unchanged,
  consumer contributions 64 and 31 bytes. New-variants check passes.
- The published census used by that preview is 0534e78db3 at 16:28 and warns
  of four changed source paths. No fresh global-link or runtime result claimed.

## Next

Verify the radar consumer against the existing native predicate, then measure
the complete image and test Windows menu, skirmish and selection decals.

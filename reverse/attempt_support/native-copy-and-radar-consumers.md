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

## Radar predicate

- Player_Radar.cpp calls the rowed int-returning predicate at 002AA04C
  instead of the withdrawn bool interface. That native body returns 0 or 1;
  explicit unsigned-char narrowing preserves the four retail AL tests.
- The helper view is declaration-only and introduces no provider or pin.
  The old bool declaration is removed from this consumer.
- Official build: 5/5 (657 bytes), EH: 4 EXACT. COFF has exactly four
  relocations to ?rva002AA04C@Rva002AA04C@@QAEHXZ, each followed by test al,al;
  the missing bool symbol is absent. New-variant check passes.
- Provider-inclusive verification: unchanged Player.cpp passes 65/65 code
  rows and two data rows. Both current objects link in scoped preview,
  2489 -> 3146 own bytes. Logs radar-provider-verify.log and
  radar-provider-link.log under build/decal-diagnostic. Census remains stale.

## Next

Measure the complete image and test Windows menu, skirmish and selection decals.

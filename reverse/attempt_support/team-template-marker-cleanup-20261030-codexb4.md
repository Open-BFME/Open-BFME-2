# TeamTemplateInfo destructor exemption retirement

Base inspected: `734530a648ba63a72c2149efc21eabf24934dca1`.
Source: `Code/GameEngine/Source/Common/RTS/TeamTemplateInfoDtor.cpp`.
Published preview index: `85f6b7f40c`, 2026-10-29 15:08.

The default picker claimed the destructor at `0x0039EAED` and its source.
Its census unresolved-string-destructor finding has already been repaired by
`83cac55f09` (LINK-141): the +0x118 array uses AsciiString rather than a
body-less placeholder. The current-object preview confirms LINKS for this
unit's 236 authored bytes. This is confirmation of an existing repair, not
new linking credit or a census result.

The destructor's 236-byte body and all 13 associated handler/cleanup rows are
already matched. The source still carried a present-unmatched exemption for
that same destructor. Remove only that comment and its exact shrink-only
hatch-register key. No C++ body, declaration, flags, ledger row, pin, global,
source path or other hatch allowance changes.

Verification:

- The whole source passes `./build.sh`: 14/14 rows, plus source ownership,
  string, float and import checks. The twelve compiler-label rows remain
  verified through the parent's native EH graph despite label renumbering.
- `find_declared_unmatched.py` passes without the old unclaimed-definition
  note, so the destructor no longer depends on the exemption.
- `eh_verify.py` reports one EXACT graph, zero baseline exemptions and no
  missing object.
- `link_check.py --prepare-current` passes all 14 rows and writes a strict
  current provider receipt; it changes no census, index or status.
- The final ordinary current-object preview retains LINKS for 236 authored
  bytes against the same index.
- The staged hatch gate credits exactly one retired present_unmatched key:
  register total 3663 -> 3662. Unrelated register allowances are preserved.

Census confirmation of LINK-141 and complete Team.cpp composition remain
separate work. No maintainer-only measurement runner was started.

The staged-tree outgoing batch audit is INCONCLUSIVE: the census index predates
base `734530a648`, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry that consumer and the destructor provider into the next scheduled
census. Complete consumer selection/loss verification remains unproven.

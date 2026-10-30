# Chat PlayerInfo view reconciliation

Base: `1d0f5dab00d6dabc36987fb491c20eea15b45ea1`. The default picker
claimed the five clean files assigned to
`Code/GameEngine/Source/GameNetwork/GameSpy/Chat.cpp`. The current in-memory
TU plan approves 49 rows, with 19 in three mixed sources excluded from merging.
No source, row, pin or compiler override moves in this prerequisite.

The two map donors, `Common/Open2Rec4F1120MapFind.cpp` and
`Common/Open2RecChain146.cpp`, now use the same PlayerInfo declaration as
`GameNetwork/GameSpy/GameSpyInfoAddChat.cpp`: three AsciiStrings, ten trailing
dwords, the existing field names and unsigned flags at +0x18. The declaration
also names the external destructor. The existing pin binds it to the rowed
68-byte native destructor at 0x001EF50E in RvaAsciiStringTripleDtors.cpp.
This suppresses Open2RecChain146's redundant compiler-generated destructor.
The addChat view only changes `Int` spelling to `int` to make the declarations
identical. These are existing target views and names; no donor layout or
new BFME source attribution is asserted.

Verification:

- Normal before/final builds and strict preparation pass all 28 function
  rows across the five files, the GameSpyColor data row, two string references
  and twelve funclet bindings. Frozen-source checks pass. EH verification is
  EXACT for all five parents with EH data.
- The [object comparison](chat-playerinfo-views-20261030-codex4.json) finds
  all 687 retained external COMDAT copies unchanged. Only the duplicate
  `??1PlayerInfo@@QAE@XZ` COMDAT disappears (688 -> 687). Strong, undefined,
  weak and COMMON facts are unchanged; external symbol records lose only
  that definition. Retained reference roots and edges are unchanged.
- Four objects have identical non-debug sections and directives. The chain
  object loses the 68-byte destructor, its 29-byte handler and 44-byte EH
  table; its SafeSEH section shrinks by one handler entry. Its remaining
  sections and directives are identical. No caller bytes or bindings change.
- Ordinary combined preview retains 5/5 LINKS and 1,443 -> 1,443 authored
  bytes against index `12b9e7a7c0` (2026-10-30 10:11). The seed's existing
  two unreferenced helper diagnostics remain. This is not a census result.
- The scoped staged batch audit exits 2, INCONCLUSIVE: the index predates
  the outgoing base and affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a
  current receipt. Full affected-consumer selection and loss checks remain
  unverified. Carry these five providers and their wider consumers into
  the next scheduled census. No linked-byte, debt-register or source-file
  count gain is claimed.

Remaining consolidation prerequisites:

- The supported merger accepts no donors under the seed's existing empty
  override. It reports losses of 4, 5, 2 and 6 rows respectively in
  Open2Rec4F1120MapFind, Open2RecChain146, Rva001EF552Chat and
  GameSpyInfoAddChat. No merged file or ledger change is retained.
- A default flag scan passes the four donors at `/O1 /arch:SSE /G7`, but
  the seed's default `/O2 /G7` fails equal_range at 0x0061F840 (83 bytes).
  Giving the seed `/O1 /G7 /arch:SSE` loses all three rowed tree helpers:
  equal_range becomes 39 bytes, upper_bound becomes 14 bytes and
  _M_upper_bound becomes 37 instead of 38 bytes. The original seed and flags
  were restored and all four seed rows reverified. Solve code generation
  without extra pragmas, overrides or pins before retrying the merge.
- The automatic PlayerInfo union selected a signed flags field and failed
  one addChat row. That trial was reverted; retaining the established
  unsigned flags passes all 21 affected rows.
- The seed still includes the peerdefs shim's two-string PlayerInfo and
  donor GameSpyInfo/interface views. This change reconciles the three clean
  donor views only; header and other class compatibility still need proof
  after the flag barrier. Mixed files must remain excluded until split by
  their own supported lane.

Scratch evidence: `build/chat-consolidation-codex4-20261030/` contains the
five before objects, comparison scripts/results, EH results and staged audit;
`build/flagscan/chat-seed-default-codex4.jsonl` records the default flag scan.

Reference freshness: the local marker is over 72 hours old. Official BFME 1
master was fetched without recursion at
`219f8937e21d3f8c6f089ad4d14ee6e1de5c7d06`. The reference file scope is held
by another worker, so the committed, clean and previously verified
`1d5131d3f193cdf01a99da66ccd6828639585650` remains in use
([verification](reference-1d5131d3-20261030.md)). No successful freshness
stamp or newer-input verification is claimed.

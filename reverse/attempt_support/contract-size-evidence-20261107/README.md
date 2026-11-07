# Size evidence for the eight contracts the extent check queues — and why size alone is not the fix (2026-11-07)

148e40a3d9a queues a contract size that two retail facts contradict, which makes
`header_adopt_lane` refuse to generate that class's header. Eight classes are newly in
that position. This is the evidence for each, and a finding that changes what should be
done about them.

## The finding: correcting the size would make things worse

`generate()` writes the class line from `contract["bases"]` and the members from
`contract["fields"]`. Both are nearly empty in all eight:

| class | recorded size | fields | bases recorded | bases the header declares |
|---|---|---|---|---|
| FXShaderSetup | 8 | 2 | none | RefCountClass |
| WorldHeightMap | 40 | 3 | none | RefCountClass |
| LivingWorldBattle | 60 | 1 | none | Snapshot, Rva00330757Member, LivingWorldBattleListener |
| LivingWorldLogic | 180 | 1 | none | - |
| GenBase009EB7D0 | 4 | 1 | none | - |
| ImageCollection | 1 | 0 | SubsystemInterface | SubsystemInterface |
| WindowVideoManager | 1 | 0 | SubsystemInterface | SubsystemInterface |
| Team | 60 | 1 | Snapshot | Snapshot |

ImageCollection records no fields at all for an object its own canonical header asserts is
0x18 (`Image.h:86`, `typedef char ImageCollectionSizeCheck[sizeof(ImageCollection) == 0x18
? 1 : -1];`). WorldHeightMap records three fields for a 73,968-byte object. Five of the
eight record no bases while their headers declare them.

So a regenerated header would be a shell: a couple of members, often no base clause, and
nothing like the layout the hand-maintained header on disk already carries. **Patching
`size` would clear the queue item, re-enable generation, and let the lane replace a good
header with that shell.** That is worse than staying blocked, so no contract was changed
here.

Read the other way, this is reassuring about the check: these contracts could never have
produced a correct header, and the queue item surfaced that rather than causing it. The
block is right, and it should stay until fields and bases are recovered - which is the
evidence pipeline's job (retail access, vtables, views), not a hand patch.

## The size evidence, for when the contracts are repaired

Gathered read-only, one reviewer per class; `evidence.json` holds each full record with
addresses and caveats. Sizes are proposals, not applied.

- **WorldHeightMap**, 40 -> 73968 (0x120F0), high. W3DTerrainVisual::load (0x0009213F)
  pushes 0x120F0 at 0x00092193, calls operator new, then the stream constructor at
  0x000921AB. Constructor writes reach 73940, inside it. No derived class.
- **FXShaderSetup**, 8 -> 52 (0x34), high. Two retail allocations before an FXShaderSetup
  constructor each request 0x34 (0x00152C64 with the ctor call at 0x001525FB; 0x0015B129
  with the copy ctor at 0x00152DE9), and the header's own fields sum to 0x34.
- **LivingWorldBattle**, 60 -> 64 (0x40), high. The deserializer at 0x002100E6 pushes 0x40
  at 0x00210143 before the constructor 0x003F6A3A; the last constructor write is the
  4-byte field at +0x3C, ending exactly at 0x40.
- **LivingWorldLogic**, 180 -> 380 (0x17C), medium. The constructor at 0x002B93B3 writes
  last at +0x178, giving 380, and the single allocation observation is 0x17c. The
  allocation site is cited only in the header comment, not in the ledger.
- **ImageCollection**, 1 -> 24 (0x18), medium, but corroborated by the header assertion
  above. The SubsystemInterface base spans [0,12] and the map at +0x0C ends at 0x18.
- **WindowVideoManager**, 1 -> 36 (0x24), medium. The header records allocation 0x0031CFCD
  requesting 0x24 and calling the constructor 0x0053F85C at 0x0031CFE2; constructor writes
  reach 0x21. The allocator is not in the ledger, so it is not cross-checked.
- **GenBase009EB7D0**: **ambiguous, and correctly so.** The class is abstract - slots 0-3,
  5-7, 13-14 are pure - so the single 0x14 allocation must be sizing a derived object, not
  this base. Its recorded 4 is still wrong (the constructor writes reach 20), but an
  allocation cannot settle a base's size. Left alone.
- **Team** was not examined: no `class:Team` claim exists, but two files in its scope
  (Team.cpp, TeamGetControllingPlayer.cpp) are held by another worker, so the class claim
  is refused. Its own evidence is already recorded in
  `reverse/attempt_support/class-contract-size-vote-20261106/`.

## What to do next

Repair these contracts properly rather than patching the size: recover fields and bases
through the evidence rules, then let the size follow. Until then the queue item should keep
refusing generation, and the hand-maintained headers on disk remain the better source.

## The missing bases are not special to these eight

Measured across every registered class that has both a contract and a readable header (565
of them): **121 contracts record no bases while the header they are paired with declares
some.** The mirror case - a contract claiming a base the header does not - happens once.
443 agree, or are both empty.

That asymmetry, 121 against 1, is the useful part: it says the contracts are the side
missing the information, not the headers. The cause looks like the same shape as the size
and the class key. `decide()` takes bases from `retail_bases` when retail's own
constructors prove them, else from the Zero Hour header, else from a plurality of the
private views - and a private stand-in almost never declares the base, so the vote settles
on none. AIPlayer records 28 fields and no base while its header declares Snapshot;
AudioManager records one field and no base against SubsystemInterface and Snapshot.

A caution on how to fix it, because the obvious route is circular: the canonical header is
generated *from* the contract, so a header cannot in general be cited as evidence for the
contract. For these 121 the header is plainly the richer artefact, but that is an
observation about their history, not a licence to copy headers into contracts. The
non-circular evidence is `retail_bases` - base constructor calls and vbtable stores in the
class's own matched constructors - and it returned nothing for these, which is the real gap
to close.

Nothing was changed on the strength of this measurement.

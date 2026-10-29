# EmotionTracker constructor: canonical ObjectModule

Inspected base: `025f81f0ca`. Published preview index: `85f6b7f40c`,
2026-10-29 15:08 UTC. Claimed constructor `0x004B21B9` and its file.

The picker reports a primary-vtable COMDAT conflict. Ordinary preview reproduces
it against the published index: the constructor does not link, with
`??_7EmotionTrackerUpdate@@6BObjectModule@@@` differing from the destructor's
first copy. This is distinct from the older missing UpdateModuleInterface
provider recorded in the obstacle register.

Replace the constructor's private ObjectModule with the existing canonical
header, already used by EmotionTrackerUpdateDtor.cpp. The header owns an
`Object *` at +8; the constructor's existing Thing view reads the native object
ID at +0x74 through an explicit const cast. No shared header changes and no
new private class, pin, alias, ledger row or source move are needed.

Verification:

- `./build.sh` verifies constructor 5/5 and destructor 6/6 rows; the 420-byte
  constructor extent is `[0x004B21B9, 0x004B235D)`. The edited constructor
  also passes the frozen-source check.
- `eh_verify.py` verifies both parent graphs EXACT. The normal verifier resolves
  the constructor's three renumbered compiler cleanup labels through that graph.
- Object comparison preserves 37 existing constructor COMDAT fingerprints,
  removes none, and adds only the five inherited empty Module/ObjectModule
  methods. Its one changed COMDAT is the primary vtable, 4 -> 40 bytes,
  fingerprint `a4027b0b0123` -> `9a83cc86e27a`; the latter equals the freshly
  verified destructor's table, including every relocation.
- Ordinary paired preview reports constructor LINKS, 0 -> 430 authored bytes;
  destructor LINKS, 159 -> 159. Combined preview is 589 authored bytes.
- A subsequent `link_check.py --refresh` refreshes 3,004 stale ledger units
  and 96 objects rebuilt since the index; the constructor still LINKS for
  430 authored bytes. This remains a preview, not a recorded census.
- `link_check.py --prepare-current` verifies both explicit providers with strict
  receipts, all 11 rows exact. `header_adopt_lane.py accept --class ObjectModule`
  passes and retires exactly one row from reverse/header_queue.tsv.

These tables still inherit pure Snapshot/name-key slots in both local derived
views. Equal compiler tables do not prove the complete retail derived table
or its dispatch behavior; recovering the concrete overrides remains separate
work. The existing Thing header prerequisite remains queued.

Full consumer verification also remains pending. The census index predates the
inspected base, and the provider's affected cohort includes
Common/0CreateAHeroManager21FE49.cpp without a current strict receipt. The push
batch audit must retain that limitation; carry this constructor provider and
its affected consumers into the next scheduled census. No census-linked-byte
gain or full consumer closure is claimed.

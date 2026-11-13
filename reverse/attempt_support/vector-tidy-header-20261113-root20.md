# Rva00565A42 queued consumer adoption

The three queued consumers now include the existing canonical header instead
of private declarations. Each declares `struct Rva0052BF9BElem;` first, as the
existing adopters already do: the generated header uses this pointer type but
does not declare it. The generated header and its contract are unchanged.

## Evidence and scope

- The two insert users only cast a vector address and call the no-argument
  `void rva00565A42()` member. They do not access the private field types they
  formerly declared. The overflow-family user also only calls that member.
- The canonical prefix is two 32-bit pointers; the consumed vector storage has
  a capacity pointer beyond that prefix. No new allocation, embedding, by-value
  use, or assertion about the complete container or element identity is added.
- The shared provider's 20-byte virtual-destructor element stride agrees with
  these consumers. This does not identify their distinct element types as one
  original source class or recover the worker's real name.
- All three sources have no remaining defined-unmatched functions according to
  `find_declared_unmatched.py`. Existing ScoreKeeper element naming and unrelated
  overflow-family link obstacles remain separate.

## Verification

The original and adopted three-file cohorts both pass `./build.sh`: 61/61
function rows. All 523 external COMDAT identities are unchanged, comparing
section contents and relocation identity with `link_census.comdat_bodies`.
The comparison is saved in the accompanying JSON record.

Strict receipt preparation passes for all three sources. The owning
`header_adopt_lane.py accept` passes each source and retires all three queue
entries. The explicit scoped preview preserves 9002 linked bytes: 242 in each
insert file and 8518 in the overflow-family file. Its census index is old
(aa7acf764d, 2026-11-12 19:19), so these per-source preservation checks do not
establish a current whole-image result or remove existing bridge scaffolding.

Current authoritative real-link evidence is run 43414575861 at commit
10efe4859ee37651bd6b7fdcc15d915325c9b9fa: 37 unresolved, zero duplicates, no
image; 469 initializer bridges and 3331 vtable bridges (50310 slots). It
predates this change. No runtime or whole-image improvement is claimed.

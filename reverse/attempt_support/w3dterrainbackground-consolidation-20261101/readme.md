# W3DTerrainBackground consolidation, halilkkaya-codex, 2026-11-01

Target facts: native ctor RVA 0x00112DBE (277 bytes) installs no vptr;
its culling statuses occupy offsets 00/04/08, bounds 0C..23, four texture
words 34/38/3C/40, origins 50/54, width 58, map 5C, tail through D0.
The existing rowed lifetime view independently spans D4 bytes. The seed
now declares this nonpolymorphic prefix instead of importing the ZH class.
No unknown terrain virtual slots exist to replace with __purecall. Pure
placeholder slots in auxiliary views must not be mistaken for recovered
retail implementations or used as proof of native vtable contents.

Retire nine unrowed legacy bodies, keeping doPartialUpdate and its marker:
it emits the existing Add_Point, Get_Filter and Set_V_Addr_Mode rows. This
is cleanup of donor code, not a claim of native dead stripping.

Pre-trim COFF audit: 590 external definitions, 573 touched by other census
objects. outside-definitions.tsv lists every such name. Exactly six were
sole providers; all six remain: rva00112259, TerrainOwner ctor/dtor, and
SlotQuartet FillFourSlots/reset/cleanup. Their four referring sources all
retain 2,006 predicted linking bytes; seed retains 820.

The trim removes eleven definitions. Only AABoxClass's default constructor
and DX8Wrapper::Set_Texture(unsigned,TextureBaseClass*) have outside touches;
all 29 and four respective referrers also define the symbol themselves.
removed-providers.json records every referrer and remaining provider for
both names. All 37 unique referring/current sources were checked together:
30 link; seven retain unrelated existing blockers. Prediction retains
85,090 -> 85,090 bytes with no per-unit loss (seed-link-after.log).

./build.sh seed: 18/18 exact; find_declared_unmatched clean; compiler
CodeView confirms D4 bytes and no vfptr. Initial full verification also
passed all 99,270 rows. No census or image ownership gain is claimed.

## Include prerequisite

Replace the seed's engine-header fanout with the library headers actually
needed by its retained emitter plus canonical ICoord2D/IRegion2D headers.
The WorldHeightMap receiver keeps only its observed refcount/extents prefix
and declarations used by the legacy body. This removes the conflicting ZH
coordinate/UnicodeString/class declarations without changing a matched row.
The terrain tail now names existing donor fields at their witnessed offsets;
60/61/62 are initialized/update-mode/need-update as native consumers use them.
CodeView and the constructor establish the nonpolymorphic D4-byte extent.

Of the original 590 emitted definitions, 40 remain. Each of the 542 removed
names with outside touches has a byte/relocation-identical alternate in the
census; include-provider-proof.tsv records a digest and alternate for every
name. All 411 affected current units were previewed together: 372 LINKS,
518,497 -> 520,236 predicted bytes, no per-unit loss. Existing blockers remain;
this prediction is not a census measurement. Eighteen seed rows stay exact
and the frozen-file check is clean. The three inline helper rows remain here.

## Final handoff

All 17 eligible donors are accepted together, 56 composed rows exact, with
no rejected donor and the merge link guard passing. The two mixed files
remain outside that set. `merge-ready.json` records the supported dry run.
Real application still writes nothing: shared folded RVA 00042F8C is held by
StarkillerHDX@fleet for GameLOD.cpp. Do not bypass that claim. Once released,
rerun the supported merge; its current inputs may require plan regeneration.

The complete 18-source cohort is 18/18 LINKS and retains 13,514 -> 13,514
predicted linking bytes. All 48 rows in the 13 changed sources have strict
current preparation and byte verification after rebasing onto 8c6bd6ae65.
No merge was applied, so source files removed is zero. Nine hatch keys and
one RenderObjClass header-queue entry were retired through their owning tools.
The three homeless seed helpers and its one legacy emitter remain.

The native texture view now names the rowed release directly; its unknown
slots are pure placeholders and no texture/buffer vtable is emitted. Both
buffer locks use the witnessed 12-byte extent. Tessellation keeps all ten
rows and its exact EH graph. Native blend allocation is explicitly POD to
avoid introducing an element-constructor walk under the shared Vector3.
Argument-view ctor/dtor instructions and relocation names equal the original
probe objects (argument-view-proof.json); the existing unreferenced constructor
shadow finding remains, with no register retirement claimed.

Whole-batch consumer clearance remains INCONCLUSIVE. The published index is
0d24c60eef, older than outgoing base 8c6bd6ae65, and the audit cannot prove a
current affected 0CreateAHeroManager21FE49.cpp receipt. Carry this provider/
consumer scope into the next census; the bounded cohort predictions above do
not claim full-image clearance. No nightly, link cycle, smoke run or push ran.

`commits.tsv` lists all 22 implementation/debt commits with their immediate
bases and subjects. The final handoff commit follows that list. The only
remaining own scope claim is class:W3DTerrainBackground; merge refusal released
its file/RVA acquisition. The lead owns publication and eventual claim release.

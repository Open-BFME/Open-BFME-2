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

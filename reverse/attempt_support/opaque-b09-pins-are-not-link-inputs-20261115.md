# The three names the real link cannot find in OpaqueScalarDeletingDtorsB09

`next_work.py --claim` serves this as a link-cycle repair worth 570 bytes:
"the real link stops here: 3 name(s) it references exist nowhere, e.g.
`??1Rva0060FE2@@UAE@XZ`". The three are identified here, and they need three
different repairs.

## The three

Found locally, without the real-link artifact: of the 42 virtual destructors
the unit declares, exactly three are backed **only** by a pin in
`reverse/symbols.csv` and have no ledger row anywhere.

| referenced name | pin | the class it really is | that destructor's row |
| --- | --- | --- | --- |
| `??1Rva0060FE2@@UAE@XZ` | `0x0060FE2` | `MilesAudioManager` | `??1MilesAudioManager@@UAE@XZ`, matched, MilesAudioManager.cpp |
| `??1Rva008E4EC@@UAE@XZ` | `0x008E4EC` | `TerrainTracksRenderObjClass` | `??1TerrainTracksRenderObjClass@@UAE@XZ`, matched, W3DTerrainTracks.cpp |
| `??1Rva009203A@@UAE@XZ` | `0x009203A` | `W3DTerrainVisual` | `??1W3DTerrainVisual@@UAE@XZ`, matched, W3DTerrainVisualDestructor.cpp |

**A pin is a ledger artifact, not a linker input.** The unit's own header says
"Other destructors remain declared so their wrapper calls resolve to their pins
in `reverse/symbols.csv`", and that assumption does not survive a real link: a
pin records that an address carries a name, it does not put a definition in any
object. All three classes have since been identified and their destructors are
rowed and matched under real names, so nothing defines the placeholder spelling.

Every other declared destructor here resolves: 4 are defined in the unit, the
rest are `__declspec(novtable)` base stand-ins that emit nothing and reference
nothing (26 of them), or carry a ledger row.

## They do not share one repair

| | wrapper | thunk | wrapper's only provider? |
| --- | --- | --- | ---: |
| `Rva0060FE2` | `0x00061AA1` | `0x0005D41D` | **no** |
| `Rva008E4EC` | `0x0008E533` | — | **yes** |
| `Rva009203A` | `0x00092123` | — | **yes** |

**`Rva0060FE2` is fully superseded.** Both its wrapper and its thunk have REAL
twins in MilesAudioManager.cpp, recorded there as "ICF twin … the copy the exit
link keeps (first provider in its input order)", and that unit also owns the
destructor. So this reconstruction can be retired from B09 without losing
coverage of any address.

**`Rva008E4EC` and `Rva009203A` cannot be removed.** B09 is the *only* provider
of their wrappers at `0x0008E533` and `0x00092123`; the identified units own
only the destructors. Retiring them would lose those two addresses. Their repair
is instead to carry the identified class, so the wrapper's call resolves to the
real destructor — which is a rename of a matched row (`??_GRva008E4EC@@UAEPAXI@Z`
becomes `??_GTerrainTracksRenderObjClass@@UAEPAXI@Z`), with the class identity
already proven by the rowed destructor at the pinned address.

## What I did not do, and why

I stopped before editing, on two points that are the link lane's to settle:

1. **Retiring `Rva0060FE2` drops two matched rows** (`??_GRva0060FE2@@UAEPAXI@Z`,
   `??_ERva0060FE2@@WM@AEPAXI@Z`). AGENTS.md wants a real claim retracted in its
   own reviewable commit, which is fine — but MilesAudioManager.cpp's notes
   record those addresses as *deliberate* ICF twin pairs. Whether the twin is
   wanted as evidence, or is exactly the redundancy to delete, decides this, and
   the note that records it is not mine.
2. **The other two are renames**, so they belong to the naming lane under
   `docs/naming.md` rather than to a link-repair seat: a canonical name may
   replace a placeholder, and the evidence is here, but the rename has to go
   through `rename.py` with the unit rebuilt.

`tools/class_views.py --unused --files <this unit>` reports 0 candidates, so
none of this is reachable as an unused-declaration prune.

I could not read the authoritative three names from the real link:
`exit_link.py --blockers` wants an `errors.tsv` the hosted runner produces, and
`--link` is sandbox/runner only. The table above is derived locally and happens
to come to exactly three, with `??1Rva0060FE2@@UAE@XZ` among them, which is the
example the queue gave.

## Reproducing

    python3 tools/next_work.py --claim        # draws the item

The three: for each `virtual ~X();` the unit declares, check `??1X@@UAE@XZ`
against `reverse/functions.csv` names and `reverse/symbols.csv` pins; the three
with a pin and no row are the list. The coverage table reads
`reverse/functions.csv` for every name at each wrapper, thunk and destructor
address.

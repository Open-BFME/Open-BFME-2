# LINK-684: VP6 host allocator deleting dtor needs a TU decision

Status: blocked on a placement decision (owner). The C++ model is known and byte-exact; only the
row's unit is undecided.

## Symptom

The real link at d2799c0b63c (2026-11-17, `tools/exit_link.py --link --local`, base 0x02000000, no
`/FORCE`, no stubs) leaves three unresolved names; one is `??1Rva0090771@@UAE@XZ`, referenced only by
`??_GRva0090771@@UAEPAXI@Z` (0x000910FF, 28B) in `Code/GameEngine/Source/Common/OpaqueScalarDeletingDtors.cpp`.
The name exists only as a pin (`reverse/symbols.csv`, 0x00090771); no object defines it.

## Target facts (game.dat 1.06)

- 0x000910FF is slot 4 of vftable 0x00BC7F74 and has no other reference (no call, no pointer).
- 0x00BC7F74 slots 0/1 are `?allocate@Rva000910E1@@QAEPAXIH@Z` (0x000910E1) and
  `?deallocate@Rva000910E1@@QAEXPAXH@Z` (0x000910EE); slots 2/3 the shared 4B return-one 0x000910FB.
- The table is installed only by 0x000910D8 (`mov eax, ecx; mov [eax], 0x00BC7F74; ret`), which the
  dynamic initializer 0x007AC15D runs on the one static global 0x00DE4878. `atexit` thunk 0x007B6C3E
  destroys that global through the plain destructor 0x00090771, never through the ??_G. The global's
  only other uses pass its address to `duck_mem_set_allocator` (0x00091412, 0x000915DD). The ??_G is
  therefore compiler-mandated vftable content that the program never executes.
- 0x00090771 (7B) is `c7 01 94 7e bc 00 c3`: it stores the base vftable 0x00BC7E94 and returns. It is
  rowed `??1Rva000906DE@@UAE@XZ` in `InlineDtorDeletingDtorsC01.cpp` (base: four purecall slots, then
  its own ??_G 0x000906DE).

## The model that compiles to retail

The derived allocator class declares no destructor, over a base whose empty virtual destructor is
inline. The derived class's implicit destructor then compiles to `c7 01 [??_7Rva000906DE] c3`, exactly
the native 7 bytes, which the retail linker ICF-folded onto the base destructor at 0x00090771; the ??_G
calls it. Verified 2026-11-17 in OpaqueScalarDeletingDtors.cpp: 71/71, emitted body identical to retail.
Trial sources and logs: `build/decal-diagnostic/rva0090771-implicit-dtor-trial/` (local).

## Why it cannot land where it is

The inline base view makes the opaque object also emit `??1Rva000906DE@@UAE@XZ` (COMDAT ANY; referenced
only by `.debug$F`) while `InlineDtorDeletingDtorsC01.cpp` owns that symbol as NODUPLICATES. Paired
`link_check.py` reports the duplicate. Earlier attempts recorded in `reverse/re_attempts.log` and
`reverse/attempt_support/allocator-base-lifetime-20261117.md` (declared derived destructor, inline
derived destructor, inline owner destructor) fail the same way or drop the owner's row. The base and
the derived class must compile in one unit, which means moving rows.

AGENTS.md allows a row to move only into its approved unit in a fresh `tu_map.csv`. A fresh
`tools/tu_map.py` (2026-11-17) assigns no TU to any row in 0x000906DE..0x0009151D, and nothing can
anchor one:

- no `__FILE__` path, string or RTTI name in game.dat for this region;
- `tools/tu_evidence.py` (R/V/I/E/P/T) yields no row for it; the neighbouring `.CRT$XCU` initializers
  of 0x007AC15D have no TU either;
- `reverse/wb_name_leads.csv` has five entries here, all without a WorldBuilder name; WorldBuilder's
  `Libraries/Source/VideoPlayer/VideoPlayer.cpp` is a different library at about 0x006897xx;
- Zero Hour and BFME 1 use Bink here, and BFME 1's own VP6 host files are address-named placeholders
  with no allocator adapter, so no donor names this code; a web search found no public source.

## Options

1. Owner-approved provisional TU for the whole contiguous VP6 host layer (player, stream and allocator,
   about 0x000906DE..0x00091A5A), carrying the `provisional` token like the 731 provisional TUs
   `tu_map.py` already approves; first move only the allocator family (0x000906DE, 0x00090771,
   0x00090778, 0x000910D8, 0x000910E1, 0x000910EE, 0x000910FF) and land the model above.
2. Name the VP6 host classes through the naming lane (an `inferred` name needs two independent
   voters); with at least two rows sharing a real class name, `tu_map.py`'s N signal can approve a
   provisional TU without an exception.
3. Leave it until new evidence anchors the region. game.dat cannot link while it stays unresolved.

The opaque and C01 sources are unchanged; the blocked verdict is recorded in `reverse/re_attempts.log`
(`??_GRva0090771@@UAEPAXI@Z`, 0x000910FF).

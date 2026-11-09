## LINK-650: wrong bindings on the boot path through CreateAHeroManager (P49, P51, P52; LINK-630 family)

Status: open for P51's two rows. P49 and P52 repaired on master; P29 repaired by code identity.

These rows byte-match with call targets masked, so none of this shows in the byte gate. Each was found from a boot receipt.

**P49 (repaired, de03662bb5).** `MoveToGroupOrder.cpp` declares the `hashtable<pair<NameKeyType const, ArmorTemplate>, ...>::resize` it needs without emitting it. Before that, an `/alternatename` in `Armor.cpp` bound `KeyToBucketMap::resize` to a body with a different hash.

**P52 (repaired).** `Rva0021F876Dtor.cpp` and `StlportVectorDtorFamily.cpp` declared `CreateAHeroSubClass` with only its dtor, so their `_Destroy` stepped one byte and the image selected one of those copies. Receipt `2026-11-08T164855Z-boot_smoke-07a9046615fb`: `parseCreateAHeroSubClass` > `push_back` > `_M_insert_overflow` > `_M_clear` > `_Destroy` > `~CreateAHeroSubClass` at first element + 1. Retail's `__destroy_aux` 0x0021F17F steps 0xD8. Both units now carry the true size, and `StlportVectorDtorFamily.cpp` declares the rowed `_Destroy` 0x0021F466 instead of emitting one. Test receipt `2026-11-08T173035Z-boot_smoke-8c6b9a56dce8` reaches `parseBaseTemplateFiles`.

**P29 (repaired, first use of the compiler-spelled route).** Rows 0x002D07F4 and 0x002D0B36 went through `name_lane.py` votes, `resolve` and `rename.py function --respell --identity`. Two honest voters agreed on the element type and class key and differed on the container: an `operator=` body cannot tell the two shapes apart, because both compile to the same masked bytes. What decides is the callee chain, chiefly `_M_create_node`'s allocation size against `sizeof` the element. A voter's brief should say so, since the old spelling's container shape is itself unproven. Running the route needs every rowed object present (`rename.py` reads them to retire old-type pins), so build any the object store lacks first.

**P51 (open).** Rows 0x0021DBBA and 0x0021E134, spelled for `map<long, LadderPref>`, do not hold that map: retail's tree copy clones its nodes through 0x0021AAE1, not `LadderPref`'s copy. A test image with the two rows respelled by hand passes this stop (`2026-11-08T164855Z-boot_smoke-07a9046615fb`), and the callee scan's 0x219B0B and 0x21AAE1 entries drop on it. 0x005DFF76 is not part of this: it jumps to 0x005DFE18, the real `LadderPref` tree's dtor.

The compiler-spelled route is closed to these two rows, three ways:

- `name_lane.py` serves no key for them: `compiler_spelled` needs an `Rva` placeholder in the old spelling.
- `stlport_map_long_ladderpref.cpp` is not an eligible source for `next`.
- `rename.identity_shape_problem` refuses both: a real class inside an STLport argument may not be swapped, and `LadderPref` is registered as canonical besides.

That protection is deliberate, and it is right for a row whose real name is correct. These rows' real name is the wrong part. Recorded as a false reject. A layout-only form is refused too: the rowed copy ctor's call has no row under the true spelling (`unresolved call`). Prerequisite: a decision on how a wrongly named real class may be respelled.

The master form also owes one thing the test form does not do: `Rva0021E85ACopy.cpp` must declare the record tree's dtor so the unit binds row 0x0021D61F. The test form emits its own copy, which lacks retail's null test before `free`.

**P55 (repaired, 139240301e).** `Rva004118B4AssetCreate.cpp` defined its own 4-byte `g_00E02FF8` and used it as the 20-byte hash map `Rva004121B2HashMapInits.cpp` builds at 0x00E02FF8, the open row in LINK-623. The first registration read a neighbour's words as the element count and asked for a 0x30000059-element bucket vector.

**P66 (repaired, d558941e7b).** `W3DVideoBufferCtorBfme.cpp`'s element view had an empty ctor, so `??0W3DVideoBuffer`'s vector ctor left texture, surface and flags as heap garbage; retail's 0x000724A0 zeroes +8, +0xC and +0x10. The first `allocate` frees before it allocates, and released a garbage pointer.

**P67 (open, not a code binding).** The first 2D draw's dynamic vertex buffer `Lock` returns S_OK with a null pointer at base 0x10000000. Retail makes the same call with the same flags. Harness's Wine trace: `GL_OUT_OF_MEMORY` on wined3d's 64 MB chunk. The game's second 256 MB reservation lands at 0x40000000-0x50000000 at that base, where retail has Mesa's memory, on Harness's reading of the two address maps. The same image at `--rebase 0x800000` passes the lock. The default base is undecided. Runs at different bases are not comparable. A later stop at the same site at the rebased base reads address 0, and is unexplained so far.

**P51's route, update.** The coordinator directed `--basis retail` instead of votes; the no-table family landed as 0a7a80d0d2 and respells no row yet. Blocked on row 0x005DFF76, which has no approved unit: `tu_skeleton --emit-move` refuses it (`map_approved_problem`), and the block is displaced to `Common/UserPreferences.cpp`, which never approves. A form that keeps it in `Rva0021E85ACopy.cpp` needs an invented carrier function that survives `/OPT:NOREF` into the image, so it was not landed. Decision with the owner.

**P51, the owner's exception (2026-11-09).** The real respell needs row 0x005DFF76
(`map<long,LadderPref>`'s destructor) out of `Rva0021E85ACopy.cpp`, and the map has no unit for it. The owner
approved a narrow tool exception: `rename.py --forced-move`, limited to rows a family lists in `forced_moves`
(`docs/consolidation.md`, "A row a rename forces out"). The row goes to `OnlinePreferences_Unresolved.cpp`.
That is placement evidence only: its row 0x005DFF7B follows this one in retail and calls the same tree
destructor 0x005DFE18, and it proves nothing about retail's unit. Fifteen objects emit the same 5-byte body. On
the test image `4117d11fb2` (base 0x10000000), `Rva004134AECtor.obj` won that COMDAT, not the destination, and
`link_check` still counts the row's bytes with the destination. The respell lands after the tool; its pass test
is recorded on the packet.

**P81 (closed).** `AptCharacter.cpp` held a private, never-set draw callback; retail's one slot is 0x00E177A8.
Landed `835eb9fc81`. Same family as P55: a second object for one retail global.

**P86 (open), the same family.** `bfme2_texture_binding.cpp` writes `BFME2CurrentTextures`, while retail's one
array at 0x00DEE5E0 is `render_state.Textures`. A test diagnostic measured no texture at stage 0 on any of
31,867 draws, and the game rendered untextured quads as white. The fix is not landed or run at the time of this
note. Retail's 0x00DEE5DC is split the same way, `render_state+4` against `ScreenMaterial`, 38 sites, unfixed.


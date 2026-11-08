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

# stlport_pod_vector_bodies.cpp: STLport 4.6 move

Base: `d0e45553a4`, 2026-11-07. Claimed scope:
`file:Code/Libraries/Source/WWVegas/WWLib/stlport_pod_vector_bodies.cpp` (160 rows).
Supersedes the earlier "fails to compile" record (e7f3fd2a7fd): the unit now
compiles under `// stlport46`, and every remaining failure is a mangled-name
change, not bytes.

Target facts / 4.6 header facts:
- Pristine 4.6 `_config.h` defines `_STLP_USE_NESTED_TCLASS_THROUGHT_TPARAM`, so
  `_STLP_alloc_proxy` has no `allocate`/`deallocate` members of its own; they
  resolve to the allocator base. 4.6's `allocator<char>` specialization (bfmealloc
  overlay) declares `static char *allocate(size_type, const void *)` (no default
  hint) and non-const `allocate` for the primary template.
- 4.6 dropped `const` from `allocator<T>::allocate` (`QBE` -> `QAE`); see
  `tools/stlport_trial.py` ALLOCATOR_MEMBER.

Edits that make the unit compile (all retained bytes identical):
1. `// stlport` -> `// stlport46`.
2. Delete the `_STLP_alloc_proxy<char*,char,allocator<char>>::deallocate`
   (old line ~62-68) and `::allocate` (old line ~729-731) forceinline
   specializations: the members do not exist under 4.6 (C2244, C1506).
3. Drop `const` from the decl-only `allocator<unsigned char>::allocate` and from
   every `template T *_STL::allocator<T>::allocate(unsigned int,void const *)const;`
   explicit instantiation (C3190).
4. In the char/`_Vector_base<char>` specializations call
   `_M_end_of_storage.allocate(n, 0)` (C2660: the char allocate takes 2 args).

Result: `./build.sh`: 127/160 match. All 33 failures are names only:
- 17 `?allocate@?$allocator@U<T>@@@_STL@@QBE...` rows owned here are emitted as
  `QAE` ("symbol not found in object").
- 16 callers (`_Vector_base` ctors, `reserve`, `_M_insert_overflow`,
  `_M_allocate_and_copy`) are byte-identical except an unresolved
  `QAE` allocate call whose RVA is registered under the `QBE` name.

Why blocked (beyond one file):
- Two callees are owned elsewhere: `allocator<BfmePod48>` row 0x003F40D3 in
  `stlport_vector_pod48_allocator.cpp` (still `// stlport`, explicit const
  instantiation), and `allocator<BfmePod32>` only as a symbols.csv pin at
  0x003F74B3.
- Renaming the 17 local rows to `QAE` strands `QBE` binders still on 4.5.3:
  `stlport_pod_malloc_deferred_copies.cpp` and
  `stlport_pod_vector_malloc_bodies.cpp` (decl-only `allocator<BfmePod68>` and
  `allocator<BfmePod44>::allocate ... const`), and InGameUI.cpp's tu-skeleton
  marker for 0x0029B27B.

Next steps:
1. Move the BfmePod cohort to 4.6 together: this unit, the two malloc units and
   `stlport_vector_pod48_allocator.cpp` (each drops its 4.5.3 `const`), with the
   17+1 allocate rows renamed `QBE` -> `QAE` through the rename/registration
   tooling (no hand-edited pin; the 0x003F74B3 pin needs its owning tool).
2. Then repoint every row with `add_match.py --replace-existing`
   (`migrated=stlport-4.6`).

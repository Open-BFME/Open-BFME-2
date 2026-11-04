# Scene TU approval: iterator declaration prerequisite

Inspected `e17c04a76a` on 2026-11-04. The default picker selected
`Code/Libraries/Source/WWVegas/WW3D2/scene.cpp`: five proposed rows in four
sources. No source or ledger ownership was changed by this investigation.

Target facts:

- `0x00140BF0` (9 bytes), `0x00140C00` (31 bytes), and `0x00141C30`
  (7 bytes) install the table at RVA `0x007D3338`. Its first five entries are
  `0x00140C00` followed by four `0x0003B810` pure-call entries; the next word
  is zero. The following table is separate.
- The named `SimpleSceneIterator` constructor at `0x00141BF0` installs
  `0x007D33BC`. The deleting destructor at `0x00141C10` calls
  `0x00141C30`, which restores `0x007D3338`.
- `./build.sh` on `InlineDtorDeletingDtorsC03.cpp` and
  `Rva0006EFC8Grow.cpp` passes 13/13 matched rows, one data row, and literal
  checks. Both files pass `find_declared_unmatched.py`.

Reference fact: the committed Zero Hour `WW3D2/scene.h` declares
`SceneIterator` with a destructor and four pure virtual operations (`First`,
`Next`, `Is_Done`, `Current_Item`). This is structural support for an inferred
identity, not canonical same-body evidence or proof of an original BFME TU.

The supported rename paths refuse the current declarations:

- `rename.py class --fold Rva00140C00 --into SceneIterator --dry-run`:
  the installing rows' table has only the `Rva00140C00` binding; no existing
  `SceneIterator` binding ties that name to this table.
- Shared-name validation for `Rva00140C00` -> `SceneIterator`:
  `SceneIterator already exists; reconcile declarations before a class rename`.
  No vote was submitted and no approval was manufactured.

Next: reconcile the existing iterator declarations through a supported
identity workflow before retrying the rename. Then rebuild the TU plan; the
pool-grow row at `0x0006EFC8` and getters at `0x00140C20`/`0x00140C40`
remain separate placement prerequisites. Do not assume an inferred iterator
name alone will approve these rows. The current plan lists 82 approved rows
and refuses the grow donor because its other row remains unapproved.

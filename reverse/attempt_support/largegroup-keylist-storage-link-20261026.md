# One backing store for the large-group audio key tree

Follow-up to [the erase binding repair](largegroup-keylist-erase-link-20261026.md),
commit `5611c263e4`, on upstream `e5c5a1787c` and BFME 1 `f633d0e97a`.
The served key-list source and all five storage consumers were claimed before
editing; frozen-file checks pass before and after.

## Storage and lifetime evidence

The old object set split retail RVA `0x00A02E50` between an unresolved typed
tree (`g_lgaKeyRecords`), a four-byte header pointer (`g_00A02E50`) and a
separate four-byte integer (`g_Va00E02E50`). A full tree could not live in
either allocation, and initialization used a different symbol from traversal.

Direct retail inspection confirms:

- Initializer `0x007AF8CD`, 22 bytes, passes VA `0x00E02E50` to constructor
  `0x0024613C` and registers cleanup `0x007B80F1`.
- That constructor calls `0x0039FB49`; the latter stores count zero at receiver
  offset `+4` and initializes the sentinel reached through receiver offset zero.
  Its base constructor `0x0023E863` allocates a 28-byte node and stores the
  pointer at offset zero.
- Cleanup `0x007B80F1`, ten bytes, passes the same address to `0x003ED94A`,
  whose jump reaches the existing tree destructor at `0x003ED879`.
- The first sixteen retail data bytes are zero. `data_xrefs.tsv` bounds this
  region at the next referenced global, `0x00A02E60`; sixteen is an upper
  bound, not an independently proven object size.

The existing STLport tree view is twelve bytes. Compile-time size checks in
both typed consumers confirm it fits the new three-word backing store.
`data_rows.py --verify` independently proves that symbol's twelve-byte
allocation and zero contents. The following four bytes are not claimed.

`LargeGroupAudioKeyTreeStorage.h` declares that one array. KeyList owns its
zero-filled definition; the existing initializer and cleanup remain the only
lifetime operations. The typed consumers cast the shared storage to their
existing views, and the pointer readers use its first word. This is storage
reconciliation under the existing descriptive identifier, not a newly recovered
native name. No duplicate constructor, symbol alias or new pin is introduced.

## Verification and measured scope

Rebase onto upstream `b85e569cee`: upstream independently introduced a typed
16-byte allocation in Rva007B6880Thunks.cpp (`e8deed0f90`). The reconciled
version retains the verified twelve-byte array and its single KeyList owner;
all six consumers use the shared header. The now-unused opaque tree class,
typedefs and typed-global declarations are removed from the four conflicting
units. The new upstream pair-tree erase instantiation in
`stlport_asciistring_set_base.cpp` is preserved, while KeyList retains its
already verified direct AsciiString erase call.

All seven whole units pass 953/953 function rows and 24 data rows. Five EH
graphs are EXACT; Count's five upstream-renumbered funclets are resolved by
their verified parent metadata, with no ledger-label edits. Frozen checks pass.
COFF inspection proves one `?g_lgaKeyRecords@@3PAIA` definition in KeyList and
five references, with no typed-global or old address-name copy. Logs:
`build/codex-cleanup-20261025/iteration22-audio-rebase-{build,eh,frozen,symbols}.log`.
This check occurs at the storage commit during rebase; the later AddKey fixes
will be replayed and the final complete cohort checked again. Upstream already
retired the same two Count/Merge data keys and five address-name occurrences;
their continued absence is preserved, not counted as a second retirement.

All six sources pass normal before/after byte/reference gates: **938 function
rows** and the existing **23 data rows**. The new twelve-byte row also passes
its owning data verifier (ledger integrity: 2,216 rows). All **five EH graphs
are EXACT**; the normal verifier resolves the retain/string unit's renumbered
funclets through their parents, without changing labels or pins.

Current COFF inspection finds the same `?g_lgaKeyRecords@@3PAIA` in all six
objects, defined only by KeyList. Neither old spelling remains in those
objects. The native references and initializer/cleanup retain their exact bytes.

Against ordinary index `f995f30157` (2026-10-25 21:36 UTC), the six-current-object
preview is **5/6 clean**, **10,184 -> 10,375 authored bytes**. KeyList changes
from **0 -> 191**; the four already-clean consumers retain their coverage.
`LargeGroupAudioKeyMapBfmeAddKey.cpp` remains blocked solely by its existing
`vector<void *>::resize(unsigned int, void *)` spelling, so the combined command
returns nonzero. This is a bounded preview gain, not a new census, closed-strict,
NOT OURS or runnable-image measurement.

## Debt and remaining work

The owning `repair_queue.py retire data` tool removes one key each for
`Rva003ED498Count.cpp` and `Rva003ED9B1Merge.cpp`, with zero remaining findings
for each. It refuses retirement for `Rva007B6880Thunks.cpp` because of 19 other
findings outside its register. That source's old key therefore remains; no
manual retirement or false-reject claim is made.

`hatch_counters.py --update` verifies removal of the two old address-global
keys in the initializer/cleanup sources, totaling **five occurrences**.
Only those generated removals are kept; unrelated generated housekeeping is
reverted. The staged gate credits exactly five fewer address-global occurrences.

The old key-tree fold pin and unrelated thunk/static-accessor debt remain.
No `data_converged.csv` or generated `data_ledger.csv` change is made: the new
verified data owner takes precedence over the historical index. Broader
whole-tree convergence and the remaining vector resize dependency are separate
work. Matched and C++ exact coverage are preserved.

## AddKey resize follow-up

After storage commit `d453de7462`, the whole AddKey source keeps its existing
bitmap/vector views but calls the native `0x000E6D39` owner through the
already-used `vector<Drawable *>` resize signature. This is the same by-value
four-byte-element call made by the merge consumer. It passes only zero as
the fill value and does not identify bitmap words as Drawable pointers.
The 63-byte provider in `DrawableVectorResize.cpp` passes its normal gate.
No new pin or alias is added; the old `vector<void *>` pin remains.

The entire AddKey source passes before/after frozen-file and normal gates:
four rows, 324 bytes, its four-byte data row and both EXACT EH graphs.
The final six-current-source ordinary preview is **6/6 clean**,
**10,184 -> 10,689 authored bytes**. It retains the four earlier clean units,
adds KeyList's 191 and AddKey's 314 authored bytes, for a bounded **505-byte**
gain against the same published index. The command now exits zero.
No current census or complete-image claim follows from this preview.

The owning identity-retirement tool refuses to remove AddKey's existing
insert-unique key because it separately finds a divergent AsciiString
destructor reference in the static accessor at `0x002862C9`, targeting
`0x00036410`. No identity key is removed and no false-reject claim is made.
That finding is separate from the ordinary link verdict and remains a
code-identity prerequisite for the whole source.

## Canonical string cleanup follow-up

The whole AddKey source now includes the registered BFME 2 AsciiString header
instead of the BFME 1 download-manager wrapper. The native cleanup call reaches
the release-buffer worker through the canonical inline destructor. All four
rows, the data row and both EH graphs remain exact, and the six-unit ordinary
preview remains clean at **10,184 -> 10,689**.

`repair_queue.py retire identity` now passes and removes the registered
AsciiString-destructor key in `bfmeAddKey`; the separate static-accessor
destructor finding is also absent. The tool explicitly retains **one** key:
the insert-unique binding at `0x003ED8B1`. Thus this retires one identity key,
not all code-identity debt. No header-queue row existed for this source, so
no header-queue retirement is counted. Shared headers and pins are unchanged.

## Native insert owner follow-up

The remaining AddKey binding now uses the existing record-tree specialization
owned by `stlport_rb_tree_BfmeStringRecord004071F7_insert.cpp` at `0x003ED8B1`.
That provider's three rows pass the normal gate. Its existing 12-byte record
view is retained verbatim; no application identity is inferred from its name.
Compile-time checks establish matching record and tree-storage sizes. The
caller retains its original pair construction and reads the returned node's
two scalar fields through its established pair view. Native instructions at
`0x003EDA7C`, `0x003EDA84` and `0x003EDA93` prove the insert target and node
offsets 24/20 respectively. The returned hidden pair slot is unchanged.

A declaration-only insert trial enlarged the caller's frame from 20 to 28
bytes. Keeping the native insert template visible, with only its rowed
`_M_insert` worker declared externally, restores the exact 168-byte caller.
No nonmatching trial is retained in `Code/`. No pin, alias, ledger ownership
or shared-header change is needed.

The final whole-file normal gate passes all four rows and the data row;
both EH graphs are EXACT and the frozen-file check passes. The six-source
ordinary preview still passes 6/6 at **10,184 -> 10,689** authored bytes.
`repair_queue.py retire identity` removes the final insert key and reports
**zero remaining findings for this source**. This is one additional retired
identity key, with no further preview-byte or census claim.

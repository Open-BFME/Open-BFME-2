# Opt-in BFME patches over STLport 4.6

The pristine release is `../stlport-4.6/`; its archive and individual file
hashes are recorded there. This directory contains only unified patches.
Modified headers and the Win32 locale source retain upstream notices and receive an Open-BFME modification
notice when materialized. No file in the pristine release is edited.

A translation unit opts in with an exact `// stlport46` line. Unmarked units
keep their existing command, headers, and STLport 4.5.3 shim selections.
`tools/stlport_overlay.py` validates the release inventory and hashes, applies
patches with exact context, and writes generated inputs beneath
`build/stlport46/<patch-content-hash>/`. Compiler command receipts include
that directory; normal dependency receipts include the generated header bytes.
Damaged generated headers are restored before cache admission; unexpected
generated files are refused. Changes or deletions of release files, patches,
or the overlay helper force the full byte gate, including extensionless headers.
Both hooks bind tracked overlay inputs to the verified Git snapshot.

Base patches carry existing project changes from `vendor/stlport`: conditional
out-of-line copy/lower-bound/list helpers, tree node helper code generation,
`_BFME_RETAIL_TREE_INSERT_LAYOUT`, the older tree insertion branch, the
`BFME_PARTICLE_LIST_NODE_TAIL` field, and the `list::resize` const-reference ABI.
The list and tree changes are carried from already matched 4.5.3-based headers,
not inferred solely from a name or an upstream byte placement. Their use on a
new unit still requires every row in that unit to pass the full byte gate.

Named subdirectories port the corresponding existing `reference/shims/`
choices: `bfmealloc`, `bfmealloc_alloconly`, `bfmehashtable`, and `bfmelist`.
For marked units only, the compiler replaces the matching explicit include
argument with the generated 4.6 shim. Their documented allocator routing,
copy dispatch, force-inline and iterator code-generation edits stay opt-in.
4.6 allocator members retain their non-const signatures; declarations in a
migrated TU must be adapted accordingly. No symbol translation or alias is
introduced into the verifier.

The patches establish a migration mechanism, not a blanket compatibility claim.
`python3 tools/repair_queue.py stlport --tsv` exposes the historical trial leads
after filtering out identities/extents no longer in the current ledger and
files already carrying the opt-in marker (a marker alone is not byte proof). The
queue counts candidate rows, not all rows in a file; migrate only complete files
verified with `./build.sh <file>` and update rows through `tools/add_match.py`.

The Win32 locale source patch removes its private __FixGrouping implementation
and binds its two grouping calls to the existing Rva0084E030Buffer::squash
owner at retail RVA 0x00021290. The caller bytes independently establish both
call destinations; the owner retains its current inferred name and thiscall
ABI. No duplicate symbol pin or verifier symbol translation is added. The Code
adapter retains the five inferred extraction wrapper names and uses retail's
lstrcmpi import spelling. Only this explicit src/c_locale_win32 path is accepted
as a source patch; other source paths are refused.

The facets adapter defines `_BFME_LOCALE_SPLIT_PROVIDERS` to omit the 16
public workers already defined by the matched split locale units. The overlay
keeps their declarations/calls and retains every other provider. This opt-in
also restores the existing external `__category_name` table, shared with
LocaleComposeName.c, instead of emitting a separate private table. The vendor
release is unchanged; see LINK-139 and the 2026-10-29 locale-provider evidence.

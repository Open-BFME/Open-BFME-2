# Win32BIGFileSystem directory-list consolidation, 2026-11-04

Base revision: `d487e00244f46c27435e6f9ac9468f6be5231387`.
Target: `Code/GameEngineDevice/Source/Win32Device/Common/Win32BIGFileSystem.cpp`.
Donor: `Code/GameEngine/Source/Common/System/Win32BIGFileSystemGetFileListInDirectory.cpp`.

## Prerequisite repair

`tu_views.py` normalized the existing Rva006038D4Less and BfmeStringNoCaseLess
comparator declarations. It rejected ArchiveFileSystem's proposed block (missing
namespace-aware template declarations) and both class/base disagreements, restoring
those failed trials. No class identity, layout, pin or alias changed.

The directory donor's comment contained a literal form feed in `directory\file`.
The composer splits source lines and consequently treated the following text as
code. Replacing that control character with the intended backslash restores
ordinary parsing. The seed's comparators now precede donor includes using their
container types. The first successful combined compile matched 37/38 rows: only
getFileListInDirectory differed, because its imported strncmp became a direct call.
Including string.h alongside stdio.h while _CRTIMP is dllimport preserves the
retail import; strcpy, strcmp and strlen retain their intrinsic direct calls.
A trial redeclaration after string.h was rejected for different linkage and was
removed before verification.

Verification before the merge:

- Three edited sources: 47/47 rows exact, one data row verified; after the final
  include change the seed was separately rechecked at 33/33 and the comment fix
  at 5/5. No new unmatched definitions or whitespace errors.
- Link preview of three edited units: 3,165 -> 3,165 linked bytes; final seed
  recheck: 2,011 -> 2,011, census index 2026-11-04 17:56 at 8c757ea0db.
- Final tu_skeleton dry run: seed plus directory donor accepted, 38 rows exact,
  link guard passed. Only hatch-register relocation is required by this merge.
- Other pure donors remain rejected: parser donor lacks rva006045A2 in the seed
  view; opaque destructor views disagree about inheritance and rva00603C5F;
  constructor donor redeclares STLport templates. Nine mixed donors remain separate.

These are scoped byte and link-preview results, not a new census or real-link run.

## Applied merge and compatibility audit

After prerequisite commit `06619ce637`, tu_skeleton applied the accepted merge:
five rows (the 548-byte method and its four EH rows) moved to the approved TU,
and the directory-list donor was deleted. Source files decrease by one; no
matched row is lost. The TU map change only repoints these five source columns;
it does not regenerate assignments. Hatch totals are unchanged.

The merged TU passes 38/38 byte matches, string/import checks and funclet-parent
verification. The link guard passes, and link_check reports the combined TU
LINKS at 2,559 own bytes, accounting for the donor's 548-byte method; the parser
donor still LINKS at 606. This is a transfer, not a measured linking gain.

The outgoing path audit covers the single removed source and destination on top
of `06619ce637`; the earlier queued commits have no source-path moves. Searches
of tools, hooks, workflows, Code includes, docs and reverse registries found no
active consumer needing an update. Remaining old paths are the source-provenance
comment, attempt evidence, and historical link_status.csv census row. The
functions ledger and TU-map source columns now name the current owner. Header,
MS-header, code-identity, data and gate registers have no keys for this scope;
no debt is retired. No /alternatename is removed. Composition's provider/consumer
guard and the subsequent link preview pass despite deduplicated instantiations.

Scoped naming reviewed all five parameters and seven locals of the complete
merged method, retaining nine clear names and clarifying the directory iterator,
file iterator and directory-match predicate. The native-child proposal and full
parent mapping/diff review use the same claims and final TU path. The generic
complex-binding inventory warning was inspected: this function's declarations
are covered; no broader C++ inventory completeness is claimed. Application
verified all 38 rows again.

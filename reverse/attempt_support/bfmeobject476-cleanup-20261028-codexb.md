# PlayerTemplate fragment constructor cleanup

Base: `34926aa896`; preview index: `d92e7e6635` (2026-10-28 15:58).
BFME 1 reference freshness: verified 2026-10-26 at `001ccd8e2768`.

The default TU-approval picker selected the proposed BfmeObject476.cpp group
(134 proposed rows in seven files). The current-input `tu_skeleton --plan`
returns zero approved rows. The destination does not exist. The refreshed
Common consolidation packet identifies the copy donor as mixed: PlayerTemplate
same-name donor evidence is only a hint, with unrelated helper placements and
unresolved placeholder identities. No TU approval, rename or source move is
claimed. Establish independent target naming/placement evidence before merging.

In BfmeObject476Copy.cpp, the default S3Money constructor was emitted despite
being inlined at every use. The object's relocation graph has no references to
that external copy. Applying the existing dllimport+forceinline convention
suppresses the unused copy and allows its present-unmatched hatch to leave.
The copy constructor and all retail-owned bodies remain.

[Object comparison](bfmeobject476-cleanup-object-20261028-codexb.json): only
`??0S3Money@@QAE@XZ` disappears. All 178 retained external COMDAT fingerprints,
strong definitions, undefined symbols, weak bindings, runtime roots and retained
reference edges are unchanged. Snapshot verdicts are unassessed; comparison
establishes equality, while normal gates establish retail matching.

Verification:

- Before and after normal builds: 147/147 function rows, one string literal,
  two empty-string references and one named import pass.
- Strict `link_check --prepare-current`: one reusable provider receipt;
  normal gates pass. EH verification: all seven graphs EXACT.
- Scoped data check: zero findings. Frozen-file check passes.
- Ordinary preview retains LINKS for 2,519 authored bytes against the same
  index. This is not a new census-linked gain.
- Hatch register updated through `hatch_counters --update`: one occurrence
  retired. No pins, names, ledger ownership or source paths change.

Other wrappers were tested and reverted. Suppressing Rva001FD458 default
construction changes the rowed tree constructor at 0x001F068F (allocation
inlines) and expands the map constructor beyond its 25-byte row. Suppressing
Rva000427195 expands the hash_map constructor at 0x001FEAB2 beyond its 31-byte
row. These are trial codegen failures, not evidence that the retail row extents
are wrong. Rva001FD42B suppression passes all rows but changes the unrowed
map<int,void*> constructor and removes seven additional helper copies; it is
also reverted pending selected-provider analysis. Reconcile the shared STL
constructor emission context before retrying those three hatches.

Scratch builds, original source and object: `build/bfmeobject476-cleanup-20261028/`
and `build/bfmeobject476-*.txt`. Runtime closure and the wider TU recovery remain
unverified.

The outgoing staged-tree audit is INCONCLUSIVE (exit 2): index `d92e7e6635`
predates the base and affected consumer
`Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt. Carry this
consumer and the removed-copy scope into the next scheduled census.

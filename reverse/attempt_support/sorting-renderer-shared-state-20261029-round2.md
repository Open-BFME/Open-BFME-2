# Sorting renderer scalar storage

Control: ea153f2145, 2026-10-29. The two renderer units were claimed together.
The Get_Sorting_Struct unit was claimed for a list-layout trial, restored and
released; none of its source changes is retained.

## Verified repair

sortingrenderer.cpp owns the following state once, with C linkage retaining
its existing COFF spellings. SortingRendererBFME1.cpp declares those owners
instead of defining private copies. No alias, pin, header or code row changes.

| Symbol | Retail RVA | sizeof / native initial value |
| --- | --- | --- |
| _DEFAULT_SORTING_POLY_COUNT | 0x009B61F8 | 4 / 16384 |
| _DEFAULT_SORTING_VERTEX_COUNT | 0x009B61FC | 4 / 32768 |
| _temp_index_array | 0x009EE948 | 4 / null |
| _temp_index_array_count | 0x009F2950 | 4 / zero |
| _total_sorting_vertices | 0x009F2954 | 4 / zero |

All five new data rows pass compiler sizeof and complete initializer
verification: 20 bytes. These are retail compiled initial values, not claims
about later runtime settings. The generated index previously gave
_temp_index_array an eight-byte upper bound to the next referenced address;
the compiler independently establishes a four-byte pointer.

Both changed units retain all 37 function rows. Including the restored
Get_Sorting_Struct unit, the verification passes 52/52 rows, three float
references and no skipped references. Converged-data checking finds zero
second names at eleven protected addresses. Explicit bounded preparation
also passes both changed units with strict reusable compiler receipts.
The ordinary preview at index d92e7e6635 reports both changed units LINKS
(591 and 13,227 authored bytes, retaining the census credit). This is a
bounded preview, not a new census or a measured linking increase.

The ordinary data scan over three units falls from eight findings (six
outside the register) to four (two outside): only the two existing list
identity findings in each renderer remain. No baseline key is removed.
The existing retirement prerequisite therefore remains open; do not delete
its keys by hand.

The code-identity shadow check also reports three Matrix4 helper definitions
outside its register. Comparing the saved control object with the final strict
object proves their code bytes and relocations unchanged for operator=,
operator[] and Init. These existing helper-identity findings are not repaired
or admitted here.

## Outgoing audit boundary

The first outgoing gate passes 75/75 rows across four sources. Its batch
link audit is INCONCLUSIVE: index d92e7e6635 predates the outgoing base,
and the additional Eva.cpp and WWLib/thread.cpp consumers lack current
reusable receipts. Explicit bounded preparation refuses both because macro
or parent-traversing includes have unknown search roots. No receipt or
compiler exception is forced. Carry these consumers and the changed owners
into the next normal census; the passed byte gate does not establish a
clean batch-link verdict.

## Rejected list extension

The native list storage at RVAs 0x009B6200 and 0x009B620C is twelve bytes:
a vptr followed by head and tail. SortingNodeStructDtor.cpp instead reads a
local eight-byte head/tail view anchored four bytes into the clean list.
The Zero Hour dllist.h independently has a virtual destructor and those two
pointer fields; it is corroborating structure, not a new target name proof.

A trial made both complete lists external owners and gave that reader its
vptr-sized prefix. All five scalar data rows passed, but five of 52 function
rows failed: Deinit, Get_Sorting_Struct, the two Insert entry points and Flush.
Observable differences include redundant null tests and different register
scheduling after losing TU-private storage. The scalar-only repair restores
all 52 exact matches. No nonmatching list reconstruction remains in Code/.

[The rejected hypothesis as a patch against this scalar repair](sorting-renderer-shared-state-20261029-round2/list-owner-trial.patch)
is a zero-context diagnostic; replay uses git apply --unidiff-zero. Reconcile the list visibility/alias
contract or its approved TU composition before retrying whole-source debt
retirement. Do not force an alias or weaken a byte gate.

Carry both changed owners and all sorting-state consumers into the next normal
census. No increase in LINKED or change in NOT OURS is claimed here.

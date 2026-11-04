# AptValue predicate header adoption, 2026-11-04

Inspected HEAD: `4fad46fa2d`, rebased onto `537ac50eeb`.

Three units now include the existing `BfmeAptValue006DCD20.h` instead of
redeclaring the base with a one-slot virtual table and anonymous bitfields:
`AptValuePredicate006DBFA0.cpp`, `AptValueUndefinedBFME2.cpp`, and
`AptValueXmlPredicatesBFME2.cpp`, under `Code/Libraries/Source/Apt/AptValue/`.
Target-backed layout is unchanged: signed type is bits 25..31 of the dword at
+4; the defined bit is bit 4. Explicit signed shifts and a mask use the existing
canonical field04. No donor identity, new field or class name is inferred.

Verification:

- Normal build.sh: 6/6 bodies byte-match (653 ledger bytes); 24 string references
  pass across the three files, with no float or import references.
- find_declared_unmatched.py: all defined functions already matched, before and
  after the edits.
- header_adopt_lane.py accept --class BfmeAptValue006DCD20 on these three files:
  PASS all three; the owning tool retired exactly three header_queue.tsv rows.
- Combined link_check.py: predicate 108 -> 108 bytes, undefined 101 -> 101,
  XML predicates 432 -> 432; all three LINKS. Index census is 2026-11-04 07:28
  at `a62ac1c10b`. These are predictions, not a new linking census.

Constructor trial, fully reverted:

The existing absent-from-retail placement-new anchor in
`AptValueConstructorBFME2.cpp` cannot instantiate the canonical abstract base
(pure virtual slots 12/13). Defining the single-int constructor directly and
removing that anchor fixes compilation: both constructors and the release-vector
data row byte-match. However, emitting the complete canonical virtual table
introduces twelve unresolved BfmeAptValue006DCD20 virtual names: AddRef, Release,
ForceDelete, GetNativeHashVirtual, ContainsNativeHashVirtual, getHasClass,
setHasClass, objectMemberLookup, objectMemberSet, vslot09, vslot10, and
DestroyGCPointers. Link preview drops 127 -> 0 bytes. The constructor source,
its existing link-wide alternatename, and its header-debt row remain unchanged.
Next work must reconcile those slot providers with the canonical table before
adopting this constructor. Both trial outcomes were recorded through re_log.py.

Outgoing path-consumer audit:

The inherited four-commit range above origin/master contains one absorbed source:
TerrainResourceBehaviorCtor.cpp -> TerrainResourceBehavior.cpp. Rechecked that
old basename across active tools, hooks, workflows, Code, build/configuration,
docs and reverse registers before publication. Remaining mentions are the
source breadcrumb, historical evidence/logs, LINK-168 history, and the published
link_status.csv snapshot; none is an active path consumer. Earlier merge proof
and permitted vanished-source header-debt accounting remain in
terrain-resource-consolidation-20261104.md and its follow-up commit. This
predicate batch introduces no source move or provider rename.

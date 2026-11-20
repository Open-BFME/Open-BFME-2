# Compiler deleting-dtor slots in the to-class post-build check

The normal MilesAudioManager to-class transaction passes all464 code rows,
63 literals,33 floats and106 imports, then the old post-build checker rejects
two unchanged native compiler vtable edges. The failed transaction restores
every source/row; the original464-row area was rebuilt successfully afterward.

The actual local COFF edges are characteristic2 WEAK_EXTERNAL ??_E to the
same class's ??_G. LatchRestore<bool> has a full37B scalar at RVA0x00051A46;
MilesAudioManager has a full28B scalar at0x00061AA1. Both before/after objects
contain these exact native scalar bodies and relocations. A weak aux TagIndex
may point at an UNDEF declaration while a separate positive-section record
defines the same scalar public in that object. Rejecting that native form or
treating every weak search default as an alias are both incorrect.

object_link_names keeps its existing blanket weak-default refusal. A separate
post-build helper proves only individual(vtable,slot,weak-name) triples. It
requires the normal current source/command/dependency receipt, exact source
path and COFF hash, the existing readonly initialized COMDAT vtable shape,
zero-addend DIR32 slot, native same-class E/G/characteristic2/RVA proof, one
real matched nonaliased/nonscaffold scalar owner, one actual local executable
function definition, its complete exact extent and relocation set, and a
strict full-body comparison with weak recursion disabled. It rechecks object,
receipt and ordinary currency afterward. No names enter a global binding map;
no table, unchanged-before slot, missing definition or arbitrary weak chain
receives an exemption. The strict-before-object rule remains unchanged.

Independent review found one additional structural negative fixture: testing
type&0x20 also accepts the COFF first-derived array kind0x30. Root reproduced
the failure before fixing the test to require(type&0x30)==0x20 and adding its
regression. This malformed-type counterexample is a fixture, not an observed
VC7.1 output; the real compiler emits function type0x20.

Coverage includes wrong/retired/rowed/strong names, wrong characteristics,
missing/ambiguous/chained/cyclic/default bindings, data/array/longer-prefix
definitions, wrong bytes/callees/relocations, stale source/object/receipt and
cross-unit owners without a complete valid local copy. A self-contained real
VC7.1 compiler/linker test closes a NOENTRY DLL without FORCE/stubs/custom DEF
and reads its actual vtable word selecting its actual local scalar address.
No fixture image or game was executed.

The initial narrow suite passes317 cases, including45 new controls. Four
existing fixture writes now explicitly use LF:13 old Windows failures were
first reproduced against the unmodified original checker and were caused by
implicit CRLF conflicting with the fixture Git snapshot. No approval/LF guard,
assertion or production source is relaxed. Root's expanded final run also
includes gate-exploit controls and the additional array-kind regression;
environment-dependent symlink/empty-fixture skips remain unchanged.

Normal build receipts need not be census version2 include-inventory receipts.
This new post-build proof uses ordinary fresh-build currency plus exact
source/output binding; it neither rewrites sidecars nor relaxes the separate
strict-before currency predicate. Private optional inventory experiments were
not represented as normal admission.

This verifier prerequisite adds no code bytes or completed queue item. The
normal approved source rename and the next published real-link removal of the
Miles Snapshot bridge remain separate requirements. No full-image link,
startup, runtime, memory or crash improvement is claimed here.

# TunnelTracker Xfer comparison prerequisite (2026-10-28)

Scope: `Code/GameEngine/Source/Common/RTS/TunnelTrackerXfer.cpp`.
The existing row at RVA `004F579C` remains 192 bytes and byte-matched.
This change removes a private iterator-comparison template and compares the
list iterator's node pointers directly at its single use.

## Composition evidence

The supported current-map merge at initial base `5c1449577d` of `Common/RTS/TunnelTracker.cpp` initially
refuses Xfer with C2995: the local `_STL::operator!=` template duplicates a
comparison already available in the composed TU. After this change, that
refusal clears and composition reaches C2039 (`TunnelTracker::xfer` missing)
and the incompatible list-member declarations. No merge is applied. Constructor,
destructor, load-postprocess and deleting-destructor declaration prerequisites
also remain; the current group has 30 approved rows and no mixed sources.

## Object and byte evidence

Before/after sanctioned `./build.sh` runs verify the complete existing row,
all code references and the zero string/float/import references. The frozen-file
check passes. A strict current receipt succeeds after the composition scratch
files are removed; an earlier overlapping preparation detected moving inputs
and accepted no witnesses. Ordinary `link_check.py` retains LINKS at 192
own authored bytes against published index `d92e7e6635` (2026-10-28 15:58).
This is a preview, not a new census measurement.

The object comparison checks every retained non-debug section's bytes, size,
flags, relocations by referent symbol, definitions and COMDAT selection policy.
All 13 retained sections, 12 external COMDAT definitions, 16 external bindings
and zero weak aliases agree. The sole removed section is the old static
iterator-comparison helper: 12 bytes, no external symbol, no outgoing
relocations and no incoming relocations in either object. The matched Xfer
body already inlined the comparison, so none of its six relocation bindings
changes. This is removal of an unused private helper, not lost row coverage.

Object SHA256:

* Before: `47ba6ce678201243a9f58a2e83fc8d22bfc57ed4e7d9109889fee9ff0d9890c0`
* After: `fc8e5fa67bd4ba5e7669b1ab7e030f5f69a30a478dde3ef9f9b17da5fa0638b9`

`eh_verify.py` finds zero EH rows and no missing object. `data_check.py` has
zero findings for this source. The existing Xfer append code-identity key is
retained: this change establishes no new retirement evidence. No header,
Microsoft-header or hatch register entry belongs to this source. There is no
source-path change or ledger repoint. No linked-byte, source-file, image
ownership or debt-count gain is claimed.

Scratch evidence lives under `build/tunneltracker-xfer-20261028-codexb4/`
(before/after objects, comparison script and object-proof receipt), plus
`build/tunneltracker-{after-dry-run,xfer-preview,xfer-receipt}-20261028*.log`.

## Publication preparation

After rebasing onto upstream `f866297371`, the byte gate and complete retained
object-fact comparison pass again. Strict current preparation and ordinary
preview also pass again. The raw after hash above is the rebased build; COFF
metadata changes do not change any retained non-debug facts.

The pending range `origin/master..ed5cf3ace8` also contains earlier sessions'
changes. Its four removed Code paths have no active tool, hook, workflow,
include or configuration consumer: the combined path/basename scan finds only
four `// ---- from` provenance comments and one historical obstacle note.
This cleanup itself changes no paths. The runner currently reports a maintainer
publication lock; commits remain local for its normal retry. The eventual
pre-push batch audit and census remain required; no clean batch-audit result is
asserted by this scoped source/preview verification.

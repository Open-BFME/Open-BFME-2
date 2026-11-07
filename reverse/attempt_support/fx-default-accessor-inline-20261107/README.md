# Inline FX default accessors and their compiler-owned cleanup

Inspected BFME 2 at 2bac16a657. The first official real link containing
e892c4321b is [84f3ab358d](https://github.com/Open-BFME/Open-BFME-2/actions/runs/42386120303).
The unresolved set drops from 209 to 200 exactly by removing the nine s_head
names. There are zero duplicate symbols and the link writes no image. This
closes the parser portion of LINK-584 and leaves the remaining exports open.

The 24 initialized/value exports have existing local storage in
FXParticleSystemDefaults.cpp. In the private VC7.1 probe, defining both
GetValue bodies inside their class templates and using the retail initialized
name makes all 24 externally defined. No dllexport is needed. The plain
in-class variant leaves the complete .drectve section unchanged, whereas
applying dllexport adds 48 export directives, including names outside this
repair. The link's retail DEF can already name the 24 definitions.

The original and candidate objects have the same ordered 12 .CRT$XCU actions,
matched by each GetValue callee and VALUE slot. The 12 accessor bodies,
12 registered exit cleanups and 12 startup initializers match in raw bytes
and relocation operands after accounting for each demonstrated compiler
symbol change. The 12 exact EH graphs and the 1,900-byte local link preview
also survive the in-class emission trial. The guard ordinals still differ
from retail; their 14 names are outside this candidate.

The unchanged native ledger fails 23 of its 72 checks when the source shape
changes. Each named compiler cleanup must be bound through its accessor's
atexit operand. Each initializer ordinal must be bound through its
GetValue call, VALUE store and CRT registration. The candidate does not add
object-symbol aliases. The tracked game source was restored. A follow-up
needs an accepted compiler-helper binding and normal data/export admission
for the new storage names before this change can land. See witness.json
for the exact old unresolved names and proposed current-object witnesses.

Reproduction: compile the original and in-class-accessors.cpp.txt with the
normal FXParticleSystemDefaults.cpp compiler command and distinct private
output paths. In both COFF objects, walk .CRT$XCU in section order. For each
registered function, compare its REL32 GetValue call and DIR32 VALUE store.
For each accessor, follow the operand passed to atexit and compare the
matched 10-byte cleanup. Compare .drectve directly before judging exports.

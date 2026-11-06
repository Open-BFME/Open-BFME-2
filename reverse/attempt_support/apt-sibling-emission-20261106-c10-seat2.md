# Apt sibling deleting-destructor emission boundary (2026-11-06, chat 10 seat 2)

Inspected base: bd49217dc81. Worker: codex-fleet-20261106-c10-seat2,
shard 28/30. Status: blocked; original source restored, no code or register
retirement retained. This is attempt evidence, not linking/runtime progress.

## Target facts

The ranked picker serves identity debt for Rva006CBF40Siblings.cpp at
0x0070A560 (35 bytes). The same file owns scalar deleting rows at 0x0070A530
and 0x0070A590 (35 bytes each), with three identity-register wrong bindings.
Existing symbols.csv pins bind the three complete-destructor names to
0x00709B80. The ledger already owns its 11-byte body as
Rva00709B80::~Rva00709B80 in Rva006D6470Derived.cpp. The old local empty
complete-destructor definitions shadow that intended selection. Historical
pin prose saying the body is unrowed is stale, not new ownership evidence.

## Controlled trial and result

Claimed the three scalar RVAs and file scope before editing. Removed only
the three empty complete-destructor definitions and their stale
present-unmatched comments, retaining the declarations, all six code-ledger
rows, existing pins, classes, pool references and sized delete operators.
No new helper, constructor, name, alias, pin, row, or escape hatch was added.

`python3 tools/find_declared_unmatched.py Code/GameEngine/Source/Common/Rva006CBF40Siblings.cpp`
passed before and after (six matched rows; unclaimed definitions seven -> four).
The shared two-slot scheduler ran the normal command, with BUILD_POOL=1 and
the brief's local VM PATH and BFME_VM_WINEPREFIX:

```
./build.sh Code/GameEngine/Source/Common/Rva006CBF40Siblings.cpp
```

Exit 1: source claims OK; data row 1/1 byte-verified; compiler reported the
object current; three of five function checks failed. Each of
`??_GRva0070A530@@UAEPAXI@Z`, `??_GRva0070A560@@UAEPAXI@Z`, and
`??_GRva0070A590@@UAEPAXI@Z` was absent from the object. The other two
function checks passed. Removing the complete-destructor definitions also
removes the compiler's corresponding scalar-delete emission, so this is a
correct verification refusal, not a false rejection. The original source
was restored exactly from HEAD. No identity register key was retired.

## Remaining prerequisites and limits

Reconcile the actual class/provider identities while retaining real
compiler emission of each native scalar-delete wrapper. Adjacent historical
famgen/tagged-constructor scaffolding does not authorize adding fresh
unrowed scaffolding. No such addition was attempted. The file remains blocked
and its three identity keys remain intact. A future repair must pass all
normal byte gates, the owning identity retirement, strict receipts, provider
and consumer audits; no link preview, full link, image or runtime smoke was
run for this rejected trial.

Selection review also found the shard's Snapshot table group at 0x007BB554
still reports multiple kept names with broad existing header prerequisites;
its temporary RVA/file claims were released unchanged. The concrete
getEventFX provider at 0x0056468E retains its prior owner-move/Snapshot and
random-variable reconciliation boundary. Those unchanged source trials were
not repeated. No queue or ledger row was edited to manipulate selection.

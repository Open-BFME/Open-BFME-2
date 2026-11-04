# Wander and panic state header cleanup, 2026-11-04

Inspected revision: `e6f1712ab36e5f525a7260cef8c67b387bc64825`.
Scope: `Code/GameEngine/Source/GameLogic/AI/AIWanderStateMethods.cpp`.

Use stddef.h for NULL and math.h for the imported floor declaration. Replace
the unused, incomplete FprintfTarget layout with an opaque declaration; this
consumer only passes its pointer to the existing game helper. No names, pins,
ledger rows, source paths or debt-register keys change.

Target facts: Capstone over build.read_target_bytes finds the following direct
retail calls to RVA 0x002CEC42:

| Row | Call site | Bytes |
| --- | --- | --- |
| AIWanderState::update, 0x0034A1BB | 0x0034A30E | e8 2f 49 f8 ff |
| AIPanicState::update, 0x0034A38E | 0x0034A4C6 | e8 77 47 f8 ff |

The current provider Common/FprintfAppendLine.cpp defines a void game helper
that formats and appends a line to a vector, not the CRT FILE operation.
Retain its existing fprintf declaration here. Shared logger naming across
provider and consumers remains the prerequisite for replacing that spelling;
the picker finding is not evidence that the CRT declaration is appropriate.
No donor identity or receiver layout is inferred from the call spelling.

Verification: ./build.sh of the source passes all six matched rows (1,441
bytes), seven string literals, eight float literals and four named imports,
with no skipped references. find_declared_unmatched.py passes before and after.
ms_header_audit.py check passes. The supported scan --write-queue refresh
reduces local Microsoft-name findings from three to one, retaining fprintf.
git diff --check passes. No census-linked gain or game execution is claimed.

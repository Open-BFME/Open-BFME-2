# Siege docking Matrix3D adoption: strict-input prerequisite

Trial at bcd82c82acff2ec8020dda7d12604d8ce21a074b plus this run's preceding
five Matrix3D adoptions. Source: SiegeDockingBehaviorInitializeBones.cpp,
native parent0x00459E05/554B,8 existing rows in total. Replacing the private
Matrix3D with canonical Matrix3DData.h and changing the row field spelling
preserves all18 external code definitions/relocations and normal8/8 byte rows.
The current strict preparation refuses this STLport46 source: no include
inventory, '(macro or parent-traversing include has unknown search roots)'.
No receipt is synthesized and no gate is changed or bypassed. This is a
documented input-proof prerequisite, not a claimed verifier false reject,
runtime failure or completed adoption. The exact source patch is adjacent.
The source is restored to its committed original and its file claim released;
a different independently verified source supplies the sixth completed task.
Ignored controls: build/six-each-full-resources-20261102-1509/blocked-siege.
Before a retry, establish the actual include-search inventory with the normal
tool, retaining compiler inputs and bytes. Do not weaken strict preparation.

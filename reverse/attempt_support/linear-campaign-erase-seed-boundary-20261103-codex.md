# LinearCampaign erase: seed suppression boundary

Base: `dbe1c351cc` (the verified real-header erase prerequisite, already handed
to the fleet publisher). No source change from the trial below is retained.

The seed declares the `vector<BfmeAssignRecord172>::erase(first,last)`
specialization three times. Removing those declarations would allow its real
STLport header to instantiate the member, potentially admitting the separately
verified donor during consolidation.

Trial: remove only those three declarations from LinearCampaignManager.cpp.
`./build.sh` still verifies all 47 seed rows and all three strings. However,
ordinary `link_check.py` reports:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/System/LinearCampaignManager.cpp: does not link  LINKED 2,600 -> 0 bytes (census 2026-11-03 20:03 at 8661f15284; file's own bytes 2,600)
  selected    ?erase@?$vector@UBfmeAssignRecord172@@V?$allocator@UBfmeAssignRecord172@@@_STL@@@_STL@@QAEPAUBfmeAssignRecord172@@PAU3@0@Z  (the definition the link keeps is not retail's)
link_check: 0 of 1 link cleanly; LINKED 2,600 -> 0 bytes (6.3s)
```

This is a preview of the affected provider, not a headline measurement. Its
selected erase copy is non-retail, so the trial was reverted in full.
The restored seed was rebuilt (47/47, strings/float/import checks clean), and
its ordinary link preview returns to:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/System/LinearCampaignManager.cpp: LINKS  LINKED 2,600 -> 2,600 bytes (census 2026-11-03 20:03 at 8661f15284; file's own bytes 2,600)
link_check: 1 of 1 link cleanly; LINKED 2,600 -> 2,600 bytes (5.9s)
```

Relevant environment facts: the standalone donor uses the repository STLport
headers, whose `__copy_ptrs` false-type tag is a const reference. The seed uses
the bfmealloc overlay, whose helper takes that tag by value and is forceinline.
This is a code-generation lead, not proof of the particular mismatching bytes.

Next: reconcile range-erase generation in the seed environment while preserving
its other 47 rows and current provider selection. Merely removing the
specialization declarations regresses this previously linking unit. Keep the
suppressions until a complete erase-body byte/relocation check and the consumer
link guard pass. No aliases, pins, flags or registers changed in this trial.
The independent element-family identities in LINK-040 remain unresolved.

Supported post-header `tu_skeleton.py --merge ... --dry-run` summary:

```text
approved rows: 111
accepted donors: []
erase donor: bytes
result: no verified merge of two or more donors
```

The former erase declaration redefinition is gone. The donor now reaches a
merged byte-check failure, consistent with the seed-suppression prerequisite
above. No files were moved; the 12 mixed donors and other rejected donors
remain for separate reconciliation. The probe exited 2, not success.

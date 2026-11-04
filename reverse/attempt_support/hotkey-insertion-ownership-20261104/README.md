# Retraction of the disproven AudioEvent insertion claim

This commit retracts exactly the AudioEvent `_M_insert` row at0x00358E9F/148B from ThingTemplate.cpp and records its tombstone. It changes no Source, pin, profile, debt register or other function record. `ledger_io.rewrite` preserved every other raw record and terminator under the shared add_match lock; the four input hashes and exact old row are recorded.

Native evidence refutes the old identity: a24-byte node is constructed through358DA0 ->358CA0 ->358B43 with counted-handle copy semantics. The old AudioEvent tree allocates0x78 bytes. This is more than an instruction-mask placement. The preceding landed native-copy prerequisite b4fe17216d supplies the correct complete HotKey implementation and current provider closure; see [native proof](../hotkey-native-copy-contract-20261104/README.md).

Policy: add_match.py expressly requires a wrong real claim to be retracted in its own reviewable commit before admission; conversion_gate Rule B permits that retraction. This commit deliberately has no substitute row. The next commit will use ordinary add_match for the actual emitted Value symbol in the current-map-approved HotKey.cpp, restoring this same148-byte range. No new name or alias is invented. Current old-symbol consumer scope is ThingTemplate itself; its existing unrowed Audio parser use remains a separate cleanup concern, and no old-name consumer is silently rebound to HotKey.

Normal verification passes22/22 remaining ThingTemplate rows after retraction (23/23 control). All Code bytes stay unchanged. The recorded map rebuilt from current inputs approves HotKey.cpp with evidence C=0x00358CCD..0x00358F33. No regenerated map is committed. Final readmission, consumers and pin retirement will be recorded separately; no census or full-game clearance is claimed here.

## Native dependency admission

Plain insertion admission correctly refused its unbound Value node-builder callee and restored the append. Rather than add pins, admit the already-proved compiler bodies in dependency order through add_match with explicit existing ICF owners: typed construct358CA0/45B, node358DA0/34B, then plain insertion358E9F/148B. These first two carry complete body and relocation/EH equivalence and add no unique coverage. The45-byte construct now passes normal46/46 source verification using the existing Rva00358CA0Construct owner; its independently verified EH graph is exact. No Code, alias or pin is added. Each body is banked in its own commit before continuing; publish only the complete restored batch.

## Completed final admission

After separate45B/34B dependency commits, plain add_match accepts the148B insertion in approved HotKey.cpp. The final batch restores coverage with one insertion owner, synchronizes one map source cell and retires one redundant pin through hatch_counters; Record binding remains. Normal72/72, strict frozen, nine HotKey EH graphs and final guard pass. Preview predicts+147 linking bytes; official census unchanged. See [outgoing audit](outgoing-audit.md).

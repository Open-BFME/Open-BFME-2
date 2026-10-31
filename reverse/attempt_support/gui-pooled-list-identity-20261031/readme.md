# GUI and pooled Object-list identity correction

The native GUI assignment at 0x002C54EE calls range erase 0x00548267 and insertion 0x000BB975. Its single-node erase frees storage through 0x00030830. The separate pooled Object-list assignment at 0x0046F0C2 calls range erase 0x004221B2 and insertion 0x00423890; its single-node erase at 0x0029DFC5 returns the node to the DB8FEC freelist. These are different families, not interchangeable fold twins.

Existing GameWindow identities on the second family came from masked placement. Current Horde code already emits the actual pooled Object-list family. The allocator spelling Rva001EB984PoolAllocator is an existing source-derived structural view; it is not a recovered original allocator name. Native source type evidence, C++ view facts and address/byte facts remain separate.

First prerequisite: tools/pin_admission.py accepted two existing pooled helper folds from the matched Horde source, proving their complete bodies and owner relocation twins. Both names were unpinned before admission; pin_consistency --check passes. No Code source, function row or native coverage changes in this prerequisite, and no linked-byte gain is claimed.

A private GameWindowManagerScript trial gives whole-body and resolved-relocation matches for pooled erase (52 bytes), pooled assignment (104 bytes), and true GUI single erase (32 bytes), retaining all other 28 code rows. Those private facts do not authorize ledger admission or publication of the source trial.

Remaining correction: reviewable withdrawal/readmission of wrong identities, consistent copy/assign consumers and obsolete GameWindow helper bindings, then all owning source/byte/EH/data/link gates. Keep rows in their current source paths: affected pooled addresses have no approved TU placement. Current whole-image and consumer closure remain unverified.

Dependency order: the attempted six-row withdrawal was correctly refused because Formation still called the old dispatch. That entire withdrawal was restored; no gate was bypassed. The live Formation caller now names the true pooled template dispatch, with its body visible to preserve compiler summary. All18 Formation rows (including the845B parent and scoped EH) and all10 Horde rows pass ordinary build. Two further native bindings were admitted through pin_admission to permit this caller-first migration; their redundant pins retire once corrected primary rows are admitted. The old six identities still remain and will be withdrawn only after this prerequisite.

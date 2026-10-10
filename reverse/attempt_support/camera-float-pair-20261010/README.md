# Camera float helper exact bank

Reviewed committed BFME1 575ba2b04743f190f069805fbdc59936123c45da. The clean W3DViewBuildCameraTransformBfme.cpp donor has genuine minimum/maximum expressions; the relevant donor source is unchanged since2f243e26d. Donor CameraMin/CameraMax labels do not establish target names.

Native entries B2B87..B2B95 and B2B95..B2BA3 are independently complete14-byte bodies, immediately after complete RETs, ending in their own RETs. Both compare the float inXMM0 with the float atESP+4 and return inXMM0, without stack cleanup. Minimum usesJBE to retain the register operand; maximum usesJA. This includes the observed unordered/tie behavior. Original helper names and source-parameter ordering remain unknown. No native CALL or data pointer reference was found, so no public cdecl callable ABI is asserted or pinned.

Ordinary /Oy in the existing proper BFME2 camera TU naturally emits both helpers14/14 and retains the existing buildCameraTransform1148 exactly. No pragma, emission anchor, alias or added pin is needed. Temporary normal add_match_batch verified all3/3 bodies and all references; supported --prepare-current also verified the explicit source with a strict reusable include/compiler receipt. The exact whole-file candidate is banked separately under each targetRVA. Source and temporary rows were restored before committing this evidence.

The existing properhome has three real unresolved dependencies: g_Va00DB457C, g_Va00DE2020 and rva00102F83(context). The last is an unrowed4299-byte camera state routine. The ordinary retainedd68 preview and fresh code-body-seat-four status agree on these three unresolved names with no COMDAT/selected blockers. The full current-ledger preview separately refused7137 inherited objects lacking strict compiler witnesses; no global proof or new LINK credit was claimed. No cold global census/build or unrelated-home workaround was started. Both helpers remain partial score1, blocked-on=0x00102F83; this bank adds0 C++ bytes.

The required min5 placement rescan offered75FBB6/5 for the context destructor. Full native context proves it is the JMP suffix of EHcleanup75FBB0 (LEAECX,[EBP-EC]; JMP899E5), not a standalone body. It was refused before adding a row or pin and the emitted name was recorded in place_denylist.

Private search evidence remains in build/seat3/float-min-b2b87-private and float-min-b2b87-fpo-private.py; current full normal-gate output was observed before restoring the unpublished recovery. These are evidence, not retained census witnesses or progress.

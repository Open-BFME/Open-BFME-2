# Provider selection for the ordinary vector accessor candidate

Bounded read-only audit, 2026-11-03. Loaded the existing local index with sanctioned `link_check.load_index()`, read narrow ledger/pin matches for the three exact names, and inspected existing object symbols. No fetch, refresh, compilation, index write, claims, tests, or tracked edits. Full machine-readable facts, exact names, bytes and positions are in provider-selection.json beside this report.

Index: `build/link_census/link_index.pkl`; date **2026-11-02 08:35**, commit **984a4cdc4d**; underlying census **2026-11-02 06:54**, commit **357ce2a88f**. Positions below are zero-based positions in its saved object order. None of these three exact names has a /MAP selection exception. Without one, `wrong_selected` selects the minimum defining position (tools/link_check.py:821-825). The candidate properties report COMDAT selection 2, so the earlier selected definition matters.

## vector<void*>::size() const

Exact name: `?size@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QBEIXZ`.

- Current narrow ledger has a matched **25-byte owner at RVA 0x00023BC0**, in `Code/Libraries/Source/WWVegas/WWLib/stlport_vector_voidptr.cpp` (functions.csv:98156). Its notes require /Od /Ob1.
- That owner is the first saved-index definer at position **385**, object `^code_^libraries_^source_^w^w^vegas_^w^w^lib_stlport_vector_voidptr.obj`, digest **062d44dd1806**, verdict **retail**. It is also the explicit ledger owner in index selection. Position 441 has the same retail digest from stlport_vector_voidptr_alloc; later wrong variants begin at 895.
- The existing owner object's actual symbol is still 25 bytes with no relocations and digest **062d44dd1806**. Its bytes exactly equal the retail 25 bytes at 0x00023BC0: `558bec51894dfc8b45fc8b4dfc8b40042b01c1f8028be55dc3`.
- The candidate adds a **9-byte** COMDAT, `8b41042b01c1f802c3`, no relocations. Its standalone source's saved-index slot is **11653**, after position 385.

Therefore, against this saved order with the current native owner's unchanged symbol bytes, the linker keeps the native 25-byte owner and discards the new 9-byte copy. This is a concrete selection argument, not a claim that the 9-byte provider itself matches retail. In census terminology a discarded wrong copy need not count as a loser when the first selected copy is proven retail (keep_rule's retail_kept/retail_first logic); do not confuse that scoring rule with the body's own byte identity.

## vector<void*>::operator[](unsigned) const

Exact name: `??A?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QBEABQAXI@Z`.

- No exact-symbol ledger row or pin was found in the narrow lookup. Its native placement and native correctness remain **unknown**.
- The index has **26** copies, all with digest **77aefc50cdb3** and native verdict **None**. It records no ledger owner or selection exception.
- First saved-order holder is position **895**, `Code/GameEngine/Source/GameClient/GameClientDrawableTOC.cpp`'s object `^code_^game^engine_^source_^game^client_^game^client^drawable^t^o^c.obj`. The next holder is position 985, MilesAudioManager, with the same digest.
- The actual existing position-895 symbol is **12 bytes**, zero relocations, `8b018b4c24048d0488c20400`, digest **77aefc50cdb3**. It exactly equals the candidate's new 12-byte provider.
- Candidate source slot **11653** is later, so it does not replace the saved-order holder. Even if it were selected in another permitted order, its measured code bytes and relocations equal this currently kept copy.

This proves compatibility with the existing selected copy for this exact symbol. It does not turn the missing native address into a verified retail placement; that conclusion remains unknown and is not waived.

## PBVThingTemplate hashtable::_M_find

The full decorated name is retained in the JSON. The current pin binds it to **RVA 0x002888D4**, and the ledger has established **47-byte** bodies there under other concrete template identities. The parent's private proof demonstrates candidate whole-body equality at that RVA with **zero relocations**.

- The saved index has exactly **one** definer for this exact PBVThingTemplate name, position **11653**, SelectionXlat_areAllSelected.obj, digest **e7204c085c9b**, verdict **unknown**. There is no indexed owner or holder exception for this exact name.
- The saved-index copy is the prior 60-byte variant represented in the private control proof. The candidate's sole exact-name definition is **47 bytes**, digest **19c037c11543**, and no relocations. On the final existing-object read the standalone object's symbol had already become this same 47-byte candidate body; it equals the candidate proof and native bytes.
- With one exact-name definer there is no competing COMDAT winner for this name. Replacing its body changes that sole provider. The saved census verdict remains historical/unknown until a later approved census; the private whole-body evidence is a separate fact.

## Evidence limits and guard

All actual existing-object reads in this audit came from the MAIN workspace build/match directory, C:/Users/clemens/Documents/Experiments/Open-BFME-2/build/match, using the main workspace tools/build.py. They did not come from the private proof workspace. Private candidate/control definitions were read only from the supplied proof.json. The final main standalone object already held the 47-byte candidate; this audit does not infer which parent replay produced it. All rank positions are from the SAVED index, not a newly measured link.

The existing whole .obj SHA256 values differ from the saved index hashes for the inspected holders. This audit therefore does not claim those whole objects or the full tree are unchanged since the census. For the two accessor winners specifically, their currently read symbol bytes, relocations and normalized COMDAT digest still equal the saved-index symbol facts. Selection here is bounded to the saved order and these three exact providers.

The supplied proof.json now records the parent's unmodified LinkGuard result: prepare=None, fetch_error=None, fetched=false, judge=[], with this same index metadata and the standalone source counted census-linked. That is the parent's check, not a guard run by this reviewer. No new census or headline linking figure is claimed.

Audit complete. No further tracked reads after this report.

# GadgetTextEntrySetText artificial-anchor cleanup: scoped private proof

Verdict: the single requested clean-C++ candidate preserves all3 ledger rows and owning EH, removes only the artificial4-byte anchor provider, and passes the unmodified private LinkGuard. It also deliberately changes the function's COMDAT selection from select-any to an ordinary no-duplicates definition; this material binding-property delta is recorded, not hidden behind identical code bytes. Root owns actual source application, ordinary verification, commit and final consumer gates.

The frozen-source scanner ran before the trial and printed 'All defined functions are already matched'. The complete current source was read. The exact anchor-name search across Code, tools, reverse, docs, .githooks and .github found only its own definition; no outside textual consumer was found. That bounded textual search is not a full-image reference claim. The unmodified LinkGuard separately checked its dropped-provider/consumer conditions below.

The candidate changes only `inline void GadgetTextEntrySetText` to ordinary `void GadgetTextEntrySetText` and removes the existing artificial anchor declaration and its explanatory four-line comment. The function body, source flags, all headers, signatures, pins, ledgers, hatches and other declarations remain untouched. Its ordinary definition naturally emits the already-rowed native function without nonretail pointer data. No helper/type/provider alias was added.

Control and candidate both pass:

- Native function RVA2C17EB/66B.
- Its cleanup row RVA776B7E/8B and EH handler RVA776B86/10B.
- The owning parent EH graph EXACT.

All4 surviving ordinary external definitions have identical full E.Obj bytes and ordered symbolic relocation lists; added/changed definition lists are empty. The only removed external name is `?_bfmeInlineAnchor_GadgetTextEntrySetText_0@@3P6AXPAVGameWindow@@VUnicodeString@@@ZA`,4 bytes in .data, with its initializer relocation to the existing GadgetTextEntrySetText function. Its source already explicitly calls this artificial pointer 'not retail data'. Provider-definition counts change5 ->4.

COFF properties: the function remains an EXTERNAL symbol in .text but COMDAT selection changes2 (IMAGE_COMDAT_SELECT_ANY) ->1 (IMAGE_COMDAT_SELECT_NODUPLICATES). Every surviving provider's other captured storage/section/selection properties is unchanged. The removed anchor was ordinary .data (selection0). This is therefore a legitimate candidate to evaluate as an ordinary-function owner, not a claim that all COFF semantics are unchanged. The unmodified private guard was asked to judge that replacement and did not waive the changed selection.

`symbol-delta.json` records defined-name, undefined, weak/alternate and include deltas. Undefined external names, weak routes, alternate routes and forced includes are unchanged; the only defined-name delta is the removed anchor, while the separate selection-property comparison captures the function becoming ordinary. No runtime/directive/import configuration was changed.

LinkGuard used its existing local index with fetching disabled. prepare returned None and judge(candidate,[source],text) returned[]; full index metadata and linked-source scope are retained in proof.json. This is the ordinary bounded source-replacement guard result, not a new census, full-image link or accepted image-ownership receipt. No NOT OURS or linked-byte metric gain is claimed. Root's final outgoing-range/link-batch checks still apply, especially given the deliberately stronger function definition.

Control source SHA256: `31703db588ad4f7e19f54d25f1dd8ef7f4b891b952405f98e7029de6fae7972f`.

Artifacts: control.cpp/candidate.cpp, both copied private objects, proof.json (all rows/EH/body/provider/property/guard facts), symbol-delta.json. Harness: ../gamewindowmanager-readonly-20261103/gadget-anchor-probe.py. Exactly2 sanctioned private Verifier compilations ran, no further trial. No tracked Code/ledger/index change, normal build/shared-cache write, header edit, new pin/hatch, claim or network operation occurred. The two active root Dtor/draw acceptances were not duplicated. Tracked reads stopped.

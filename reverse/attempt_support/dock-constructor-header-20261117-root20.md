# Dock constructor uses the shared data prefix

Inspected 80848a58e08669410010d64d6a40ec90eb30554e on 2026-11-17. Normal header_adopt_lane adoption replaces DockUpdateCtor.cpp's private DockUpdateModuleData view with the canonical header. Its16-byte layout and field names already agree: vptr0, module tag4, approach count8 and passthrough byte0C. The constructor only reads the approach count. No body, flag, row placement, pin or alias changes.

The complete non-debug runtime graphs before/after are identical under class_cleanup.same_runtime: all code/data bytes, relocations, provider names, weak defaults and COMDAT policies. Source-restoring class-layout diagnostics produced the evidence in the [JSON](dock-constructor-header-20261117-root20.json). Constructor0x0058A290 remains384bytes with complete EXACT EH.

Validation:18/18 changed-source rows;28/28 with the restored SupplyCenter peer,3 EXACT EH parents; strict current four-source consumer/provider cohort54/54 plus1data row; all four preview LINKS. The consumer preserves1245/1245 predicted bytes. The cohort's old-index4269->4276 includes the previously landed seven-byte ICF copy, not new coverage. Index0e4b2640a1 predates198 source-path changes, so no current whole-link claim follows.

Acceptance with mandatory Monster constructor, SupplyCenter and native Dock constructor providers passes and retires exactly one header-queue row. Its generated context is staged with the consumer and queue edit. SupplyCenter's unused-padding mapping refusal remains separate; its preparation was restored. This adoption adds no unique body bytes and establishes no game reach or bridge-count change.

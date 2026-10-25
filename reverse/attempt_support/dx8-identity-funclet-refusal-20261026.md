# DX8 identity retirement: verified funclet labels are not resolved

Inputs: BFME 2 upstream `2f9834aa34`, pinned BFME 1 `c0385ef6ba`.
The default picker served `VectorClass<RenderDeviceDescClass>::Resize` at
0x00125460 (376 bytes) in `Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp`.
The complete source was read. Its identity register holds 13 keys, including
descriptor constructor/destructor bindings and string-vector teardown bindings.
No source, ledger, pin, hatch, baseline or verifier change was attempted.

The frozen-file check passes with the existing admitted markers. Normal
`build.sh` passes 228/228 function rows, 13 data rows, 79 literals plus one
empty-string reference, 26 floating-point literals and 24 imports.
`eh_verify.py` reports all 21 EH graphs EXACT.

The retirement command refuses without modifying the register. It reports two
separate prerequisites:

1. Four participating provider objects are not current, first HeightMap.cpp.
   These need normal provider refresh before a retirement verdict is usable.
2. It demands old compiler labels for 72 funclet rows which the normal byte
   gate already resolves through verified parent EH data. For example,
   `uw_00764f30` at 0x00764F30 (8 bytes) records `$L34716`; the current object
   emits `$L34278`, and its exact parent graph places that label at the same
   retail address. The normal byte gate explicitly verifies this mapping.
   Retirement instead reports that the object defines no code symbol `$L34716`.

The second condition is a false reject of the verified funclet identity:
`repair_queue.identity_verdict` checks `build.ledger_object_symbol(row)` directly
against the object, while normal matching uses `build.read_funclet` and its
verified parent-graph resolution. This does not establish that the 13 remaining
code-identity keys are fixed. Their repairs and provider currency remain separate
requirements; no debt or byte gain is claimed here.

Tooling follow-up: reproduce the missing-label refusal with this unchanged
source, reuse the existing verified EH resolution in a separate verifier change,
and add a regression test preserving the gate-exploit refusals. Then refresh
providers and investigate the whole descriptor/vector identity family through
the normal retirement pass. Do not rewrite labels or bypass the register check
to make this source admissible.

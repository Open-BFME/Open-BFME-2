# RegisteredGeneration allocation/gap roundtrip: isolated tooling package

Sicher: this is a reproducible representation-preserving roundtrip incompatibility. It is not evidence that Gen007F0130's omitted+4/+8 fields may be accepted.

## Exact proposed scopes

* `tools/header_generation_proof.py`
* `tools/tests/test_header_generation_proof.py`

Patch: `registered-roundtrip.patch`. Baseline/proposed source SHA256s: `patch-inputs.json`. No productive tool, header, contract, register, Git or claim was edited by this worker. This package is separate from the ongoing transactor source prerequisites/merge.

## Reproducer and existing path

`RegisteredGeneration.__init__ -> proof.capture -> _elide_header` examines the literal canonical declaration before native capture. The generator/special_declarations legitimately carries an explicit static allocation method. The proof previously rejected `operator` globally, without considering its method role. The unchanged Gen007F0130 header is token-for-token the output of the actual owning generator with its current contract and declaration records (`gen-own-roundtrip.json`: true). It therefore has a reproducible own-generator roundtrip failure, independently reproduced by all8 generic AllocationRoundtrip cases (new/delete, scalar/array, with/without gap). The original tool rejects all8; the proposal accepts the supported forms.

There is a second deliberately unsupported representation: the generator's own literal char gap array. Removing only the operator regex check would still fail. The proposal does not remove the array-data gate. It recognizes only the exact gap storage that the same `layout_plan(contract)` emits, preserving the same native storage rather than inventing new fields.

## Narrow fix and retained proof

Allocation roles are recognized through the existing `class_members`, `member_role` and `declaration_records` path plus complete declaration grammar. Only explicit `static void *operator new/new[](unsigned [int] [name]);` and `static void operator delete/delete[](void *[name]);` are supported. Bodies, foreign operators/conversions, placement/sized/defaulted arguments, aliases and unrecognized roles remain refused. The original complete tokens and all words are retained for native preprocessor binding and macro collision checks. RegisteredGeneration's later declaration/owner selection remains responsible for the actual native provider; a header still supplies no ownership fact.

Gap arrays must be literal `char` storage with the owning planner's exact name and decimal extent; method role must be absent. All expected pads must occur once. The complete unmodified owning assertion suffix is mandatory for this padding form and is compared exactly. The normal native layout proof then requires exactly that name, offset, char-array element type and byte size, with no missing or overlapping region. All true contract fields retain their exact native name/type/width checks. The planner's existing primitive alignment/misalignment rules remain active; char gap storage has one-byte element alignment and introduces no alignment attribute or profile change. The native component test independently measures the resulting class alignment through a real leading-char containing object.

No scope, macro, namespace, typedef/using, aggregate/union, intrinsic, qualified type, arbitrary array, preprocessor, provenance, whole-object, receipt/profile/search, COMDAT ownership, frozen-input or mandatory-consumer gate is removed. No class-specific name, flag override, whitelist or alternate acceptance path is added. No changes to class_contract's outlier rule, generator layout policy, snapshots or assertions are proposed.

## Verification actually completed

* Default full current `test_header_generation_proof.py` (private proposal copy) plus all collected `test_gate_exploits.py`: **212 passed,7 skipped**, `tests-final.log`. Existing skips include the2 opt-in native components, unavailable Windows symlink cases and the empty audit-fixture parameter; no closed exploit test was changed or newly skipped.
* New explicit real VC7.1 native component: **1 passed**, `native.log`. The ordinary object strongly defines the allocation operator under its real mangled static signature. A separate fresh native CodeView object proves class12B, uint value+0, literal char[8]+4 and the containing-object value at+4 (alignment4). Actual compiler preprocessor tokens bind the generated header. It does not forge a full capture receipt or call a synthetic header an owner.
* The same native test compiles4 valid negative C++ variants: inline allocation body, unsupported alias, same-size unsigned-char padding and same-total-size extra hidden data. Every one is still refused by admission; the two storage mutations also fail the actual native layout check.
* Existing explicit real VC7.1 generated-declaration component: **1 passed**, `native-existing.log`, with a dedicated private class-layout cache.
* Negative control using the original unmodified tool on the new generic allocation/gap roundtrip tests: **8 expected failures**, `original-negative-control.log` (exit1 checked). Failure is the original unsupported-type-role rejection, not a native setup error.
* Current real Gen007F0130 header: original input parser refuses, proposed parser accepts under the UNCHANGED contract. Extending the contract by the unaccepted received/buffer fields still refuses the same old header (`canonical array is not exact owning-generator gap padding`). `gen-own-roundtrip.json` records both outcomes.

The earlier first-test failure was a test-layer mistake: an ordinary data member named operator_new is not an operator role and need not be lexically rejected; actual unknown data is refused by native layout equality. The test now uses an actual foreign/malformed operator role, and valid compiled hidden-data negatives exercise the correct layout boundary. No gate was relaxed to make that test pass.

The native output is private under `build/codex-thing-agent-20261120/roundtrip-native/`; native diagnostic objects use an explicit private cache. The existing optional native component used its ordinary scratch directory plus an explicit private layout cache. The normal match-cache objects/receipts were not replaced.

## Remaining limits / root actions

This does not establish a successful full RegisteredGeneration transaction for Gen007F0130, alter its current contract, or make the reply donor exact. Mandatory full-cohort ordinary byte/link/COMDAT tests and frozen input checks remain required if root later uses regeneration. Implicit default-ctor/reset declarations and genuine new fields remain separate declaration/contract questions. The5 reply scheduling differences remain untouched.

Root can review/apply this as a separate verifier change, re-run the ordinary test and exploit suites at the actual integrated head, and publish it separately before a source retirement depends on the new admission. A suitable trailer explains that native allocation-method roles and exact owning-generator gap storage roundtrip without changing class layout, assertions or proof ownership. There is no header-debt retirement or source/runtime credit in this tooling package.

## Root integrated verification

The actual integrated files pass212 default proof/exploit tests with7
existing optional/environment skips. Both explicit real VC7.1 native
components pass separately. Independent review found no concrete issue;
four additional in-memory layout cases pass while12 syntax/suffix/macro
mutations and6 wrong padding offsets remain refused. No header, contract,
profile, freeze policy, register or source adoption is changed here.

The dependent header-adoption, header-input and virtual-slot suites also
pass611/611 tests at the actual integrated head. No additional source
change followed those checks.

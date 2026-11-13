# AI-upgrade abstract callback ABI

The abstract Rva005DAA36 base table870B80 has two entries: purecall and its deleting destructor5970C9. Dispatcher59710E forwards one incoming four-byte word to child slot0, stores EAX at+40 and returns with RET4. Concrete callback5DA67F returns an integer and consumes that word. These target facts contradict the old zero-argument void slot declaration.

The contract now records the integer result and single-word ABI. The generated header keeps slot0 pure, using the existing address-derived `rva005DA67F` identifier so the concrete row can override it through ordinary virtual respelling. Its current int carrier is preserved; Player* semantics found in another family view and the original source method name remain unresolved. This is an ABI view, not a claim that RET4 proves a source int parameter.

The header was regenerated with the owning header generator after updating the contract. Size8, held pointer+4, destructor, constructor and slot count remain unchanged. The incomplete sibling Rva005DA64B::f0 still occupies its existing extra slot; its bridge debt is unchanged.

`./build.sh` passes52/52 rows across the six-unit class/base cohort. Direct before/after object comparison proves **all140 COMDAT fingerprints and all38 emitted table payloads, extents, relocations, selection kinds and weak defaults are identical**. This correction is separately verified before any concrete method gains virtual dispatch or either private base view is adopted.

[Complete before/after table inventory](ai-upgrade-base-abi-20261113-root20.json). Parent37031a30f97. Independent native review found the planned three-CPP virtual preparation coherent, subject to this sibling-table preservation proof.

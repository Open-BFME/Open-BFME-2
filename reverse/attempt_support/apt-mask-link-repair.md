# Apt property setter link repair

Base: 9ef5f16f (origin/master at selection). Published linker census:
2026-10-17 02:26, fb06805bf5; refreshed local definitions before both previews.

## Target evidence and repair

The property setter in AptCharacterSetMember.cpp used two unresolved names:
AptValue::getVtblIndex and the int-returning AptCIH::rva006E1F90.
The seven-byte type-index provider at RVA 0x006DBB30 already exists as
Rva006DBB30SarDwordField::get; use that established owner at both call sites.

The 115-byte mask-query provider at 0x006E1F90 was declared bool, although all
five retail call sites test full EAX. Its 11-byte forwarder at 0x006E24D0
preserves EAX through a tail jump, and the input dispatcher tests EAX too.
Change both existing owners to int and update their consumers together.
Four member-function pointer reinterpret casts are replaced by ordinary calls.
No new pin or duplicate function owner is introduced. The existing int query
pin now agrees with the function ledger's owner.

## Validation

- Full byte gate for all eight affected provider/consumer units: 14/14 exact.
- EH verification: 3/3 EXACT; no baselines or missing records.
- Strict new-variant linker check: passes.
- Published-census link preview with refreshed local objects: 5/8 -> 6/8
  clean units; linked bytes 1,669 -> 5,404 (+3,735 nonpadding bytes).
- AptCharacterSetMember.cpp: 0 -> 3,735 linked bytes, both unresolved names gone.
- Clip-event queue and AptInput still require AptActionInterpreter::callFunction,
  contributed separately in PR #79; this branch does not duplicate that body.
- Existing bodies are preserved byte-for-byte; this repair adds no C++ coverage.

## Donor review and larger blocker

Reviewed BFME 1 revision 3ce339fbfa7655686c7cf4d70088991e27a3062c.
Its AptLoad.cpp has a different invoke/deferred-run body and is not an
AptLinker::Load donor. BfmeConv1474 erase and Bfme5ThirtyFour getter helpers
are already present in BFME 2. This repair follows BFME 2 ABI and call-site
evidence, rather than transferring a BFME 1 layout.

AptLinker::Load at 0x006D1F80 remains blocked by four allocator choices.
The existing bank compiles to its whole 1,525-byte extent with no unresolved
calls, but differs in 11 bytes across nine instruction lines. Tests of visible
callee definitions, iterator/holder access, member-list layout, copy forms,
counter forms and 873 permutation trials did not improve it. The existing bank
is preserved; no nonmatching Load body is added to Code/.

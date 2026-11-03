# Current ObjectCreationUpgradeUpdate supports /G7

Bounded private diagnostic,2026-11-03. Current source's old comment claims /G6 is needed for the angle spill. That claim is stale for the CURRENT source: changing only the private compiler profile to /G7, while preserving every other flag and all C++ text, passes ALL3 current rows. The primary update body is exactly753B and has ZERO mismatches against retail after ordinary relocation normalization. Its complete associated EH graph is EXACT. There is therefore no current first primary-body divergence to disassemble and no clean-C++ body repair required to use /G7.

The experiment forces BOTH profiles with sanctioned Verifier(flags=...) arguments. This matters: an ordinary Verifier.effective() call already chose the region's /G7 despite the source's raw /G6 cl-line. The first script stopped at an assertion before compiling because it detected that fact; the corrected script intentionally tests explicit /G6 against explicit /G7 rather than silently comparing /G7 twice.

Explicit /G6 control retains the753B primary but fails the one static-guard cleanup row at0x0078EB92 and its actual parent EH graph: .text$x guard-and differs three unmasked sites after the one-byte and-EAX instruction growth, exactly like the seed's G6 blocker. Explicit /G7 candidate matches the primary, guard cleanup and handler (3/3) and has an EXACT parent graph. Thus /G6 cannot be treated as the known-good full-EH baseline here. Source/body history may explain the obsolete scheduling comment, but this experiment asserts only the present result.

proof.json records both actual flag sets, source control SHA, private row verdicts, primary sizes, full raw candidate/native body bytes, symbolic relocation names/offsets/types, and the complete masked mismatch calculation (zero). Candidate/native disassembly around the initial instructions is included; call/global operands in candidate.obj remain normal unresolved relocations and are named separately in the relocation list. No non-relocation byte divergence exists in the753B primary. No full-image library selection claim or census credit is made.

No tracked source, row, flag register, claim, network, shared match cache or check was changed. The explicit-profile candidate.cpp is scratch evidence. Root should apply any source-comment/flag cleanup through ordinary normal/strict/EH/link verification and separately reconcile current class-view prerequisites before a supported donor merge. This diagnostic does not land the merge itself.

Tracked follow-up: replace the stale source /G6 directive and G6-only scheduling
comment with the independently verified /G7 profile. Normal3/3 and strict
receipt verification pass. The seed's separately proven G7 profile and this
Update G7 proof provide a compatible profile prerequisite; no TU merge or
census gain is claimed. The rejected explicitG6 seed trial remains valid
negative evidence, not a blocker to this successful commonG7 choice.

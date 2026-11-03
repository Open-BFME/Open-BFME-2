# Explicit pair constructor under ConnectionManager's existing size block

ONE private repair hypothesis,2026-11-03. Control SHA256:5a791d8e770970352176af7cf953db2d535b77af86a1f6336caf2198cc558c31. Candidate forward-declares the existing _STL::pair<const unsigned short,AsciiString> two-reference constructor specialization immediately after <map>, then defines its ordinary first(a),second(b) initializer under the EXISTING size-optimization block immediately before FileCommandMap::operator[]. It adds no pragma, header/class edit, pin, alias, marker or fallback. #pragma optimize count remains9.

Control passes32/32 matched source rows. Candidate passes32/32. All FIVE actual parent EH graphs are EXACT in both. The typed pair constructor changes from32B to31B and the candidate matches the complete native0x004D04FF body exactly after its single ordinary REL32 relocation is accounted for. Its copy-member relocation remains ??0?$StringBase@D@@AAE@ABV0@@Z; at the candidate's native operand offset21, the retail call resolves0x000365F0. This is the same existing narrow copy-constructor family; no new callee binding/name is introduced. The preliminary control print's attempted retail-target calculation at offset22 is inapplicable, because the old32B constructor's instruction schedule does not line up with native; do not treat that arithmetic result as a real native call target.

The full ordinary external set remains858->858, with no additions or removals. An uninitialized-section-aware comparison changes ONLY this constructor; the other857 definitions are identical. Undefined symbol sets, weak externals and linker directives are also identical. provider-proof.json is authoritative for this complete comparison. The earlier generic definitions helper flagged TheDisconnectMenu and commandsReadyDebugSpewage because it read file offset0 for .bss instead of modeling zero-fill storage; these are audit-helper artifacts, not actual global-data changes. The owning EH COFF reader's real zero-filled section representation proves both unchanged. No repository check or helper file was modified to obtain this result.

Frozen-source inspection calls the owning find_defined_functions parser on actual control/candidate text. It reports no additional parsed definitions or new markers. Its regex inventory does NOT fully understand explicitly specialized templated constructor scopes, so that empty parser delta is not a claim of full parser coverage. The actual emitted provider name is preexisting, count does not grow, and its full31B body now matches native. Root must still run the actual path-based frozen/ordinary/strict/identity/link gates after applying against the captured source hash; debt retires ONLY through repair_queue.py retire identity SOURCE. No ledger owner rename, new row or fresh missing-function claim is made by this trial.

Artifacts: clean candidate.cpp/control.cpp, private objects, proof.json and provider-proof.json. No tracked source, ledger, shared header, claim, network, shared match-cache or check mutation occurred. This is a scoped provider repair candidate, not a broad ConnectionManager linking clearance or census gain. All tracked reads stop after this report.

Tracked application matched captured control before applying. The actual frozen
path check and normal32/32 pass, with the same54 legacy unclaimed definitions
and no new markers. Strict reusable receipt passes. The five participating
providers required by identity retirement were refreshed through one normal
build:406/406 and16data rows pass. Owning repair_queue retire identity then
removes exactly the constructor key; two other identity keys remain. No key is
removed by hand. The explicit specialization uses existing size-optimization
scope, retaining all9 pragmas and all existing pins/aliases/names.

The ordinary link preview remains UNLINKED0->0 with separate unresolved names
and the two other selected-helper defects. This is one registered-debt repair,
not whole-unit or census clearance. Private source coverage summary intentionally
omits the raw858-definition payload; provider-proof.json retains the complete
comparison verdict, actual constructor/native bytes and zero-fill semantics.
No gate or comparison policy was edited. Continue the remaining Construct and
insert_unique keys through their owning verifier before claiming full closure.

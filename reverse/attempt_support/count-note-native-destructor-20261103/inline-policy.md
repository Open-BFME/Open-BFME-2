# Count-note inline-provider policy audit

Read-only scope: AGENTS.md, `tools/find_declared_unmatched.py`, relevant frozen/link documentation, and the fixed generated-object omission logic in `tools/exit_link.py`. No builds, tests, source/ledger/pin edits, claims or network. Target/provider/header/history facts below are supplied by the owning reviewer, not independently reverified here.

## Narrow conclusion

A genuine ordinary C++ inline destructor whose complete emitted 5-byte body and relocation match the existing native destructor can be a physical provider in an already claimed, retained TU without moving the existing generated row. That is a linking repair, not source/TU recovery or new coverage. Keeping the `j_0052b7b3` row/source unchanged avoids an unapproved row move; it does not establish that `Rva0052B7B3Dtor` belongs to the CountNoteRun TU. The generated owner remains unrecovered debt.

An ordinary derived destructor with no additional work can legitimately compile to a tail jump to its genuine base destructor. Its shortness alone does not make it a stub. This conclusion is conditional on the actual complete body/relocation, receiver/lifetime semantics and selected base provider being native-correct. A fabricated empty implementation, a manual alias, or forwarding to an incorrect body merely to remove an undefined name would not satisfy it. The owner is separately repairing the genuine 57-byte base destructor in its existing established row source; this audit does not certify that proof.

## Frozen-file handling is narrower than the prose

`docs/matching.md:777-806` requires the owner to run `find_declared_unmatched` before and after work, remove stale markers, and revert if it still refuses. Its remedies for a reported real body are rowing it, or an honest `absent-from-retail` marker only when retail actually dead-stripped it. This native 5-byte destructor is not absent from retail. Hand-added `present-unmatched` and whitelist growth are not remedies.

`tools/find_declared_unmatched.py:157-165,268-295` inventories qualified out-of-class definitions. The word `inline` does not exempt an out-of-class `inline Class::~Class()` definition. An ordinary in-class `~Class() { ... }` has no `Class::method` shape and is not inventoried by this parser. Therefore a passing check on an in-class body is a mechanical result, not proof of identity, byte matching or TU approval. Do not change spelling or add a false marker merely to evade a refusal.

At 396-429, a bare full-symbol annotation is accepted if declared, and an unannotated method is accepted if its mangled method/class prefix matches a matched row anywhere. The checker does not establish exact overload identity or source ownership. Lines 366-368 explicitly recognize that a body may physically occur in one source while its matched owner remains in another; markers for a body matched from the current source are stale. This is compatible with real inline/COMDAT copies, but does not itself prove that a new typed spelling denotes the old generated thunk.

## Generated-thunk omission

`exit_link.py:87-95,117-125` identifies exactly 17 placement-only TUs: `Code/gen_small/uw_gen_000.cpp` through `uw_gen_014.cpp`, `gthunks_000_admitted.cpp`, and `thunks_000_admitted.cpp`. `link_setup` excludes their objects at 566-573. That operation changes neither row ownership nor recovery status.

The proof at 144-159 and 287-324 examines every kept object's undefined, weak and `/INCLUDE` references. The refusal at 681-683 covers references to any omitted external name, even when another kept object also defines that same name. The typed destructor must therefore satisfy its typed consumers without retaining a reference to the omitted generated `j_` name. Adding a physical copy under the old generated name does not automatically satisfy the omission proof.

## Remaining owner obligations

- Run the normal frozen-file and byte/EH checks on the actual resulting source. No check was run by this audit.
- Prove the entire typed 5-byte body and relocation to the genuine selected 57-byte base destructor, including the correct receiver and automatic lifetime chain. Preserve the other rowed bodies/providers.
- Check actual kept-provider selection and affected consumers after removing the two obsolete manual aliases; ensure neither stale aliases nor references to omitted generated names remain. A passing omission proof is separate from byte/ABI/identity proof.
- Retain the original generated row/source unchanged, add no second address claim, and claim no TU approval, generated-row recovery, unique bytes or census/runtime clearance. Future row rehoming still requires current approved TU evidence and the supported tools.
- Update the existing linking obstacle/handoff with verified scope and remaining ownership debt. Obey normal hooks and batch link admission; inconclusive consumer results remain unverified.

No blanket prohibition on a physically matching ordinary inline copy was found. This is conditional legitimacy for a genuine native provider, not a gate waiver or permission to conceal an unapproved row move. Tracked reads stopped after this report.

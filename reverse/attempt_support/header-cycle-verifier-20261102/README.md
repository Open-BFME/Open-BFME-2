# Guarded intermediate include-cycle verifier repair

The previous include walker refused an unguarded repeated entry even when
a fully guarded intermediate header terminates the cycle. Collect the same
complete literal include graph, retain all bodies for macro/hierarchy checks,
remove only stable full-file guard vertices, and reject cycles in the remaining
graph. A guarded ancestor outside a cycle and an alternate unguarded route
through a previously seen node must still fail. No path exemption or new
permissive guard shape is introduced.

Guard reset evidence is conservative across the entire discovered closure.
Splice preprocessing lines before lexical masking. Literal #undef and its
digraph/whitespace spellings invalidate that guard; pop_macro and __pragma
forms invalidate literal guard names, and unknown/aliased reset operations
invalidate every guard proof. Saving a macro alone does not reset it. The
existing literal-include model is unchanged; this does not implement macro-
computed include expansion or a general preprocessor.

Final regression verification:229 header/adoption/bulk/decision tests pass.
The required exploit suite retains61 passes and one existing skip. Independent
review exposed digraph/whitespace and aliased reset cases; all are added as
negative regressions and refused before this commit. Tests use temporary Git
repositories with expected newline normalization; no main checkout hook is
bypassed. The final code has no Code or ledger policy change.

The focused original STLport graph contains51 files and eight stable full
guards; its residual unguarded graph is acyclic. The actual strict walker
now reaches a separate unchanged continued-comment refusal at
vendor/stlport-4.6/stlport/config/stl_dec_vms.h:50. Its witness is retained.
Do not call this a completed Carryover header adoption or bypass that refusal.
The parent declaration and header queue remain unchanged. A later source pass
must still use the owning adoption/acceptance and all ordinary byte/data/EH/
consumer checks. This verifier-only fix is separate from the already published
game-source prerequisites and claims no matched/linked-byte or debt gain.

# FadeInTextRender destructor placement review

Read-only review, 2026-11-06. No builds, claims, network, source edits or ledger
edits were performed. The root is verifying the actual composition and current
provider selection independently.

## Supported path: existing ICF-alias exception

The native seven-byte body at RVA `0x00596686` has two genuine ledger identities:

* The first non-`gen-alias` identity is
  `?apply@Rva00596686DwordImmSetter@@QAEXXZ`, owned by
  `Code/GameEngine/Source/Common/Disp0DwordImmSetters.cpp`.
* The later identity is `??1Rva0059675ABase@@UAE@XZ`, owned by
  `Code/GameEngine/Source/Common/Rva0059675ADtor.cpp`. Its existing evidence
  states the complete destructor is the same seven-byte body and is called by
  two retail unwind funclets. It is not a new name or new fold.

`tools/tu_skeleton.py:519` implements `fold_alias`: the row is in the current
ledger and its `(name, source)` differs from the first non-gen-alias row at its
address. This destructor meets that predicate. In `donors`, the foreign-row
filter explicitly excludes `fold_alias(r)`; a genuine secondary identity does
not make its file mixed, even when the map gives the shared address no TU.

The existing test `test_an_icf_alias_makes_no_file_mixed` demonstrates this rule
for ordinary destructors. `docs/consolidation.md`, in the splitting workflow,
explains that the map places the address's identity rather than every ICF alias
and that such aliases travel with the file emitting them. This is separate from
the narrower `tu_map.homeless` rule.

Therefore the supported ordinary merge should be tried without changing the
destructor's classification or inventing approval. The unmapped first identity
does not itself require a new TU approval for this existing folded destructor
to follow its verified emitting donor. Every other row, compile result and
link/selection guard still applies. If the current tool reports this exact
secondary row as a foreign/mixed blocker, preserve the precise refusal and
investigate its cache/input/version rather than modifying annotations.

## Rejected route: manually declaring the row homeless

An `inline` note in `functions.csv`, or merely spelling the C++ definition
`inline`, is not the mapper's documented evidence.

`tu_map.evidence_rows` derives its inline flag from reference-header COMDAT
evidence (`header_comdat`) or independently recognized implicit copy
construction (`implicit_copy`). It emits the map's exact `inline` evidence
token from that flag. Current C++ spelling and arbitrary ledger notes do not
drive this classification. `tu_map.homeless` accepts that generated token,
template-instantiation names, or its compiler-generated COMDAT-name patterns;
the ordinary complete-destructor spelling `??1Rva0059675ABase...` is not one of
those patterns. The current map's address identity is the setter and has no
inline token or TU.

Adding or injecting an inline classification solely to admit this move would
not establish retail header-inline provenance and would be a classification
bypass. Do not do it. An actual codegen need for C++ `inline` may still be an
ordinary separately verified source change, but grants no TU approval by itself.

## Provider-selection implication

Root's current-object evidence identifies a 28-byte out-of-line-call base
deleting destructor in the seed and the native 29-byte inline-vptr-store form
in the dedicated destructor donor. The three-source composition is the
preferred trial because bringing the existing complete destructor into the
same TU can produce the correct native wrapper without introducing aliases,
pins, annotations or invented placement. This review did not compile or
independently remeasure that composition and does not claim a passing merge.

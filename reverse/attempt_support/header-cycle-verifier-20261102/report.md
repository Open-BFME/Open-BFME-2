# Header include-cycle false reject — read-only investigation

**Recommendation: worth a narrow verifier fix in a separate commit**, with
regression tests. The refusal is a structural false positive; do not edit the
STLport headers, add a path exemption, narrow angle-include candidates, bypass
the owning lane or land the Carryover header swap before its normal checks.
The root has already banked the refusal while publishing the verified Code
prerequisites. This investigation changed only scratch evidence.

## Reproduction and exact cause

`tools/header_adopt_lane.py:346` recognizes complete outer `#ifndef G` /
`#define G` guards. `include_walk` at370 traverses literal include inputs,
collecting all existing angle candidates deliberately. At381–384 it refuses a
back-edge unless the **repeated entry file itself** has a complete guard.
That condition depends on where traversal entered an otherwise safe cycle.

Minimal files are in `minimal-repro/`:

```
unit.cpp: #include "A.h"
A.h:     #include "B.h"
B.h:     #ifndef B_H
         #define B_H
         #include "A.h"
         #endif
```

The current `include_problem` refuses A.h. A preprocessor terminates the
recursion at B.h's second encounter: its guard is already defined. Reversing
the top-level entry to B makes the existing check accept the same cycle.
The existing cycle test covers only a guard on the repeated entry, missing
this interior-guard case.

A focused real reproduction is a unit containing only `<string.h>`, with the
STLport4.6 stlport/base and actual VS2003 include roots. Its first back-edge is:

```
string.h -> stl/_prolog.h -> stl/_config.h [guarded]
         -> config/stlcomp.h [guarded] -> config/stl_como.h
         -> math.h -> stl/_prolog.h
```

The checker reads all conditional branches, so the Comeau branch also enters
the graph under the MSVC environment. `string.h` and `_prolog.h` intentionally
support repeated inclusion and must not receive invented guards. The outer
header-ID sentinel is not a full include guard. Different traversal context
reports string.h rather than _prolog.h; the structural defect is the same.

`minimal-real-trace.json` records the exact paths and roots. Read-only complete
graph analysis (`real-graph-proof.json`) finds51 literal-closure files and
eight complete whole-file guards. No guard macro is undefined anywhere in
that visible closure; no push_macro/pop_macro tokens occur. Removing these
eight guarded vertices leaves **no unguarded cycle**. The original/canonical
seed private compilations already succeeded independently; this is not an
attempt to suppress a real compiler include failure.

## Safe shape of the fix

Keep existing file loading, comment/trigraph refusals, quoted resolution,
all-candidate angle traversal and macro/hierarchy scans. Only change cycle
classification:

1. Discover the entire existing literal include graph, retaining every edge.
   Active recursion may stop expansion of an already active file, but must
   not reject or erase that edge. Preserve the complete source list.
2. Determine stable complete whole-file guards using the current strict
   guard shape. A guard is ineligible if any header in the visible closure
   contains a literal `#undef` of its macro. Join backslash-newline directives
   before scanning invalidations, matching preprocessing phase2.
3. Treat `#pragma push_macro/pop_macro` and MSVC `__pragma(...)`, including
   uses in macro definitions, conservatively. A literal guard name invalidates
   that guard; an unparseable reset argument invalidates all stable-guard
   proofs. Escaped/concatenated/dynamic reset arguments must not accidentally
   count as harmless. No new permissive guard form or path whitelist is needed.
4. Remove only the stable guarded vertices and run iterative three-color DFS
   over the remaining graph. Refuse an actual residual cycle. This is O(V+E)
   and avoids Python recursion depth on long include chains.

This is sound for the checker's existing literal-include universe: every cycle
must pass a guard that remains defined. Macro-computed includes are already
outside this walk's model; this patch should not pretend to implement a
preprocessor or expand that existing scope.

Do **not** merely accept if any active ancestor is guarded: a guarded root
outside an inner A<->B cycle does not stop that inner loop. Also do not merely
accept if a guard occurs on each DFS back-edge: the existing `seen` shortcut
can hide an alternate wholly unguarded cycle. Example: unguarded A includes
guarded B and unguarded D; B includes C; C includes A; D includes C. The first
observed cycle crosses B, but A->D->C->A remains unguarded. Whole-graph residual
analysis catches it.

## Required tests and impact

Extend `tools/tests/test_header_field_renames.py` near the existing tests at419:

- Accept unguarded A -> fully guarded B -> A, retaining both bodies.
- Keep the existing repeated-entry guarded cycle accepted and wholly
  unguarded cycles refused.
- Refuse a guarded ancestor outside an unguarded inner cycle.
- Refuse the alternate-cycle/seen counterexample above.
- Refuse partial guards and outer-guard else branches as guard evidence.
- Refuse a would-be guard reset by self/cross-header `#undef`, including a
  directive joined across a splice.
- Refuse reset through both pragma spellings, in macro definitions too;
  unknown reset arguments must not create stable guards.
- Preserve all-angle macro-shadow coverage (`test_r5_angle_macro_shadow_all_candidates`),
  unresolved quoted include, trigraph/comment-splice and conditional-member
  refusals. A guarded cycle containing a watched macro must still expose it
  to `macro_shadow`; successful cycle classification never means skipping it.

Run the focused header-field/header-adoption tests and every existing
`tools/tests/test_gate_exploits.py` case; the latter must retain its refusal
behavior. Keep the verifier change and regression tests in their own commit
with the required Verifier-Change trailer, then retry the owning Carryover
adoption normally. No full game/global gate was run here. The51-header focused
case proves this cycle eligible; other whole-seed adoption checks remain
independent and may report further real prerequisites.

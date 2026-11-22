# AptMyHero native composition: class-provider context, not an operator parser failure

**Certain:** the unchanged native composer reproduces the saved normal source text
exactly and the unchanged native compiler reproduces its first errors. The operator
is tokenized and emitted intact. No production source, tool, ledger, index, claim,
Git or shared object was changed by this worker. No task/body/byte credit is claimed.

## Exact binding

Original source base: `55dd91d046f25ce01a961f2582867b2b620dcdcf`.

- AptMyHero.cpp raw SHA256 `9555de3d9ff7e257c1c7179ec59ff8141ee5535e9f212e22ff8d736de7555a28`.
- AptMyHero_Unresolved.cpp raw SHA256 `0b7f226bec8cc35e0ffdaea8c8f20bedb7fd908fc1a790052ae93f9ad0a82a3a`.
- Native tools/tu_skeleton.py SHA256 `05a807f431834f7ac74fd1c1c05a28be9567f63fdeef2a737f490a7fc8f73291`.
- Full reproduced native composed text SHA256
  `10c3d60fa2be2b44f8004e31f21d1c04fa406545515b57a993908ca33a665451`;
  exactly equals the selected-rejection context in Root's original log.

The original selected diagnostic was extracted with ast.literal_eval from only the
`compiler_diagnostics:` record of `bfme2/apt008-window-native-tu-dryrun.log`, then
only its AptMyHero_Unresolved donor was selected. No full functions.csv was loaded:
the replay streamed the102 approved target RVAs and their actual ledger identities.
Root's later Matrix adoption does not silently change this source-base assertion.

An initial log-reader rerun unnecessarily resnapshotted the now updated production
sources into PRIVATE diagnostics. The immutable55dd snapshots were restored by
reversing the exact already measured Matrix-only private patch and requiring both
original raw SHA256s above. The complete normal-text hash independently confirms
the reconstruction. The reader is now guarded and cannot replace an existing bound
snapshot. No production source was restored or overwritten by the child.

## Native control flow and actual cause

1. `chunks` and `composition_chunks` classify the seed's complete
   `__forceinline Vector3 operator-(const Vector3 &a){...}` as `def`.
   No operator keyword, minus token, argument or function body is lost.
2. `compose` preserves definitions before a donor's last include in the preamble
   (`tools/tu_skeleton.py:1191-1198`), intentionally preserving header/inline context.
3. Normal redefinition repair (`3515-3524`) discovers Vector3 still redefined after
   donor-local removal, and retries with `drop_all={Vector3}`. The actual recorded
   context is strategy `union-first`, drop `ImageCollection,Vector3`, drop_all `Vector3`.
4. The drop at `1216-1217` removes the early seed class. Its free operator remains
   in the preamble at composed line87. The canonical `Vector3Data.h` include from
   the later donor occurs at composed line935. No complete Vector3 provider is
   visible at the earlier definition.
5. The normal compiler consequently reports C2143 before `-`, C2433
   `__forceinline not permitted on data declarations`, then C2501 unknown Vector3.
   Private replay of the exact normal input emits the same first diagnostics at87.

This is declaration/provider ordering after class-view removal, not a demonstrated
operator parser bug. The original code itself contains two independently valid
contexts; compiling59/59 in separate translation units does not establish a common
class definition or that their linked/provider contracts can be combined.

## Why this actual merge is not established as a false reject

The seed private Vector3 has `const float &operator[](int) const`; the canonical
class independently proved by retail004047D9 returns `float` by value. The latter
is already used by Unresolved. They are different real signatures/mangled providers.
The prior canonical Vector3 source study also retained only42/43 seed rows: the
971B Sun function had24 true nonrelocation differences. Canonical Matrix3D adoption
alone later preserves59/59, but does not solve that Vector3 difference.

`docs/consolidation.md:100-116` explicitly calls for rejected class views to be
reconciled against common/canonical headers and verified before merging. The actual
normal log already lists Vector3 in `adopt_first`. The current inputs have not
met that source prerequisite. A rewrite that merely places the canonical header
earlier does not prove Sun exactness, complete providers or a safe final merge.

Therefore no gate fix or source workaround is proposed for this actual pair.
There is not yet an independently verified exact merge that the checker wrongly
refuses, so this finding should not be recorded as proven safe-merge false rejection.
Keep it tied to the pending Vector3 prerequisite and existing source-study evidence.

## Independent minimal causal fixture

`aptmyhero-composer-minimal.py` creates only private scratch sources and invokes the
unchanged native `compose` and isolated native compiler. The fixture intentionally
models the real reference-return/value-return class-view difference; it claims no
engine row or byte equality. Results in MINIMAL-RECEIPT.json:

- Seed alone: compiles.
- Donor alone with canonical provider: compiles.
- Normal compose with drop_all: fails C2143/C2433/C2501 at its early operator.
- Independent minimal provider-before-use control: compiles.
- Negative control with no class provider: still fails the same real compiler checks.

This establishes the source dependency as the cause. The corrected-order toy is a
control, not a patch to AptMyHero and not a declaration of actual merge safety.
All compiler sources/outputs are under the transport-private build directories;
BFME_OBJSTORE=off and all compilers ran serially.

## Bounded follow-up recommendation

First finish the existing canonical Vector3 source/ABI prerequisite with all actual
rows and providers exact; then use the normal TU merge again. Preserve ordinary
byte/link/provider/claim/hook checks. No source copies, flag/headerguard tricks,
fake annotations or body omissions are justified by the displayed C2143.

A separate generic composer investigation could examine dependency-aware placement
after a type provider is dropped. It would need an independently equivalent-view,
byte/provider-preserving minimal positive case before calling it a false reject;
moving every function or include globally would violate existing context contracts.
If Root opens that separate tooling task, record the native false reject and reserve
tools/tests first. This study changes no composer semantics and supplies no gate patch.

Main receipts: NORMAL-REPLAY.json, MINIMAL-RECEIPT.json, INPUTS.json.
NORMAL-COMPOSED-55DD.cpp.txt and the two hash-guarded original source snapshots are
retained privately for reproduction. A full-image link/runtime/CRC gain is not claimed.

# ResourceGatheringManager conditional include proof: blocked implementation

Inspected `e00363180fb426f0fb0d38a03c3d9c97ef3308c1`, 2026-11-13.
Owner: `codex-root20-rgm-conditional-includes-r24`. This is diagnostic
evidence, not a gate correction, adoption, byte pass or runtime result.

## Result and scope

The current refusal is reproduced. A safe correction needs an ordered,
compiler-bound include/macro proof, beyond adding positive names to the
existing closure-wide absent-name fixed point. No production tool, test,
source, header, baseline, queue or admission was changed. The earlier
method-only fix `07148c0226a` and its structural checks remain intact.
No ordinary source adoption was retried: the required separate tool fix
has not been established. The published inline-cast candidate remains at
`rgm-opaque-header-20261113-root20/candidate.cpp.txt`; its old 8-row/952-byte,
22-COMDAT result is not a fresh result of this attempt.

Only this delegated worktree and its `build/r24` scratch were written.
The root publication environment was read and sourced without changing it;
the owner and its injected hooks-path override were then set for this
worktree. `worktree_setup.py prepare` established the worktree configuration,
and `check` passed with `.githooks`, own submodule gitdir, full checkout and
pin `946f3c05a1b1e60448734e874a8f47f8017cfdb9`. No other checkout's build or
checkpoint was used. The shared account clock and landing lease were retained.

## New compiler and configuration evidence

The adjacent `diagnosis.json` records the revision, original source/header
hashes, exact compiler command/fingerprint, native opened-file hashes and
preprocessor output hashes. These are diagnostic observations, not reusable
gate receipts. Its reproducer is `diagnose.py.txt`: copy it to this checkout's
`build/r24/diagnose.py`, load the normal configured Python/toolchain
environment and run `python build/r24/diagnose.py`. It writes scratch probes
and output under `build/r24`, and asserts the original source stays unchanged.
No hand invocation of the `tools/build.py` CLI occurs.

* The ordinary walker reads 92 files before refusing
  `vendor/stlport/pthread.h: unresolved include /usr/include/pthread.h`.
* A diagnostic in-memory addition of `__SUNPRO_CC` and `__HP_aCC` to the absent
  names (restored in `finally`, never used to adopt anything) reads 266 files
  but still refuses: `(<afx.h> resolves nowhere)`. This confirms the second
  blocker independently on the current checkout.
* Native MSVC preprocessing succeeds with the original unit's effective
  compiler command/options and `/E /showIncludes`. The wrapper adds only
  diagnostic marker tokens before and after including the original source
  by its exact path. There are 68 actual inputs including that wrapper.
* Initially `_MSC_VER` is defined; `__SUNPRO_CC`, `__HP_aCC`, `__MWERKS__`,
  `__ICL`, `__COMO__`, `_STLP_MSVC`, `_STLP_PTHREADS` and `_STLP_WIN32` are
  absent. After the unit's includes, `_STLP_MSVC` and `_STLP_WIN32` are defined
  and `_STLP_PTHREADS` remains absent. `config/stlcomp.h:43-45` derives
  `_STLP_MSVC` from `_MSC_VER` in the real closure. `_threads.h:93-98` needs
  that positive state to dismiss the non-MSVC/MFC alternative.
* `census_receipts.snapshot` provides input/preprocessed-stream currency,
  not conditional-position macro state. `#line` is display provenance;
  it must not become include-identity evidence. `/showIncludes` reports
  opened files but does not identify every skipped edge or macro mutation.

## Why the smaller designs were rejected

The native probes all exit zero and assert their expected markers. Seven
cases demonstrate a live conditional edge: definition after the edge,
undef/redefine, push/undef/pop, mutation in an included header, `/DCONFIG=1`,
`/U_MSC_VER`, and mutation through a macro-built include operand. Except for
the intentionally absent final CONFIG in the `/U` case, the final CONFIG
state is present while the earlier edge is live. An end-state dump cannot
prove an earlier condition; an initial dump alone cannot prove a later one.

The same-header mutation case keeps the probe source, compiler command,
include identity and final CONFIG state unchanged. Changing only
`mutator.h` from `#define CONFIG` to `#undef CONFIG` activates the edge.
The recorded input hash changes. Hashing merely the source, final macro
state or previously resolved include identity would miss this dependency.

Six synthetic structural cases assert the existing walker still refuses
the missing quoted include: late definition, undef/redefine, macro stack,
unknown/unread angle header, source `/D`, and source `/U` of a native macro.
These are executable diagnostic regression assertions, not new gate tests
or a claim that a future proof implementation has passed its regressions.

Rejected approaches: extend NEVER_DEFINED; treat all compiler-defined macros
as permanently present; infer presence from any closure definition; take a
post-include dump as global state; ignore unresolved or macro-built headers;
accept a native compile/byte result in lieu of structural checks. In
particular the existing traversal is file-deduplicated and unordered for
macro purposes. It reads all literal alternatives, ignores macro-built
include operands, and returns early on the first unknown quoted missing
edge. Adding a `defined` set to `branch_walk` does not fix those properties.

## Proposed implementation boundary

This is an implementation contract, not an implemented or reviewed proof:

1. Separate discovery from validation. Keep existing original-text scans and
   structural checks, collect unresolved edges, and ask a proof provider
   only about exact `(file identity, logical directive offset, include
   context)` edges. An absent proof retains today's refusal. No caller may
   supply a trusted dict/set of compiler or configuration macro names.
2. Bind the proof to the actual effective compiler command, selected profile
   and executable inputs, C/C++ language mode, sanitized compiler environment,
   all `/D`, `/U`, `/FI` and include-search inputs. Probe native initial state
   using that configuration, not a table of platform assumptions. Treat
   unsupported command/probe behavior as unknown, never as macro absence.
3. Replay conditionals, definitions, undefinitions and includes **in order**,
   with context per entry. A tri-state evaluator may handle a conservative
   subset; unsupported expressions, macro expansion, pragmas or resets join
   to unknown. `#elif` must retain prior-arm reachability; unknown arms must
   merge state conservatively. A definition in a possible arm is not a
   guaranteed definition. Do not silently promote closure-wide facts.
4. Macro-built includes and native search resolution need witnessed target
   identity at the relevant edge or a supported exact resolution proof.
   A bare list of native opened files is insufficient. Unknown/unread
   headers invalidate dependent positive **and** negative facts. Include
   guards may cut recursion only with stable guard state in that context;
   all push/pop/reset operations must be modeled or invalidate the proof.
5. Bind original source, canonical seed and all relevant header bytes and
   search identities before/after proof collection and use. Header changes,
   newly shadowing files, changed flags, unread inputs and context changes
   must invalidate it. A canonical seed remains its own identity, with the
   unit's configuration, not an appended include susceptible to shadowing.
6. Keep macro-shadow, conditional class declarations, hierarchy/base/layout,
   whole-file guard and complete compiler/native verification checks. Use
   original text for structural scans; never replace it with a preprocessed
   stream that hides declarations or unsafe macros. No source-specific or
   platform-name exceptions. The proof can only explain an inactive edge.

The actual STLport closure combines unknown numeric conditions,
macro-built include operands and repeated prolog/epilog macro resets. A
limited evaluator may safely remain inconclusive; it must not claim the
Windows positive case passes until those contexts are proven. This is the
specific larger transaction/proof prerequisite that blocks this attempt.

## Required regression matrix and next action

The implementation must demonstrate positive acceptance for the real
Windows/STLport closure with the source's actual flags and canonical seed.
Pair that with hostile mutations of flags, reachable definitions, define
ordering, unknown/unread headers, macro-built includes, undef/redefine,
push/pop (literal and macro operands), header bytes, search-order shadowing,
seed identity, unknown arithmetic and cycles with reset guards. Positive
controls must be accepted; the same proof must refuse after each invalidation.
Existing exploit cases must remain refused, including the method-only
header's lost-field/base and macro-shadow controls. None of these future
acceptance results is claimed here.

After that separate verified `Verifier-Change` tool commit: acquire the
ResourceGatheringManager class/source/header/eight-RVA scopes, reproduce
the inline-cast candidate, use ordinary `adopt`, `./build.sh`, strict provider
preparation and owning `accept`, and compare every emitted COMDAT's contents
and relocation identity. Keep the header unchanged and preserve center's
native +8 iteration/+4 erase. Do not touch PlayerInitFromDict, lifecycle
Snapshot/getter/empty-provider prerequisites, AIUpdateInterface, Object's
base, Eva, or any parent checkpoint as part of this repair.

## Validation and limits

`check_csv.py`: OK (101115 function rows, 9276 symbols, 2361 data rows).
Unchanged HEAD suites: header_adopt_lane, header_field_renames,
header_dependents, header_vslots, header_run_all, header_key_backref,
header_decision_items, ledger_guards, ledger_guard and gate_exploits:
**958 passed, 1 skipped**, 122.70 seconds. The skip is the existing empty
fixture. Native diagnostic and structural assertions all pass.

Initial setup-only invocations failed because the sandbox could not read
shared Python dependencies, and an initial pytest command omitted creation
of its basetemp parent. Both were corrected and the full listed suite rerun
against unchanged production code. No unrelated Windows baseline failure
is being waived or hidden. Source/header/tool diffs are empty.

No native candidate build, full source COMDAT comparison, provider preparation,
acceptance, real link, nightly or game smoke was run. The parent recovery
goal remains active and incomplete. The supplied latest measurement is
historical context only; this task establishes no game/runtime progress.

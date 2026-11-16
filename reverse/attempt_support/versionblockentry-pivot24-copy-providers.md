# Version record copies: native and caller evidence

Baseline: VersionBlockParser.cpp passes 50/50 but its COFF undefined set holds
both ??0VersionBlockEntry@@QAE@ABU0@@Z and ??0Pivot24@@QAE@ABU0@@Z.
The diagnostic runtime stops in the former's int3 stub before menu.

Rejected trial: an inline two-string base copy and an inline derived copy
emit a correct 61-byte base but an incorrect 18-byte derived wrapper. One
insertion_sort caller swaps mov ecx,esp and its saved-ESP store (49/50).
This trial is replaced, not committed as source.

Accepted VersionBlockEntry change: direct m_key/m_value members, explicit
views into the unchanged vector element footprint at two push_back calls,
and the inline definition placed after the existing callers. The string copy
specialization calls the existing native string owner instead of emitting
another implementation. No flag override or pin changes.

Verification on base 88d393186b:
- Official build.sh: 50/50 functions, two string literals and one empty-string
  reference, one import; existing EH: 9/9 EXACT.
- link_census.RetailTruth judges the emitted VersionBlockEntry copy 61B retail.
- eh_verify.verify with this symbol at 00427F75 reports EXACT, no missing object.
- tu_skeleton.provider_definitions before/after: only the constructor added;
  no retained body changed or disappeared.
- Scoped link_check: VersionBlockEntry resolved, Pivot24 remains unresolved.
  Census baseline is stale; this is not a full-link verdict.

Local logs: build/decal-diagnostic/version-copy-trial.log,
version-direct-trial.log; baseline object version-before.obj.

Pivot24 follow-up on 4f768982c3:
- Rejected member-wrapper copy: altered callers' ESP-save ordering and one
  funclet placement. Log pivot-copy-trial.log. Replaced before commit.
- Direct two-string members and definitions after callers produce the native
  61-byte copy and 65-byte destructor. Initially five callers could not resolve
  the newly emitted destructor (pivot-direct-trial.log).
- After claiming 00238580 and checking pin_consistency, official
  pin_admission --add with fold-proof=Code/GameEngine/Source/Common/VersionBlockParser.cpp
  proved and admitted the destructor, updating its hatch counter automatically.
  No hand-written alias, thunk, flag override or masked body was used.
- Official build: 50/50, all string/import references pass
  (pivot-fold-verified.log). Existing EH 9/9 EXACT; direct EH checks for both
  constructors and the destructor EXACT, no missing objects. Both copies are
  61-byte retail according to link_census.RetailTruth.
- Relative to version-fixed-before-pivot.obj, only Pivot24's copy is added;
  no providers removed. Changed providers: the destructor and its five direct
  callers (Insert, PushHeap, AdjustHeap, Partition, PopHeap). The callers now
  bind the complete destructor directly; all five match retail.
- Scoped link_check reports LINKS, 2965 own bytes, no missing constructors.
  Its census is still 0534e78db3 (16:28), so this is not a fresh full link.
  pin_consistency --check passes (0 new/stale conflicts).
- The VersionBlockEntry commit hook reported a shadow code-identity finding
  for the parser's _Vector_base constructor. Provider comparison with the
  pre-change object shows the caller and callee unchanged; this work does not
  claim to repair that pre-existing finding.

Next: fresh full link including both commits, then Windows menu/selection
testing with that image. Do not skip executed diagnostic traps.

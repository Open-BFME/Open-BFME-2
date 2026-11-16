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
Next: implement and verify Pivot24 separately, preserve all caller bytes and
the constructor's complete EH graph, then obtain a fresh linked image for the
manual Windows menu/selection test. Do not skip executed diagnostic traps.

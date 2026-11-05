# LinearCampaign erase: explicit-body and tag boundary

Base: `9f8815d896`. Target: range erase at `0x001EBDFA`, 51 bytes,
owned by `stlport_vector_bfmeassignrecord172_erase.cpp` and approved for
`Code/GameEngine/Source/GameLogic/System/LinearCampaignManager.cpp`.
This is an existing matched provider and consolidation prerequisite, not a
missing row. No source, ledger, flag, alias or debt change is retained.

The fresh supported planner and merge dry run found 112 approved rows,
18 whole source owners including the seed, and 12 mixed owners. No donor
was accepted; the tool exited 2. The erase donor still fails the merged byte
check. Other donors retain private-view, STL declaration and codegen blockers.
This confirms the prior seed-suppression boundary in
[the earlier attempt](linear-campaign-erase-seed-boundary-20261103-codex.md).

The new trial supplies an explicit erase member body rather than merely
instantiating the header member beside the seed's specialization declarations.
VC6 emission and byte comparisons narrow the remaining problem:

| Trial | Result |
| --- | --- |
| Explicit member body, with or without `template <>`, without a following instantiation | No erase symbol emitted. |
| Member body followed by explicit instantiation, calling `__copy` directly | Body emitted, but an extra null argument and `add esp, 0x1c` replace retail's wrapper call and `add esp, 0x18`. |
| Same emission pattern, selecting the const-reference `__copy_ptrs` overload through a typed function pointer, value-initialized empty tag | Extra local initialization and frame allocation. The `_TrivialAss()` spelling has the same result. |
| Same overload selection, uninitialized local `__false_type tag` | 50/51 normalized bytes: only the tag-address displacement differs. |

The verifier's normalized byte streams differ at offset 7:

```text
retail:   55 8b ec 56 57 8d 45 0b 50 ff 75 08 ...
attempt:  55 8b ec 56 57 8d 45 0f 50 ff 75 08 ...
```

The remaining displayed bytes, including both normalized calls, stack cleanup
and return, agree. The attempt puts the empty tag at `[ebp+0x0f]`; retail uses
`[ebp+0x0b]`. This is compiler-temporary placement evidence, not recovered
element identity or proof that the replacement would preserve COMDAT selection.
The replacement has not passed a merged byte check or consumer link audit.
The commit hook correctly refused a `reverse/attempts/` stash for this already
matched address. That partial verdict was retracted through `re_log.py`, the
stash was deleted, and a blocked consolidation verdict records these findings.

A separate seed trial removed the three erase suppression declarations and
specialized the allocator overlay's by-value, forceinline `__copy_ptrs` to call
the const-reference overload. Declaring both generic overloads causes VC6
`C2668` at STLport 4.6 `_vector.h:474`: the header's erase call is ambiguous
between `__false_type` and `const __false_type &`. A typed pointer inside the
wrapper does not resolve that outer call. This trial was also reverted.

Next: preserve the header template's empty-tag lifetime/placement while choosing
the retail const-reference wrapper, without making the header's unqualified
call ambiguous. A matching replacement must also preserve COMDAT/provider
selection before any seed suppressions are removed. Keep LINK-040's separate
element-family identity question open. Do not remove the suppressions alone.

Restoration verification:

- Both `Code/` files exactly match the base commit; no nonmatching trial remains.
- `./build.sh` on the seed and donor: 56/56 rows, one data row, three string
  literals, and float/import checks pass; 18 funclet pins verify.
- `find_declared_unmatched.py` on both sources: all defined functions matched.
- Ordinary restored-source link preview against the `3fbce7bcb2` index
  (2026-11-04 22:01): both providers LINKS, with current dependency receipts
  reused. Seed: 2,613 census bytes -> 2,817 authored bytes; donor: 51 -> 51.
  These are predictions, not new census figures or gains from this attempt.
- No source files moved and no debt keys or hatches were retired. The cached
  objects saved before iteration contained older providers, so they are not
  treated as current baseline fingerprints.

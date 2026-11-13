# Rva002D9531 shared partial prefix

This drains the second queued class in `Rva002D9531CondSetter.cpp`, after
the sibling position-setter adoption in `21842c90743`. Work and claims
belong to `codex-01a1071d-root-isolated-r20` in isolated `build/r20`.

## Target facts

Retail RVA `0x002D9531`, 28 bytes, independently checked against the
worktree's baseline image:

```
8b 41 38 6a 02 5a 3b c2 74 05 83 f8 06 75 0a
8b 44 24 04 89 41 34 89 51 38 c2 04 00
```

The selector dword at `+0x38` must be two or six. Only then does the method
store its argument at `+0x34` and write two to the selector. It consumes a
prefix through `+0x3B`, not a proven complete object of size `0x3C`.
`BfmeAudioEventPrefix136`'s owner constructor and position worker support
an owner-ID/selector interpretation, but do not establish original member
names or selector six's meaning. The existing field types/names and the
complete setter body are preserved.

All exact textual uses across `Code/` were checked without a suffix
filter. No allocation, by-value instance, embedding or `sizeof` use of
`Rva002D9531` was found. Thirty-six source files already include its
canonical header. The provider is the one remaining private `.cpp` view.
A separate method-only declaration in
`GameLogic/System/LogicDispatch/owner_context.inc` remains outside this
queue and header-dependent closure; `GameLogicDispatch.cpp` calls through
pointers to it.

## Change and scope

The existing manual header now carries the provider's consumed prefix.
`header_adopt_lane.py adopt` removes that provider's private class. The
other six queued sources already include this header, so they need no
source rewrite: SpecialAbilityUpdate, SpecialAbilityUpdateRun,
SpecialAbilityUpdateTriggerAbilityEffect and the three
ToggleDeploySpecialAbilityUpdate slot units.

As with the sibling, the discovery contract takes size one from opaque
views and discards the provider fields despite recording native accesses.
The unchanged survey is not a complete retail layout. This uses the fixed
manual header, documents its limits and verifies all existing dependents;
it does not regenerate a header from that majority result.

The conflicting AudioEventRTS pins in LINK-004 remain registered. Neither
setter adoption renames that class or migrates its other member symbols.
The separate `.inc` views remain follow-up work.

## Verification

The normal `./build.sh` over the provider plus all thirty-six existing
dependents passes 616/616 rows, four data rows, 118 string references,
135 float references and three named imports.

The companion JSON records all3,353 external COMDAT fingerprints unchanged
across those37 sources, with no additions or removals. It compares bytes
and relocation identity through `link_census.comdat_bodies`; it does not
establish correctness of every pre-existing binding.

An initial bounded strict preparation stopped after its normal byte gate:
the handoff file above was added after ProductionUpdateQueue's strict
receipt had captured its repository-root include inventory. The refusal
was valid. The record paths were completed before retrying; no receipt or
gate was edited to waive currency.

The stable retry passes strict preparation for all37 sources in supported
32+5 batches (537+79 rows). The owning acceptance test passes all seven
queued sources and retires their entries itself. All37 ordinary link
previews retain72,692 bytes against index `aa7acf764d`, 2026-11-12 19:19;
that index warns of seven subsequent source-path changes. These scoped
predictions are not a new census result.

These source/header checks do not establish a working game image.

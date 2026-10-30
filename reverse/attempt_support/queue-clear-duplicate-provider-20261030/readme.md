# Build-queue clear duplicate provider

## Existing coverage and cause

The 2026-10-30 14:18 census (`e1f7c1dd18`) records one duplicate-name blocker in
each of `StrategicInGameUIBuildQueueUnitQueued.cpp` (929 authored bytes) and
`GapBodiesSeat5A.cpp` (520). Both objects define `Rva005E8044::clear`; the
existing 11-byte row at `005E8183` belongs to the latter's strong definition.
The earlier inferred rename `6066b2f51f` gave that provider the name already
used by the observer's visible inline body. Its recorded naming agreement is
preserved. This is duplicate-provider cleanup, not an unrowed-body regression.

The observer still needs the clear body visible: the dequeued callback forms
the vector bounds once and inlines the erase call. Its existing member now uses
the established `__declspec(dllimport) __forceinline` recipe, retaining those
native caller instructions while suppressing the competing external copy.
The strong owner, all source paths, all rows, names, pins and debt registers
remain unchanged. No new alias, import reference or counted hatch is introduced.

## Before/after and actual-object evidence

Private before/after compilations reproduce all 15 caller rows exactly. Only
the duplicate external clear disappears; all 31 retained external code bodies
and their symbolic relocations are identical. Compiler-local labels renumber,
so they are checked through their actual parent graphs rather than by ordinal:
all four emitted handler parents, including the existing insert-overflow
instantiation, are independently EXACT. No clear import symbol is emitted.
[Private comparison](private-comparison.json).

Ordinary strict preparation in an isolated checkout passes all 36 rows in the
caller/provider cohort, with three owned EH graphs EXACT. The ordinary preview
against `e1f7c1dd18` retains 2/2 LINKS, 0 -> 1,449 authored bytes: caller 929,
provider 520. Frozen-definition and CSV checks pass. The isolation keeps the
separate pending WallHub publisher's checkout stable; it changes no gate or
matching rule. The existing verified toolchain is selected explicitly through
its supported `VC71_ROOT` setting, and the retail baseline hash is unchanged.

[The actual strict objects](actual-proof.json) prove that only the existing
strong owner defines clear, its whole 11-byte body remains native exact, and
the caller has neither its duplicate definition nor an import reference.
These are bounded provider/consumer checks; broader outgoing selection and the
next scheduled census remain separate. No official linked percentage or unique
byte gain is claimed.

## Outgoing audit qualification

The combined ready-batch audit also prepares the three WallHub rows, for 39
strict rows across the three explicit witnesses. The audit is INCONCLUSIVE:
index `e1f7c1dd18` predates outgoing base `575807ffef`, and affected
`Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt. This does not
clear broader selected-copy/loss behavior. Carry both repaired scopes and
their affected consumers into the next scheduled census.

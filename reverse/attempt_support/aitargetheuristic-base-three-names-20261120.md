# AITargetHeuristic base: one retail class, three placeholder names

Date 2026-11-20, at origin/master 5d0e3edab8. Blocked; nothing applied.

**Update (b796529e5b):** the tool now covers this. `rename.py class --fold` merges one body
rowed under both names and admits an alias-only third name with `--with`. See docs/naming.md
for the two fold commands. Still to do: fix the Rva005CB22A contract (inline dtor, 1 slot;
retail has 3), then run the folds and the steps under "What would unblock".

## Goal

Retire the bridge on `??_7AITargetHeuristicExpansionBase@@6B@` (0x0086E0B8). Its only
unbound slot is slot 2, 0x0020E34F. That slot is rowed as `?clear@Rva0020E34FDwordClearer@@QAEXXZ`
(macro `BFME_DISP8_DWORD_CLEAR` in Disp8DwordClearers.cpp), and the body clears `m_08`.
The prepared move is:

    rename.py function --rva 0x0020E34F --to-class AITargetHeuristicExpansionBase --new clear
      (AITargetHeuristicExpansionBase.cpp: `virtual void clear();` after findBestTarget plus
       `void AITargetHeuristicExpansionBase::clear() { m_08 = 0; }`;
       Disp8DwordClearers.cpp: drop the Rva0020E34F macro line)

It refuses because the class has no canonical header. `header_adopt_lane.py run --class
AITargetHeuristicExpansionBase --generate --header
Code/GameEngine/Include/GameLogic/AITargetHeuristicExpansionBase.h` then refuses too: the
contract queues `bases`, `inherited@0x4` and `field@0x4`, because the three views name three
different bases.

| View | Base it declares |
|---|---|
| `AITargetHeuristicExpansionBase.cpp` | `Rva005CB22A` (matches retail ctor 0x005730FF) |
| `Rva005CB23CDerived.cpp` | `Rva005CB23C` (destructor views of 5 heuristics) |
| `Rva0041E561.cpp` | `ModuleData` (allocation-only view) |

## Root cause

The heuristic base is one retail class, with vftable 0x00C74CA4: slot 0 is `??_G` 0x005CB243,
slot 1 is `__purecall`, and slot 2 is the shared 0x000B3FD0. It is rowed under three placeholder
names:

| Name | What it owns |
|---|---|
| `Rva005CB22A` | ctor 0x005CB22A. Registered in canonical_classes.csv with header `Include/Common/Rva005CB22A.h`. Owns the alias row `??_GRva005CB22A` with `fold-proof=InlineDtorDeletingDtors1.cpp`. |
| `Rva005CB23C` | dtor `??1Rva005CB23C@@UAE@XZ` 0x005CB23C (Rva005CB23CBase.cpp), plus the alias row `??_GRva005CB23C` (same fold-proof). |
| `Rva005CB243` | stand-in in InlineDtorDeletingDtors1.cpp that owns the original `??_GRva005CB243@@UAEPAXI@Z` row and `?slot08@Rva005CB243` (0x000B3FD0, fold-proof region.cpp). |

data_ledger.csv row 0x00874CA4 lists all three `??_7` names.

## Every fold refuses

| Command (`rename.py class --fold ...`) | Refusal |
|---|---|
| `Rva005CB23C --into Rva005CB22A` | third name Rva005CB243 |
| `Rva005CB243 --into Rva005CB22A` | third name Rva005CB23C |
| `Rva005CB243 --into Rva005CB23C` | third name Rva005CB22A |
| `Rva005CB22A --into Rva005CB23C` | registered class; "moves in a class-reconciliation commit" |

No tool or doc describes a class-reconciliation commit.

## What would unblock

One of two things:
- a multi-name fold in rename.py that collapses all three into the registered `Rva005CB22A`, or
- a maintainer-approved reconciliation.

After that, align the three heuristic views on the one base, register
AITargetHeuristicExpansionBase, and run the slot-2 move above. The siblings in
Rva005CB23CDerived.cpp (Rva00572C6E, Rva00572DE8, Rva00572ED8, Rva005734EB) would then share
the same base.

Not measured: link effect (nothing applied).

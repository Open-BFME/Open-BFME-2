# GettingBuiltBehaviorModuleData consumer adoption

Inspected base: `a83333646ee7f2d2bb527a6d991f8415f805d590`.
Scope: the five units claimed by `next_work.py --claim` for this class.

## Applied and verified

`GettingBuiltBehavior.cpp` replaces its partial module-data struct with the
existing canonical header. Its +0x14 worker name uses the header's AsciiString;
its +0x24 rebuild time and indexed +0x30..+0x3C percentages use the existing
canonical fields. The template lookup no longer needs the StringBase-to-string
cast. These are mappings to an established contract, not recovered original
field spellings.

`GettingBuiltBehaviorResume.cpp` replaces its partial module-data struct with
the same header. Only module-data accesses change: the unrelated
`PlayerPart::alternate` field retains its meaning and spelling. That separate
member was the automatic token-renaming conflict.

- `find_declared_unmatched.py` before and after: all defined functions matched.
- `./build.sh` over both units: 34/34 rows match, including one renumbered
  funclet through its parent EH data; data, string, float and import checks pass.
- `header_adopt_lane.py accept --class GettingBuiltBehaviorModuleData` accepts
  both consumers and retires exactly their two rows from `reverse/header_queue.tsv`.
- Current-object `link_check.py`: both LINKS, main TU 1,893 -> 1,893 B and
  resume consumer 449 -> 449 B, total 2,342 -> 2,342 B. Published census index:
  2026-11-05 05:17, `c95fcfcfcd`. This preview is not a new census or headline
  link gain.
- No shared-header, provider, alias, pin, ledger-identity or source-path change.

## Remaining claimed cohort

The automatic adoption tested all five units and retained none. Its failed
trials were restored before the two manual consumer changes. The other three
units remain unchanged and retain their header-queue rows:

- `ModuleFactoryInit.cpp`: C2011, ModuleData redefinition through the existing
  ModuleFactory include chain. This is the same base-header prerequisite
  recorded in LINK-467, not a new byte regression.
- `GettingBuiltBehaviorModuleDataCtorShard.cpp`: canonical-header layout
  discovery fails with C2011 while the source still includes BfmeModuleData.h.
  A subsequent manual swap must reconcile the base, the three ThingRef members
  and the filter's actual constructor/destructor calls. The current ThingRef
  destructor directly decrements a refcount, whereas canonical OpaqueRefElement4
  calls Release_Ref; prior attempt entries at 0x00789D72/7D/88 document the
  37-byte versus 12-byte callee mismatch. Do not pin this wrong callee.
- `GettingBuiltBehaviorModuleDataDtor.cpp`: the same duplicate-base C2011 stops
  layout discovery. Reconcile its base and member teardown with the canonical
  header as one provider change, preserving the rowed destructor, deleting
  destructor and EH funclets.

Source inspection supplies a further prerequisite for both lifetime providers:
the canonical +0x40 ObjectFilter is a four-byte handle but declares no special
members; the private Rva00360D26Member in these units has out-of-line constructor
and destructor declarations and therefore contributes cleanup states. A plain
field-name substitution would omit that lifetime behavior. This is structural
analysis, not a tested claim that an honest canonical reconstruction cannot
byte-match. Resolve ObjectFilter's special-member identity with its class owner
and audit all affected table/provider consumers before changing that header.
The constructor/destructor trial did not reach a body-byte or link comparison.
No unmatched reconstruction is retained, and no whole-class closure is claimed.

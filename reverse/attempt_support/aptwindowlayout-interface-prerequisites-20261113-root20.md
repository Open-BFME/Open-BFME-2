# AptWindowLayout: paired lifetimes precede table closure

Inspected base `bc1ac42b01d`. The default picker selected the bridged nine-slot
table at RVA `8395E4` in AptWindowLayoutConstructor.cpp. No source, ledger,
alias, queue or bridge entry was changed. The untouched constructor, current
Apt unit and WindowLayout unit pass `./build.sh`: 15/15 code rows and one
string literal. The native bytes and table words are in the adjacent JSON.

| Slot | Apt target RVA | Current row owner |
| --- | --- | --- |
| 0 | 40FB9C | AptWindowLayout::rva0040FB9C(void*) |
| 1 | 40FD1C | Rva0040FB4A scalar deleter; destructor 40FB4A |
| 2 | 40FC79 | Rva0040FC79Host::guard(int) |
| 3 | 40FCC0 | Rva0040FCC0::rva0040FCC0(int) |
| 4 | 538AB0 | BfmeQuickMatchScreenBase::rva00538AB0(bool) |
| 5 | 538B07 | WindowLayout::bringForward() |
| 6 | 538B48 | WindowLayout::addWindow(GameWindow*) |
| 7 | 538B95 | WindowLayout::removeWindow(GameWindow*) |
| 8 | 538ADC | BfmeQuickMatchScreenBase::rva00538ADC() |

The constructor's base view currently has seven slots; the last two are
missing. Both the native base table `839608` and derived table `8395E4` have
nine. The base's first four targets are `40FD7C`, `40FDB5`, `40FD8F`, `40FDA2`;
its final five equal the derived table's. Native base destructor `538C5F`
stores VA `00C39608`, adds four to its receiver and jumps to the existing
string worker. Native Apt destructor `40FB4A` stores VA `00C395E4`.

## Actual cleanup dependency

Constructor handler `785A84` reaches FuncInfo `932568`, whose two unwind
actions are `785A74` and `785A7C`. Their complete eight-byte bodies tail-jump
to `538C5F` and `48BA39` respectively. This is parent-graph evidence, not an
adjacency guess. The former is the base teardown; the latter is the string
temporary. The current constructor's nonvirtual base-destructor alias to
operator delete is not a valid native binding for `785A74`. That action remains
generated, and no attempted ownership repoint is retained.

## Owning planner results

- `class --fold Rva00538C5F --into BfmeQuickMatchScreenBase` reaches a duplicate
  declaration refusal in the current Apt unit: it contains both base views.
- `class --fold Rva0040FB4A --into AptWindowLayout` reaches the analogous
  duplicate Apt declaration refusal in that same unit. The historical separate
  Common/Rva0040FB4ADtor.cpp path is gone; its rows are already in the Apt unit.
- `class --fold BfmeQuickMatchScreenBase --into WindowLayout` refuses the
  installer tie: the native base table is named for BfmeQuickMatchScreenBase
  and Rva00538C5F, with no current WindowLayout own-table binding. This is not
  established as a false reject. The named method providers or donor layout
  alone do not prove the two classes identical.

All three were read-only dry runs. No prepared transaction was applied or
compiled. A scratch base-only preparation stopped at an assertion before its
planner ran; it must not be treated as an accepted plan.

## Safe next transaction

Reconcile the two native lifetime families together, then move the placeholder
callbacks through the existing `--to-class` route. Preserve their current int
argument carriers until a supported type proof exists; int-to-pointer signature
respelling is not an equal-length spelling change. Keep the unresolved
WindowLayout/base identity explicit. The donor WindowLayout header also has a
private GameWindow view and `hide(int)`, unlike the current native bool row.

Do not bank a base-only virtual-destructor edit. Replacing base slot 1 while
the derived view still declares `bfmeSlot1()` appends that method and generates
an implicit Apt destructor/deleter that omits the native 82-byte cleanup.
Require the paired real Apt lifetime provider, an explicit derived destructor
declaration, removal of the derived placeholder, and inspection of every new
COMDAT/table copy. Any composition must prove complete native bodies, unwind
actions, all nine table slots and combined link preservation. Existing aliases
are debt, not permission to add new ones. Bridge retirement still requires the
next authoritative measurement; no source gain is claimed by this record.

# Canonical State transition surface

Base: 1bba2f618a, 2026-11-07. The served StateMachine.cpp consolidation
initially accepts none of five donors. StateCtor.cpp introduces canonical
State, while the seed defines a private State with three transition helpers.
Composition loses the early StateReturnType declaration and the canonical
class lacks the helpers and their typed transition fields.

The canonical State header now declares the existing rowed rva004D7127,
friend_checkForTransitions and friend_checkForSleepTransitions methods. The
native 0x004D7127 loop advances through 12-byte StateConditionInfo records and
stores their count at receiver+0x14; the other two helpers consume that count.
Thus +0x10 is a const StateConditionInfo pointer and +0x14 an int. The legacy
m_transitionsLast spelling is retained and documented; this changes no name,
offset, total extent or virtual slot. StateCtor's existing zero initialization
remains correct. The other Code occurrences of that spelling are declarations.
StateConditionInfo.h separates native callback/layout facts from donor names.

StateMachine.cpp includes canonical State before its private Machine view,
removes its duplicate StateReturnType and State declarations, and uses the
canonical count field. Its Machine/map view and lifetime code remain intact.
header_adopt_lane.py accept --class State passes and retires exactly the
seed's one State header-queue row.

## Verification

- Reproducible private candidates and normal build: seed 17/17, constructor
  6/6; all 23 rows and three data rows remain exact. The private probe reads
  pre-change sources/header from git and the frozen 23-row evidence subset.
- Normal EH: 2/2 EXACT. Three strings and one compiler float verify.
- Object comparison with the pre-change seed: no external name added or
  removed, all 67 comparable external code sections retain flags, bytes and
  relocations, and both emitted vtables retain their complete definitions.
  Four code sections contain local/EH relocations and need the independent
  native row/EH/data checks rather than the simple comparison.
- Ordinary current-object preview at index 9c81acd297: both units LINKS,
  conserving 745 + 158 = 903 authored bytes. This is not a new real image.
- The supported merge dry-run now accepts the seed plus StateCtor.cpp,
  retaining all 23 rows under the link guard, and plans five data-ledger
  ownership transfers. The approved actual merge is a separate commit.

Remaining donors: setGoalObject needs the complete canonical Machine view;
the destructor still needs its typed map teardown and CRT declaration order;
Xfer has enum/member conflicts; defineState differs under the seed's signed
map/volatile context. Seven mixed files remain outside the merge. An Object
view union does not resolve these prerequisites. No full StateMachine table,
image, runtime or broader family clearance is claimed.

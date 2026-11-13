# GODupBase native table recovery, pending admission

The normal getter move was refused by find_declared_unmatched after all
64,790/64,790 rows across 6,312 sources passed, along with 1,741 data rows.
The tool restored every edited source and ledger. The restored original then
passed all six rows/178 bytes and has no declared unmatched body. No source,
name, address binding or table change was banked.

The native constructor at RVA 00306782 is 66 bytes. It completes Snapshot
at +0, calls SubsystemInterface's constructor at +4, then installs the secondary
table C07D3C and primary table C07D2C. The object is 16 bytes. The destructor
is 60 bytes; the secondary deleting-destructor thunk subtracts four.

The original file's six rows/178 bytes match. The complete prepared class
preserves all six and reproduces the 27-byte native xfer at RVA 00341E2D.
The ordinary getter to-class dry run proves slot 2 at C07D2C is the six-byte
GetSnapshotName, currently rowed under Rva003067C4Named. The literal is BuffLogic;
it is not claimed as proof of the original class name.

The immutable candidate object has exactly 16-, 16- and 56-byte Snapshot,
GODupBase-primary and GODupBase-secondary tables. The owning bridge checker
finds no Snapshot-base mismatch. The other tables need five unadmitted names:
GODupBase::loadPostProcess, xfer, init, reset and update. Full code comparisons
prove the four one-byte empty bodies at B3FD0 and the 27-byte transfer at 341E2D.
With those five hypotheses all 22 table slots agree. This does not admit any
binding, change any symbol map, or demonstrate bridge retirement.

The append tool's --icf-owner option accepts a covered address of the same
extent, but tu_ownership A1 rejects a second row in another source. The current
candidate's out-of-class xfer is also reported by find_declared_unmatched.
Do not hand-pin, invent a gen-alias tag, move the body into an unrelated TU,
change syntax to hide it from inventory, or weaken a gate in the source commit.
An admission prerequisite remains unless the owning tools provide a valid route.

The exact [candidate](godup-native-tables-20261113-root20/candidate.cpp.txt)
and [slot/code proof](godup-native-tables-20261113-root20/slot-proof.json) are
retained as evidence. Parent logs remain under build/root-godup-*.
Five direct consumer baseline receipts cover 12 rows and retain 333 linked
bytes in the old-index preview; this is not a current whole-image result.

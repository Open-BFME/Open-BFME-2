# PingThread composition prerequisites (2026-11-04)

Inspected revision: `29c2eaf353`. Scope: the approved
`Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PingThread.cpp` TU and its
six whole-file donors. No new retail source identity or layout is inferred.

The initial supported `tu_skeleton.py --merge ... --dry-run` accepted no donors.
The current destination itself byte-verifies (48 rows) and its census-backed
`LinkGuard.prepare/judge` succeeds. The older seed-object COMDAT blocker is not
reproduced on these inputs.

For `PingThread_Pinger_getPing.cpp`, identical `NumWorkerThreads` declarations
spelled `Int` and `int` prevented composition; using `int` in both preserves all
four donor rows. After that change, composition compiles but moves the empty
string-allocator temporary from `[ebp+0xB]` to `[ebp-0xD]`, increasing the frame
from 0x14 to 0x18 and shifting local accesses. Instructions and resolved callees
otherwise agree. Isolated scratch `tu_skeleton.Verifier` probes identify the
seed's declaration-only `_String_base<char>` constructor as the cause; adding
`_STLP_NO_EXCEPTIONS`, its inline nothrow destructor, or the declaration-only
string copy constructor to the donor independently preserves its bytes.

Removing that constructor declaration allows the combined rows to match, but
the imported inline base-destructor specialization leaves an unresolved
`__imp_??1?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAE@XZ` in unwind cleanup.
Keeping the existing forceinline/nothrow body with ordinary linkage resolves
that reference. The scratch pair uses the merge engine and its normal byte and
census link guards, with no guard disabled: both files are accepted, covering
50 distinct addresses. It writes no game source or ledger.

Prerequisite verification: `./build.sh` preserves 48/48 destination rows and
4/4 donor rows, including EH companions; both frozen-file checks pass. The
changed destination passes `class_gate.py`, `link_check.py --new-variants`, and
census-backed `LinkGuard.prepare/judge` (`None`, `[]`). All existing linker aliases
remain; none was removed or added. No new census or headline link gain is claimed.

The supported full merge and its path-consumer audit are the next step. Other
initial donor failures are cleanup's duplicate `StringBase`, destroy's allocator
specialization signature, constructor/slot-method private views, and worker-loop
bytes. These were not repaired by the prerequisite commit.

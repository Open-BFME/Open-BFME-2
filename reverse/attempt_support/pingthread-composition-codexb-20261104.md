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

## Supported merge trial and application handoff

Prerequisite commit: `dc706b4ef3` (handed to the fleet publisher). The subsequent
full supported `tu_skeleton.py --merge ... --dry-run` accepts the destination
and `PingThread_Pinger_getPing.cpp`: 50 distinct addresses, normal census link
guard enabled. It would absorb one donor and transfer its existing free alias
through `hatch_counters --update`; no alias deletion is proposed. All five other
whole donors still fail with the same declarations/bytes listed above. The
constructor names `m_B0` absent from the destination view; the slot-method donor
instantiates a string destructor before its explicit specialization.

A refreshed supported consolidation planner completed with 47 selected source
files, 12 groups and no missing inputs. Its first refresh raced a transient
`.tu_skeleton.cpp` scratch file; rerunning after the dry-run finished succeeded.
The real apply command then stopped before writing anything:

```
accepted: []
rejected: {}
blocked: held by another worker: 0x0007FAB3
```

The live claim belongs to `yasinschroeder-claudeb` for `ChatWindowsLan.cpp` (about
four hours left when inspected). This is the shared ICF cleanup address included
in the destination's full merge scope. No bypass, claim takeover, source move,
ledger repoint, register transfer or source-file-count reduction occurred. The
failed admission released this worker's merge-scope claims.

The prerequisite's object comparison against the saved original has 876 -> 880
COMDAT names: zero removed and zero changed bodies/digests. Its four additions
are the ordinary `_String_base<char>` destructor, `_M_deallocate_block`, proxy
and allocator destructors. The hook's shadow `allocator<BfmePod16>::deallocate`
identity finding is inherited: both objects have the same 20-byte body and
normalized digest `083eb30a50cf`. Existing identity-register keys remain.
The prerequisite commit hook verified 52/52 rows across the two files and all
nine EH graphs EXACT, plus data and frozen-file checks.

Next: after the other worker releases `0x0007FAB3`, take the normal merge scope
and rerun the supported merge (its saved plan checks input freshness). Verify
its final TU, transfer and audit the donor's hatch key, header queues and active
path consumers, then publish the source move promptly. A source-path audit and
scoped naming remain follow-up work because no final TU was written. Do not
repeat the already isolated constructor/declaration experiments.

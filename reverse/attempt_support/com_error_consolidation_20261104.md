# COM helper consolidation, 2026-11-04

Scope: absorb `Code/Libraries/Source/COM/ComRaise.cpp` and `ComInvoke.cpp`
into the approved, provisional `Code/Libraries/Source/COM/_com_error.cpp`.
This preserves the current TU-map assignment; it does not establish a retail
source filename. `ComInvokeError.cpp` is mixed and remains untouched.

`tools/tu_skeleton.py --merge` accepted both donors in retail order: nine rows,
2,036 bytes, one fewer source file. The census-linked guard accepted both
donors with no rejected donor. No new link census or game run was performed.
The applied plan is reproducible with the merge tool; its local log is
`build/com_error_merge_apply.log`.

Verification of the composed source:

- `./build.sh Code/Libraries/Source/COM/_com_error.cpp`: 9/9 exact, source claims
  pass, 11 named imports verified.
- `find_declared_unmatched.py`: all defined bodies matched; `check_csv.py`: pass.
- `data_check.py`: zero findings; `--converged`: 11 addresses, zero second names
  and zero unjudged names. `code_identity_gate.py --staged`: nine rows, zero new
  findings. `tu_ownership.py --staged`: pass.
- `eh_verify.py`: zero rows with EH data, zero non-exact rows and zero missing
  objects. This is not an independent C++ exception-metadata proof.
- Replayed `0x00654c90-com-error/check_metadata.py` with the composed source:
  nine RTTI/vtable/throw-metadata symbols match the native object and retail
  bytes with relocation placement checked; all five former ComRaise bodies
  also pass its byte/extent assertions. Receipt:
  [com_error_metadata_20261104.json](com_error_metadata_20261104.json).

Protected-register audit: the merge tool transferred both flag-override keys
to the destination, retaining the aggregate five rows/two default losses.
There is no debt retirement. Narrow searches found no donor keys in the
identity/data baselines, header/MS-header queues, hatch baseline, symbol/data
ledgers or body-owner registry. The tool refreshed destination header reports;
only functions, TU-map source columns and flag overrides required repointing.
No TU assignments or approvals were regenerated. Existing canonical SDK
declarations and the shared global binding are retained; no aliases were removed.

Tooling compatibility audit covers the two-to-one move staged after
`89768f324b`, the only source-path change in this worker's outgoing commits.
Combined basename/directory searches across tools, hooks, workflows, Code,
build entry points, doxygen configuration and the active registers found no
active hard-coded consumer requiring another change. Intentional old mentions:
the composition's provenance comments, the flag-parser regression test, and
historical attempt evidence. In particular,
`reverse/attempt_support/0x00654c90-com-error/check_metadata.py` retains its
historical default source; replay accepts the current TU as its source argument.
The merge guard checked census-linked providers/consumers; the publication
hook supplies the outgoing link-batch audit.

Prerequisite tooling fix: quoted SDK include operands now survive flag parsing,
comparison and rendering. Validation: 263 consolidation unit tests passed;
61 gate-exploit tests passed and one skipped. Malformed quoted paths remain
refused. The earlier false rejection was recorded separately before that fix.

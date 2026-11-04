# Apt math CRT-header migration false reject

Inspected revision: 59f109551a4b69964e6bc7c5897c6ba91e7fa3eb.
Scope: Code/Libraries/Source/Apt/AptMathCallbacksBFME2.cpp.

The attached trial replaces the local CRT declarations and inline bodies with
`<math.h>`. Two preceding `extern "C"` static prototypes keep the header's
`sinf` and `cosf` helpers internal. These are declarations without bodies;
the implementations come from the real header. Without them, the header adds
external `_sinf` and `_cosf` definitions to this early unit (the original
comment warns that retail's separate wrappers have different code generation).

Verification of the trial:

- `./build.sh Code/Libraries/Source/Apt/AptMathCallbacksBFME2.cpp`: 20/20 rows
  matched; strings, three float literals and imports pass.
- `find_declared_unmatched.py` reports all definitions already matched.
- Independently built before/after objects have identical sets of 24 external
  definitions. `link_census.comdat_section_bodies(..., digests=True)` reports
  all 24 retained external COMDAT byte/relocation digests identical.
- `link_check.py` predicts LINKS, 1,332 -> 1,332 bytes, against census
  2026-11-04 07:28 at a62ac1c10b. This is a preview, not a new census or a
  real-link measurement.
- `ms_header_audit.py check` refuses the new bodyless static `cosf`/`sinf`
  declarations as local function definitions identical to math.h:443/465.
  The prior file had 19 reported local header-name occurrences; the trial
  has just these two. No checker or register was altered to admit the trial.

The source was restored. Next step: reproduce the declaration-only false reject
in the tooling lane and distinguish linkage declarations from copied bodies;
then reapply and reverify this trial. The broad LINK-135 history is unchanged.

## Resolution

The separate checker repair b7e88d5f0c recognizes only bodyless static
prototypes whose signatures match a header-defined inline function as linkage
configuration. Copied inline bodies, incompatible signatures and prototypes
for ordinary CRT functions remain findings. The regression suite has 74 passes;
its two failures (`test_extra_root_arguments` and
`test_included_project_headers_are_inspected`) reproduce identically with the
unchanged checker on this Linux runner. All gate-exploit cases still pass
(61 passed, one skipped).

With that repair committed separately, the attached source trial was reapplied.
The file again passes all 20 byte checks, literal/import verification,
`find_declared_unmatched.py`, and `ms_header_audit.py check`. The supported
`ms_header_audit.py scan <source> --write-queue` refresh removes its 19-definition
queue row; both bodyless prototypes now count as configuration. No debt baseline
or admission was added. The object retains the same 24 external COMDATs and
byte/relocation digests measured above; no linking gain is claimed.

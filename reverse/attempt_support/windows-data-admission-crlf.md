# CRLF-only false rejection in existing data-definition admission

On Windows, `_admission_definitions` compared the line endings of Git's LF
baseline with CRLF source written by `Path.write_text`. A permitted added
definition then looked like replacement of resolved lines and was refused.
The two existing name-lane admission tests reproduced this on unchanged HEAD
modules. A direct probe changed only LF to CRLF and reproduced the refusal;
converting those bytes back recovered the passing result.

The repair normalizes CRLF to LF only in SequenceMatcher's comparison keys.
The original source remains the input to definition, scope, token and splice
checks. Approval/source hashes and compiler currentness checks are unchanged.
Bare CR, missing final newline, whitespace changes, modified/removed resolved
lines, macros and line splices do not become admissible.

Validation:

- The new focused regression run failed before the fix and passes afterward:
  13 cases covering both conversion directions and retained refusals.
- Full `test_data_rows.py`: 125 passed with the native compiler available.
- `test_gate_exploits.py`: 89 passed, 5 skipped; no formerly refused case
  became accepted.
- Both pre-existing name-lane admission failures now pass.

The initial sandboxed combined run could not launch MSVC in nine tests
(WinError 623). The entire data-row suite was rerun with native execution
permission and passed; those failures were not skipped or treated as passes.
Evidence is under `build/decal-diagnostic/name-global-init/`, in the
`data-rows-newline-*` logs. This change is separate from direct-initializer
name discovery and introduces no data row, alias or admission exception.

# W3DFloorDraw accepted-donor merge audit blocker (2026-11-04)

The allocated TU plan accepted only `W3DFloorDrawXfer.cpp` and
`W3DFloorDrawPoolKey.cpp` unchanged. `tu_skeleton.py --merge` applied those two
donors, preserved 24 rows, and its LinkGuard reported the current six census
units linked. `./build.sh Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DFloorDraw.cpp`
passed all 24 rows; `find_declared_unmatched.py` reported no unmatched
definitions.

The pre-publish identity audit did not clear the composition:

- `code_identity_gate.py --staged`: 1 new shadow finding,
  `definition: duplicate | ?size@Rva000CF0FF@@QBEHXZ`.
- `data_check.py --staged`: 3 findings outside the baseline on the merged TU:
  duplicate definition `_DRAWABLE_FRAMES_PER_FLASH` at `0x009EBBD4`, and
  wrong-name findings for the local-static guard and `_DRAWABLE_FRAMES_PER_FLASH`
  at `0x009EBBD0`/`0x009EBBD4`.
- `code_identity_gate.py --full` could not complete: it raised
  `UnverifiedFunclet: funclet $L8020: no unique verified local code label from parent EH`.

Per the consolidation audit rules, the trial was restored without publishing.
The tool's dry-run also rejected the ctor donor (`m_10` undeclared), dtor and
`doDrawModule` donors (missing type before `*`). These need code/view work from
another lane. Do not retry this unchanged merge until the identity bindings
have been reconciled and the scoped audit passes.

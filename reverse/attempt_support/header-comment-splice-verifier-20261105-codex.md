# Header-adoption continued-comment false rejection

Inspected base: `47db4528da`; worker: `yasinschroeder-codex`, 2026-11-05.

The existing false-reject record for `stl_dec_vms.h:50` in
`reverse/re_attempts.log` was reproduced while previewing Object adoption in
`OneRingPenaltyUpdateRva00499C6C.cpp`. The initial owning-lane command was:

```
python3 tools/header_adopt_lane.py adopt --class Object --header Code/GameEngine/Source/GameLogic/Object/object.h Code/GameEngine/Source/GameLogic/Object/Update/OneRingPenaltyUpdateRva00499C6C.cpp --apply
```

It refused before writing source: `field renames: .../vendor/stlport/config/stl_dec_vms.h:50: trigraph or continued line comment in include input`.
The header comments out a continued preprocessor condition, and both physical
lines independently begin with `//`. Joining those lines does not hide code.

The verifier now permits only chains whose opening `//` is physically present
and whose every continuation independently begins with `//` after spaces/tabs.
Splices forming the comment delimiter, swallowing declarations/macros, or
continuing a later comment into code still refuse. Trigraph checks are unchanged.
This is a tooling-only fix; no source adoption or debt retirement is included.

Verification:

- New reproducer before the fix: 2 failed, 4 passed (LF and CRLF positives fail;
  four unsafe chains already refuse).
- `python3 -m pytest -q tools/tests/test_header_field_renames.py tools/tests/test_gate_exploits.py`:
  **149 passed, 1 existing skip**. All active exploit fixtures remain refused.
- Direct scanner check of the actual `vendor/stlport/config/stl_dec_vms.h`:
  `header_comment_splice` returns `None`.
- Repeating the owning-lane command without `--apply` advances past this
  header and conservatively refuses `obj occurs in a comma declaration or
  expression`. That independent scanner limitation is not relaxed here.
- `git diff --check`: passed.

The OneRing consolidation dry run still accepts zero donors. The seed's raw
`m_20`/`m_vtable` stores conflict with canonical donors; Slot0 still names
`rva00499D18` instead of `onDie`. The provider prerequisites documented in
`onering_headers_20261105_codex4.md` remain. No game source, row, protected
register, or source path was changed; no linked-byte or census gain is claimed.

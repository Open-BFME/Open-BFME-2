# gamebrowser merge: redundant /O2 override rejected

At `678d949f99e0faec5d8ad55dda7b766711a0a4a1`, the supported dry run rejects
`Rva007F63D0Set.cpp`: its override `-O2` differs from gamebrowser.cpp's empty
override. The compiler command starts with `-O2` in either case
(`tools/build.py`, `compiler_command`), so these managed settings are equivalent.
The donor's region default adds `/G7` and loses its row; removing the override
with `flag_defaults.py propose` is therefore not a repair.

No source or gate change was applied. A scratch-only experiment used
`tu_skeleton.skeleton`, `donors`, `relocate_includes` and `compose` with the seed's
flags and the `first` strategy. `Verifier(gamebrowser, flags="").matched` proves
all 39 existing rows, including the donor's 25-byte body at 0x00662B60.
`LinkGuard.prepare` and `judge` report no findings. [proof.json](proof.json)
records the source revision, object hash, matched scope and guard verdict.

Next: separately repair override equivalence in both donor selection and
protected-register carry. Preserve distinctions involving `/O1`, `/Ox`, `/G6`,
`/G7`, and `/arch` settings. Add regression tests before repeating the supported
merge. The eventual merge must still pass its normal byte and link checks.

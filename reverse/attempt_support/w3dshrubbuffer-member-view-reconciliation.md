# W3DShrubBuffer member-view reconciliation

The consolidation trial for
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBuffer.cpp`
rejected `Rva000E9BACDtor.cpp`: its private `Rva000E9BAC` declaration hid
the setter declared by the destination. `tu_views.py --dry-run` also found
different base clauses for `Rva000E6AC0` and overlapping member views at
`+0x4FB60`.

Target facts: row `0x000E9CFB` assigns through the 12-byte `Rva000E3A8D`
view at `+0x4FB60`, then sets the byte at `+0x4FB5E`. The rowed destructor
at `0x000E9BAC` destroys the member at `+0x4FB60`, the 64 elements of
stride `0x5C` at `+0x4FB70`, and the base. Its compiler-emitted unwind rows
remain at `0x007636E2`, `0x007636EA`, `0x007636F8`, and `0x00763710`.

The two sources now share the destination's existing `0x5C0` base extent
and the destructor's array declaration. The existing empty destructor
view `Rva0008B470`, also used by `W3DPropBufferClass.h`, has explicit
storage following it to preserve the next array's offset. The setter
casts the member to its existing assignment view. This reconciles source
views; it does not establish an original member type or donor identity.
No pins, aliases, or ledger extents change.

Verification on 2026-11-05:

- `./build.sh` on both sources: 31/31 rows match, including the existing
  compiler-generated EH rows and all literal/import checks.
- `find_declared_unmatched.py` on both sources: all defined functions matched.
- `tu_views.py W3DShrubBuffer.cpp --dry-run`: the four reconciled views
  are already shared; other private mesh/record views remain separate work.
- `link_check.py` on both sources: destination 5,430 -> 5,430 linking bytes,
  destructor 109 -> 109 (preview against census 2026-11-05 05:17,
  `c95fcfcfcd`). This is not a new census measurement.

Next step: retry the supported TU merge after this prerequisite commit.
The other six donor files still have independent private-view conflicts;
no acceptance of those files is claimed.

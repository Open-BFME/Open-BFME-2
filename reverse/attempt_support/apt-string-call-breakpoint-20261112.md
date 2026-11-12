# Apt string call breakpoint at 0x006CCB80

The matched 513-byte string-argument wrapper in `Apt.cpp` has two assertion
breakpoints. The value-argument sibling at `0x006CCD90` matches with the
compiler's `__debugbreak()` intrinsic, including its unwind graph.

The existing source records that the bare intrinsic changes the string
wrapper's stack homes. Adding `_ReadWriteBarrier()` before and after both
traps still changes them. At the first `EAStringC` construction, the
`lea ecx,[esp+0x1C]` becomes `lea ecx,[esp+0x20]`. The spilled context moves
from `esp+0x14` to `esp+0x10`. The verifier also reports three differing bytes
in the unwind funclet at `0x007A8100`. Both traps still emit INT3, so trap
encoding is independent of the stack-home mismatch.

The string wrapper's assembly is restored. A next trial would need to
account for the path string, argument temporary, context spill, and name
string's native stack homes, including the offsets used by their cleanup
funclets. A bare intrinsic or the same pair of barriers repeats a known
mismatch.

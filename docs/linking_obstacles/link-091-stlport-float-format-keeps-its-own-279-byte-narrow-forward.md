### LINK-091: stlport_float_format keeps its own 279-byte narrow forward-iterator append

Status: Open. Updated: 2026-10-26; inspected revision: 9e70605d3f; census 2026-10-26 13:18 at d1f046749a.
Evidence / affected units: `??$append@PBD@...forward_iterator_tag...` has seven census copies. The first
in link order is `stlport_float_format.obj` (rows 0x15E80/0x160D0 put it at index 102), an unknown
279 B copy; retail's 254 B body (0x0001B3E0) comes later from `stlport_narrow_string_append.obj`
(index 322). That holds out `stlport_float_format.cpp` (2,619 B), `StlportNarrowAppendCStr.cpp`
(58 B), `urlBuilder.cpp` (868 B), `Rva001F9524Concat.cpp` (160 B),
`stlport_narrow_stringbuf_overflow_setbuf.cpp` and `stlport_narrow_ostringstream_dtor.cpp`. This
contradicts LINK-020's "already link" list for those units. The `PAD` twin is not a blocker
(`stlport_narrow_string.obj`, retail, is first).
Completed: the float_format decl-only lines from 2c405b7793/7fdf7a74b3 sat in the HP-UX
`#else` arm and never compiled; removed in 6ae74e4d53 (object COMDATs unchanged, 23/23 rows).
Tried and failed (re_log 0x0001B3E0 blocked): a live decl-only `append<const char*>` specialization
(either live spot, with `__declspec(noinline)`, with the `PAD` twin) and an explicit inline
`_M_append_dispatch<const char*>` specialization calling it all hit C1001 (P2 main.c 148) under
the region's -O2. The unit must emit `_M_append_dispatch<const char*>` (its 0x15E80 row), so the
decl-only pattern that works in units emitting no dispatch does not apply here.
Remaining / next check: retail 0x1B3E0 lies inside float_format's own run (0x1B010..0x1BBD0), so
retail's copy was float_format's. The fix is float_format emitting the retail-shaped body: approve
the TU for 0x1B3E0 (tu_map only proposes `_STL.cpp`), then move the 254 B row and its source shape
into that unit, or find the STLport 4.6 `append` shape that compiles to 254 B.
Clearance: none.
Census confirmation: n/a.

### LINK-548: generated msvcr71 import thunk shadows msvcrt.lib's `_adjust_fdiv` (boot crash at entry)
Status: Repair landed / awaiting verification. Updated: 2026-11-05; inspected revision: 2b840363c8.
Evidence / affected units: the first diagnostic image (sha256 `fc2d10d59f07…`, commit
`3bfe30efed`, base 0x10000000) faulted on the game queue (receipt
`2026-11-05T174452Z-boot_smoke-fc2d10d59f07`) with 0xc0000005 at 0x1065c82e,
`_WinMainCRTStartup`+0xa9: `mov [0x1092845a], eax`, the `_adjust_fdiv = *_imp___adjust_fdiv`
store in `Code/Libraries/Source/CRT/WinMainStartup.cpp`. The map binds `__adjust_fdiv` to
`imp_msvcr71:msvcr71.dll`, a `jmp [__imp___adjust_fdiv]` thunk in read-only .text. Retail
(`game.dat` 1.06, base 0x400000) stores the same value to 0xe23308 in .data's BSS tail. VC7.1
`msvcrt.lib` declares the import DATA and defines `__adjust_fdiv` as a 4-byte common in
`adjustfd.obj`. `tools/exit_link.py` wrote it as a CODE entry in `imp_msvcr71.def` (DATA only
when a source object defines the name), and that library precedes `msvcrt.lib`. Note: the
receipt's `retail_rva` 0x6293af is retail's entry (0x629306) + 0xa9, not a mapped address.
Retail has no fault there: its own .text is writable (0xe0000020), so the same harness reaches
the menu.
Completed: exit_link marks DATA every entry the runtime import libraries declare DATA (45
names in msvcrt.lib). On the 3bfe30efed link set this changes `_adjust_fdiv`, `_acmdln`, `_iob`
and `__pioinfo`. The last three thunks have no reference in the image (all source uses are
dllimport). A two-object probe link (startup object + generated libs + msvcrt.lib) binds
`__adjust_fdiv` to the thunk before the fix and to msvcrt.lib's common in section 3 after.
Remaining / next check: a boot_smoke queue receipt for an image linked from a commit with the
fix, showing it gets past `_WinMainCRTStartup`+0xa9. The census path
(`link_cycle.link_libraries`) builds the same CODE entry and a separate `.text$zz` thunk for
it; it was not changed here.
Clearance: pending the queue receipt.
Census confirmation: not claimed.

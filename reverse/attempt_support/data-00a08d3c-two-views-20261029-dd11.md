# 0x00A08D3C: two StringClass views, one address; the picker's extern fix would drop two rows

Seat dd-11, 2026-10-29. Data-identity row
`Code/GameEngine/Source/Common/Rva00E08D3CString.cpp` (`duplicate-def` and
`wrong-name` for `?g_rva00E08D3CString@@3VStringClass@@A` at 0x00A08D3C,
baseline lines 17-18). Base 286d810c88.

## Facts

- `reverse/data_ledger.csv` names 0x00A08D3C
  `?OSVersionExtraInfo@CPUDetectClass@@0VStringClass@@A`, source
  `Code/Libraries/Source/WWVegas/WWLib/cpudetect.cpp`, status provisional, with
  both spellings as aliases.
- `cpudetect.cpp:92` defines that static member. Its object defines
  `?OSVersionExtraInfo@CPUDetectClass@@0VStringClass@@A` and emits **no**
  `??__E`/`??__F` initializer or cleanup: in cpudetect's StringClass view the
  default constructor is trivial, so the compiler generates no dynamic
  initialization for the global.
- `Rva00E08D3CString.cpp` defines `StringClass g_rva00E08D3CString;` through
  `wwstring_teardown/zhmd` + `/DBFME_WWSTRING_NATIVE_CSTR_ASSIGN`, whose
  StringClass does need dynamic initialization. Its object emits the two
  matched rows: 0x007B54A0 (50 B, `_$E1`) and 0x007B9AA0 (10 B, `_$E2`).
- Retail 0x007B54A0 is that global's dynamic initializer: it loads the empty
  sentinel from 0x00DD528C into [0x00E08D3C], calls 0x00610B00, copies a byte
  from 0x00E08C18 into the buffer, then registers the cleanup through atexit
  (push 0x00BB9AA0, call 0x006291F8). 0x007B9AA0 is `mov ecx,0xE08D3C; jmp
  0x00610A40`.

## Why the served fix does not work

Declaring the global `extern` in `Rva00E08D3CString.cpp` (the picker's
instruction) removes the only TU whose StringClass view emits the initializer
and cleanup, so rows 0x007B54A0/0x007B9AA0 have no symbol to verify: the byte
gate refuses, and two matched rows (60 B) are lost. Repointing those rows to
cpudetect.cpp does not help either, because cpudetect's object emits neither
symbol.

## The two real paths (both need a maintainer-scale step)

1. Move the definition to the canonical name in this TU
   (`StringClass CPUDetectClass::OSVersionExtraInfo;` here, delete cpudetect's
   definition) and repoint the two rows to
   `??__E?OSVersionExtraInfo@CPUDetectClass@@0VStringClass@@A@@YAXXZ` /
   `??__F...`. This keeps the bytes and gives the global its real name, but the
   derived `reverse/data_ledger.csv` then names this file as the source, so the
   ledger must be regenerated (`tools/data_ledger.py`) — a full-tree object
   read that a worker sandbox cannot do here.
2. Give cpudetect.cpp's StringClass view the nontrivial constructor that retail
   proves, so that unit emits the initializer/cleanup itself; then this file can
   be reduced to an extern declaration or deleted. That is a change to a
   49/49-matched TU and needs the same ledger regeneration.

Until one of those lands, keep the definition here and the two baseline lines:
the duplicate is a model conflict, not a stray definition.

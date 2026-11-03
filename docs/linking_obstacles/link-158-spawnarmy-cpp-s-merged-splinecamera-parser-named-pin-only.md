### LINK-158: SpawnArmy.cpp's merged SplineCamera parser named pin-only placeholders and an undefined field table (2026-10-30, seat halilkkaya-lk8)

Status: repaired; census confirmation pending.
The TU merges `45b18288a4` / `6b48143b7d` folded `SplineCameraParseINIBlock`
(0x004E3300) into `WWLib/SpawnArmy.cpp`, so the whole TU (1,927 B) failed on
the parser's four unresolved names (census 2c21184e84):
`??0Rva003BA660Record@@QAE@XZ`, `??1Rva003AB460Tree@@QAE@XZ` and
`?append@Rva003BA660Owner@@...` existed only as symbols.csv pins (to
0x004E32D5, 0x002B80CE and 0x00566D7B), and
`?Rva003BA660FieldParseTable@@3QBUFieldParse@@B` (0x00861FB8) had no definer
("unowned" in the data ledger). Retail 0x004E3300 calls the rowed
`??0Rva004E32F2@@QAE@XZ` (0x004E32D5), passes VA 0x00C61FB8, appends through
the rowed `?rva00566D7B@Rva00566D7B@@QAEXABVRva004E32F2@@@Z` and destroys the
record inline with vptr 0x00C61F68 and the tree dtor 0x002B80CE, the body of
the rowed `??1Rva004E32F2@@UAE@XZ` in the same TU. Fix: the parser's record is
the TU's existing `Rva004E32F2` view (ctor declared), its owner the rowed
`Rva00566D7B` call, and the TU now defines the table under its data-ledger
spelling (three entries plus terminator, 64 B; new data row byte-verified).
Verified: `./build.sh` 52/52 rows and 5 data rows; scoped DIR32 consistency over
SpawnArmy.cpp and its five providers OK (19 symbols); `link_check` 273 -> 2,200 B
over the six units (SpawnArmy.cpp 0 -> 1,927, providers unchanged). Follow-up
done in `95c6888450`: the three pins above had no consumer left and are dropped
(pin 9405 -> 9402).

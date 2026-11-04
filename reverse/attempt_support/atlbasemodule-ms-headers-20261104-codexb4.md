# ATL base-module Microsoft-header cleanup

Inspected revision: `7c79aa880d`, 2026-11-04.
Scope: `Code/Libraries/Source/ATL/atlbasemodule.cpp` only.

Replace the local Windows types, structures, constants, API prototype and
`memset` prototype with the toolchain's `<windows.h>` and `<string.h>`.
The `// platformsdk` marker selects the real SDK. `WIN32_LEAN_AND_MEAN`
avoids unrelated COM headers and their `uuid.lib` directives.

The scoped Microsoft-header scan reduces this source from 17 local names
(conflicting ABI) to one same-type declaration, `__ImageBase`. This linker
symbol remains declared using the SDK's complete `IMAGE_DOS_HEADER`.
Including `_vcclrit.h` solely for that declaration would also define managed
CRT startup state, unrelated to this native ATL constructor.

Validation:

- `./build.sh`: both constructors byte-match, 197 bytes; one named Windows
  import verified. Frozen-file check: all defined functions already matched.
- Saved baseline and final COFF objects are identical except for the four-byte
  COFF timestamp. This includes code, data, all symbols, relocation targets,
  COMDAT selections, undefined references and linker directives.
- Strict `link_check.py --prepare-current`: both rows verified with a reusable
  receipt. `data_check.py`: zero findings.
- The ordinary preview retains the known `___ImageBase` model artifact
  documented in LINK-133 and LINK-168, against census index `f12552d0a7`
  (2026-11-04 20:47). Identical object contents prove no new link dependency;
  this cleanup claims no linked-byte or ownership gain.

`ms_header_audit.py scan SOURCE --write-queue` refreshes only this source's
queue entry. No source paths, ledgers, pins, aliases, protected identity/data
keys, shared headers or reference pins change. No runtime or maintainer-only
measurement was invoked.

# WWLib mpmath SDK min cleanup

Inspected base: `30ddf36ccb`; upstream base: `f3aeaab9aa`.
Scope: `Code/Libraries/Source/WWVegas/WWLib/mpmath.cpp`, claimed as a file.

Replace the private `min` macro and `win.h` shim include with the Platform SDK's
`windows.h`. Put the SDK include directory before donor and sweep directories;
the `// platformsdk` environment path alone follows those explicit directories.
The final dependency manifest resolves `Windows.h` from the toolchain's
`Vc7/PlatformSDK/Include`, with no donor `windows.h` shim dependency.

`always.h` defines `NOMINMAX`, so undefine it before the SDK include to select
the SDK macro rather than instantiate WWLib's global `min` templates.
`WIN32_LEAN_AND_MEAN` avoids unused OLE headers' additional uuid.lib directives.
No shared header or function body changes.

Checks:

- `./build.sh Code/Libraries/Source/WWVegas/WWLib/mpmath.cpp`: 61/61 matched
  functions, one byte-verified data row, five verified named imports; string
  and floating-reference checks pass.
- Before/after COFF comparison using `exit_link.coff_view`: all 61 external
  definitions retain their complete section bytes, flags, COMDAT selection,
  symbol offsets and relocation targets. Compiler-local label names are
  normalized to their owning section's external names and label offset.
  All four external references and the complete linker-directive payload
  remain identical. No provider was added or removed.
- `find_declared_unmatched.py`: all defined functions already matched.
- `ms_header_audit.py scan <source> --write-queue`: zero local Microsoft
  definitions; removes this unit's sole queue entry through the owning scanner.
- `check_csv.py` and `git diff --check` pass.

No linked-byte, image-ownership or runtime gain is claimed. This retires one
local Microsoft-header definition and its queue entry.

# RtcPdbLookup SDK-header picker false positive

Inspected `d8bb49e7da` on 2026-11-04. Scope:
`Code/Libraries/Source/CRT/RtcPdbLookup.cpp`, GetImageInfo at 0x0075ACEE.

Target/source facts: the TU includes `psapi.h` for `MODULEINFO`. It masks the
SDK function names while including that header, then declares static function
pointer variables named `GetModuleInformation` and `EnumProcessModules`.
GetImageInfo fills those variables with `GetProcAddress` after loading
`PSAPI.DLL`; its Toolhelp path remains an alternative runtime branch.
These variables are not replacement declarations of the SDK functions.
Removing them in favor of SDK calls would change dynamic loading and binding.

The default picker classified these two variables as removable SDK copies and
served an `adapt` task. No source change was attempted. `./build.sh` for the
whole TU passed all 3 rows, 23 string literals plus one empty-string reference,
and 28 named import references. `find_declared_unmatched.py` reported all
defined functions matched.

Remaining tooling work: distinguish SDK function-pointer storage from copied
SDK function declarations in the Microsoft-header audit/picker. Retain checks
for genuine function declarations and bodies. The queue row remains unchanged;
this note retires no debt and claims no linking improvement.

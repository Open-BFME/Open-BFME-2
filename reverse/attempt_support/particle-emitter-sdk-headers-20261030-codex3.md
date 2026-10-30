# Particle-emitter saver SDK headers

Scope: ParticleEmitterDefClassSaveInfoBool.cpp, SaveInfoV2Bool.cpp,
SaveLinePropertiesBool.cpp and SaveW3DBool.cpp under
Code/Libraries/Source/WWVegas/WW3D2/. Existing rows at 0x001B0C50,
0x001B0CA0, 0x001B0E50 and 0x001B0A70 cover 399 bytes. This changes
header ownership, not their recovered identities or layouts.

Replace winbase_shim.h and the local MAX_PATH/LPCTSTR definitions with the
VS2003 Platform SDK's windef.h and winbase.h. The platformsdk marker opts
into that SDK; _X86_ supplies the architecture selection normally made by
windows.h. stdarg.h supplies the varargs type needed by the component
headers. Remove the sweep include directories. The neighboring recovered
particle-emitter serializers already use this component-header arrangement.
The build dependency manifests confirm windef.h, winbase.h and winnt.h
resolve inside Vc7/PlatformSDK/Include, with no windows.h or sweep header in
these four units' dependencies. Merely spelling <windows.h> was insufficient:
the sweep directory and then the donor WWLib directory each supplied a stand-in.

Ordinary builds verify 4/4 rows. Before/after object_facts and
object_references compare equal: COMDAT names, normalized code/relocation
digests and sizes, exclusive definitions, undefined/weak externals, root sets
and per-function edges. Each unit has two COMDATs and one exclusive definition;
the first three have three undefined symbols and SaveW3D has two. None has a
weak external. The vector-constructor-iterator anchor and its optimization
settings are unchanged. Retail verification comes from the normal build;
the summary's digest-only comparison is not a separate retail-truth claim.
See [the object comparison summary](particle-emitter-sdk-headers-20261030-codex3.json).

find_declared_unmatched.py passes before and after. A scoped ms_header_audit
scan finishes with no local Microsoft definitions in these four sources;
refresh_queue removes exactly their four entries (eight local definitions).
This does not retire definitions in shared/reference headers. check_csv.py
and git diff --check pass. Strict receipt preparation succeeds for all four
providers. The ordinary link preview against index 12b9e7a7c0, 2026-10-30
10:11, retains four clean units and 399 -> 399 authored bytes. No census
linking or ownership gain is claimed.

SaveHeaderBool.cpp and SaveUserDataBool.cpp remain queued and unchanged.
Commit 82d31c2fef independently verified their legacy unsuffixed kernel32
imports and deliberately selected winbase_shim.h first. Their lstrcpyn and
lstrlen calls need that existing import identity addressed before the same
SDK migration can apply. No blanket ANSI-suffix substitution was attempted.

# Script debug DLL declarations from the Windows SDK

The default picker serves ScriptEngineAppendDebugMessage.cpp's three local
Microsoft definitions: HMODULE, FARPROC and GetProcAddress. Replace them
with <windows.h> and the explicit // platformsdk source opt-in. Preserve
the existing int st_DebugDLL global declaration;
its shared owner is unchanged. An explicit reinterpret_cast<HMODULE> adapts
that existing four-byte value at the API call without a second global or
any new address binding.

Private verification checks all three owned addresses: the171-byte parent,
eight-byte cleanup and ten-byte EH handler. All match, and all eight previous
code COMDATs remain byte-and-relocation identical with none added or removed.
Thus the SDK import retains the existing callee and stack ABI rather than
merely fitting an otherwise masked call. No compiler flags or headers owned
by the project are changed.

The isolated worktree's normal ./build.sh passes3/3 functions, two nonempty
literals and one empty string, and the single named GetProcAddress import.
The frozen-file check passes. The owning ms_header_audit scan completes with
zero local definitions, zero prototypes and zero failed analyses for this
file, and refreshes only its queue inventory. Three local definitions and
one queue entry retire;461 other queue files remain.

Final strict reusable preparation passes. The own link_check verdict reads
LINKS,181->181 bytes, using the published20:08 index at b974574bd6. This is
a scoped preview and does not establish a new census or an executable image.
The strict dependency receipt names the toolchain's PlatformSDK/windows.h;
no sweep windows.h or fallback include retry is used. The real-SDK private
probe preserves all eight COMDATs, and normal build, strict preparation,
the clean inventory scan and LINKS preview are repeated under that profile.

No source path changes or additional consumer edits are needed. This is
header debt removal with zero unique-byte gain, not a new linked image or
game-run result. The preceding Hashable repair's wider audit remains
inconclusive on AggregatePrototypeRegistration.cpp's current receipt; this
source cleanup does not clear that separate consumer/census scope.

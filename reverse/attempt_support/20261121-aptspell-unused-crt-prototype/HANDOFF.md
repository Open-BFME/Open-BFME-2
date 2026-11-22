# Item015 AptSpellStore — unused declaration cleanup ready, normal build pending

Source base/head `4c3ccf6f37e556b07d17e6dce2b7dd605d0cc89b`. Proposed edit: remove only line89, `extern "C" char *__cdecl _mbscpy(char *dest, const char *src);`. Candidate SHA256 **0f19945c8ec6296b6276f94cda4770b82ec33579ecd4c0f660395299d8df6e92**; original **796ca02ee9649e5ac2963efbb634f21f30552fc691b6e9727a77e095104987a8**. No new header or _CRTIMP/dllimport override, cast, function, class, layout or pin is required.

**Sicher:** the current whole695-line source uses `_mbscpy` exactly once, as that unused prototype. Its complete current COFF has no `_mbscpy`, atoi, strncmp or parser symbol at all; therefore no relocation can reference one. The static parser at the top uses atoi/strncmp from existing real `<stdlib.h>`/`<string.h>` headers and is not emitted in this seed. Its named target bodies remain in parseSpellIndex_Thunk.cpp. All16 existing source rows/1250B are inventoried in CLAIM-SCOPE.json, including constructor917B,4 other primary bodies and all11 compiler companions. `find_declared_unmatched.py` says all definitions already matched.

## Current native audit, not stale queue counts

Using the existing header index490e5f72e45d00f4 only after recalculating its full native header/compiler key, pure `ms_header_audit.scan_text` finds exactly **1** local occurrence, `_mbscpy` at89. Its ABI is indeed incompatible with the real unsigned-char-pointer/dllimport prototype from Vc7/include/mbstring.h:123. The queued3 count is outdated: atoi and strncmp already come from actual headers and are not local definitions in the fresh audit. Deleting the unused prototype gives **0 occurrences, no scanner error, clean classification**. No shared cache, occurrences file, queue or tool was written. READONLY-HEADER-AUDIT.json records both arms and index hash.

Pre-existing include-closure warnings remain identical and visible: Shell's name collision with ShlDisp and3 unresolved bfmealloc STL includes. Zero local occurrences is not a claim that all headers or class contracts are reconstructed. The ordinary owning scan is the authority for refreshing this source's queue entry.

## Old blocker and actual CRT boundary

Re-log120108 said the direct non-dllimport _mbscpy declaration was load-bearing, by analogy with parseSpellIndex_Thunk.cpp. That is not current evidence for this seed: there is no invocation or emitted symbol. Do not repeat a blanket `<mbstring.h>` swap or alter this TU's `_CRTIMP` configuration. The unchanged public prototypes are atoi(stdlib.h270), strncmp(string.h133), unsigned-char `_mbscpy`(mbstring.h123); /MD normally makes _CRTIMP dllimport unless its supported guard is set empty.

In the other actual callers the direct native _mbscpy thunk629176 and IAT BBA6D0 remain real, as the existing import row/pin and Nov4 AptPlayerStatus evidence show. That is a boundary to preserve there, not a justification for keeping an unused conflicting declaration here. The broader AptSpellStore merge/novtable/header/14-slot issues remain separate, unchanged work; LINK219's scoped restoration was already cleared. No full image/runtime result is claimed.

## Scope and normal completion

CLAIM-SCOPE.json has all16 source RVAs and its single file path. Root already holds the file; no class, shared header, dependent provider or import scope needs changing. No compiler invocation has been performed by this worker. The minimal edit can be applied and reviewed directly by Root after normal scope reservation; a new compiler experiment is not needed merely to revisit the old unrelated thunk blocker.

Root should copy the candidate with bytes preserved, run normal `./build.sh Code/GameEngine/Source/GameClient/GUI/AptSpellStore.cpp`, compare its complete runtime COFF footprint with CURRENT-COFF-READONLY.json/old object as needed, and run normal `ms_header_audit.py scan SOURCE --write-queue`. That tool alone removes the stale queue entry while preserving unrelated entries. Then ordinary commit/hooks/publication apply. Expected code change is0; this is declaration debt cleanup, not new bodies/bytes/link/runtime progress. A normal build/queue pass is still pending, so the task is not yet marked complete by this worker.

Private evidence/source proposal only. No production/tool/header/ledger/queue/claims/Git or shared-cache/object/index mutation.

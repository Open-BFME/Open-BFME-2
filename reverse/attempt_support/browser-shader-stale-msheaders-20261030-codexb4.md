# Browser and shader-manager stale Microsoft-header queue entries

Inspected base: `c647a75e55b27d0c76c8b56a8475fd4ba680ec52`, 2026-10-30.

The Microsoft-header queue still served declarations already removed by
published source changes:

- `43e9ec072a` replaced DX8WebBrowserInitialize.cpp's local
  `_com_issue_errorex` declaration with `<comdef.h>`.
- `73b74a51cc` replaced W3DShaderManager.cpp's local `GetProcessHeap`,
  `HeapAlloc`, `HeapFree` and `OutputDebugStringA` declarations with its
  Windows-header include. That commit removed its queue row, which the
  current queue nevertheless contains again.

No source, header, ledger, pin or ABI changes are needed here. The owning
`ms_header_audit` scanner reports zero local occurrences and class `None`
for both current sources. Its `refresh_queue(results, index)` removes only
these two records (five queued declarations); unrelated queue records stay
byte-for-byte. This reconciles the queue with existing repairs and does not
claim new header adoption.

W3DShaderManager's include closure still reports 720 findings, principally
in `reference/shims/sweep/windows.h`, plus the unresolved d3d9 include and
mmsystem shim. These are distinct shared-header prerequisites. This local
queue refresh does not establish real-SDK closure or retire those findings.
The browser scan has zero include-closure findings. Local scan receipts are
in `build/msheaders-refresh-codexb4/scan.json`.

Verification of unchanged current source:

| Source | Function rows | Data rows | Link preview authored bytes |
| --- | ---: | ---: | ---: |
| DX8WebBrowserInitialize.cpp | 7/7 | 1 | 771 -> 771, LINKS |
| W3DShaderManager.cpp | 24/24 | 5 | 3,795 -> 3,795, LINKS |

Both declared-unmatched checks pass. Each unit passes
`link_check.py --prepare-current` with strict reusable receipts and ordinary
byte, literal, import and funclet checks. Ordinary paired preview uses the
published index at `12b9e7a7c0` (2026-10-30 10:11 UTC). The preview confirms
only these two units; there is no new census, ownership or runtime claim.
The paired `./build.sh` also passes 31/31 rows, six data rows, five strings
and 22 imports; `eh_verify.py` reports EXACT 6 with no baseline exceptions.

The default picker first selected collect.cpp at `0x000EFB4C`. Its current
preview against the same index still reports the documented 14 unresolved
names and four COMDAT conflicts, with five matched rows and 148 authored
bytes. RenderObjClass's persistence/dependency interfaces and the
ProxyClass-vector lifetime/virtual providers remain prerequisites; the four
losing RenderObjClass methods are Is_Visible, Set_Collision_Type and both
Get_Bone_Transform overloads. No unchanged trial was repeated and no source
was edited. Its claim was released before selecting the queue cleanup.

# FileSizeHelper: use the actual Windows SDK, 2026-10-28

Selected by `tools/ms_header_audit.py next --class drop-in-candidate`: `Code/stlport/FileSizeHelper.cpp`, two local API declarations (`GetFileSize`, `GetLastError`). The whole file owns one already matched 50-byte body at RVA 0x0001D240.

Replace the API declarations and private LARGE_INTEGER stand-in with `<windows.h>` and SDK `LARGE_INTEGER`, using the supported `// platformsdk` marker. Keep /MD, the low/high size query, last-error condition and truncated long result. Configure the SDK with WIN32_LEAN_AND_MEAN and remove this TU's unused `// stlport` include profile: the helper uses no STLport declaration.

The earlier unrestricted include trial (Windows run 40682600083) verifies the original and modified 50-byte body and both imports, but its COFF `.drectve` adds stlport_vc7.lib and two uuid.lib directives. It is not the landed source. The final variant must preserve all runtime sections, relocation targets, external symbols and linker directives before the scoped queue row can be retired.

No new C++ bytes, measured link gain or full-game link clearance is claimed.

The preceding fully qualified source commit 6661d06b798979bd317a9e36f67dcfdd95a47421 passed all required native hooks and its normal fork push. Its publication retry stopped when upstream refreshed the canonical BFME 1 reference. The continuation reviews the new published paired-reference receipts and rechecks the same SDK cleanup; it claims no additional reference or byte progress.

The same source was subsequently qualified and normally pushed as f9c8dadf1620fc12fdf0bc7059ba2c07f950c07e in Windows run 40718695340. A later normal rebase stopped on a queue-only conflict after upstream retired neighbouring Microsoft-header rows. The continuation permits only that exact conflict: it takes upstream's queue, asks ms_header_audit.refresh_queue to retire this file's row, asserts all unrelated rows are byte-for-byte preserved, and continues the normal Git rebase. Any source, reference or AGENTS conflict still stops for review.

Correction to the prior extra diagnostics: their exit code 2 came from unsupported BFME-1 CLI options accidentally passed to BFME-2 link_check.py. They were command-line usage failures and do not establish a link-preview result. The native body, import, runtime COFF comparisons and unmodified hooks were independently valid. This continuation uses the supported BFME-2 preview command and prepares current-provider receipts with --prepare-current. It does not change any verifier, authority, census definition or admission baseline.

## Native qualification receipts

Original and updated source each verify the existing 50-byte body at RVA 0x0001D240 with the unmodified original-compiler driver.
Runtime COFF sections, relocation targets, external definitions and undefined symbols are identical. EH verification passes.
The normal compiler dependency receipt records the vendored Vc7/PlatformSDK/Include/windows.h.
The owning Microsoft-header audit classifies the updated file as clean; its scoped refresh removes only this file's two-definition queue row.
Canonical inputs: 0424131c818fba6641613ef826222ecf30845025. Fetched official BFME 1 master: c2740bede76a563c5e7a8a611b9304315725ff31.
The canonical pointer was already refreshed and fully verified upstream in commit 67587ea6ec644ca847cf1cf77cd6f3bcba6401a6; both full old/new gates and the donor scan pass in its tracked receipts. This SDK task reuses that verification within 72 hours, with the earlier canonical-commit timestamp 2026-10-28T11:20:47Z.
No reference pointer is advanced and no qualification of the newer fetched HEAD is claimed. The independently published reference update is not counted as this contribution.
The supported strict current-provider preparation runs before both paired checks. The published census index is fetched before the paired checks. Census-backed link previews: original exit 0, SDK exit 0. Preview scope is recorded in the native logs; no full-game or census gain is claimed.

Windows evidence: https://github.com/McMickey93/Open-BFME-2/actions/runs/40731823379

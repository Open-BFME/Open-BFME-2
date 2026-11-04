# W3DShaderManager glow consolidation prerequisites, 2026-11-04

Base: `790bb903a4`. Claim owner: `yasinschroeder-codex3`.
Published index fetched at `3fbce7bcb2`, 2026-11-04 22:01 UTC.

The current map approves performGlow (RVA `0x00077392`, 2150 bytes) for
W3DShaderManager.cpp. The original supported merge accepts neither remaining
whole-file donor. performGlow first fails on protected DX8Wrapper statistics;
setShroudTex reaches a non-POD ShaderClass inside RenderTargetTemp.

The performGlow private view now preserves the seed's three friend declarations.
Its DEVICE9 macro uses the same qualified accessor as the seed. Its texture
helper uses explicit IDirect3DBaseTexture9 casts: the seed's TEXTURE9 macro
returns IDirect3DTexture9 for GetSurfaceLevel, so the two macros cannot overwrite
one another. No header, compiler flags, pin, alias, object identity or ABI changes.

Verification:

- Original and final performGlow scoped builds: 1/1 exact, four float literals
  verified, named-import and string checks pass; no declared-unmatched body.
- Final ordinary link preview: LINKS, 2150 -> 2150 authored bytes. This is a
  preview against the published index, not a census gain.
- Supported final merge dry-run: accepts the seed and performGlow, preserving
  all 33 rows. LinkGuard accepts the composition of census-linked inputs.
- `header_adopt_lane.py accept --class Vector4` for setShroudTex passes and
  retires its one stale header queue row. The canonical include already exists;
  no hand-edited retirement or donor source change. Its EH graph is EXACT.
- `check_csv.py`: OK, 99451 functions, 9328 symbols, 2268 data rows.

Remaining prerequisite: setShroudTex still reaches C2621 for
RenderTargetTemp::shaderHome because canonical ShaderClass has a copy
constructor. Recover its four-byte shader overlay as POD storage before
reconciling that donor; keep the native 12-byte temporary lifetime overlay.
The two mixed sources remain excluded. Canonical DX8Wrapper adoption and the
older consumer-coverage/census handoff remain separate work.

## Applied composition

After prerequisite commit `5debe8b3b6`, `tu_skeleton.py --merge` absorbs
performGlow into its approved W3DShaderManager.cpp and removes one source file.
It preserves all 33 function rows and six data rows. The only TU-map change is
the absorbed row's source column; assignment evidence is unchanged. The donor's
DX8Wrapper header-queue key transfers to the destination, preserving the debt.
The destination already has the same class/source key, so commit-msg requires
the documented per-key Debt-Retired accounting trailer for the vanished donor;
both individual header adoption rows remain, including their original RVAs.
The other donors remain untouched; setShroudTex is rejected at the same C2621.

Post-merge verification:

- `./build.sh` passes 33/33 functions, 6/6 data rows, three string literals,
  20 float literals and 16 named imports. Declared-unmatched check passes.
- `eh_verify.py`: five EXACT graphs, no baselined or missing graph.
- Ordinary link preview: LINKS, destination authored bytes 6036 -> 8186.
  The 2150 bytes moved from the removed donor; total coverage is unchanged.
  Supported LinkGuard accepts the census-linked input composition, including
  provider/consumer and selected-COMDAT checks.
- `link_check.py --prepare-current` passes for the destination and writes a
  strict reusable byte receipt. This does not verify affected-consumer closure
  or replace the scheduled census.
- Code identity: 33 rows, zero new findings. Data check retains the seed's
  existing wrong-name finding at 0x009E1F24; no identity or data keys retired.
- `check_csv.py` and staged whitespace checks pass, with ledger counts unchanged.

Path/debt audit covers `origin/master` through `5debe8b3b6` plus this composition.
The only outgoing source deletion is W3DShaderManagerPerformGlow.cpp. Combined
basename/path search finds no active tool, hook, workflow, include or build-file
consumer. Functions, TU map and header queue resolve to the destination; no
code-identity, data or MS-header register key needs transfer. Remaining old-path
mentions are the historical census result in reverse/link_status.csv, previous
attempt evidence and the generated composition-origin comment. Census status
is intentionally not rewritten by a consolidation. Current destination byte
and link receipts replace donor receipts. No alias or hatch was removed.

Full selected-consumer coverage remains open in the existing obstacle entry;
the next scheduled census must include the destination and affected consumers.

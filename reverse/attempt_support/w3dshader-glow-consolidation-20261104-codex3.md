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

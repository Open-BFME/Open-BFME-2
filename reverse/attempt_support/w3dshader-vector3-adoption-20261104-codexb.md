# W3DShaderManager canonical Vector3 adoption, 2026-11-04

Inspected base: `54202cebba`. Seat: `yasinschroeder-codexb`.
Provider index: updated `a62ac1c10b` (2026-11-04 07:28 UTC), census
`5a13f2cd61` (05:53 UTC). Fetch kept that local index and imported matching
published objects. These are preview checks, not a new census.

## Target facts and change

The existing 378-byte `startRenderToTexture` row at RVA `0x00075BD8` lives in
its approved W3DShaderManager.cpp TU. Its three clear-color floats occupy the
same 12-byte temporary overlay as the scale and shader temporaries. The initial
supported merge dry-run rejects performGlow on C2621: the canonical Vector3
brought by that donor has a copy constructor and cannot be a VC7.1 union member.
The canonical header already documents retail's 12-byte, three-float layout;
no donor layout was adopted as target evidence.

Replace the private Vector3 declaration with Vector3Data.h. Keep the union's
color storage as three POD floats and pass its address as the existing
`const Vector3 &` Clear parameter. This preserves the native overlay without
putting a non-POD class inside a VC7.1 union. Hoist the existing SDK markers
to the top so header-layout probes retain the source's compile environment.
No compiler flag, pin, alias, data owner, ledger identity or source path changes.

The automatic adoption proposal refused a field rename because `X` already
exists in another type. The final source needs no field renames: the union's
float array is not a Vector3 member, and no access to the private Vector3's
m_x/m_y/m_z remains. Canonical-header acceptance judges the final source.

## Verification

- Before and after scoped builds: 32/32 function rows and all six data rows pass;
  literal/import verification passes and the funclet labels resolve through
  their exact parent EH data.
- `header_adopt_lane.py accept --class Vector3 <TU>` passes structural, byte and
  ordinary link-preservation checks, retiring exactly one header_queue.tsv row.
- `find_declared_unmatched.py <TU>`: all definitions already matched.
- `eh_verify.py <TU>`: all five EH graphs EXACT, none baselined or missing.
- `check_csv.py`: OK (99,440 functions, 9,336 symbols, 2,269 data rows).
- `git diff --check`: clean.
- Data identity preview still reports the existing `g_00DE1F24` wrong-name at
  0x009E1F24 (see earlier shader-data handoffs); this change neither defines nor
  renames that global. No data-debt retirement is claimed.

### Scoped build output

```text
Source claims: OK (1 sources, scoped byte-verified)
Data rows: OK (6 row(s) byte-verified)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Funclet pins: 5 row(s) verified past a renumbered $L label
    uw_0075ef4e (Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp): $L511 was renumbered; verified parent EH data places $L63769 at 0x0075EF4E
    $L736 (Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp): $L736 was renumbered; verified parent EH data places $L63792 at 0x0075EF62
    Unwind@00b5efdb (Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp): $L1543 was renumbered; verified parent EH data places $L63662 at 0x0075EFDB
    Unwind@00b5efed (Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp): $L1575 was renumbered; verified parent EH data places $L63695 at 0x0075EFED
    Unwind@00b5efff (Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp): $L1602 was renumbered; verified parent EH data places $L63723 at 0x0075EFFF
Functions: OK 32/32 matched across 1 source file(s)
String-ref verify: OK (3 literals + 0 empty-string refs verified, 0 baselined, 0 unverified/skipped)
Float-ref verify: OK (16 compiler literals verified)
Import-ref verify: OK (16 named imports verified)
```

### Owning header retirement verdict

```text
  PASS Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp
  retired 1 row(s) from reverse/header_queue.tsv; commit it with the adoption
```

## Remaining merge prerequisite

The final supported dry-run still accepts no donor. performGlow now reaches
C2248 on DX8Wrapper::texture_stage_state_changes instead of the removed C2621
union failure. setShroudTex still reaches C2039 on DX8Wrapper::Set_Render_Target.
The view planner marks DX8Wrapper as canonical-header work; reconcile its
existing declarations, inline codegen and access contracts before another
merge trial. The two mixed sources remain outside this merge. Both failures
are recorded through re_log.py. Neither donor was edited or removed.

### Final merge trial (exit 2, no verified merge)

```text
tu: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp
approved: 48
mixed: {'Code/GameEngine/Source/Common/Rva00066A9ABody.cpp': 1, 'Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManagerShutdown.cpp': 3}
refused: {}
accepted: []
rejected: {'Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManagerSetShroudTex.cpp': "compile: Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\.W3DShaderManager.aa49643f0a69ac81.tu_skeleton.cpp(557) : error C2039: 'Set_Render_Target' : is not a member of 'DX8Wrapper' | Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\.W3DShaderManager.aa49643f0a69ac81.tu_skeleton.cpp(557) : error C3861: 'S", 'Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManagerPerformGlow.cpp': "compile: Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\.W3DShaderManager.a9eb4037943ac3b5.tu_skeleton.cpp(567) : error C2248: 'DX8Wrapper::texture_stage_state_changes' : cannot access protected member declared in class 'DX8Wrapper' | Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\.W3DShaderManager.a9e"}
adopt_first: {'Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp': ['BaseHeightMapRenderObjClass', 'DX8Wrapper', 'GlobalData', 'RefCountClass', 'ShaderClass', 'VertexBufferClass', 'VertexMaterialClass'], 'Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManagerPerformGlow.cpp': ['DX8Wrapper'], 'Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManagerSetShroudTex.cpp': ['BaseHeightMapRenderObjClass', 'DX8Wrapper', 'StringClass', 'Vector4', 'WW3D']}
link_guard: census-linked: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp, Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManagerPerformGlow.cpp, Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManagerSetShroudTex.cpp
blocked: no verified merge of two or more donors
```

Scope of progress: one canonical-header debt row retired and a concrete merge
prerequisite removed. Source count, census LINKED and image ownership gains
are not claimed. The earlier consumer-coverage handoff remains open.

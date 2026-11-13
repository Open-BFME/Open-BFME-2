# Shader texture array: real parent lifetime

Parent object: `RefCountPtr<TextureClass> g_shaderTextureSlots[8]`, the
existing sole32-byte storage owner at VA `0x00DE1F8C` in
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShroudMaterialPass.cpp`.
Worktree `build/r20`, owner `codex-01a1071d-root-isolated-r20`, base18c7dfbf938.

## Native and placement evidence

The36-byte initializer0x007ABF7B passes count8, stride4 and this storage to
the EH vector constructor helper0x00629512, with the existing RefCountPtr
default constructor0x00326BE6 and destructor0x0017098D. It registers
cleanup0x007B6BB9 through atexit0x006291F8. That20-byte cleanup passes the
same storage/count/stride/destructor to0x00629110. Both member callbacks
already have matched providers; no pin or new callback body is needed.

The PE's CRT pointer at VA0x00DA4124 names this initializer; the preceding
entry names the separate half-rate initializer0x007ABF6B. Storage is zero
filled. Nearby shader-manager globals suggest a neighborhood, not an
original-TU identity.

The owning map was regenerated with `tools/tu_map.py` and passed
`--check-fresh` before the edit. Both lifetime addresses still have empty
TU/confidence and `by=-`. The companion JSON records the map hash and rows.
The compiler-row exception in docs/consolidation.md therefore permits the
actual emitted initializer and atexit callback to follow this parent object.
The regenerated map and fingerprint remain local evidence and are not
committed. The parent's original TU remains unproved.

## Change

The existing handle view receives only the declaration `RefCountPtr();`.
The array now has its real nontrivial type; its native-copy template,
assignment and destructor are preserved. Getter/shutdown externs and the
single existing data row/index name follow the changed COFF decoration.
There is one owner, no alias and no second storage.

The compiler emits `_$E1` and `_$E2`, exactly36 and20 bytes with native
relocation targets. The manual initShaderTextureSlots and
destroyShaderTextureSlots definitions and claims are retracted in their
own reviewable commit; the actual compiler rows are admitted next. No
hand-shaped function is copied from the mixed initializer file.

## Verified parent stage

- All21 original four-source rows and both data rows passed before editing.
- All19 surviving rows and both data rows pass the normal build afterward.
- The owner's nine existing rows still match; its fourteen COMDAT payloads
  and relocation identities are identical after normalizing only the old
  and new decoration of this one data symbol. No COMDAT was added or removed.
- Scratch-emitted36/20-byte lifetime bodies match every native byte after
  resolving each relocation through an existing matched callback/helper or
  the proved parent-storage/cleanup address. Ordinary compiler-row admission
  is still required after the retraction commit.

This is source/lifetime recovery evidence. No whole-game link, bridge-count
measurement or runtime result is claimed here.

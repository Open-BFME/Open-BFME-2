# Shell menu image constructor identity repair

Date: 2026-11-05. Inspected revision: `aa156741d311a3648c89cd041e8574e3b3b310da`.
Scope: `Code/GameEngine/Source/GameClient/GUI/Shell/ShellMenuScheme.cpp`,
image constructor `??0ShellMenuSchemeImage@@QAE@XZ`, RVA `0x002004C3`, 58 bytes.

The registered key named StringBase<char>::clear at retail releaseBuffer RVA
0x00036410. The current pre-edit constructor instead referenced the public
AsciiString::clear spelling; the owning retirement scan refused that new wrong
binding too. The repair invokes the existing public StringBase storage clear
operation through the compatible string view. A local forceinline specialization
calls the native releaseBuffer worker and emits no clear wrapper. No shared
header, alias, pin, row or compiler flag changes.

Verification:

- `./build.sh Code/GameEngine/Source/GameClient/GUI/Shell/ShellMenuScheme.cpp`:
  32/32 rows exact before and after; string, float and import checks pass.
- `find_declared_unmatched.py` passes before and after.
- `eh_verify.py` after: six EXACT EH graphs, zero missing objects or failures.
- COFF comparison using allowed_symbols.Obj and _object_defs: all 645 external
  definitions retained, including all 97 code definitions. No added or removed
  definition. Only the image constructor's code/relocation digest changes;
  the sole removed external reference is AsciiString::clear. No link-wide
  provider or alternatename is removed.
- `allowed_symbols.py --source ...`: 64 references, zero wrong bindings
  (47 owner, nine alias, six EH, two fold).
- Initial retirement refused ten missing ledger objects and stale providers.
  Rebuilt exactly the 46 sources identified by the owning check's missing-object
  and participating-provider rules through `./build.sh`: 2,001/2,001 rows,
  402 literals plus 69 empty strings, 179 float literals and 208 named imports
  all verify. No source edit was needed for those providers.
- `repair_queue.py retire identity ...`: PASS, one registered key retired,
  zero still found; no manual register deletion.
- Ordinary `link_check.py` after: LINKS, 1,092 authored nonpadding bytes,
  against the 2026-11-05 15:19 index at f44cbcf5b0. This is a scoped preview;
  its displayed 850 -> 1,092 comparison includes earlier consolidation and
  is not attributed to this repair. No census or whole-game link gain claimed.

The native string-clear prerequisite is repaired for this constructor only.
Other remaining ShellMenuScheme composition prerequisites in LINK-117 are
outside this repair. Carry the changed consumer into the next scheduled census.

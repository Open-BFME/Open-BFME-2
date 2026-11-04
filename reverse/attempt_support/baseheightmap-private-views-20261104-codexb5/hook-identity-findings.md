# Identity findings from the commit hook

The pre-commit hook for `a465f255fb` passed, including 106/106 byte-matched
rows. Its code-identity check reported four findings outside the existing
register in **shadow** mode. They remain unresolved; the local link previews
do not establish identity correctness.

| Kind | Owner / caller | Symbol | Target / verdict |
| --- | --- | --- | --- |
| Binding | `BaseHeightMapReset.cpp`, `?reset@BaseHeightMapRenderObjClass@@UAEXXZ` | `?clear@AsciiString@@QAEXXZ` | `0x00036410`, wrong |
| Binding | `Rva0006D0D7Dtor.cpp`, `??1BaseHeightMapRenderObjClass@@UAE@XZ` | `??1Rva001F3574Vec@@UAE@XZ` | `0x0049B47C`, wrong |
| Binding | `Rva0006D0D7Dtor.cpp`, `?rva0075E9AB@@YAXXZ` | `??1Rva001F3574Vec@@UAE@XZ` | `0x0049B47C`, wrong |
| Definition | Set destructor | `??1?$set@PAURva001408C0Target@@U?$less@PAURva001408C0Target@@@_STL@@V?$allocator@PAURva001408C0Target@@@3@@_STL@@QAE@XZ` | divergent |

Both source basenames above are under
`Code/GameEngineDevice/Source/W3DDevice/GameClient/`.

The hook reported `106 row(s), 4 new finding(s), mode shadow`. Here “new”
means outside the register; a comparison against freshly compiled pre-change
objects was not performed. The functions' call expressions were unchanged
and the view reconciliation checked external symbol sets, but those facts
alone do not establish whether these findings predate the change. No
regression, false reject or clearance is claimed.

Next: investigate the three binding targets and the competing set-destructor
definitions in the identity lane, comparing pre-change objects where needed.
Carry this scope into the next scheduled census along with the existing
BaseHeightMap prerequisites. No baseline entry was added, no debt key was
retired, and no alias was removed to silence these findings.

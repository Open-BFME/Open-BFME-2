# One DX8PolygonRendererClass consumer adopts the existing header

Base4c9fb6b261 integrates official aff975ad9c5f. The native header picker claimed
the five remaining DX8PolygonRendererClass queue keys. This change completes only
the whole dx8renderer.cpp consumer; four other keys stay open and were not tried.

The old local view omitted two real4-byte words after vertex_index_range, placing
strip at24 and pass at28 with extent2C. The existing authored canonical header's
independent retail constructor/copy-constructor, Add_Mesh and allocation evidence
establishes words24/28, strip2C, pass30 and allocation34. The existing neutral names
field_24/field_28 are reused; they do not invent semantic identities. No new virtual,
base or nontrivial lifetime is introduced. The exact two-line prerequisite patch
is retained: after reconciling those genuine offsets, the normal header-adoption
tool removes the private view and writes the include. The final source has no
new private class and no remaining two-line duplicate layout.

The authored canonical header is unchanged. The saved class_contract JSON remains
partly stale: its old strip24/pass28 coexist with Strip2C/Pass30 and an inherited
question. Only its independently recorded retail fact sites are a lead here;
this change does not call that entire stored contract resolved or regenerate it.
The source's inline two-argument Set_Vertex_Index_Range is unused; the existing
17-byte provider lives in DX8RendererAddMesh.cpp. The canonical four-argument
overload is distinct and unused in this consumer. There is no new/sizeof of the
class here. The preexisting MULTILIST_H include order and base wrapper are kept.

Normal before/after build:91/91 code rows and one data row. Native FDU accepts
all existing definitions and marker inventory is byte-for-byte unchanged.
The full ordinary object comparison preserves236 nondebug runtime nodes, all
bytes and relocation targets, external definitions and undefineds, weak bindings,
COMDAT choices and SafeSEH input sequence. No newly emitted inline body is hidden.
Normal link previews and native accept preserve this consumer's existing linked
bytes. Native accept retires exactly its one queue key, with all normal commit
and publication hooks retained. No header, contract, pin, row or allowance edit.

This is one completed declaration/header-debt task, not a newly recovered C++
body or unique-byte increase. It proves no whole-image link, game execution,
crash, memory or performance improvement. The separately observed upstream real
link535ac49e is not evidence for this feature head.

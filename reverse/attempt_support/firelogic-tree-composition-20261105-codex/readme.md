# FireLogicSystem tree composition prerequisite, 2026-11-05

Inspected revision: `19805bc85602ab55af693c1e9e25fb42c18cb55c`. Index/census: `c95fcfcfcd`, 2026-11-05 05:17.
No census, real link, nightly or smoke run was started.

## Target facts and repair

The normal guarded merge initially accepts neither WWLib helper (both `bytes`),
as recorded in LINK-252. A focused composition shows the 56-byte destructor at
0x0028681A loses its EH state reset before `free` under the destination's /EHsc
region. Its native body calls clear, sets the EH state to -1, checks the header
and calls the game-free wrapper at 0x00030830. The existing matched
`Rva00030830GameFree` names that wrapper; no pin, extent, type identity or layout
was added. An inline specialization spells the same base header release through
that C++ declaration, retaining the call's exception contract across composition.
Opaque record spelling/layout remains the existing donor inference.

`./build.sh` on both helpers passes 8/8 rows, including the unchanged ObjectID
helper. The repaired helper passes declared-unmatched, class gate and EH verify
(EXACT 1). Both previews remain LINKS, 61 and 66 nonpadding bytes respectively.
`prerequisite-object-proof.json` compares original and repaired first-helper
objects: all 17 external definitions are retained; 15 COMDAT digests are
unchanged; two destructor COMDATs retain identical raw bytes and change only
the free-call relocation from `_free` to the existing matched game-free name.
The ordinary byte gate verifies the native call destination. A focused temporary
composition retains all destination and first-helper rows.

## Second helper: trial reverted

A corresponding specialization and explicit ObjectID tree destructor body can
preserve all rows when composed, but the helper's standalone preview loses LINKED
66 bytes: its emitted `_Rb_tree_base<pair<const ObjectID,int> >` destructor differs
from the selected first COMDAT (no retail address). Its raw bytes agree; the
free-call relocation name differs. `dllimport __forceinline` suppression changes
the native EH state stores and fails both 56-byte bodies. Plain `__forceinline`
still emits the conflicting copy. All second-helper edits were reverted and its
8-row combined ordinary build and LINKS 66-byte preview were restored.
The next repair needs to preserve or reconcile that shared base COMDAT binding
while retaining native EH state under /EHsc. Do not repeat the unchanged merge.

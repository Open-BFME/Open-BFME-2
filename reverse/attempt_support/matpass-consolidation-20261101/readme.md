# Material-pass consolidation boundary, 2026-11-01

Control `5aaa45b`; current in-memory TU map approves 14 rows across six files.
The supported merge dry run accepts no donor. No source path or ledger moves.

The evidence planner was regenerated for WW3D2 and passed its currency check.
Its original-path and declaration warnings were reviewed against the current
TU map and compiler dependencies. The seed resolves MaterialPassClass and
RefCountClass through pristine Zero Hour headers; those headers were untouched.

## Concrete prerequisites

- The native constructor at 13EDD0 builds eight owning four-byte stage wrappers
  at +8, through ctor 326BE6 and destructor 17098D. The seed header has eight
  raw pointers: the offsets agree but the lifetime behavior does not.
- Tail offsets are shader +28, material +2C, enable +30 and cull volume +34.
  Simply renaming the constructor's fields is insufficient: ShaderClass's
  default constructor resets to a nonzero value, unlike native zeroing.
- Native table BD330C has four slots: DeleteThis 46CE57, deleting destructor
  13EF80, Install_Materials 13EFA0, and empty UnInstall_Materials 69E440.
  The install donor's one-slot view is incomplete for owning that table.
- The neutral 35-byte getter refuses baseline matching under the seed's carried
  empty flag override. A private build isolates INC-word versus native ADD-word,
  with all other original-body instructions identical. G7 restores the getter,
  Set_Shader's 22 bytes and Peek_Texture's 11 bytes, but breaks the seed's
  existing 39-byte Set_Material row at 30D3AD. Do not change tuning globally
  without recovering all these bodies and their identities.

`tu_views.py` temporarily unifies MaterialPassStage and the getter's category
view. All 13 affected rows pass strict verification, with four verified EH
label renumberings and unchanged external symbols. The merge still accepts
zero donors. Its RefCountClass rewrite is correctly restored because it changes
an external provider/reference; MaterialPassClass base clauses and texture-ref
destructor views remain unresolved. All applied mechanical source changes were
then restored; the final frozen scan is clean.

Next work needs a TU-scoped native class/lifetime reconciliation and a coherent
compiler profile, preserving the existing rows and providers. No new pragma,
pin, alias, private canonical copy or vendored-header change was introduced.
No source-file reduction, byte recovery, linked gain or census clearance is
claimed. The dry-run, view report, strict control and tuning proof are included.

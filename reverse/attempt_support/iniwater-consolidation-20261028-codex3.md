# INIWater consolidation prerequisite (2026-10-28)

Inspected base: b35ccaab0e. Scope: INIWater.cpp and the four clean donors
served by next_work.py --tier consolidate. name_lane.py consolidate --under
Code/GameEngine/Source/Common/INI/ supplied the evidence packet; tu_skeleton
rebuilt its stale TU map in memory. No committed TU-map regeneration.

## Seed declarations

The original seed imported broad donor headers for a single parser. Baseline
merge dry-run accepted nothing: the headers collided with the ctor donor's
_STL allocator/vector, the transparency donor's OVERRIDE, and the destructor's
WaterTransparencySetting(int). The assignment donor failed byte verification.

Replaced those imports with TU-local declarations and retained the parser body.
The 0x7C WaterSetting stride is a target fact, corroborated by the rowed
WaterSettingsArray.cpp initializer (six elements). The parser provenance remains
Open-BFME-1 revision 6d9434269164392c5ba62aaa7c15a86b5b020d76; that donor is
not claimed as a BFME 2 source path or layout proof.

Verification:

- ./build.sh on all five original sources: 16/16 function/EH rows, two data rows,
  string/import references passed. All five preview LINKS (738 bytes) against
  the 2026-10-28 15:58 census index at d92e7e6635.
- Edited seed: ./build.sh, find_declared_unmatched.py, converged data check and
  link_check.py --prepare-current passed. Three function/EH rows remain exact.
- COFF facts before/after: all eleven retained COMDAT names, byte fingerprints
  and sizes match; strong definitions, undefined symbols and weak references
  are unchanged. Only ??_H@YGXPAXIHP6EPAX0@Z@Z (34 bytes, fingerprint
  6246c280fc30) disappeared. The index selects ATL/atl_vector_constructor_iterator
  as its retail owner; INIWater was an unselected identical copy.
- The new supported dry-run accepts Rva00200CB1Assign.cpp,
  Rva00200D38Ctor.cpp and Rva00200E95Dtor.cpp together with the seed: eleven
  rows, one carried data-ledger entry. This is a proposal, not a landed merge.
- Transparency still fails composition because its selected INI view omits
  parseWaterSettingDefinition and getNextToken. Its Overridable/setting views
  also need reconciliation before adding it to the same TU. Four mixed files
  remain outside this mechanical merge; do not split them during composition.

The five sources have no keys in the identity/data debt registers, hatch
baseline, header_queue, ms_header_queue or flag_overrides. No source paths or
ledger owners changed in this prerequisite, so there is no path-consumer audit
or queue transfer yet. No census gain is claimed.

Seed outgoing audit: link_batch_audit.py --base HEAD --tip <staged tree>
--sources-from <seed receipt> returned 2 (inconclusive). The index predates
b35ccaab0e and the affected-consumer check lacks a current receipt for
Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp. This is not a clean
consumer audit; carry it into the next scheduled census. The seed's own strict
current preview remains LINKS, 198 -> 198 bytes. No proven loss was reported.

## Applied composition

After publishing "Isolate INIWater parser declarations for composition", tu_skeleton.py --merge applied
its accepted subset: Rva00200CB1Assign.cpp, Rva00200D38Ctor.cpp and
Rva00200E95Dtor.cpp are absorbed into the approved INIWater.cpp. SOURCE FILES
falls by three. Nine ledger rows and the one data row move; eight corresponding
committed TU-map source cells are mechanically repointed, not regenerated.
The existing generated/EH identities, data extent and placeholder class names
are preserved. The existing vector data-row size 1 versus data-ledger extent 12
is pre-existing debt, not a layout claim introduced by this merge.

Verification on composition:

- ./build.sh: 12/12 function/EH rows and the moved data row pass. Together with
  the untouched transparency parser, strict-current preparation passes the
  same 16/16 rows and two data rows as the original five-file scope.
- check_csv.py and find_declared_unmatched.py pass. eh_verify.py: three EXACT
  parent graphs. Converged data check: zero second names or unjudged rows.
- The merged object has 22 retained COMDATs, all with fingerprints and sizes
  equal to at least one corresponding original copy. Five strong definitions,
  26 undefined names and the one weak alias equal the union of the originals.
  The already-dropped vector iterator is the only removed COMDAT.
- Supported link guard accepts the merge of census-linked donors. Current
  preview: destination LINKS with 484 own bytes; transparency LINKS with 254.
  Total 738 bytes is unchanged from the five-file baseline. This is source
  recovery, not a linking gain or new census result.
- Outgoing link_batch_audit remains inconclusive: the index predates the base,
  and six identity-affected objects lack current receipts, first INI/INI.cpp.
  LINK-135 retains this scope for the next scheduled census. No proven loss is
  reported; consumer-wide stability is not asserted.

Batch path-consumer audit (prerequisite plus this composition): searched the
three absorbed paths/basenames across tools, hooks, workflows, source/includes,
root/build configuration, docs and reverse registers. No active path consumer
requires an edit beyond tu_skeleton's ledger/data-owner repoints. Remaining
mentions are historical attempt evidence, the census-owned link_status.csv,
merge provenance comments, and explanatory comments about the old fragments.
They are intentionally retained. No fold-proof references name a removed path.
No identity/data debt keys or hatch/flag keys require transfer. The merge's
refresh_reports step refreshed header_queue and ms_header_queue for the
combined destination and removed sources; neither queue requires a changed row.
The refreshed name_lane consolidation snapshot passes --check after composition.

Remaining: the transparency parser's INI declaration lacks the two seed parser
members; its Overridable and WaterTransparencySetting views must also reconcile.
The four mixed donor files remain intact. No unmatched interior range has been
claimed as newly lost code.

## Parser-view prerequisite after composition

Applied tu_views.py --class INI --class INIException to the destination and
transparency residual. Both now use the same declaration of each class; the
INI view preserves the residual's verified load-type field at +0x08 and adds
the seed's token reader/parser declarations. The exception view preserves its
eight-byte layout and existing names, using the seed's m_argCount spelling.
The tool re-read layouts, byte-verified both sources and checked frozen-source
coverage before keeping each class. An inherited trailing space in a moved
comment was also removed.

The two objects' complete COFF facts are unchanged from immediately before
this prerequisite: destination 22 COMDATs, residual 26, identical byte/relocation
fingerprints and sizes, strong/undefined names and weak aliases. Strict-current
preparation passes all 16 rows and two data rows. No ledger/path changes.

Supported merge dry-run still accepts no residual donor, now at the next
independent blocker: WaterTransparencySetting(int) is absent from the residual's
selected declaration. tu_views also reports the primary base's explicit m_vptr
under the destination's real vfptr and different secondary base clauses.
The mixed WaterTransparencySettingCtor.cpp already calls the rowed registration
constructor 0x00200D38 on this+0x10; its virtual secondary-base view differs from
the destructor fragment's value-only Rva00200E95Second view. Resolve those views
against the constructor, vtables and destructor before changing inheritance.
The identical FieldParse function-pointer member also produces a tu_views
source-reader diagnostic (parse absent from its parsed source member list);
that diagnostic does not show a target layout mismatch. No tool gate was changed
or bypassed in this pass.

Final parser-view preview: both sources LINKS with the same 738 total own bytes.
Its outgoing audit remains inconclusive against the older index, naming
0CreateAHeroManager21FE49.cpp as the missing current affected-consumer receipt.
No new source-path move was added after the composition's compatibility audit.

Final hook handoff: code-identity shadow mode reports a divergent definition for
`??B?$OVERRIDE@VWaterTransparencySetting@@@@QBEPBVWaterTransparencySetting@@XZ`
when the residual is checked. The OVERRIDE template itself was not edited;
all 26 residual COFF facts equal the original snapshot. Keep this warning with
the remaining override/setting reconciliation; no baseline admission or debt
retirement was attempted. The hook passes byte, data and all four EH graphs.

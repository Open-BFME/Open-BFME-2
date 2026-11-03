# AptScriptFunction GC donor header adoption, 2026-11-03

Base: `7c99285f90`. Source:
`Code/GameEngine/Source/Common/Rva00709C10Cluster.cpp`.
Retail row: `?rva00709D80@Rva00709B80@@QAEXXZ`, RVA `0x00709D80`, 113 bytes.

The default picker first served Coord3D. Its six-source package still has the
unchanged class-key/member/lifetime prerequisites in the 2026-11-01 handoff;
the claim was released without another trial. The consolidation picker then
claimed AptScriptFunction.cpp and this whole-file donor. The required planner
ran under Code/Libraries/Source/Apt/AptObject/; its stale-map and mixed-source
warnings do not approve moves. tu_skeleton rebuilt current TU approval in memory.

The donor's private AptValue view blocked canonical-header adoption only because
it called slot 13 `unused13`. Include the existing canonical AptValue.h and call
its neutral `vslot13` instead. Target table evidence and the slot offset are
already documented in the source and canonical header; this change adds no
application identity claim. The receiver layout and all calls remain unchanged.

Checks:

- Before and after: build.sh passes the sole 113-byte row; no literal/import
  references need verification. find_declared_unmatched.py and class_gate.py pass.
- header_adopt_lane.py accept --class AptValue passes and retires exactly this
  source's header_queue.tsv entry. No queue line was deleted by hand.
- The relocation-aware COMDAT digest and extent, external definitions/references,
  weak symbols and linker directives are identical; see object-comparison.txt.
  There is one COMDAT/definition, three referenced names and no weak symbols,
  alternatenames or forced includes. No link-wide alias was removed.
- Ordinary link_check before and after preserves LINKS, 113 -> 113 authored bytes,
  against census index 8661f15284 (2026-11-03 20:03 UTC). This is a preview only;
  no census gain, ownership gain or source-file reduction is claimed.
- check_csv.py passes: 99,431 function rows, 9,343 symbols, 2,269 data rows.

The independent baseline build initially overlapped the non-applying adoption
trial's temporary source swap and saw that trial's compile error. Both commands
completed, the source was restored, and the serialized baseline passed before
the retained edit and saved object comparison. Subsequent checks ran serially
with respect to this source.

The current merge dry run still accepts no donor (merge-after.txt). Its next
prerequisites are the AptValue definition inside AptScriptFunction.h, which now
conflicts with the donor's canonical include, and Rva00709B80's differing base
clauses/method declarations (tu_views.py confirms Rva006D6470Owner versus
Rva006D6360). Reconcile those providers and declarations in separately verified
changes before merging. The destination has a carried -O2 override and private
AptCIH debt; those remain untouched. Shared headers, ledgers, debt baselines,
hatches and source paths are unchanged. No tooling path audit is needed for
this batch because no source path moved. The outgoing hook still audits bindings.

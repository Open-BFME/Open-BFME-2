### ObjectTypes erase alias also served external consumers (2026-11-15)

Status: source repair verified, awaiting publication.

The real link at `2e687dc063` reported two unresolved references to
`?erase@?$vector@UGen_t_001db910_p4cd@@V?$allocator@UGen_t_001db910_p4cd@@@_STL@@@_STL@@QAEPAUGen_t_001db910_p4cd@@PAU3@@Z`,
from `AptOverButtonHandlerAdder.cpp` and `Rva005241DF.cpp`.
Commit `3c7fdba61cb` removed ObjectTypes.cpp's alias from that name to
`?erase@Rva003769C2StringVector@@QAEPAVAsciiString@@PAV2@@Z`.
A matching ledger row did not establish that the old name was a native
definition: its existing `object-symbol=` names the latter provider at
RVA `0x003769C2` (55 bytes). ObjectTypes itself called that provider;
the two external consumers still called the alias.

The first repair route was checked and refused. Restoring just the historical
pragma and its old baseline entry fails `hatch_counters --staged` as a
0-to-1 register increase. With the baseline restored to HEAD,
`hatch_counters --update` also refuses the net increase. No allowance,
new alias, or raised register entry is included in this repair.

The source repair shares the existing `Rva003769C2StringVector` declaration
through a header and uses that same view in both consumers. Its three
AsciiString pointers match the previously used 12-byte vector prefix;
the existing rowed member supplies erase directly. ObjectTypes keeps the
same provider body and ledger identity. The address-derived view name is
retained; this is not a claim about retail's original C++ type spelling.
No new lifecycle is requested by the shared view.

Verification at a9c23eeaef, using the index updated 2026-11-15 18:13 at
0fc06ec808 (census 16:43 at 1a70db7acf):
- Before and after build.sh: 19/19 rows across the three units.
- Before link_check: only ObjectTypes linked, 1/3; 891 -> 576 bytes.
- After link_check: ObjectTypes 576, AptOverButtonHandlerAdder 250,
  Rva005241DF 65; 3/3 clean, 891 -> 891 bytes.
- Data check: no findings; converged 11 addresses, no second names or
  unjudged rows. Pin consistency and check_csv passed; hatch gate passed.
- Object comparison covers every non-debug section, flags, bytes and
  relocations, matching reordered COMDATs by native function identity and
  local labels by section/offset. The expected symbol changes are the erase
  redirect and the two inline getter names. ObjectTypes' external definitions
  are unchanged. All three new begin/end copies are identical 3/4-byte bodies.
  No extra code/data/lifecycle is introduced.
- No outside index object touches any of the three retired Gen_t erase/begin/end
  names (17,680 objects scanned, including alias sources and targets).
- Full real-link/image validation was not rerun. exit_link --blockers needs a
  real link's errors.tsv; classifying the old image again would not establish
  this repaired image's result. The next real link must confirm zero missing
  symbols. The consumer predictions above are not a full-link/runtime claim.

The initial ordinal/symbol-label-only diagnostic comparison rejected harmless
COMDAT reordering and compiler-local label renumbering. The source-bound
function/section/offset comparison above resolves those differences; no gate
or baseline was changed.

Removal rule: a same-file alias can still serve other objects.
Before retiring one, inspect actual native definitions and directives,
find its external consumers, and run link_check over those consumers
together with the defining TU. A matching ledger name or a clean
link_check of the carrier alone is insufficient. Also see LINK-141 for
the earlier ObjectTypes string-destructor alias carrier loss.

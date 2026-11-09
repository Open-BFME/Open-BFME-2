# Complete native Wind table owners

After b7d3808f37 recovered the two transfer overrides, both compiler tables
in Rva003A53C4Finish.cpp contain all four native slots. Native constructor
003A5856 operands at 003A5870/003A5886 independently bind primary 0081B5A8
and secondary 0081B598. Both allocations are sixteen bytes.

DefaultModuleTemplateCopyCtors.cpp previously defined a one-byte strong
char at each address and installed those stand-ins in its copy constructor.
This change removes exactly those two definitions, binds their only source
consumer to the existing complete compiler symbols and transfers the two
explicit data rows to the emitter with their proven sixteen-byte extents.
Current Code text and the downloaded index show no outside consumer of
either retired spelling. Neither method row moves; no alias, pin, global
stand-in or compiler table is added.

All five copy constructors (435 bytes) match retail. Every retained code
body, relocation position, flag, selection policy and other data definition
is unchanged after the exact two reference substitutions. Normal four-source
verification passes 122 code rows and 21 data rows, no string/float/import
obligations, frozen checks and zero EH obligations. Four scoped link verdicts
retain LINKS 1,708 bytes against index 717b70f4ab. The final proof separately
records strict reusable receipts for the four owned sources.

The explicit six-object cached replay changes two strong-definition and
two unbounded-row refusals to zero, with both tables already correct and
no generated bridge. FXParticleSystem.cpp's unchanged getter object lacks
a strict-current receipt; it is neither claimed nor recompiled in this pass.
The other unchanged support object is debug_purecall.cpp. This bounded replay
does not establish global provider selection, a real image or game behaviour.
The raw heuristic data cache is left untouched; data_ledger.load reconciles
these two authoritative explicit owners and full extents in memory.

No donor was used. The exact table operands and bytes are target facts;
the emitter's partial class views do not prove retail's original class name
or complete layout. The two RenderObject byte owners and final pure-table
aliases in the same copy source remain a class-recovery prerequisite recorded
in LINK-636; their current producer emits no complete replacement table.

Local evidence is in build/wind-prepared-respell-20261109/: owner-trial.py,
apply-owners.py, verify.py --owner, owners-replay.py and their logs. Broader
audit receipt gaps must be carried into the next maintained census/image.

Published as 239be033c2 on the first attempt in 29.3 seconds. Normal hooks
and post-publication whole-object/native proofs pass; all four owned sources
retain strict receipts. The broader audit is INCONCLUSIVE at 717b70f4ab/base
b7d3808f37 for unchanged AIBuildable.cpp's missing receipt. Seven completed
Wind claims are released; the copy-source scope stays reserved for the
two remaining RenderObject owners. No global or runtime clearance is implied.

# Banner primary bootstrap and Windows verifier transport

The served BannerCarrierUpdate.cpp primary at 0084F838 remains a verified
52-byte strong array. Its only current compiler alternative is the four-byte
Rva004969FF UpdateModule table in Rva0024A797Derived.cpp. Destructor operand
00496A01 independently binds that helper table to the primary address; the
other stores bind 007EFF90 and 0084F82C. No complete replacement is established.

Two private experiments test a different prerequisite. Removing the explicit
primary store lets the existing canonical UpdateModule inheritance emit a
52-byte BannerCarrierUpdate ObjectModule table, preserving every existing
native row under a private proposed primary-address mapping. Selecting the
existing Snapshot name-slot mode and declaring the four real virtual roles
preserves those rows too. Nine of thirteen slot names already bind their native
targets. The remaining roles are deleting destructor496AC2, post-load497805,
name496A18 and transfer47F94C. These are declaration-only experiments, not a
recovered native table, admitted identity, new match or image result.

The unique getter can move through the supported function --to-class route.
Its dry-run accepts Banner's native constructor496A98, primary84F838 slot2,
and the prepared compiler table as structural evidence. The actual transaction
byte-verifies149 rows across the getter owner and Banner, the existing52B data
row and114 string references. It then requests585 additional name-dependent
sources. This conservative fanout is expected for a removed bare identifier
`name` when some consumer objects are stale or absent. No provider definitions
disappear in the private Banner comparison (148 before,157 after).

rename.build_verify passes all585 source paths on the Windows command line,
roughly40KB, and CreateProcess raises WinError206 before they start. There is
currently no source-list CLI in build.py. The transaction restores every source
and ledger file. A normal two-source rebuild afterward passes149/149, the52B
data row and114 string references, refreshing the restored caches.

This is a verifier transport failure, recorded through re_log.py before any
gate-code change. Fix transport separately with a regression test: preserve
all selected sources, every verification check, cancellation and exit handling;
do not narrow the conservative dependency scope. Then retry the supported
getter transaction and complete the real destructor/shared-slot providers
before publication. Incomplete declarations are not a publishable bridge repair.

The current class-fold route also refuses the old Rva scaffold: there is no
live Banner-named installer table yet. Prepared sources are consumed after its
initial fold-evidence check, so they do not bootstrap that proof. The destructor
and getter have only proposed TU placements; no unsupported row move is made.
Genuine ICF ownership, if used for distinct classes sharing transfer47F94C,
must follow the existing admission tool and its native fold proof. No manual
alias, pin, check bypass or nonmatching source is added.

Local evidence: build/banner-primary-recovery-20261109/ contains before.obj,
automatic-primary.obj, surface.obj, the two probe JSONs, getter-to-class dry-run
and application logs, and restored-baseline.log. proof.json summarizes the
bounded objects and transport failure. The old strong data owner is unchanged.
No donor was used in these experiments.

The preceding GPU destructor package landed as fb51e8d556 on its first attempt
in37.8 seconds; its post-publication strict/native proof passed. All GPU info
header queue rows are retired. Its broader audit remains INCONCLUSIVE for
unchanged AIBuildable.cpp's missing receipt (index717b70f4ab, basef5f6802754).
Carry that consumer and the current info family into the maintained census
and actual image. These previews and cleanups do not establish game execution.

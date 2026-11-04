# ExperienceTracker.cpp TU merge: header-adoption chain (2026-11-04)

Served: `tu-merge Code/GameEngine/Source/GameLogic/Object/ExperienceTracker.cpp`
(donors ExperienceTrackerXfer.cpp, ExperienceTrackerXfer_ExperienceTracker.cpp).
`tu_views.py --dry-run` routes ExperienceTracker to the header lane and reports
a Rva0039ADF3 base-clause conflict (seed `public Rva0039AD56`, donors
`public ExperienceTracker`).

Done: ExperienceTrackerXfer.cpp adopts `GameLogic/ExperienceTracker.h`
(commit "Adopt ExperienceTracker.h in ExperienceTrackerXfer.cpp"), 7/7 exact,
link_check LINKS 569 B. The dry run after it rejects that donor only on the
Rva0039ADF3 view (`rva0039AE04 is not a member`), i.e. on the seed.

Remaining chain (target facts from the existing row comments, not re-derived):

1. Ctor donor (0x0039AEBC) cannot adopt the canonical header: retail's EH
   states destroy a real AsciiString at +0x08, which the header declares
   `unsigned char m_08[4]`. Including one AsciiString shim from the header is
   unsafe: 35 of its 63 includers do not include `ascii_string.h`, and ten
   other shims define `AsciiString`. Candidate: a TU-selected surface in the
   header (like Snapshot.h's `BFME_SNAPSHOT_CONSTRUCTOR_ONLY`), e.g. a macro
   that makes +0x08 `AsciiString` for the ctor/dtor units only; same layout
   for everyone else. Header edit = full gate.
2. Adopting the canonical header in a ctor unit emits ExperienceTracker's
   vtable, whose slot 1 becomes `?loadPostProcess@ExperienceTracker@@MAEXXZ`.
   No row carries that name: retail slot 1 is 0x0039AC9C, rowed in the seed
   as `?rva0039AC9C@Rva0039AC9CForwarder@@QAEXXZ`. Rename that row first
   (`tools/rename.py`, docs/naming.md) or the ctor unit loses its link.
3. Seed: its private ExperienceTracker reads +0x34/+0x38 (Rva0039ADF3's
   fields) in rva0039B315; under the canonical header they go through the
   Rva0039ADF3 view. Its `~Rva0039ADF3` must keep calling
   `??1Rva0039AD56@@UAE@XZ` (byte verify does not follow the
   `/alternatename` to it), so Rva0039ADF3's base can only become
   ExperienceTracker after the split-identity dtor 0x0039AD56/0x0039AF5A is
   renamed to ExperienceTracker's (LINK-009 route), which also needs step 1.

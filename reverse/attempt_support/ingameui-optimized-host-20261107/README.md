# Optimized InGameUI host prerequisite

2026-11-07, following donor cleanup 5d3b84e454. The unchanged eight code rows
fit /O1 /Ot /G7 /arch:SSE, allowing an optimized host for the next consolidation
trial. flag_defaults.py propose records the existing override through its owning
path. The regional /O1 setting still loses one row, so no override is retired.

The blocker is compiler-generated scalar deleting-wrapper 0x007593F0, 25 bytes.
Retail tests the delete flag, saves this in ESI, optionally calls operator delete
and uses `add esp,4` before returning this. The regional size preference chooses
`pop ecx`, producing 23 bytes. /Ot retains the complete native 25-byte shape
while keeping /O1's other optimization passes. All seven other rows, including
the 16-byte static initializer at 0x007AE087, remain exact. This is codegen
evidence for an existing row, not new evidence for its original class or TU.

Private and normal source verification pass 8/8 code rows and both data rows,
with one compiler float. The private original and pruned optimized candidates
both pass LinkGuard. The 12 native borrowed-name checks lose no prior strict
owner twin: all seven previously matching copies still match; five previously
different or incomparable copies retain that classification. The ordered CRT
records are equal. These are bounded provider checks, not a new real image.

The prior 114-donor trial accepted none: 39 override/flag refusals, 73 without
a baseline match, one declaration conflict and one byte refusal. That trial used
the old no-/O override. The new flags require a fresh guarded merge trial;
private/canonical header and layout prerequisites can still reject donors.
No file-count reduction or whole-class clearance is claimed by this prerequisite.

The retained private probe reads the pruned before-source from git and its
frozen eight-row subset. Candidates stay under ignored build/, using the normal
private Verifier rather than the shared match-cache compiler. The existing
compiler override changes through flag_defaults.py; the commit and publication
hooks run the full repository gate required for that register.

# Sorting renderer data-debt handoff

Served source: SortingRendererBFME1.cpp. Current normal build passes26/26 and
three float references. data_check now finds only its two local-list identities;
the five registered DX8-global keys are already absent in current code. The
owning repair_queue retirement refuses because those two newer findings remain.
No register key or source is changed by this pass. Existing repairs get no new
source or byte credit here.

The bounded native read-only review in audit.md confirms a real ownership gap:
two separate private twelve-byte list pairs, a third eight-byte clean-list
fragment, plus two separate undersized four-byte vptr owners. Native complete
lists atVAsDB6200/DB620C are each[vptrBD23B4,0,0]. The latter's head atDB6210
is a subobject reference, not evidence for another independent global.

The small setter routines7B7090/7B70A0 are atexit cleanups. Startup7ACD90/
7ACDA0 registers them; it is not missing head/tail construction. Do not add
duplicate initialization or treat the vptr anchors as complete backing storage.

Read prior attempts before retrying: the October29 full extern-list trial
failed5/52 rows; the November5 narrower owner-cast trial failed Deinit151B.
Neither failed hypothesis is rerun unchanged here. The next source-level proof
must preserve the five known visibility/alias-sensitive bodies while giving
all consumers one complete object and one truthful lifetime/table identity,
or complete approved TU recovery. Mixed/proposed ownership currently prevents
blindly merging the three readers. No pin, alias, preferred-name edit or weaker
check is a substitute. See audit.md for precise source/row/provider boundaries.

Publicationbaa896fe56 audit remains INCONCLUSIVE: index7bd55416c6 versus base
49d862b2073c460233b2072c05ed18cacdc1f49b,2 missing current receipts, first
BoneFXUpdate.cpp. Keep these affected consumers for the next census/image run;
no actual game-runtime, link gain or image ownership claim is made.

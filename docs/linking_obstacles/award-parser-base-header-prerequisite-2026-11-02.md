### Award parser base-header prerequisite (2026-11-02)

AwardSystemManagerParseThingStat.cpp selects the canonical full14-slot
SubsystemInterface at its existing subsystem include position. All seven rows,
nine full code and21 data definitions remain exact, including the176B parse
table and20 relocations. Normal/strict/data/EH checks pass. The old summary
DataRows FAIL was a duplicate-base compile boundary, not evidence that its
initializer needed changing. ThingFactory adoption is a separate next step;
no shared header or private factory view is changed by this prerequisite.
Evidence: reverse/attempt_support/award-base-header-20261102/.

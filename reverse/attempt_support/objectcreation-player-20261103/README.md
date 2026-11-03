# Canonical Player prerequisite for the ObjectCreationUpgrade check merge

The first proposed absorption passed byte/link checks but the commit hook
correctly refused moving a private registered Player view into the seed. That
uncommitted move was restored to its verified prerequisite state. No check or
allowance was changed and no private-view waiver was added.

Both source files now include the canonical Player header before Snapshot's
first inclusion. The donor's private Player definition is removed. Its existing
128-byte mask-copy view reads the same proven+0x13C storage; that field is still
opaque in the canonical header. No guessed canonical field name or layout is
introduced, and the raw memory operation/lifetime is unchanged.

All19 native rows, existing data and EH checks pass normal verification.
Every external code/data definition in both objects is identical to its
pre-adoption control. The joint preview preserves680 linked bytes. The owning
header-adoption tool passes both sources and retires exactly the donor's one
Player queue entry. The seed had no entry to retire.

The source absorption is retried separately through tu_skeleton. The original
rejected composition is not progress; no source-file reduction or census/runtime
clearance is claimed by this prerequisite. Other class/lifetime conflicts remain.

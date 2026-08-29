# Local reverse-engineering fleet

Create two additional writer/build roots with:

    python3 tools/setup_local_fleet.py

The primary checkout and clones under `~/Projects/open-bfme-local-fleet/` have
independent build directories. Each default `tools/next_work.py` invocation
chooses one randomized candidate; no fixed slots or worker configuration are
installed.

Every writer follows `AGENTS.md`: finish one unit, verify it, stage specific
files, commit, pull with rebase, push, then pull again. Writers publish
optimistically to the same branch. If a push loses a race, rebase and retry.
Run long full gates in only one writer at a time.

The fleet manifest is machine-local at
`~/Projects/open-bfme-local-fleet/fleet.json`. It lists only the primary and
writer clones. Re-running setup refreshes configuration without resetting them.

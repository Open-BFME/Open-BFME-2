# Recovery publication retry, 2026-11-04 (codex3)

The first fleet wait handed over all eleven recovered commits, then returned
after sixty minutes with the batch still queued. Retrying `/opt/runner/publish
--now` synchronized the batch with current upstream and refused a new LINK-195
collision before hand-over. Upstream's MixFileInfoBuffer entry now owns that ID.

Move only this batch's AptScriptFunction entry to free LINK-197. Preserve its
existing text and all earlier commits; this is a new correction commit. The
NetGameCommandMsg entry remains LINK-196. The checkout has no source conflicts
or uncommitted saved work, and the original backup ref remains available.
The renamed entry's old path has no active references in tools, hooks,
workflows, shims, Code, build.sh or current source/debt ledgers.

Logs: `build/recovery-20261104-codex3-publish.log` records the first queued wait;
`build/recovery-20261104-codex3-publish-retry.log` records this collision.

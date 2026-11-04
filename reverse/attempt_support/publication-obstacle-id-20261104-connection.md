# Publication ID collision after Connection consolidation

The runner accepted the first eight commits for fleet publication. The final
Connection merge then rebased onto newer upstream work, where LINK-236
already headed the static-initializer obstacle. Its preflight suggested
LINK-237 for the local BuildingBehavior entry. Move only that entry's path
and heading, preserving its status, content and existing evidence.

The same preflight accepted the outgoing retirement verification; its only
refusal was the duplicate obstacle ID. This follow-up does not rewrite any
previously delivered commit. Earlier handoffs retain the old ID history.

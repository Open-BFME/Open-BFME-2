# BuildingBehavior publication ID collision repair

The fleet publisher refused the outgoing batch because LINK-237 also heads
upstream's RefCountClass/RenderObj entry. After `git pull --rebase origin master`,
the register's maximum ID is LINK-239. Move only the local BuildingBehavior
entry to LINK-240, retaining its blocked status and existing technical evidence.

This follow-up preserves all delivered commits. The old publication notes
remain historical evidence. `python3 tools/check_csv.py` passes (99,442 function
rows); the outgoing hook and runner handover supply publication verification.

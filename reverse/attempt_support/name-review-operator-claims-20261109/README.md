# Independent review of operator-held sources

At `569d5371a2`, automatic naming review changed `BFME_CLAIM_OWNER` to
the independent voter before calling `name_lane.cmd_next`. The standard
claim filter then treated the submitting operator's own reserved sources
as foreign and returned an empty review without running the model.

The repair captures the operator's fresh, fully expanded busy-claim snapshot
before changing voting identity. The internal packet picker uses that same
snapshot. Votes still belong to the independent reviewer; source application
still runs as the operator and checks claims again. Foreign file, RVA,
class, persisted and namespace locks remain excluded, including an overlapping
own claim or a foreign claim acquired during the model run. There is no new
CLI claim override or write authority.

Eleven focused regression cases pass. Loading both unchanged HEAD tools in
a separate test process reproduces six failures: all four own-scope forms,
caller application and a mid-review claim change. The other five cases still
refuse foreign claims. The existing reviewer tests, these regressions and
the required gate-exploit suite pass together: **179 passed, 1 skipped**.

Local evidence is under `build/name-review-operator-claims-20261109/`:
`focused.log`, `head_repro.py`, `head-repro.log` and
`reviewer-and-gates.log`. The tests use temporary repositories and fixture
votes; this tooling repair changes no game source, function row or real vote.

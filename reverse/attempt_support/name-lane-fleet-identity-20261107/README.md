# Check a naming seat's worker id before it votes, not after

Measured 2026-11-07 while running two trios through `tools/name_lane.py`. A trio spent its whole
naming effort on a packet and then lost two thirds of it at `validate`, because the three seats
turned out to share one worker identity. The check that would have caught it costs one command.

## What decides who a voter is

`tools/name_agreement.py:worker_identity()` builds the id from the environment, never from
anything the voter passes on the command line:

- `BFME_CLAIM_OWNER` or `BFME_RUN_ID` set, or `CLAUDE_CODE_SESSION_ID` absent -> `claims.owner(root)`,
  which depends on the **worktree** it is given;
- otherwise `w-` + the first 12 hex of `sha256("session:" + CLAUDE_CODE_SESSION_ID)`.

The `model` and `session` columns of `reverse/name_votes.csv` are **labels**. The `worker` column
is the identity, and the tally counts agreement per worker, so three labels prove nothing about
three voters.

## What was measured

- A sub-agent spawned from a coordinating session reported, verbatim:
  `CLAUDE_CODE_SESSION_ID='<the parent's id>'`, `BFME_CLAIM_OWNER=None`, `BFME_RUN_ID=None`,
  `worker_identity=w-0bfb01cf5d54` - which is the coordinator's own id. Freshly spawned and
  resumed sub-agents both behaved this way.
- So on `W3DGadgetTabControlDraw.cpp` the first seat to submit recorded all 47 votes under that
  one id, and the other seats were refused - at `validate` with *"this worker already voted on it
  (under some session label)"*, or at `next` with *"no shared names are left"*, since `next`
  filters out keys the worker has already voted on. Every refused seat had already done the work.
- Three seats earlier the same day did record three distinct ids on
  `W3DGadgetTabControlImageDraw.cpp` (`w-8b75d40078dd`, `w-0c2d8999ffef`, `w-195c4306f7eb`), and
  all 27 keys agreed.

## What separates seats, and the trap in checking it

`AGENTS.md` already says it: *"An orchestrator sets a stable, distinct `BFME_CLAIM_OWNER` per seat
and one claim namespace per fleet."* That is the whole mechanism, and a seat briefed without it
inherits the coordinator's identity, which is what happened above.

A warning about verifying it after the fact: the vote rows record the seat's `model` **label**, not
the `BFME_CLAIM_OWNER` string that produced the identity, so you cannot work backwards from a
recorded hash to the owner that cast it. Guessing the owner string from the label does not
reproduce the hash - trying `BFME_RUN_ID=b2r1` and `BFME_CLAIM_OWNER=b2r1` against every worktree
on this machine reproduced none of the three hashes above, which says only that the label is not
the owner. Check a seat forwards, from its own environment, before it votes.

## The rule

Give each seat its own `BFME_CLAIM_OWNER`, and have it print its identity before it names
anything, continuing only if the ids differ:

    export BFME_CLAIM_OWNER=<something stable and distinct per seat>
    python3 -c "import sys;sys.path.insert(0,'tools');import name_agreement;print(name_agreement.worker_identity('.'))"

Check the printed id against the coordinator's own, and against the `worker` column of
`reverse/name_votes.csv`, so a seat cannot silently reuse an identity another fleet is voting
under.

If two seats print the same id, the packet can take exactly one vote from them, and the rest of
that work is wasted. Stop and get a genuinely separate voter instead.

What not to do: never re-key a seat's `--model` or `--session`, and never hand a seat another
identity, to get past those refusals. The guard exists so one voter cannot supply two of the
matching votes an agreement needs. Every seat that hit it here stopped and said so, which is the
behaviour to keep.

## Where this leaves the packet

`W3DGadgetTabControlDraw.cpp` holds **one** honest proposal for its 47 function keys, recorded
under `w-0bfb01cf5d54` with the label `b2s2`: `get` + state + field + the literal index from the
body (`getEnabledColor3`, `getEnabledBorderColor6`, `getHiliteBorderColor8`, ...), in the style of
the committed sibling `W3DGadgetTabControlImageDraw.cpp`. It needs two more independent workers to
reach agreement. Those can come from the same orchestrator, as long as each seat is given its own
`BFME_CLAIM_OWNER` and checks its identity before naming - which is the point of this note.

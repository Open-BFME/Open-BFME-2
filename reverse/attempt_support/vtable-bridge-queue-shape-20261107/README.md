# The shape of the real link's vtable queue: 4,631 rows, and what actually refuses (2026-11-07)

The link tier is now 1,683 items, and almost all of its mass is one entry: "1693 source
file(s) for 4631 vtable refusal/retirement rows". This is a read-only pass over
`reverse/vtable_bridge_queue.tsv` to say what that mass is before anyone works it. Nothing
was changed.

## The split

- **4,422 rows are `bridged`, every one with the reason `bridge-retirement`.** That is 95%
  of the queue under a single reason. These are the generated vtable bridges AGENTS.md
  names as a headline figure to drive to 0 - scaffolding that lets an image start and is
  retired by a real class emitting its own table. Retiring them is class and header
  adoption, not queue work.
- **209 rows are `refused`**, across seven reasons: `strong-definition` 134,
  `target-not-winning-provider` 33, `ambiguous-table-name` 28, `no-kept-definition` 8,
  `unrowed-target` 5, `ambiguous-target-name` 1.

The refusals are the rows that actually stop the real link, so they are where the 209
matter and the 4,422 do not.

## What refuses them: ICF-folded tables, mostly legitimately

161 of the 209 refused tables carry more than one name at the same address. The
distribution has a long tail: 115 tables with 2 names, 24 with 3, and single tables with
17, 18, 20, 27 and 221.

The temptation is to read that as naming debt to clean up. It is mostly not. Looking at the
tail:

- `??_7SecondaryModuleBase@FXParticleSystem@@6B@` at 0x0081C780 carries **221** names, and
  they are `CategoryModuleInfo<0>`, `<1>`, `<2>` and so on - template specializations whose
  vtables are identical, so retail folded them onto one address. Likewise
  `CategoryModuleClass@$04` with 18.
- `??_7DozerAIUpdate@@6BAIUpdateInterface24@@@` at 0x00852F88 carries 17, among them
  AnimalAIUpdate and AssaultTransportAIUpdate - distinct classes sharing an identical
  secondary interface table.

Those are genuine distinct owners, not aliases of one class. So the generator is not
failing to clean up; it is correctly declining to attribute an owner to a table that
several real classes share. `strong-definition` (median 2 names, the largest group) reads
the same way: a definition already exists, so bridging is refused.

The practical consequence: these refusals are not reducible by retiring names. Each needs
the per-class evidence that says which class's table the address is, exactly as the
`fold-proof=<ledger source>` convention already requires for an ICF fold.

## The same condition blocks class folds

This is worth connecting, because it is the second lane to hit it today.
`reverse/attempt_support/regionturnobserverview-fold-20261107/` records
`rename.py class --fold` refusing because table 0x00C62A20 carried a third name. That is
this condition, and the rule behind it ("T is no ICF fold of distinct classes' tables") is
the same judgement the bridge generator is making.

The difference, and it matters for how each is fixed: that fold's extra two names had **no
rows in `functions.csv` and no contract** - genuinely stale placeholder spellings, which is
why regenerating the derived ledger clears them. The refusals here mostly have real owners
with real rows. A reader should not generalise from that case to this queue.

## A false lead, recorded so nobody repeats it

Every sourced row in the committed queue carries a Windows CI absolute path
(`D:\a\Open-BFME-2\Open-BFME-2\Code\...`) and none resolves in a Linux checkout, which
looks like a bug that would stop the picker attributing ownership. It is not:
`repair_queue._checkout_relative()` normalises exactly these paths to `Code/...`, with a
comment saying so. The picker's 1,693 source files are correct. I checked the caller only
after measuring, and would have published a false finding otherwise.

## Not taken this hour

LINK-626 (13 names left undefined by pin-only destructor bindings) is the other live item
in this tier and is the more valuable repair, but its entry hands both the repair and its
prevention to work already in progress - "handoff to the active deleting-dtor identity
work" and an audit fix "in progress in the Link lane". The four files are unclaimed right
now, which is not the same as unowned, and two seats editing the same destructor identities
would conflict. Left alone deliberately.

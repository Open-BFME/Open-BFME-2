# What the fixed ZH probe actually yields: 53 of 57, and 30 bases corroborated (2026-11-07)

d73d3dde8bd gave the Zero Hour layout probe's `PreRTS.h` attempt an STLport include, after
57 classes failed it on one shared cause. This is the measured result of that fix and what
the recovered evidence is worth. `zh_layouts.json` holds every probe outcome.

## The fix: 53 of 57

Re-probing all 57: **53 now compile, 4 still fail.** The four residual failures each report
a *different* set of error codes - AIPlayer C2143/C2061, SimpleSceneClass C2027/C2227,
SpecialAbilityUpdateModuleData C2143/C2146/C2433, SpecialPowerModuleData C2143 throughout.

That corrects a guess in the previous note, which predicted "another single shared cause"
behind AIPlayer's failure. There is no shared cause: these are four separate problems, one
class each, so there is no further systemic win here - only four individual investigations
with low value apiece.

## What the recovered layouts are worth

The 121 classes this started from record no bases in their contract while their canonical
header declares some. For 53 of them there is now a ZH base clause to compare against that
header:

- **30 agree exactly.** CommandButton and CommandSet over Overridable, DieModule over
  BehaviorModule and DieModuleInterface, DisplayStringManager over SubsystemInterface,
  DrawableModule over Module, FrameDataManager over MemoryPoolObject, and 24 more.
- **12 overlap but differ**, and they differ the same way: ZH carries `MemoryPoolObject`
  ahead of `Snapshot` where the BFME2 header declares only `Snapshot` - AIGroup,
  AttackPriorityInfo, Locomotor, Module, ObjectTypes among them. That is one question to
  settle once, not twelve: did BFME2 drop the MemoryPoolObject base, or is the header
  incomplete?
- **7 have no overlap**, and six of those are the same shape too: ZH names an intermediate
  module base (`UpdateModuleData`, `BodyModuleData`, `BehaviorModuleData`) where the BFME2
  header names the general `ModuleData`. Also one question, not six. The seventh, MapCache,
  is not a real disagreement - ZH gives a full STL map template and the comparison here
  extracted bare identifiers from the header, so template bases are not compared reliably
  by this measurement.
- 4 have a ZH layout that declares no bases at all.

## Why the 30 matter, and why no rule changed

For these classes the contract records no bases, so the header's base clause cannot have
come from the contract - it was authored from something else. ZH agreeing with it is
therefore corroboration from two sources, neither of which is the contract. Those 30 are
the strongest candidates for a reviewed bases correction.

No rule was changed on the strength of this. "Use ZH when it agrees with the header" is
circular in general, because a canonical header normally *is* generated from its contract;
it is only non-circular here because these particular contracts are empty, and a rule
cannot tell the two situations apart. The decision stays with a reviewer, per class, which
is what the evidence above is for.

Also unchanged: the ZH base clause is still gated on a private view declaring exactly those
bases, so none of these 53 contracts decides its bases differently today. The gate earns
its place - ZH probes Team at size 88 against a BFME2 object of 0x13c.

## The MemoryPoolObject question, narrowed but not settled

The 12 partial disagreements all turn on one base, so it is worth what is known about it.

`MemoryPoolObject` exists in BFME2: it is registered, has a contract, and its canonical
header declares a 4-byte polymorphic class - a vptr and a virtual destructor, no data. But
**no mangled row in `reverse/functions.csv` names it, and no contract lists it as a base.**
In ZH it is the memory-pool base of many classes; in BFME2's ledger it appears nowhere.

That suggested a clean test. If a class had MemoryPoolObject at 0 and Snapshot at 4, and
both were polymorphic, retail would store two vptrs, and a vptr at a non-zero offset is
exactly what retail *can* see. Retail records one vptr for these classes, at offset 0 -
AIGroup's constructor at 0x36e4c7 stores table 0x817d00 at 0x0, Locomotor's at 0x1e449a
stores 0x7de888 at 0x0, and nothing else.

**That does not settle it, because Snapshot's own polymorphism is unclear.** Snapshot's
contract records size 4 with zero virtual slots and no retail facts at all. If Snapshot
carries no vtable, then a single vptr store at 0 is equally consistent with
`MemoryPoolObject` at 0 and Snapshot's four data bytes at 4, and with the class's own vptr
at 0. The one-vptr observation is real evidence and it is relevant, but it does not
discriminate between the two shapes on its own.

So the question reduces to settling Snapshot first: does BFME2's Snapshot have a vtable,
and what are its four bytes? Its contract claims size 4 from no recorded evidence, which is
exactly the kind of empty contract measured in
`reverse/attempt_support/class-contract-size-vote-20261106/`. Until Snapshot is settled,
the 12 partials cannot be, and no contract here was changed.

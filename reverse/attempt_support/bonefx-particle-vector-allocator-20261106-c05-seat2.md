> Recovery publication: historical investigation from 5b3df97bce2e. Recovered against `8bb483ac9115`; original commands and results below were not rerun during recovery. All original fleet claims were released. These are prerequisites/attempt evidence, not a completed repair or runtime result.

# BoneFX particle vector allocator trial (2026-11-06, chat05 seat2)

Inspected revision: f15737ff46b. Picker `next_work.py --claim --shard 13/30`
served code-identity debt for BoneFXUpdate::xfer, RVA 0x00487C75 (349B),
Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp. Existing key:
push_back<ParticleSystemID> at 0x002E01C6 resolves to a selected wrong copy.
No lost row or new function was discovered. Prior attempt at re_attempts.log
100735 reports an overflow of172B versus retail179B and no admitted fold pin.

## Target facts and trial

The selected conflicting provider is BoneFXUpdateUpdate.cpp. Its existing six
rows pass ordinary `./build.sh` through the fleet scheduler. Both source files
pass `find_declared_unmatched.py`. Existing NameKeyListHelpersBFME2.cpp has the
real named179B overflow owner at0x00148D00 and49B push_back at0x002E01C6;
ScienceType also has existing matched rows. No new body or alias was added.

Hypothesis: the provider lacks the bfmealloc allocation contract used by the
native exact enum-vector owner. Trial added only `/D_STLP_USE_MALLOC /D_CRTIMP=
/Ireference/shims/bfmealloc` to BoneFXUpdateUpdate.cpp's cl flags. Ordinary
`./build.sh Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdateUpdate.cpp`
through verification_slot.py passed6/6 rows both before and after. Funclet
uw_0078c2a6 was verified through the exact parent EH graph despite renumbering
$L61904 (before) to$L62053 (trial). This is byte preservation only; overflow
extent/relocations and selected consumer closure were NOT established.

## Supported admission boundary

The attempted command was:

```
python3 tools/pin_admission.py --add '?_M_insert_overflow@?$vector@W4ParticleSystemID@@V?$allocator@W4ParticleSystemID@@@_STL@@@_STL@@IAEXPAW4ParticleSystemID@@ABW43@ABU__false_type@2@I_N@Z' 0x00148D00 --notes 'ParticleSystemID enum-vector overflow; fold-proof=Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdateUpdate.cpp'
```

The first invocation omitted the runtime PATH. It refused with nothing written:
existing real NameKeyType name; no ICF proof because the source could not compile
(`wine not found. Install Wine to run MSVC 7.1 on this host.`). It did not prove
that the trial overflow differs from retail.

A retry with the configured VM PATH, BFME_VM_WINEPREFIX and verification scheduler
was rejected before execution by automatic approval review. Exact stated reason:

> The prior admission explicitly found the target RVA already has a real name and requires renaming the owner; retrying the same conflicting pin violates the repository’s one-address/one-identity rule.

No bypass, retry via indirect execution, gate edit, new pin or hatch was made.
The allocator flag trial was restored byte-for-byte from HEAD. The identity
register remains intact. This is a blocked attempt, not a successful repair or
a claim of a broken repository gate. Resolving the admission authorization/tool
boundary and then validating the full recursive fold remains required.

## Unverified scope

No current link preview, strict consumer receipt, identity retirement, batch audit,
real link or runtime smoke was run for this trial. The available index is dated
47fd56b879 and predates the inspected revision. No linked-byte gain, unresolved
count reduction or runtime improvement is claimed. No source-path move occurred.
Claims:0x00487C75 and file:Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdateUpdate.cpp;
release both after recording this blocked attempt. t=30min model=gpt-6.1-sol.

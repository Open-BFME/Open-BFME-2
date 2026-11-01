# GlobalWeatherSystem destructor owner: native interface prerequisite

2026-11-01, base60e005e3d21f1d7fdc47a932b5f2d3e993d4d5c5, GPT-6,
lane R, budget30m, t=10min. The prior goal turn published the WeatherData
constructor. This pass leaves Code and all function rows unchanged. No pin,
hatch, shared-header edit, source move or measured linking credit is added.

## Target facts

Native ctor318588 finishes its +0/+C vptr writes with C0C734/C0C724. Complete
dtor318637 begins with those same two writes. Its scalar deleting wrapper31861B
calls it; the318613 secondary entry subtracts C and forwards to that wrapper.
The table sizes are14 and4 entries, bounded by the next named string datum
C0C76C (GlobalWeatherSystem). Snapshot slot2 reaches the six-byte getter31860D,
which returns that string. This is target evidence for one complete owner,
separate from any donor name or a byte-only guess.

Native tables contain no purecalls. Six entries are concrete weather overrides:

| Table/slot | Native RVA | Existing provider |
|---|---|---|
| primary1 | B3FD0 | shared empty body; weather init identity still needs ownership proof/admission |
| primary9 | 3186A5 | reset@Rva003186A5Owner, Common/Rva003186A5Reset.cpp |
| primary10 | 318768 | rva00318768@Rva00318333, GameNetwork/Rva00318333.cpp |
| Snapshot1 | 3187A0 | secondary-this adjustor in Common/GapForwardersSeat8.cpp, forwarding to3184B8 |
| Snapshot2 | 31860D | name@Rva0031860DNamed, Common/SubsystemNameGetters2.cpp |
| Snapshot3 | 3189AD | rva003189AD@Rva003189ADOwner, Common/System/Rva003189ADXfer.cpp |

Those owners exist. The work is reconciling live class/override identities and
complete views, not matching missing functions or introducing alias pins.

## Private trial and falsified shortcut

candidate.cpp.txt changes only the private destructor candidate: its class
becomes GlobalWeatherSystem and it reuses the existing14-slot subsystem_bfme2
header instead of the one-slot canonical SubsystemInterface header. It creates
no new private base definition. The private Scorer uses exactly the source's
production flags plus that existing include directory, outside build/match.

The complete110-byte destructor is exact1.0, unresolved=false. All eight
existing family/EH byte sequences compare exact under the projected class
names, but the8-byte renamed adjustor has an unresolved primary deleting-helper
reference. This is not full family verification. No pin or wrapper was added.

More importantly, object inspection proves the candidate's two derived tables
agree with the current constructor's two tables but both put __purecall in
all six concrete native slots above. Agreement and body scores cannot justify
landing it. The candidate is deliberately banked as inadmissible interface
work, not a matched source or a normal near-match stash. Full native callback
and getter/transfer reconciliation must precede the placeholder-to-real merge.
The earlier generic class-merge planner limitation remains, but a new merge
mode alone cannot fix this class. Do not spend tooling effort merely to admit
this incomplete candidate.

## Current controls and remaining work

The unchanged two production sources pass normal15/15 body checks. Published
index0d24c60eef predicts the old destructor unit LINKS146 ->146, while the
constructor stays0 with missing GlobalWeatherSystem and WeatherData destructors.
The former LINKS result does not prove its one-slot private derived table is
retail's14-slot table. Native table validation remains an independent obligation.

The fresh WeatherData destructor claim was refused; no edit followed, and its
two partial scope claims were released immediately. GlobalWeather owner/file
claims were confirmed for this private investigation and are released after
publishing this handoff. Both live weather dependencies remain open. A next
pass should claim/reconcile concrete callback providers, preserve their own
whole-parent/EH byte checks, then apply a supported owner-class merge with
both18-entry table relocation sets proved native. Include the old146-byte
provider and transitive users in the ordinary regression audit and next census.

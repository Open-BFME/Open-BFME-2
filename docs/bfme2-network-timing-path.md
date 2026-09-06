# BFME2 network and frame timing path

This note records the BFME2 1.06 evidence recovered while tracing the
Danetta-style timing locations. It describes the retail control flow and the
identities that are still hypotheses. It does not alter network or delay
behavior.

## Verified GameEngine timing helpers

`Code/GameEngine/Source/Common/GameEngineFrameTiming.cpp` now contains two
byte-verified private `GameEngine` members:

| RVA | VA | size | recovered operation |
|---:|---:|---:|---|
| `0x00225D68` | `0x00625D68` | 16 | divide the FPS global at `0x009BA4E8` by the logic-tick global at `0x009BA4E4` and store the derived client-frame counter at `this+0x38` |
| `0x00225D78` | `0x00625D78` | 49 | convert the client-frame period at `this+0x34` and counter at `this+0x38` to SSE floats, divide period by counter, and clamp the ratio to zero through one at `this+0x3C` |

The globals contain `30` FPS and `5` logic ticks per second in the shipped
baseline. The private access decoration is consistent with the BFME1
`GameEngine` frame-pacing helpers; the field offsets and exact bytes are
independently established from BFME2.

The class ownership is now anchored by its vtable as well. The constructor at
VA `0x0062DA70` installs vtable `0x00BE7188`; slot 0 points to the verified
28-byte scalar deleting destructor at RVA `0x00226333`, and slot 10 points to
the larger frame-loop candidate at RVA `0x00225DA9`. The wrapper calls the
complete destructor body at RVA `0x00225B9B`; that body remains a separately
unrecovered dependency, so the pin documents the call target without claiming
its bytes.

## The adjacent frame gate

Ghidra gives a 48-byte boundary at RVA `0x00225D38` (`FUN_00625d38`). Its
instructions are:

```text
mov eax,[0x00DBA4E8]
cdq
idiv dword ptr [0x00DBA4E4]
push esi
push 6
mov esi,eax
pop eax
cmp esi,eax
jge 0x00625D5D
cdq
idiv esi
xor edx,edx
pop esi
cmp dword ptr [ecx+0x34],eax
sete dl
mov al,dl
ret
00625D5D:
xor eax,eax
cmp dword ptr [ecx+0x34],1
pop esi
sete al
ret
```

Every direct callsite first loads the global at `0x00DFE710` into `ECX`, which
is strong evidence that this is a `GameEngine` member. The ten callsites are
at VAs `0x004627A7`, `0x0048E989`, `0x004B599E`, `0x004B7486`,
`0x004EDCEA`, `0x0063C166`, `0x0063C23D`, `0x00675690`, `0x0082F7B4`, and
`0x0089CBE3`. They all consume `AL` as a gate or condition. The semantic
reading is a client-frame boundary test based on the FPS/logic ratio and the
period at `+0x34`, but its exact source shape and name remain unresolved;
no unverified body is committed for it.

## Verified frame-admission helper

RVA `0x00225BA6` (VA `0x00625BA6`) is now reconstructed as
`GameEngine::_bfme_shouldSkipClientFrame`, with a 108-byte exact match. It
checks the network pointer at `0x00DFEA28` and the logic time scale at
`0x00DBA2F8`, queries the network vtable at slot `+0x58`, increments the
client-frame counter at `this+0x38` when the period at `this+0x34` is ahead,
and clamps the headroom limit at `this+0x44` when the network is behind. The
BFME1 helper supplied the structural comparison; the field offsets, branch
direction, and `/O1` code-generation requirement were verified against the
BFME2 bytes.

## Concrete network pacing status (`NetworkInterface` slot `+0x58`)

The BFME2 native network object is anchored by the vtable at VA
`0x00BF6040`. Its constructor at VA `0x0065DB6D` stores that vtable, and the
global at `0x00DFEA28` is allocated as a 0x40-byte object, constructed there,
and initialized through slot `+0x04` at VA `0x0065E4BE`. The relevant vtable
entries are concrete, rather than inferred from the BFME1 layout:

| slot | target VA | observed role |
|---:|---:|---|
| `+0x54` | `0x0065E014` | frame-advance/availability query |
| `+0x58` | `0x0065E163` | frame-pacing status |
| `+0xAC` | `0x0065DCCB` | packet-router predicate |

The 172-byte body at `0x0065E163` gives the exact status calculation. In
pseudocode (with the signed return value preserved):

```text
if (network->state != 1)
    return 1;

if (!network->isPacketRouter())
    return network->connectionManager->frameCeiling
         - TheGameLogic->currentFrame;

now = QueryPerformanceCounter();
network->elapsed += now - network->previousQpc;
network->previousQpc = now;
quantum = network->qpcFrequency / logicFps;
if (network->elapsed < quantum)
    return 0;
if (network->elapsed < 1.5 * quantum)
    return 1;
return 2;
```

The non-router path reads connection-manager offset `+0x1205C`, which is the
latest admitted network frame/ceiling, and subtracts `TheGameLogic+0x40`, the
current logic frame. Consequently its results have a direct frame-headroom
meaning: `0` means exactly at the ceiling, `1`, `2`, `3`, and `4+` mean that
many frames available, and a negative result means logic has run ahead of the
admitted network frame. The caller at `0x00625BA6` uses this signed result as
the client-frame admission gate. The larger loop at `0x0062634F` allows
advancement while status is at most `1` when its period limit is still ahead;
otherwise it allows status through `3` and adjusts the limit. Those thresholds
explain why values above `2` matter for a client but cannot be returned by the
router branch.

The router branch is a time accumulator, not a frame count. The constructor
initializes the QPC fields at `+0x18/+0x1C` (frequency), `+0x20/+0x24`
(previous timestamp), and `+0x28/+0x2C` (elapsed accumulator). With the
shipped globals (`logicFps = 5`, QPC frequency supplied by Windows), return
`0` is less than one logic quantum of accumulated time, `1` is one quantum up
to but below the 1.5-quantum threshold, and `2` is at least 1.5 quanta. The
accumulator is consumed by the companion `+0x54` frame-advance method; the
status method itself only adds the new QPC delta and updates the previous
timestamp. It never produces router statuses `3` or `4+`.

This separates two quantities that are easy to conflate. The desired/current
network frame headroom for a client is the signed
`frameCeiling - currentLogicFrame` value. Router pacing uses elapsed QPC time
against the desired one-logic-frame quantum. Neither is the same field as the
GameEngine adaptive limit described below.

## GameEngine `+0x44` initialization and writers

The GameEngine constructor at VA `0x0062DA70` installs vtable
`0x00BE7188`, initializes `+0x44` to `1.0f`, and leaves the other client timing
fields at their initial zero values. The reset/reinitialization body at VA
`0x00629708` writes the same timing block and sets `+0x44` to
`renderFps / logicFps` (six in the shipped 30/5 configuration). The matched
frame-admission helper at `0x00625BA6` is the only verified live update path:
it raises `+0x44` to the incremented client counter when it is catching up and
lowers it to the client period when network headroom exceeds the admission
threshold. These are the two stores at VAs `0x00625BE9` and `0x00625C09`.

An additional reset-shaped sequence at VA `0x0063048B` writes the same
`+0x34/+0x38/+0x44/+0x48` timing block and computes `renderFps / logicFps`
before storing `+0x44`. The surrounding function has exception/cleanup
continuations and its object pointer has not yet been tied to the
`0x00BE7188` GameEngine vtable by a caller, so this is recorded as a likely
initialization writer rather than a claimed GameEngine method. Other raw
`[object+0x44]` stores in the image belong to unrelated classes or stack
objects; they are not counted as GameEngine writers without the vtable/object
proof.

For the confirmed GameEngine paths, `+0x44` is therefore an adaptive client
admission limit. Its reset target is the render-to-logic FPS ratio; the live
network headroom quantity comes from `NetworkInterface::getFramePacingStatus`
and is read separately through the network vtable.

## Delay-loop candidate

The likely Danetta analogue begins at RVA `0x0022634F` (VA `0x0062634F`).
The body is approximately 354 bytes and is not yet a ledger claim. The
relevant sequence starts at RVA `0x00226434`:

```text
mov eax,[0x00DBA4E8]
cdq
idiv dword ptr [0x00DBA4E4]
mov ecx,eax
cmp ecx,6
jge 0x006264A2
lea eax,[edi-1]
imul eax,ecx
cdq
push 6
pop esi
idiv esi
inc eax
imul eax,eax,6
cdq
idiv ecx
mov esi,eax
inc esi
...
inc dword ptr [ebp+0x34]
...
push eax
call 0x00625A0C
...
push edi
call dword ptr [eax+0x34]
inc edi
cmp edi,esi
jl 0x0062645F
mov ecx,ebp
call 0x00625D78
```

The direct edit analogue to Danetta's division site is RVA `0x0022643A`
(VA `0x0062643A`). The original bytes are retained in the baseline; no
replacement is proposed. The loop computes a per-call upper bound from the
logic/FPS ratio, advances a period at `this+0x34`, emits work through
`0x00625A0C`, advances a subsystem through vtable slot `+0x34`, and updates
the interpolation ratio after the loop. This is the path to inspect before
any future delay or buffering experiment.

Before the loop, the same routine calls through objects at globals
`0x00DFE78C`, `0x00DFEA28`, `0x00DFEF10`, and `0x00DFE77C`. Observed slots are
`+0x54`, `+0xC4`, `+0x40`, `+0xC8`, `+0xAC`, `+0x58`, `+0x34`, `+0x28`, and
`+0xC8` respectively. These are recorded as call-graph leads only; their
class names and network meanings require constructor/vtable evidence.

## BFME1 structural comparison

BFME1 exposes the concepts that make these leads useful: a GameEngine client
frame period/counter/ratio, a network frame-advance query, packet-router
pacing, command-list extraction, and network updates around logic
advancement. The BFME2 bytes above establish the corresponding arithmetic and
the loop's call order, but do not establish that BFME2 has the same class
layout, vtable slots, or admission policy. Future work should identify the
BFME2 objects and trace received commands to their eventual logic-frame
consumption before changing delay behavior.

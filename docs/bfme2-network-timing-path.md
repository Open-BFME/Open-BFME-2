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

The `+0xAC` bridge is now reconstructed as a 23-byte C++ member. It loads the
connection-manager pointer at native-network `+0x0C`, returns zero for a null
manager, and otherwise delegates to the exact 17-byte connection-manager
predicate at VA `0x008CF9CD`. That predicate compares connection-manager
offsets `+0x12028` (local slot) and `+0x1202C` (packet-router slot), returning
one only when they are equal. This is the concrete reason the router branch is
selected: the local connection is the packet router, rather than a generic
“host” guess.

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

## Concrete frame admission and command readiness

The `+0x54` vtable target at RVA `0x0025E014` is now a 335-byte exact C++
reconstruction in
`Code/GameEngine/Source/Common/NetworkInterfaceFrameAdvance.cpp`. In the
client branch it returns the signed difference between the connection-manager
frame ceiling at `+0x1205C` and the current logic frame, then asks the local
frame-ring set whether the next frame's commands are complete. If the counts
are not complete it invokes the network update slot and returns zero. The
router branch uses the QPC accumulator and one-logic-frame quantum; it returns
zero or one and records an overrun when the accumulator exceeds two seconds of
frequency. This exposes the actual admission path without changing its policy.

The command-count gate at RVA `0x004CF799` is a separate 92-byte exact C++
reconstruction in
`Code/GameEngine/Source/Common/ConnectionManagerFrameCommands.cpp`. It walks
the eight frame-data managers at `+0x12104`, skips null or quitting managers,
and sums each manager's command count for the requested frame. It compares that
sum with the local manager's expected frame-command count. The three small
frame-ring accessors used by this body are pinned to their independently
decoded retail bodies at RVAs `0x0058B826`, `0x0058B74B`, and `0x0058B78F`.

The frame-ring reset at RVA `0x0058B666` is now recovered as a 69-byte exact
`FrameDataManager::reset` in
`Code/GameEngine/Source/Common/FrameDataManagerReset.cpp`. It initializes each
`0x14`-byte ring entry, writes an unknown expected-command count (`-1`) for a
local manager, then clears the quit frame and quitting flag. The ring length is
read from the retail global at `0x00DD2DB8`; the entry helpers are pinned to
their independently decoded bodies at `0x005DA4F9` and `0x0009070B`.

The connection-manager body at RVA `0x004CF032` is also a verified 81-byte
`BFMEConnectionManager::init` in
`Code/GameEngine/Source/Common/ConnectionManagerInit.cpp`. It calls that reset
for each non-null frame-data manager, clears `frameCeiling` at `+0x1205C`,
resets the eight per-player latest/state/flag/count fields, and clears the
initialized byte. Its address is vtable `0x00C601C0` slot `+0x08`, anchoring
the identity and confirming the `0x008CF056` writer as initialization code.

The companion router-stall target at RVA `0x004CFBF9` is also identified by the
direct call from `+0x54`: it first requires local slot == packet-router slot,
then scans eight open peers and tests each latest-frame value against the
current logic frame minus startup/configured run-ahead slack. Its target body
and the active-player predicate are recorded as call-graph dependencies for a
follow-up conversion; no delay or buffering behavior has been changed here.

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

## `frameCeiling` writer inventory

The requested field is `connectionManager + 0x1205C`. A full `.text` scan found
six retail stores to that displacement. The table records the surrounding
control-flow evidence; it does not claim an identity where the containing
exception region has not yet been reconstructed.

| store VA | store form | verified context and likely role |
|---:|---|---|
| `0x008CF056` | `mov [esi+0x1205C], ebx` | Exact 81-byte `BFMEConnectionManager::init` at RVA `0x004CF032`; vtable `0x00C601C0` slot `+0x08`. It clears the ceiling while resetting the eight frame-data managers and per-player arrays/flags. |
| `0x008D07C8` | `mov [esi+0x1205C], ebx` | Initialization/exception region; also initializes local and router slots, latest-frame/state arrays, and frame-data-related flags. The complete outer boundary is still unclaimed. |
| `0x008D0BB8` | `mov [esi+0x1205C], eax` | Frame-info publisher region beginning at VA `0x008D0AA9`; builds a frame-info record, totals frame-manager commands, broadcasts it, and when local slot == router slot publishes the record's frame as the shared ceiling. |
| `0x008D254E` | `mov [esi+0x1205C], ebx` | Reset/cleanup region; resets slots, ceiling, per-player latest/state arrays, and releases frame-data objects. The outer EH body remains unclaimed. |
| `0x008D27A8` | `mov [esi+0x1205C], ebx` | Constructor/reset-shaped region beginning near VA `0x008D274B`; clears the connection-manager timing block and initializes its frame-data state. |
| `0x008D34B4` | `mov [edi+0x1205C], eax` | Large incoming command/event-processing body beginning at RVA `0x004D316A`; after a network update and local/router-slot check, advances `TheGameLogic+0x40` and publishes `currentFrame + 1` as the ceiling. This is the strongest delayed-command/router writer lead. |

The first and third rows are the clearest reset and frame-info publication
paths. The final row is a concrete received-command path and should be traced
through its message type and eventual frame-ring consumption before any future
multiplayer delay experiment. The remaining three stores are initialization
or cleanup writers, not evidence that the ceiling is advanced during normal
simulation.

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

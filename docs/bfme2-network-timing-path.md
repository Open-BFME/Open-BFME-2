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
| `0x00225D68` | `0x00625D68` | 16 | divide the FPS global at `0x009BA4E8` by the logic-tick global at `0x009BA4E4` and store the period at `this+0x38` |
| `0x00225D78` | `0x00625D78` | 49 | convert the period and client-frame counter at `this+0x34` to SSE floats, divide counter by period, and clamp the ratio to zero through one at `this+0x3C` |

The globals contain `30` FPS and `5` logic ticks per second in the shipped
baseline. The private access decoration is consistent with the BFME1
`GameEngine` frame-pacing helpers; the field offsets and exact bytes are
independently established from BFME2.

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
counter at `+0x34`, but its exact source shape and name remain unresolved;
no unverified body is committed for it.

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
logic/FPS ratio, advances a counter at `this+0x34`, emits work through
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

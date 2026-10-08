# GameWindowManager mouse-event reference repair

Target: `0x002C1FD5..0x002C2533`, 1374 bytes. The served source was
`Code/GameEngine/Source/GameClient/GUI/GameWindowManager.cpp`; all 2598 lines
were inspected. Its other emitted definitions produced zero body placements
and zero pins with the normal placement tool. The original mouse handler
emitted 1550 bytes with three unresolved helpers and incompatible native
layout, virtual-slot and string-construction accesses.

The standalone bank uses the readable Zero Hour body as its semantic guide,
also retained at verified BFME1 revision
`34f59164f6d1efd413c5fd37f4894ec834c3c0fe`. Independent WB function
`0x00EA1150` has callgraph score 5.0; its name is not asserted from a string.
Native boundaries and the recovered neighboring window-manager and window
providers support the subsystem/receiver identity.

Retail-supported adaptations:

- Manager fields at 0x0C, 0x18, 0x1C, 0x24, 0x28, 0x2C and layer 0x3C;
  input-message slot 0xEC, hidden query 0xDC, lone-window setter 0xD0.
- Window status 0x08, size 0x0C, region 0x14, instance 0x30, layer 0x1F4,
  next 0x1F8 and parent 0x200. Tooltip query/callback use slots 0x24/0x10.
- A single native top-level search filters hidden windows and layer, selecting
  the first above window, otherwise first normal, otherwise first below.
- The grabbed-window switch includes mouse-position handling absent in ZH.
- Existing target providers replace unresolved donor helper spellings;
  canonical UnicodeString reproduces the StringBase wide copy constructor.
- Display width/height slots are 0x40/0x44.

The best complete trial emits exactly 1374 bytes, resolves every direct call,
and differs only in six arithmetic instructions at `0x002C221D..0x002C222D`.
Retail loads grab width to EAX before the new origin to ECX; the compiler
loads the origin first, then width, and chooses the opposite sum destination.
The following height loads/store interleave accordingly. All other code,
branches, offsets and resolved call displacements agree.

Bounded trials covered commuted sums, staged/compound coordinate copies,
reversed axes, nested assignment, equivalent subtraction, pointer expressions,
ordinary force-inlined helpers, G6/G7, O1/O2-size, SSE, speed preference,
inline suppression, precise floating point and disabled global optimization.
None improved the best body. No nonmatching reconstruction was left in Code,
no new pins or shared headers were introduced, and no byte progress is claimed.

Reproduce from the standalone bank with the normal mismatch tool. Detailed
local outputs are ignored `build/window-mouse-*-diff.txt`; the bank includes
its flags, complete declarations and body rather than depending on scratch
headers.

Publication rebase: upstream independently banked the same 1374-byte body with 1364 positions exact (score 0.9927227074). Retain that existing bank rather than replacing it with this session's equivalent 0.99 attempt. Both investigations locate the remaining clipping-load/register scheduling difference at 0x002C221D..0x002C2230. These notes preserve this session's independent full-file review and bounded trial evidence.

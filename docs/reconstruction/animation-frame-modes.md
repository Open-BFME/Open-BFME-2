# BFME2 frame calculation and rendering closure

Compute_Current_Frame is738 executable bytes at1A5020. Its six-entry jump table
is24 bytes at1A5304. Two alignment bytes separate code and table; four further
CC bytes precede Single_Anim_Progress at1A5320. None of that data/alignment is
credited. Every local table label and all five float payloads were checked.
The sync counter DEC3CC is independently established by WW3D::Sync117490.

The native mode map is1 loop,2 once,3 ping-pong,4 clamp-to-target,5 backward
loop,6 backward once. The descriptive clamp-to-target name is local to this
reconstruction. With positive direction, mode4 clamps a frame above its target;
with nonpositive direction, it clamps a frame below its target. Equal values
remain unchanged. The older source had no mode4 and numbered backwards4/5.
These correct enum values are scoped to the frame calculation rather than
changing unverified users of the older shared enum.

The field block is motion mode100, animation pointer104, frame108, target10C,
animation mode110, last sync114, direction118 and rate multiplier11C. The
inherited object/hierarchy prefix occupies100 bytes in hexadecimal. Its internal
fields are deliberately opaque in this out-of-line declaration, not invented
padding or a claim of new ownership behavior. Complete declared size is120 hex.

A separate agent verified this field block against assignment261 at1A5570 and
independently decoded all six cases. A second agent audited the HAnim interface:
concrete table BD5D88 is installed at object+0 by constructor18F123 and
destructor190F2D; paired Hashable table BD5D80 goes to+8. Slot5 at+14 calls
A6D730 (integer field44); slot6 at+18 calls58F180 (float field50). Slot7's held
Get_Total_Time at58F190 divides exactly those fields. Load_W3D18FEC7 recognizes
chunk281 and reads the44-byte W3dCompressedAnimHeaderStruct. Its NumFrames24
and uint16 FrameRate28 are stored to object44 and50 at18FFF5/18FFF8, independently
establishing the two getter roles. Unused slot3 is a DWORD getter of unknown
meaning; Get_HName belongs to slot4. The declarations preserve that distinction.

Single_Anim_Progress is51 bytes. It updates frame/time and invalidates hierarchy;
retail does not overwrite the target frame with the obsolete sound-triggering
previous-frame bookkeeping. Animation Render is83 bytes and HLOD Render is293.
Their primary tables BD6D10 and BD6780 independently confirm both slot12
identities. Together these four bodies recover1165 executable bytes and preserve
all95 previously matched bodies in the animation and HLOD source files.

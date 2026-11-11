# Texture predicate at RVA 0x00130FCE

Retail table VA `0x00C7C584`, installed by the rowed
`GenBase009EB7D0` constructor at `0x0061ED40`, names this body in
zero-based slot 10. The virtual caller at `0x0061EDA0` tests AL.
The two texture overrides at `0x00131CF2` and `0x00151415` tail-jump
here after checking their pointer at +0x14. The existing canonical
declaration is `virtual bool vslot10()`.

The isolated VC7.1 experiment defined that member with the existing
`0x0061EEC0` call on the same receiver and
`return (m_04 & 0xff0000) == 0x30000;`. Both /O2 and /O1 emitted all
28 retail bytes after resolving the call at displacement offset 4.
The prepared caller view derives from `GenBase009EB7D0` and uses the
qualified call `GenBase009EB7D0::vslot10()`. With the source's inherited
/O1 /arch:SSE /G7 flags both 21-byte bodies match after resolving their
sole REL32 at offset 17 to `0x00130FCE`. The /O2 caller control emits
22 bytes and moves that operand to offset 18.

`rename.py function --to-class GenBase009EB7D0 --dry-run` refuses the
transition from the donor's `?bfmeGoURB@BfmeThingURB@@QAEHXZ` to
`?vslot10@GenBase009EB7D0@@UAE_NXZ` before building. It treats the
int-to-bool return type change as unsupported. The old provider,
consumer bodies and alias pin remain in place. A supported respell
needs to verify the native slot, compiled installer and both callers
together before retiring the alias pin.

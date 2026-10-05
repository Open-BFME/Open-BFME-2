// ?rva004CA6F3@AnimationSoundTree@@QAEXAAPAUAnimationSoundTreeNode@@PBX@Z
// partial score=0.9 date=2026-10-05
// ?rva004CA6F3@AnimationSoundTree@@QAEXAAPAUAnimationSoundTreeNode@@PBX@Z
// partial score=0.9 date=2026-10-05
// cl: /O1 /Oy- /DNDEBUG /MD /EHsc
// stlport
// ?rva004CA6F3@AnimationSoundTree@@QAEXAAPAUAnimationSoundTreeNode@@PBX@Z
// retail 0x004CA6F3, 26 bytes:
//   push ebp / mov ebp,esp / push [ebp+0xc] / lea eax,[ebp+0xc] / push eax
//   call 0x4ca68b / mov ecx,[eax] / mov eax,[ebp+8] / mov [eax],ecx
//   pop ebp / ret 8
//
// LEVER FOUND THIS SESSION, and it is the real one: MSVC 7.1 /Oy (bare) OMITS
// frame pointers; /Oy- KEEPS them. The backslash-free reading of the flag is the
// opposite of the intuitive one, and the previous row's "0.88 with no source
// form found" was measuring /O1 without it. A/B on the identical body:
//   /O1            25B / 8 insns, 8 diffs   no frame, no `ret 8`
//   /O1 /Oy-       26B / 11 insns, 4 diffs  frame + `ret 8` correct
// Both the prolog (push ebp / mov ebp,esp / pop ebp) and the callee-cleanup
// `ret 8` appear only with /Oy-, taking this from 8 to 11 matching instructions.
// This is a general lever, not specific to this body: it is what fixes frame
// pointer presence generally, and it helps when retail HAS a frame.
//
// What still differs is the final 3 moves, which are MIRRORED:
//   ours    8b00  mov eax,[eax]        value into eax
//           8b4d08 mov ecx,[ebp+8]      dest  into ecx
//           8901  mov [ecx],eax
//   retail  8b08  mov ecx,[eax]        value into ecx
//           8b4508 mov eax,[ebp+8]     dest  into eax
//           8908  mov [eax],ecx
// Both are the same mistake: /O1 loads the STORE DESTINATION before the VALUE,
// so the value is forced into the register that is about to die.
//
// Measured this session and all rejected, none closing it:
//   * /O2 has retail's ORDER (value load first, destination second) but elides
//     the frame: 27B/12 insns, 9 diffs.
//   * /O2 /Oy- keeps the frame and has the right order: 28B/12 insns, still 9
//     diffs, and the value lands in edx rather than ecx.
//   * a VOLATILE key slot is the one thing that puts the value in ecx -- it
//     breaks the destination-first fold of the whole assignment. At /O2 that
//     yields `mov ecx,[eax]` exactly as retail, but the volatile also forces a
//     `mov [esp+0x10],eax` spill and drops the frame: 32B/14 insns.
//   * forceinline helpers taking the destination and the value as ARGUMENTS
//     (the natural way to make the destination live before the value is read) do
//     not help: at /O1 and /O2 alike the bodies are ICF-folded identical, and
//     the folded shape still loads the destination first.
//   * naming the destination address, the value, both, a second indirection, a
//     plain-pointer destination parameter, and an early return: all ICF-fold to
//     the same body.
//
// The reason is that retail's pair needs the destination in eax WHILE the value
// comes out of the call in eax. MSVC will not hold a by-reference parameter in
// eax across the callee, and both operands competing for that register is the
// whole 3-move difference. That is a register-allocation constraint, not a
// source-shape problem, so no spelling of `dest = tmp[0]` closes it.
//
// Evidence: callee rowed ?rva004CA68B@AnimationSoundTree@@QAEPAPAUAnimationSoundTreeNode@@PAPAU2@PBX@Z
// at 0x004CA68B (74B); the wrapper reuses the by-value key slot as the callee's
// out parameter, which is retail's `lea eax,[ebp+0xc]` / `push eax` pair.
struct AnimationSoundTreeNode
{
	int m_color;
	AnimationSoundTreeNode *m_parent;
	AnimationSoundTreeNode *m_left;
	AnimationSoundTreeNode *m_right;
};

class AnimationSoundTree
{
public:
	AnimationSoundTreeNode **rva004CA68B(AnimationSoundTreeNode **out, void const *v);
	void rva004CA6F3(AnimationSoundTreeNode *&dest, void const *v);
};

// ?rva004CA6F3@AnimationSoundTree@@QAEXAAPAUAnimationSoundTreeNode@@PBX@Z present-unmatched
void AnimationSoundTree::rva004CA6F3(AnimationSoundTreeNode *&dest, void const *v)
{
	AnimationSoundTreeNode **tmp = this->rva004CA68B((AnimationSoundTreeNode **)&v, v);
	dest = tmp[0];
}

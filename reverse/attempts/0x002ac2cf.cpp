// ?rva002AC2CF@Rva002AC2CFTarget@@QAEXHHH@Z
// partial score=0.97 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
// ?rva002AC2CF@Rva002AC2CFTarget@@QAEXHHH@Z @0x002AC2CF 113B
//
// Two-segment copy through memcpy with an empty-string fallback. The retail
// body splits one copy across this object's own buffer and a second, linked
// segment, and the interesting part is that both offsets live in the caller's
// stack slots and are updated in place rather than in locals:
//
//   mov eax,[ebx+4]      m_len, kept to [ebp-4] as `len`
//   mov edi,[ebp+0xc]    a1 -- this is the RUNNING offset, reused as such
//   cmp edi,eax / jge    if the running offset is already at the end, skip
//   mov esi,[ebp+0x10]   a2 -- the remaining count, also the caller's slot
//   lea ecx,[edi+esi] / cmp ecx,eax
//   mov esi,eax / sub esi,edi   clamp the first chunk to the remaining length
//   push esi / add eax,edi / push eax / push [ebp+8]   memcpy(dst, buf+off, chunk)
//   sub [ebp+0x10],esi   the count argument is decremented in place
//   cmp [ebp+0x10],0 / jle
//   add [ebp+8],esi      the destination argument is advanced in place
//   add edi,esi          and the running offset too
// then, unconditionally:
//   mov ebx,[ebx+8] / mov ebx,[ebx]     the second segment, through a pointer
//   sub edi,eax        the second segment's offset within its own buffer
//   test ebx,ebx / lea eax,[ebx+8] / mov eax,0xbbac1c   empty-string fallback
//   push [ebp+0x10] / add eax,edi / push eax / push [ebp+8]   memcpy again
//
// The two caller-slot updates are what keep `a1` and `a2` out of registers:
// they are memory locations MSVC must write, so the values are reloaded on
// every use instead of held across the memcpy calls. The `esi`/`edi` and
// `eax`/`ecx` mirror, and the clamped-chunk form
// `esi = (a1 + a2 > len) ? len - a1 : a2`, are read straight off the
// disassembly above. Both memcpy calls go to the rowed ji_006291a8.
typedef int Int;

extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int n);
extern const char g_Rva0107301CEmptyString[];

class Rva002AC2CFTarget
{
public:
	void rva002AC2CF(Int dst, Int off, Int count);
private:
	char *m_buf;		// +0x00
	Int m_len;			// +0x04
	char **m_second;	// +0x08
};

// ?rva002AC2CF@Rva002AC2CFTarget@@QAEXHHH@Z
void Rva002AC2CFTarget::rva002AC2CF(Int dst, Int off, Int count)
{
	// Retail's prologue is `push esi / push edi / mov ebx,ecx / mov eax,[ebx+4]
	// / mov edi,[ebp+0xc]`: `this` in ebx, the running offset in edi, both
	// callee-saved and both saved before the first use. `len` takes the
	// [ebp-4] home retail gives it; `this` and `off` stay in callee-saved
	// registers across the first block. Reading through a named copy of `off`
	// instead makes that copy addressable, and MSVC then spills it back to
	// [ebp+0xc] and re-pushes esi, costing 7 bytes.
	Int len;
	// The named copy inverts the register pair, and it must be the ONLY copy:
	// writing back to the parameter adds `mov [ebp+0xc],edi` and a second
	// `push esi` (+7 bytes), and a reference re-latches MSVC onto the mirror
	// allocation. The second block reads `self_off` directly, so the update
	// never leaves the register.
	Int self_off = off;
	Rva002AC2CFTarget *self = this;
	if (self_off < (len = self->m_len))
	{
		Int chunk = count;
		if (self_off + chunk > len)
			chunk = len - self_off;
		memcpy((void *)dst, self->m_buf + self_off, (unsigned int)chunk);
		count -= chunk;
		if (count > 0)
		{
			dst += chunk;
			self_off += chunk;
		}
	}
	char *second = *self->m_second;
	char *base = second ? second + 8 : (char *)g_Rva0107301CEmptyString;
	memcpy((void *)dst, base + (self_off - len), (unsigned int)count);
}

// ?rva006e6a30@@QAEXHPAX@Z
// partial score=0.78 date=2026-10-05
// cl: /O2 /DNDEBUG /MD
// ?rva006e6a30@@QAEXHPAX@Z @ 0x006E6A30 209B
//
// Apt action-initialization dispatcher. The work order's near file
// Rva008A2C80RefDrop.cpp is a different subsystem (0x008A2C80 range) and only
// tells me this area uses /DNDEBUG /MD /EHsc; the real neighbourhood here is
// the 0x006E3230 / AptCIH cluster, and 0x006E0CB0 (rowed
// ?rva006E0CB0@AptCIH@@QBEPBV1@Z) plus the 0x0070xxxx interpreter debug frames
// 0x00700090 / 0x007002C0 / 0x00706950 that this body calls with ecx loaded
// from the interpreter global at VA 0x00E182E0.
//
// Structure read off the retail bytes:
//  * `sub esp, 0x14` frames five dwords; the +0x04 slot holds the `this` object
//    saved across the whole body.
//  * A linear scan walks [this+4]->count elements, each 4 bytes, comparing
//    `dword [elem] == 8` and `dword [elem+4] == arg2`. That pair is the
//    AptValue type tag (8) plus its integer payload -- the same test the
//    sibling 0x006E46A0 performs at 0x006E4705 with `cmp dword [eax], 8`.
//  * A miss returns immediately (ret 8), so this is a void two-argument
//    method.
//  * On a hit the body calls the unrowed 0x006E46A0 (which walks the *outer*
//    registry at this+0x28/+0x2C and repeats the same tag-8 scan), then builds
//    a 0x14-byte interpreter debug-info block on the stack: {arg2, 0, name
//    pointer, 0x100000} where the name pointer is VA 0x00CEBD54, which reads
//    "AptImported_Init_Actions" from the image.
//  * It then calls 0x006E0CB0 (rowed AptCIH paren accessor) and 0x006CD650
//    (rowed AptValueAnimationInst) on arg2, pushes the result, and calls the
//    interpreter entry 0x007002C0 with the tag-8 element payload and -1.
//  * Finally 0x00706950 pops the debug frame and the found element's integer
//    is negated and stored back at [esi+4].
//
// 0x006E46A0 is an unrowed retail body reached only from here; it is pinned
// address-derived below. Its identity is not proven.

// Interpreter debug-info block, the 0x14 bytes staged at [esp + 0x14].
// Offsets are proven by the four stores at 0x006E6A87 / 0x006E6A8B /
// 0x006E6A93 / 0x006E6A9B.
struct Rva00700090Info
{
	int m_arg;                 // +0x00, the second argument
	int m_zero;                // +0x04
	const char *m_name;        // +0x08, "AptImported_Init_Actions"
	int m_flags;               // +0x0C, 0x100000
	int m_pad;                 // +0x10
};

// The AptValue element the scan compares: tag dword then one payload dword.
struct AptValueTagged
{
	int m_tag;                 // 8 is the integer tag the scan matches
	int m_value;
};

// Outer registry the scan walks: a count at +0x00 and a pointer array at
// +0x04. Retail does `mov eax, [edx + 4]` then `mov esi, [eax]`, so the
// array holds pointers to elements.
struct AptValueRegistry
{
	int m_count;
	AptValueTagged **m_elements;
};

// The object this method hangs off: the registry at +0x04, and the outer
// registry pair at +0x28 (count) / +0x2C (pointer) that 0x006E46A0 walks.
class Rva006E6A30This
{
public:
	void rva006e6a30(int tag, void *payload);

	// Pinned here, address-derived: thiscall, one stack arg, void. The body is
	// 400+ bytes and repeats this function's registry walk, reaching the same
	// tag-8 test at 0x006E4705. Unrowed; identity not proven.
	void rva006e46a0(void *payload);

private:
	unsigned char m_pad0[4];
	AptValueRegistry *m_registry;               // +0x04
	unsigned char m_pad1[0x28 - 0x08];
	int m_outerCount;                           // +0x28
	unsigned char m_pad2[4];
	void *m_outerElements;                      // +0x2C
};

// Rowed: ?rva006E0CB0@AptCIH@@QBEPBV1@Z at 0x006E0CB0.
class AptCIH
{
public:
	void *rva006E0CB0() const;
};

// Rowed: ?rva006CD650@Rva006CD650@@QAEPAXXZ at 0x006CD650.
class Rva006CD650
{
public:
	void *rva006cd650(void *arg);
};

// Rowed/pinned interpreter debug frames, all thiscall off the interpreter
// global at VA 0x00E182E0.
class AptActionInterpreter
{
public:
	void *rva00700090(Rva00700090Info *info);
	void rva007002C0(int index, void *value, int arg);
	void rva00706950(void *frame, Rva00700090Info *info);
};

extern AptActionInterpreter g_aptActionInterpreterAtE182E0;	// VA 0x00E182E0

void Rva006E6A30This::rva006e6a30(int tag, void *payload)
{
	Rva006E6A30This *self = this;
	AptValueRegistry *registry = self->m_registry;
	int count = registry->m_count;
	if (count <= 0)
		return;
	AptValueTagged **elements = registry->m_elements;
	AptValueTagged *found = 0;
	int i = 0;
	do {
		AptValueTagged *element = elements[i];
		if (element->m_tag == 8 && element->m_value == (int)payload) {
			found = element;
			break;
		}
		++i;
	} while (i < count);
	if (found == 0)
		return;
	self->rva006e46a0(payload);
	Rva00700090Info info;
	info.m_arg = (int)payload;
	info.m_zero = 0;
	info.m_name = "AptImported_Init_Actions";
	info.m_flags = 0x100000;
	void *frame = g_aptActionInterpreterAtE182E0.rva00700090(&info);
	void *extra = 0;
	if (payload != 0) {
		((AptCIH *)payload)->rva006E0CB0();
		extra = ((Rva006CD650 *)payload)->rva006cd650(0);
	}
	g_aptActionInterpreterAtE182E0.rva007002C0(found->m_value, payload, -1);
	g_aptActionInterpreterAtE182E0.rva00706950(frame, &info);
	(void)extra;
	found->m_value = -found->m_value;
}

# HLOD animation ownership closure

BFME2's HTree has no W3DMPO base. Its copy constructor at1662A0 is285 bytes:
name[16], pivot count+10, pivot pointer+14, scale+18, an owned sequence+1C,
and three trailing words at+28/+2C/+30. The copy allocates count*88 bytes,
copies each pivot, and rebases its parent pointer+10 through the parent's
index+4C. The destructor at1667E0 is26 bytes: release hierarchy storage through
166510, then free the owned pointer+1C through430830. These independently
decoded bodies establish the two callable identities. They are pins only and
add no claimed bytes. A scoped declaration retains neutral names for fields
whose full behavior is still unknown. The actual assignment allocates52 bytes.

Animatable assignment at1A5570 is261 bytes followed by11 alignment bytes.
The older source's ModeInterp.PrevFrame0/1 compatibility writes overwrite the
union's playback direction and rate. Retail does not perform those writes.
Removing them preserves the two1.0 values. All10 previously matched animobj
routines remain exact with the scoped RenderObj and HTree declarations.

The assignment's named float is1.0f atBBB8D8. Its synchronization counter
DEC3CC is independently established by the held WW3D::Sync at117490, which
moves the old counter to PreviousSyncTime atDEC3D0 before storing its argument.
The complete exception graph has four nodes: handler768EEB(10), metadata90DDD0
(28), unwind map90DDC8(8), and allocation cleanup768EE0(11). The handler ends
at the named msvcr71.dll __CxxFrameHandler import; cleanup calls the held global
operator delete at42FD60. No exception metadata or alignment is credited.

Integration also retires a17-byte generated alias at210C91. It labeled an
anonymous float-store body as RenderObj::_bfme_ro_set_98. The actual base
constructor initializes field98 with integer -1; the actual virtual interface
uses an indexed-factor setter instead. Matching this short code shape did not
establish the claimed object identity. No replacement identity or bytes are
claimed for that address.

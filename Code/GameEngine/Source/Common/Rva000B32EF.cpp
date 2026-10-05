// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// Draw decal helpers in the 0xB32 table family (retail 0xB3198/0xB32C2/0xB32D7/0xB32EF).
// Dedicated TU with TU-scoped views only; no shared-header edits.
//
// Identity (target evidence, not bytes alone):
// - Code-pointer tables at 0x7C6960 et al: 7 parallel Draw vtables share
//   consecutive slots [0xB3266,0xB3271,0xB32C2,0xB32D7,0xB32EF,0xB330C,0xB333D,
//   0xB6FFE]. Matched neighbors prove the subsystem: 0xB3271 RadiusDecalTemplate
//   at +0x228, 0xB333D +0x218.clear (RadiusDecal), 0xB6FFE W3DModelDraw
//   setFullyObscuredByShroud. These three bodies occupy slots in every table,
//   same Draw family (vtable 0x00BCBC40#24/26/28/29/34 per forwarder rows).
// - Layout: +0x1D0 and +0x218 are both RadiusDecal value members
//   (template+0/shadow+4/empty+8/extra+0x0C, size 0x10 per BFME1 RadiusDecal
//   donor + rowed clear/setPosition). Proven: 0xB333D +0x218.clear,
//   0xB3266 +0x1D0.clear, 0xB318D +0x1D0.frameOpacity, 0xB3198 calls both
//   RadiusDecal setters on +0x1D0. Shadows at +0x1D4 (+0x1D0+4) and +0x21C
//   (+0x218+4) per same layout; 0xB31B9 tail-jumps Shadow setter on +0x1D4.
// - Provenance: BFME1 RadiusDecal.cpp (setPosition copies Coord to shadow+0x08),
//   RadiusDecalTemplate_createRadiusDecal.cpp (Shadow::setColor/setAngle shapes,
//   shadow+0x20 angle, shadow+0x08 position), ZH Shadow.h (setColor/setOpacity
//   branching, exactly the rowed 0x330995/0x3308F6 bodies). Providers reused:
//   0x330DFD setPosition, 0x330E15 second Coord setter, 0x330995 Shadow color.
//   Reference inspected for shape only; retail shapes modeled directly.
// - Names: honest address-derived Rva000B32*; Draw/Shadow semantic names beyond
//   rowed providers remain unclaimed.
//
// ?rva000B32EF@Rva000B32EF@@QAEXPAH@Z, retail 0x000B32EF, 29 bytes:
//   mov eax,[esp+4]; mov eax,[eax]; test; je; mov ecx,[ecx+0x21C]; test; je;
//   push eax; call 0x330995; ret 4. Forwards *color to Shadow setter on
//   +0x218 decal's shadow. Arg is int* (pointed-to type beyond int unproven).
// ?rva000B32C2@Rva000B32EF@@QAEXPBVCoord3D@@@Z, retail 0x000B32C2, 21 bytes:
//   cmp [esp+4],0; je; add ecx,0x218; jmp 0x330DFD; ret 4. Null-checked
//   forwarder of +0x218 RadiusDecal::setPosition.
// ?rva000B3198@Rva000B32EF@@QAEXABVCoord3D@@0@Z, retail 0x000B3198, 33 bytes:
//   push esi; push [esp+8]; lea esi,[ecx+0x1D0]; mov ecx,esi; call 0x330DFD;
//   push [esp+0xC]; mov ecx,esi; call 0x330E15; pop esi; ret 8. Double setter
//   on +0x1D0 RadiusDecal (setPosition then second Coord slot).

typedef int Int;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Shadow
{
public:
	void rva00330995(Int color);
	char m_pad00[0x20];
	Real m_angle; // +0x20 (BFME1 Shadow m_localAngle per createRadiusDecal donor)
};

class RadiusDecal
{
public:
	void setPosition(const Coord3D &pos);
	void Rva00330E15(const Coord3D &pos);
	const void *m_template; // +0x00
	Shadow *m_shadow; // +0x04
	bool m_empty; // +0x08
	char m_pad09[3];
	Int m_extra; // +0x0C
};

class Rva000B32EF
{
public:
	void rva000B32EF(Int *color);
	void rva000B32C2(const Coord3D *pos);
	void rva000B32D7(Real v);
	void rva000B3198(const Coord3D &a, const Coord3D &b);
private:
	char m_pad00[0x1D0];
	RadiusDecal m_decal1D0; // +0x1D0
	char m_pad1E0[0x218 - 0x1D0 - 0x10];
	RadiusDecal m_decal218; // +0x218
};

void Rva000B32EF::rva000B32EF(Int *color)
{
	Int v = *color;
	if (!v)
		return;
	Shadow *s = m_decal218.m_shadow;
	if (!s)
		return;
	s->rva00330995(v);
}

void Rva000B32EF::rva000B32C2(const Coord3D *pos)
{
	if (!pos)
		return;
	m_decal218.setPosition(*pos);
}

void Rva000B32EF::rva000B32D7(Real v)
{
	Shadow *s = m_decal218.m_shadow;
	if (!s)
		return;
	s->m_angle = v;
}

void Rva000B32EF::rva000B3198(const Coord3D &a, const Coord3D &b)
{
	m_decal1D0.setPosition(a);
	m_decal1D0.Rva00330E15(b);
}

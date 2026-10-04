// cl: -DNDEBUG -MD -EHsc /Os -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient
//
// ??0PlaneClass@@QAE@ABVVector3@@M@Z
// retail 0x00376D29, 32 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngineDevice/Source/W3DDevice/GameClient/
// BaseHeightMap_getMaximumVisibleBox.cpp (reference/open-bfme-1 @ 6d943426),
// trimmed to this one body; the donor's other definition is omitted.
//
//   00376D29  8b c1              mov eax, ecx          ; return this
//   00376D2B  8b 4c 24 04        mov ecx, [esp+4]      ; the normal
//   00376D2F  8b 11              mov edx, [ecx]
//   00376D31  89 10              mov [eax], edx        ; N.X
//   00376D33  8b 51 04           mov edx, [ecx+4]
//   00376D36  89 50 04           mov [eax+4], edx      ; N.Y
//   00376D39  8b 49 08           mov ecx, [ecx+8]
//   00376D3C  89 48 08           mov [eax+8], ecx      ; N.Z
//   00376D3F  8b 4c 24 08        mov ecx, [esp+8]      ; dist
//   00376D43  89 48 0c           mov [eax+0xc], ecx    ; D
//   00376D46  c2 08 00           ret 8
//
// with 0x00376D28 (`ret`) immediately before it, so the boundary is proven.
//
// The four stores are dword-at-a-time rather than the three `rep movsd` the
// 12-byte copyTo thunk gets, because the second argument is a float and the
// compiler keeps it in a register across the first three moves rather than
// spilling. Vector3 is spelled with the donor's own definition, minus the
// constructors the constructor under test never calls.

// The four stores are dword-at-a-time rather than the three `rep movsd` a plain
// POD copy would get, because the donor's Vector3 declares its own copy
// assignment: a user-defined operator= defeats the block-move recognition, so
// N = normal becomes three separate mov/mov pairs. Dropping that operator (as a
// bare three-float struct does) produces push esi/push edi and three `rep movsd`
// instead -- 25 bytes, not retail's 32.
class Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3 &operator=(const Vector3 &v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		return *this;
	}
};

class PlaneClass
{
public:
	Vector3 N;
	float D;

	PlaneClass(const Vector3 &normal, float dist);
};

// Defined out of line on purpose: an in-class definition is implicitly inline,
// and MSVC 7.1 does not emit an inline member this TU never calls, so the body
// would be missing from the object and the byte gate would have nothing to
// compare. The emitted code is the same either way.
PlaneClass::PlaneClass(const Vector3 &normal, float dist)
{
	N = normal;
	D = dist;
}
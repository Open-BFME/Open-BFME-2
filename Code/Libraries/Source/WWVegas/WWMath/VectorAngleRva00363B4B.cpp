// cl: /O1 /G7 /arch:SSE /Oy- /MD /EHsc /DNDEBUG
// Semantic donor: Open-BFME-1 694d7d49dcaf31cc4bc0fa85a7dd6888b549dcb2,
// game/GameEngine/Source/Common/bfmeUnitAngle.cpp. Target Ghidra 363B4B..363BC7
// proves a cdecl two-pointer helper with x87 float return. The target clamps
// before its 0.99 comparison; all four constants are independently PE-read.
// Original names/input types are unknown; only the three-float prefix is used.
struct Rva00363B4BVector { float x, y, z; };
float ACos(float);

float rva00363B4BAngle(const Rva00363B4BVector *a, const Rva00363B4BVector *b)
{
    float dot = a->z * b->z + a->y * b->y + a->x * b->x;
    if (dot > 1.0f) dot = 1.0f;
    if (dot < -1.0f) dot = -1.0f;
    if (dot >= 0.99f) return 0.0f;
    return ACos(dot);
}

// cl: /O1 /arch:SSE /G7 /Oy-
// BFME1 donor interface: game/GameEngine/Source/GameClient/LivingWorldEyeTowerState.cpp
// at 5a79bd207c9c50b67f8687dc507796c6c924e75e. That donor declares,
// rather than implements, this method. Its name and pair types remain
// donor-supported structural inferences, also used by the verified BFME2
// caller at 003F9B93. Target evidence: 002BEB6F..002BEBE3, RET 16;
// curve receiver +28 and two calls to 00504BA9 (RET 4, x87 float result).
struct Gen0060CBB0Pair { float first; float second; };

class Rva00504BA9Curve
{
public:
    float rva00504BA9(float progress);
};

class BfmeStateDF
{
public:
    void interpolate(Gen0060CBB0Pair *from, Gen0060CBB0Pair *to,
        Gen0060CBB0Pair *current, float progress);
private:
    unsigned char prefix28[0x28];
    Rva00504BA9Curve curve;
};

// ?interpolate@BfmeStateDF@@QAEXPAUGen0060CBB0Pair@@00M@Z
void BfmeStateDF::interpolate(Gen0060CBB0Pair *from, Gen0060CBB0Pair *to,
    Gen0060CBB0Pair *current, float progress)
{
    Rva00504BA9Curve *c = &curve;
    float factor = c->rva00504BA9(progress);
    float start = from->first;
    current->first = (to->first - start) * factor + start;
    progress = c->rva00504BA9(progress);
    start = from->second;
    current->second = (to->second - start) * progress + start;
}

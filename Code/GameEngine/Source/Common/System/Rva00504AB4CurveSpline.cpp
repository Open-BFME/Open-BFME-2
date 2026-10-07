// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Semantic donor: BFME1 ba7ddda7e8 game/GameEngine/Source/Common/FCurve.cpp.
// Target facts: 00504AB4..00504BA9 RET4/ST0, 16-byte keys, cached key+18,
// coefficients+1C..28. Both calls in the independently measured 00504BA9
// evaluator retain this receiver, supporting the existing neutral class view.
// Target changes from donor: range search through the measured 34-byte member
// at 005049A4, register-only delta and explicit 2/3 coefficient factors/order.
// Original class and search-container identities remain unknown.
struct Rva00504AB4Key
{
    float time, value, tangentIn, tangentOut;
};

class Rva005049A4KeyRange
{
public:
    Rva00504AB4Key *rva005049A4(const float &time) const;
    Rva00504AB4Key *begin;
    Rva00504AB4Key *end;
    char unknown08[5];
    unsigned char flag;
    char unknown0E[2];
};

class Rva00504BA9Curve
{
public:
    float rva00504AB4(float time) const;
private:
    int unknown00, unknown04;
    Rva005049A4KeyRange keys;
    mutable Rva00504AB4Key *volatile current;
    mutable float coefficientA, coefficientB, coefficientC, coefficientD;
};

float Rva00504BA9Curve::rva00504AB4(float time) const
{
    Rva00504AB4Key *end = keys.end;
    Rva00504AB4Key *next = current + 1;
    Rva00504AB4Key *left = current;
    if (left == end || left->time > time || next == end || time >= next->time)
    {
        next = keys.rva005049A4(time);
        if (next == end)
            next = end - 1;
        left = next - 1;
        current = left;
        float delta = next->time - left->time;
        float leftValue = left->value;
        float leftTangent = delta * left->tangentOut;
        float rightValue = next->value;
        float rightTangent = delta * next->tangentIn;
        coefficientA = (leftValue - rightValue) * 2.0f + rightTangent + leftTangent;
        coefficientB = (rightValue - leftValue) * 3.0f - leftTangent * 2.0f - rightTangent;
        coefficientC = leftTangent;
        coefficientD = leftValue;
    }
    left = current;
    float leftTime = left->time;
    time = (time - leftTime) / (next->time - leftTime);
    return (((time * coefficientA + coefficientB) * time + coefficientC) * time + coefficientD);
}

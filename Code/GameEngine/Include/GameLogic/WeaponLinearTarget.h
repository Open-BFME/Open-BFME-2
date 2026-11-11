#pragma once

// LinearTarget parses X and Y as real offsets and T as an unsigned delay.
// Weapon firing reads successive records at a stride of 12 bytes.
struct WeaponLinearTarget
{
    WeaponLinearTarget() {}
    WeaponLinearTarget(const WeaponLinearTarget &other)
        : x(other.x), y(other.y), delay(other.delay) {}

    float x;
    float y;
    unsigned int delay;
};

// Neutral view of the target 128-byte memcpy constructor; original type unknown.
#pragma once
#include <string.h>
struct BfmeFixedStorage128 {
    unsigned char bytes[128];
    __declspec(noinline) BfmeFixedStorage128(const BfmeFixedStorage128& rhs) {
        memcpy(bytes, rhs.bytes, 128);
    }
};

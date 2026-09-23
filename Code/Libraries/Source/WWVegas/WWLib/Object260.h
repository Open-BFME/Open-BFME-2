// Target copy constructs a DWORD and two128-byte members; original names unknown.
#pragma once
#include "FixedStorage128.h"
struct BfmeFixedObject260 {
    unsigned int word_00;
    BfmeFixedStorage128 storage_04;
    BfmeFixedStorage128 storage_84;
};

#include <stddef.h>
typedef char Object260Size[sizeof(BfmeFixedObject260) == 260 ? 1 : -1];
typedef char Object260Member[offsetof(BfmeFixedObject260, storage_84) == 0x84 ? 1 : -1];

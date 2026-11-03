// Target facts (retail RVAs): 0x00466EA7 copies the key via 0x000365F0 and four payload bytes at pair+4; 0x00317EBB uses eight-byte pair strides.
// 0x0020F569 allocates 0x0C with the pair at +4; 0x00221201 allocates 0x18 with the pair at +0x10: payload sizeof=4, offset=0, no base or virtual functions.
// 0x0021051F and 0x0020D6AE zero the default payload; 0x0048BA39 destroys only the key via 0x00036410. No payload methods are rowed; the application identity is unknown.

#pragma once

#ifndef BFME2_NO_CASE_TREE_VALUE4_H
#define BFME2_NO_CASE_TREE_VALUE4_H

struct NoCaseTreeValue4
{
    NoCaseTreeValue4() { *(unsigned int *)m_body = 0; }

    char m_body[4];
};

#endif

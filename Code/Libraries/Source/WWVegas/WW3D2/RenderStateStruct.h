// FILE: RenderStateStruct.h /////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 RenderStateStruct, the type of DX8Wrapper::render_state.
//
// Target facts:
//  - No virtual functions: the constructor stores no table, and +0 holds the shader
//    bits. sizeof is 0x290. DX8Wrapper::Init clears 0xA4 dwords of render_state at
//    VA 0x00DEE5D8 (0x0052568D), the second instance at VA 0x00DEDC80 is a 0x290-byte
//    data row, and the last field ends at +0x28E.
//  - The constructor is 0x0011FB40 and the destructor 0x0011C5C0, both out of line.
//    The dynamic initializers 0x007ACC20 and 0x007ACC00 call the constructor on VA
//    0x00DEE5D8 and 0x00DEDC80 and register the thunks 0x007B6FD0 and 0x007B6FC0,
//    which jump to the destructor. The ledger names these two rows
//    ??0SortingRenderStateStruct@@QAE@XZ and ??1SortingRenderStateStruct@@QAE@XZ.
//  - The constructor stores 0x0010441B at +0 (ShaderClass's default bits), clears
//    material at +4, constructs 16 four-byte elements at +8 through the eh vector
//    constructor iterator (element constructor RVA 0x00326BE6, destructor RVA
//    0x0017098D, the RefCountPtr<TextureClass> rows), and clears +0x280, +0x284 and
//    +0x288.
//  - The destructor releases material (+4), vertex_buffers (+0x280, two entries) and
//    index_buffer (+0x288) through the RefCountClass count at +4 of each object,
//    then destroys the 16 elements at +8 with the eh vector destructor iterator.
//  - operator= (0x0012D8A0) copies four 0x68-byte blocks at +0x48, +0xB0, +0x118 and
//    +0x180, the bytes +0x1E8 to +0x1EB, the dwords +0x1EC to +0x268 (two 64-byte
//    matrices), the dwords +0x26C, +0x270 and +0x274, the words +0x278, +0x27A and
//    +0x27C, and the word +0x28C, and reference-counts +0x280 to +0x288.
//  - DX8Wrapper::Set_Transform (0x000A68A7) writes world at +0x1EC (VA 0x00DEE7C4,
//    from 0x004A6A0B) and view at +0x22C (VA 0x00DEE804, from 0x004A6D36).
// Donor (Zero Hour dx8wrapper.h) facts: the member names and order, with
// MAX_TEXTURE_STAGES 16 and MAX_VERTEX_STREAMS 2 fitting every offset above.
// Zero Hour's Lights are D3DLIGHT8 structs; they stay opaque here so the header needs
// no SDK. Zero Hour spells Textures as TextureBaseClass pointers; BFME2 constructs and
// destroys each one, which only the out-of-line members do. world and view are the
// canonical Matrix4 of Matrix4Data.h (Zero Hour spells them Matrix4x4, its typedef).
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef BFME2_RENDERSTATESTRUCT_H
#define BFME2_RENDERSTATESTRUCT_H

#include "ShaderClass.h"
#include "../WWMath/Matrix4Data.h"

class VertexMaterialClass;
class TextureBaseClass;
class VertexBufferClass;
class IndexBufferClass;

struct RenderStateStruct
{
    ShaderClass shader;
    VertexMaterialClass *material;
    TextureBaseClass *Textures[16];
    unsigned char m_48[4][0x68];
    bool LightEnable[4];
    Matrix4 world;
    Matrix4 view;
    unsigned vertex_buffer_types[2];
    unsigned index_buffer_type;
    unsigned short vba_offset;
    unsigned short vba_count;
    unsigned short iba_offset;
    VertexBufferClass *vertex_buffers[2];
    IndexBufferClass *index_buffer;
    unsigned short index_base_offset;

    RenderStateStruct();
    ~RenderStateStruct();
    RenderStateStruct &operator=(const RenderStateStruct &src);
};

#endif

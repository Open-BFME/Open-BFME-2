// Target facts (game.dat; code addresses are RVAs): constructors 0x00187DE0 and 0x00187E90 install VA 0x00BD5AEC at +0 and clear the MultiListObjectClass node at +4. Its sole slot is deleting destructor 0x00187E70, which calls destructor 0x00187CE0 and conditionally operator delete 0x0002FD60; VA 0x00BD5AF0 starts a format string. Destructor 0x00187CE0 calls ~MultiListObjectClass at 0x00187D22; that base body 0x006109C0 restores its separate VA 0x00BC5C6C table at 0x006109C7. No additional virtual slots or base subobjects are present.
// Target layout: push 0x34 at 0x00145793, operator new at 0x00145799 and constructor call 0x001457CC prove sizeof 0x34. Constructor stores prove mmc +8, texture_category +0x0C, index_offset +0x10, vertex_offset +0x14, index_count +0x18, min_vertex_index +0x1C, vertex_index_range +0x20, two unsigned words +0x24/+0x28, strip byte +0x2C and pass +0x30; the copy-with-model constructor copies those widths and offsets. Out-of-line rows are Render 0x00143630, Render_Sorted 0x00143770, Set_Vertex_Index_Range 0x001435F0 and Log 0x00187D40. The matched Add_Mesh 0x00145620 calls its four-argument Set_Vertex_Index_Range inline: stores at 0x00145A0C/14/21/24 update +0x20/+0x1C/+0x24/+0x28.
// Donor names and inline accessors: Zero Hour GeneralsMD WW3D2/dx8polygonrenderer.h names the common fields, Get_Vertex_Offset, Get_Index_Offset, Get_Pass, Get_Mesh_Model_Class, Get_Texture_Category and Set_Texture_Category. Retail's constructors and Render/Log accesses corroborate the common fields; the two additional words have neutral names because Zero Hour does not declare them. The donor is not included; constructors, virtual destructor and rowed methods remain out of line.
#pragma once

#ifndef BFME2_DX8_POLYGON_RENDERER_CLASS_H
#define BFME2_DX8_POLYGON_RENDERER_CLASS_H

#include "../WWLib/MultiListObjectClass.h"

class MeshModelClass;
class DX8TextureCategoryClass;
class SphereClass;

class DX8PolygonRendererClass : public MultiListObjectClass
{
public:
    DX8PolygonRendererClass(unsigned index_count, MeshModelClass *model,
        DX8TextureCategoryClass *category, unsigned vertex_offset,
        unsigned index_offset, bool strip, unsigned pass);
    DX8PolygonRendererClass(const DX8PolygonRendererClass &source, MeshModelClass *model);
    virtual ~DX8PolygonRendererClass();

    void Render(int base_vertex_offset);
    void Render_Sorted(int base_vertex_offset, const SphereClass &bounding_sphere);
    void Set_Vertex_Index_Range(unsigned min_vertex_index, unsigned vertex_index_range);
    void Set_Vertex_Index_Range(unsigned minimum, unsigned range, unsigned value24, unsigned value28)
    {
        vertex_index_range = range;
        min_vertex_index = minimum;
        field_24 = value24;
        field_28 = value28;
    }
    void Log();

    unsigned Get_Vertex_Offset() { return vertex_offset; }
    unsigned Get_Index_Offset() { return index_offset; }
    unsigned Get_Pass() { return pass; }
    MeshModelClass *Get_Mesh_Model_Class() { return mmc; }
    DX8TextureCategoryClass *Get_Texture_Category() { return texture_category; }
    void Set_Texture_Category(DX8TextureCategoryClass *category) { texture_category = category; }

    MeshModelClass *mmc;
    DX8TextureCategoryClass *texture_category;
    unsigned index_offset;
    unsigned vertex_offset;
    unsigned index_count;
    unsigned min_vertex_index;
    unsigned vertex_index_range;
    unsigned field_24;
    unsigned field_28;
    bool strip;
    unsigned pass;
};

#endif

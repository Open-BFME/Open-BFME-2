#pragma once
// BFME2 native30B980/30B3D1/30B8E4; consumed40-byte layout, no vptr.
#include <vector>
#include "../../../Libraries/Include/Lib/Region2D.h"
// Existing matched point provider spelling, not a recovered original type name.
struct BfmeE8 {
 float x,y;
 BfmeE8() {}
 BfmeE8(const BfmeE8 &v):x(v.x),y(v.y) {}
};
struct BfmePod8;
class DataChunkInput;
class Matrix3D;
struct AreaPolygonBase {
 _STL::vector<BfmeE8> m_points; //0..B: native eight-byte records
 Region2D m_bounds; //C..1B
 float m_innerRadius; //1C
 float m_radius; //20
 bool m_dirty; //24, native derived next field28
 __forceinline AreaPolygonBase() {}
 AreaPolygonBase(const AreaPolygonBase &);
 void reserve(int);
 void rva0030B3D1();
 void insertPoint(int,const BfmeE8 &);
 void setPoint(int,const BfmeE8 &);
 void parse(DataChunkInput &,int);
 void rva0030B135(const BfmePod8 *);
 void rva0030B1A7(float);
 void rva0030B232(const Matrix3D &);
 void deletePoint(int);
};

#ifndef BFME_RVA002E7D6D_INFO_H
#define BFME_RVA002E7D6D_INFO_H
#include "Lib/Coord3D.h"
class PathfindCell;
class Rva002E6DC4;
// Callback2E7D6D and initializer2E7D3F jointly prove this32B context layout.
// The query is an opaque16B copy; its original semantic types remain unknown.
struct Rva002E7D3FQuery { unsigned int words[4]; };
struct Rva002E7D6DInfo {
 Rva002E6DC4 *m_provider;
 Coord3D *m_result;
 int m_layer;
 Rva002E7D3FQuery m_query;
 bool m_check;
 Rva002E7D6DInfo *rva002E7D3F(Rva002E6DC4 *provider, Coord3D *result,
                            int layer, const Rva002E7D3FQuery &query, bool check);
 int cellCallback(PathfindCell *previousCell, PathfindCell *currentCell,
                  int cellX, int cellY);
};
#endif

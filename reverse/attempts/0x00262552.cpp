// ?rva00262552@AIUpdateInterface@@QAEHPBUCoord3D@@@Z
// partial score=0.85 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class Object { public: int rva0028B511() const; };
enum PathfindLayerEnum { LAYER_INVALID=0 };
class TerrainLogic { public: PathfindLayerEnum getLayerForDestination(Object *, const Coord3D *); };
extern TerrainLogic *TheTerrainLogic;
class AIUpdateInterface {
public:
 int rva00262552(const Coord3D *destination);
 void *m_vptr;
 char m_unknown04[4]; Object *m_object;
 char m_unknown0C[0x1e1-0xc]; bool m_bfmeByte1E1;
};
int AIUpdateInterface::rva00262552(const Coord3D *destination)
{
 int sourceLayer = m_object->rva0028B511();
 int destinationLayer = TheTerrainLogic->getLayerForDestination(0, destination);
 bool flag = m_bfmeByte1E1;
 if (sourceLayer != destinationLayer) {
  if (destinationLayer == 16) return 3;
  if (sourceLayer == 1) return flag != 0;
  if (sourceLayer >= 2 && sourceLayer <= 15) {
   if (destinationLayer == 1) return 0;
  } else {
   if (sourceLayer == 16) return 4;
   if (sourceLayer >= 17) return flag ? 2 : 0;
   return 0;
  }
 }
 return 5;
}

// cl: /O1 /MD /EHsc /ICode/Libraries/Include/Lib
// Native381B reconstructViewBox4D9B6 uses four12B world points and four8B
// float radar points, each with shared47A6A9 ctor/B3FD0 dtor callbacks.
// Canonical bases provide layouts; scoped lifetime adapters reproduce complete
// constructor3B/destructor1B byte-and-relocation twins with no unique gain.
#include "Coord3D.h"
#include "Coord2D.h"
struct BfmeRadarWorldPoint:Coord3D{BfmeRadarWorldPoint();~BfmeRadarWorldPoint();};
struct BfmeRadarMapPoint:Coord2D{BfmeRadarMapPoint();~BfmeRadarMapPoint();};
BfmeRadarWorldPoint::BfmeRadarWorldPoint(){}
BfmeRadarWorldPoint::~BfmeRadarWorldPoint(){}
BfmeRadarMapPoint::BfmeRadarMapPoint(){}
BfmeRadarMapPoint::~BfmeRadarMapPoint(){}

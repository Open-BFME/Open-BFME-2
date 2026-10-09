// ?QuickDoesPathExistToStructure@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@0H@Z
// partial score=0.91 date=2026-10-09
// The BFME1 client-safe quick-path routine supplies the terrain-zone test;
// WB D39F80 and native 0x002F4B33 add BFME2's structure centre, shape offset,
// and four cell walks. Position +0x38, geometry +0xA8, and radius +0xB8 are
// read from the retail body. The callback's +4 value and goal-info +0x28
// remain address-based views.
struct BfmeShapeE15
{
	char m_pad00[8];
	float m_height;
	char m_pad0C[4];
	Coord3D m_offset;
	char m_pad1C[8];
};
class BfmeObjE15
{
public:
	BfmeShapeE15 *bfmeAtE15(Int index);
};

Bool Pathfinder::QuickDoesPathExistToStructure(Object *obj,
	const Coord3D *from, Object *structure, Int overrideSet)
{
	Pathfinder *pathfinder = this;
	Object *owner = obj;
	LocomotorSet *set;
	char *ai = owner->m_258;
	if (ai)
	{
		if (overrideSet)
			set = (LocomotorSet *)overrideSet;
		else
			set = (LocomotorSet *)(ai + 0x1cc);
	}
	else if (overrideSet)
		set = (LocomotorSet *)overrideSet;
	else
		return false;
	obj = (Object *)set;
	if (!(set->getValidSurfaces() & 0x8f))
		return false;

	Coord3D goalPos;
	copyCoord3D(&goalPos, (const Coord3D *)structure->position);
	PathfindLayerEnum goalLayer = TheTerrainLogic->getLayerForDestination(owner, &goalPos);
	PathfindLayerEnum fromLayer = TheTerrainLogic->getLayerForDestination(owner, from);
	PathfindCell *parent = pathfinder->rva002E8BF8(fromLayer, from);
	PathfindCell *goal = pathfinder->rva002E8BF8(goalLayer, &goalPos);
	if (goal->getType() != PathfindCell::CELL_OBSTACLE)
		return pathfinder->QuickDoesPathExist(owner, from, &goalPos, (Int)obj);

	BfmeShapeE15 *shape = ((BfmeObjE15 *)((char *)structure + 0xa8))->bfmeAtE15(0);
	Coord3D *shapeOffset = (Coord3D *)((char *)shape + 0x10);
	goalPos.x += shapeOffset->x;
	goalPos.y += shapeOffset->y;
	goalPos.z += shapeOffset->z;
	goal = pathfinder->rva002E8BF8(goalLayer, &goalPos);
	if (goal->getType() != PathfindCell::CELL_OBSTACLE)
		return pathfinder->QuickDoesPathExist(owner, from, &goalPos, (Int)obj);

	void *goalInfo = *(void **)goal;
	Int goalKey = goalInfo ? *(Int *)((char *)goalInfo + 0x28) : 0;
	ICoord2D startCell;
	Rva002E7875WorldToCell(&startCell, true, &goalPos);
	Bool flag = obj->m_template->flag;
	Int priority = obj->m_template->priority;
	Rva002E8BCF zoneInfo((const Rva002E8BCFSrc *)set, !flag,
		priority - 1, obj->rva0028AFBB());
	Int sourceZone = ((Rva002E99F9Sub460 *)((char *)pathfinder + 0x460))
		->rva0053241F(&zoneInfo, parent->quickZone());

	Rva002E7261Info callbackInfo;
	callbackInfo.m_pathfinder = pathfinder;
	callbackInfo.m_arg = goalKey;
	callbackInfo.m_key = -1;
	callbackInfo.m_position.x = -1;
	callbackInfo.m_position.y = -1;
	Int radius = 2 - (Int)(*(float *)((char *)structure + 0xb8) * -0.1f);
	if (pathfinder->rva002F4AC1(&startCell, radius, 0, owner, fromLayer, sourceZone,
		&callbackInfo, &zoneInfo, (void *)obj))
		return true;
	if (pathfinder->rva002F4AC1(&startCell, -radius, 0, owner, fromLayer, sourceZone,
		&callbackInfo, &zoneInfo, (void *)obj))
		return true;
	if (pathfinder->rva002F4AC1(&startCell, 0, radius, owner, fromLayer, sourceZone,
		&callbackInfo, &zoneInfo, (void *)obj))
		return true;
	return pathfinder->rva002F4AC1(&startCell, 0, -radius, owner, fromLayer, sourceZone,
		&callbackInfo, &zoneInfo, (void *)obj);
}

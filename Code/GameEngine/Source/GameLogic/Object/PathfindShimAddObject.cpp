// cl: /O1 /DNDEBUG /MD /EHsc
// ?addObjectToPathfindMap@BFMEPathfinderMapShim@@QAEXPAVObject@@@Z @0x002E7178
// Shard TU: friend_notifyOfNewMapBoundary lives in
// Object_friendNotifyOfNewMapBoundary.cpp under /Oy- frames; this frameless
// leaf needs no frame so it lives here.

class Object;

void __stdcall Rva00530212Helper(Object *object, int a1, int a2, int a3);

class BFMEPathfinderMapShim
{
public:
	void addObjectToPathfindMap(Object *object);
};

// ?addObjectToPathfindMap@BFMEPathfinderMapShim@@QAEXPAVObject@@@Z
void BFMEPathfinderMapShim::addObjectToPathfindMap(Object *object)
{
	Rva00530212Helper(object, 1, 0, 0);
}

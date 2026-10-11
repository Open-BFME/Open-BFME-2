// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?restoreObjectToWorld@Object@@QAEXPBUCoord3D@@@Z 0x0029766B 25B. WB confirms
// restoreObjectToWorld; retail runs the internal restore then teleport(pos, 0).
// WB CCB850 names internal restore291C20, now recovered in ObjectScriptStatus.cpp.
// Matrix3D sibling: Object::rva00291C84 (ObjectRefreshThenSetTransform.cpp).
struct Coord3D;
class Object
{
public:
	void restoreObjectToWorldInternal();
	void teleportTo(const Coord3D *pos, bool flag);
	void restoreObjectToWorld(const Coord3D *pos);
};
void Object::restoreObjectToWorld(const Coord3D *pos)
{
	restoreObjectToWorldInternal();
	((Object *)this)->teleportTo(pos, false);
}

// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva0029766B@Rva0029766B@@QAEXPBUCoord3D@@@Z 0x0029766B 25B evidence: twin of SimpleObjectIterator firstWithNumeric 0x00291C84 reset-first shape; callees pinned reset 0x00291C20 and Object teleport 0x0029660C; caller 0x004AFA6B
struct Coord3D;
class Object
{
public:
	void rva0029660C(const Coord3D *pos, int i);
};
class Rva0029766B;
class SimpleObjectIterator
{
private:
	void reset();
	friend class Rva0029766B;
};
class Rva0029766B
{
public:
	void rva0029766B(const Coord3D *pos);
};
void Rva0029766B::rva0029766B(const Coord3D *pos)
{
	((SimpleObjectIterator *)this)->reset();
	((Object *)this)->rva0029660C(pos, 0);
}

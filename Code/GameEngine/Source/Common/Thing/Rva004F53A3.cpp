// cl: /DNDEBUG /MD /EHsc
// ?Rva004F53A3Destroy@@YAXPAVObject@@@Z, retail 0x004F53A3, 32 bytes.
// Chain from 0x0028FB6F: pushes Object+0x274 into Object::rva0028FB6F then
// destroys Object via TheGameLogic->destroyObject. Evidence: free cdecl
// (esi from stack, plain ret); rowed rva0028FB6F 0x28FB6F and rowed
// destroyObject 0x242C09; TheGameLogic at 0x00DFE78C; neighbours
// 0x004F5334 and 0x004F553F prove Thing TU and /O1 /DNDEBUG /MD /EHsc.
class Object
{
public:
	void rva0028FB6F(void *param);
	char m_pad00[0x274];
	void *m_274;
};

class GameLogic
{
public:
	void destroyObject(Object *obj);
};

extern GameLogic *TheGameLogic;

void __cdecl Rva004F53A3Destroy(Object *obj)
{
	obj->rva0028FB6F(obj->m_274);
	TheGameLogic->destroyObject(obj);
}

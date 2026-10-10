// stlport
// cl: /O1 /DNDEBUG /MD /Oy- /G7 /arch:SSE
// Native BBDDF..BBE29 is a74B thiscall lookup on flagsF4/mapA0.
// BBE29..BBE86 is its93B float-translation wrapper with the same receiver.
// The older stdcall declarations omitted the live ECX receiver.
// The int/int map is only the established key-search storage view: native
// node payload is a48B matrix followed by the bone index at node44.
#include <map>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
class Rva000BBDDF {public:void*rva000BBDDF(int,int*)const;bool rva000BBE29(int,struct Vector3*)const;
 char opaque00[0xA0];_STL::map<int,int> lookup;char opaqueAC[0xF4-0xAC];unsigned char flags;
};

struct Vector3
{
	float x, y, z;
};

struct Rva000BBDDFNode
{
	char m_pad00[0x0C];
	float m_0C;
	char m_pad10[0x1C - 0x10];
	float m_1C;
	char m_pad20[0x2C - 0x20];
	float m_2C;
};

// Native BBE29 wrapper returns a byte and preserves the caller receiver.
bool Rva000BBDDF::rva000BBE29(int key, Vector3 *out)const
{
	Rva000BBDDFNode *node = (Rva000BBDDFNode *)rva000BBDDF(key, 0);
	if (node != 0)
	{
		Vector3 tmp;
		tmp.x = node->m_0C;
		tmp.y = node->m_1C;
		tmp.z = node->m_2C;
		*out = tmp;
		return true;
	}
	out->x = 0.0f;
	out->y = 0.0f;
	out->z = 0.0f;
	return false;
}

void*Rva000BBDDF::rva000BBDDF(int key,int*index)const{
 if(!(flags&1)||key==0){if(index)*index=0;return 0;}
 _STL::map<int,int>::const_iterator it=lookup.find(key);
 if(it._M_node!=lookup.end()._M_node){
  if(index)*index=*(const int*)((const char*)it._M_node+0x44);
  return (char*)it._M_node+0x14;
 }
 if(index)*index=0;return 0;
}

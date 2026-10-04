// cl: -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// stlport
// ??0?$vector@UGen003AA0D0@@V?$allocator@UGen003AA0D0@@@_STL@@@_STL@@QAE@I@Z
// retail 0x005DE870, 93 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/R5VectorDtorEHFramedPolymorphic.cpp: the donor
// preamble and this one vector<Gen003AA0D0> member, the donor's other
// elements omitted. Gen003AA0D0 is the donor's opaque 0x18-byte polymorphic
// payload (virtual dtor owning slot 0); no element identity reaches the bytes.
#include <vector>

struct Gen003AA0D0
{
	virtual ~Gen003AA0D0();
	char m_pad[0x18 - 4];
	Gen003AA0D0();
	Gen003AA0D0(const Gen003AA0D0 &);
	Gen003AA0D0 &operator=(const Gen003AA0D0 &);
};

template _STL::vector<Gen003AA0D0>::vector(unsigned int);

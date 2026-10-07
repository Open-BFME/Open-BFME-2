// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD
#include "Rva002E7D6DInfo.h"

// Native2E7D3F..2E7D6D is a46B leaf, ending RET20 immediately before
// this context's verified callback. Its stores match every callback-consumed
// field: provider0/result4/layer8/queryC..1B/check1C. The four MOVSD copy the
// opaque16B query. EAX returns the receiver. Original initializer name unknown.
Rva002E7D6DInfo *Rva002E7D6DInfo::rva002E7D3F(Rva002E6DC4 *provider,
    Coord3D *result, int layer, const Rva002E7D3FQuery &query, bool check)
{
 m_provider=provider;
 m_result=result;
 m_layer=layer;
 m_query=query;
 m_check=check;
 return this;
}


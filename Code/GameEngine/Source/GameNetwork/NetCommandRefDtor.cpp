// NetCommandRef::~NetCommandRef at 0x0058B8AE is 12 bytes. The target-rowed
// NetCommandNode::detach at that address conditionally calls
// NetCommandMsg::detach; BFME1's donor dtor has the same guarded release body.
// Target layout evidence: NetCommandRef and NetCommandNode both hold m_msg at
// +0, followed by their list links. This is a real second identity folded onto
// the identical detach body, not a rename of the node operation.
#include "../../Include/GameNetwork/NetCommandMsg.h"

class NetCommandRef
{
public:
	~NetCommandRef();

private:
	NetCommandMsg *m_msg;
};

NetCommandRef::~NetCommandRef()
{
	if (m_msg != 0)
		m_msg->detach();
}

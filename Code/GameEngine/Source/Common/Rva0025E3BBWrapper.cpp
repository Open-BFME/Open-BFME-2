// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva0025E3BB@Rva0025E3BB@@QAEHHVAsciiString@@@Z @0x0025E3BB 75B
// Wrapper over ConnectionManager::getFileTransferProgress at +0xc.
// Evidence: calls rowed 0x004D28C6 with int plus AsciiString by value; StringBase copy 0x365F0 plus releaseBuffer 0x36410; ret 8; chain from 0x004D28C6.
#include "ascii_string.h"

class ConnectionManager
{
public:
	int getFileTransferProgress(int pid, AsciiString path);
};

class Rva0025E3BB
{
public:
	int rva0025E3BB(int pid, AsciiString path);
private:
	char m_pad[0xc];
	ConnectionManager *m_mgr;
};

int Rva0025E3BB::rva0025E3BB(int pid, AsciiString path)
{
	return m_mgr->getFileTransferProgress(pid, path);
}

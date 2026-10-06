// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// BFME1 donor: reference/open-bfme-1/game/GameEngine/Source/GameNetwork/IPEnumeration.cpp
// donor revision 10af19f44a89ab7ecc23195bb9a842ceafbc02c9. BFME2 omits the
// MemoryPoolObject word from EnumeratedIP; the retail allocation is 12 bytes.

#define LOBYTE(w) ((unsigned char)(w))
#define HIBYTE(w) ((unsigned char)(((unsigned short)(w) >> 8) & 0xff))

struct WSADataBlock
{
	unsigned short version;
	unsigned short highVersion;
	char details[0x18A];
};

struct hostent
{
	char *h_name;
	char **h_aliases;
	short h_addrtype;
	short h_length;
	char **h_addr_list;
};

extern "C"
{
	__declspec(dllimport) int __stdcall WSAStartup(unsigned short, WSADataBlock *);
	__declspec(dllimport) int __stdcall WSACleanup(void);
	__declspec(dllimport) int __stdcall gethostname(char *, int);
	__declspec(dllimport) hostent *__stdcall gethostbyname(const char *);
	__declspec(dllimport) unsigned long __stdcall htonl(unsigned long);
}

class AsciiString;
#include "string_base.h"
#include "ascii_string.h"

class EnumeratedIP
{
public:
	EnumeratedIP();
	unsigned int getIP() { return m_IP; }
	void setIP(unsigned int ip) { m_IP = ip; }
	EnumeratedIP *getNext() { return m_next; }
	void setNext(EnumeratedIP *next) { m_next = next; }

private:
	AsciiString m_IPstring;
	unsigned int m_IP;
	EnumeratedIP *m_next;
};

// This byte-verified setter owns the AsciiString at EnumeratedIP+0.
class Rva0050BFFD
{
public:
	void rva0050BFFD(AsciiString s);

private:
	AsciiString m_str;
};

class IPEnumeration
{
public:
	EnumeratedIP *getAddresses(void);

private:
	EnumeratedIP *m_IPlist;
	bool m_isWinsockInitialized;
};

// ?getAddresses@IPEnumeration@@QAEPAVEnumeratedIP@@XZ
EnumeratedIP *IPEnumeration::getAddresses(void)
{
	if (m_IPlist)
		return m_IPlist;

	if (!m_isWinsockInitialized)
	{
		WSADataBlock wsadata;
		int err = WSAStartup(0x202, &wsadata);
		if (err != 0)
			return 0;

		if (LOBYTE(wsadata.version) != 2 || HIBYTE(wsadata.version) != 2)
		{
			WSACleanup();
			return 0;
		}
		m_isWinsockInitialized = true;
	}

	char hostname[256];
	if (gethostname(hostname, sizeof(hostname)))
		return 0;

	 hostent *hostEnt = gethostbyname(hostname);
	if (hostEnt == 0)
	{
		EnumeratedIP *newIP = new EnumeratedIP;
		reinterpret_cast<Rva0050BFFD *>(newIP)->rva0050BFFD(AsciiString("127.0.0.1"));
		newIP->setIP(0x0100007f);
		m_IPlist = newIP;
		newIP->setNext(0);
		return m_IPlist;
	}

	if (hostEnt->h_length != 4)
		return 0;

	int numAddresses = 0;
	char *entry;
	while ((entry = hostEnt->h_addr_list[numAddresses++]) != 0)
	{
		EnumeratedIP *newIP = new EnumeratedIP;
		AsciiString str;
		str.format("%d.%d.%d.%d", (unsigned char)entry[0],
			(unsigned char)entry[1], (unsigned char)entry[2],
			(unsigned char)entry[3]);

		unsigned int testIP = *((unsigned int *)entry);
		unsigned int ip = htonl(testIP);
		reinterpret_cast<Rva0050BFFD *>(newIP)->rva0050BFFD(str);
		newIP->setIP(ip);

		if (!m_IPlist)
		{
			m_IPlist = newIP;
			newIP->setNext(0);
		}
		else if (newIP->getIP() < m_IPlist->getIP())
		{
			newIP->setNext(m_IPlist);
			m_IPlist = newIP;
		}
		else
		{
			EnumeratedIP *p = m_IPlist;
			while (p->getNext() && p->getNext()->getIP() < newIP->getIP())
				p = p->getNext();
			newIP->setNext(p->getNext());
			p->setNext(newIP);
		}
	}

	return m_IPlist;
}

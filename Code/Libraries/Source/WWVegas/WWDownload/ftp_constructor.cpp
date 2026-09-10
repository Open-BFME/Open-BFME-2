// cl: /O1 /DNDEBUG /MD
//
// Cftp::Cftp, retail 0x006CA5E0, 18 bytes.
// Dedicated TU so DownloadManager.cpp cannot see this body.
// Installs the Cftp vtable then calls ZeroStuff.

class Cftp
{
public:
	Cftp();
	virtual ~Cftp();
	void ZeroStuff();
};

Cftp::Cftp()
{
	ZeroStuff();
}

// cl: /O1 /MD /EHsc
// ??1Rva0073EE55@@UAE@XZ retail 0x0073EE55 82B
// Virtual dtor with no own vptr store (novtable). Under EH state 1 the member
// at +8 runs the rowed ?set@Rva0040F9D@@QAE_NXZ 0x00040F9D and the object
// held by the member at +4 gets its slot-0 virtual called with -1; then the
// member at +8 runs the rowed ??1Rva0040EDB@@UAE@XZ 0x00040EDB and the member
// at +4 runs its inline dtor, the rowed ?clear@Rva000A880F@@QAEXXZ 0x000A880F.
// Names address-derived.

#include "../../Include/Common/Rva00041004Lock.h"

class Rva0073EE55Target
{
public:
	virtual void Rva0073EE55Slot0(int value);
};

class Rva000A880F
{
public:
	~Rva000A880F()
	{
		clear();
	}

	void clear();

	Rva0073EE55Target *m_target; // +0x00
};

class Rva0040F9D : public Rva0040EDB
{
public:
	bool set();
};

class __declspec(novtable) Rva0073EE55
{
public:
	virtual ~Rva0073EE55();

private:
	Rva000A880F m_holder; // +0x04
	Rva0040F9D m_flag; // +0x08
};

Rva0073EE55::~Rva0073EE55()
{
	m_flag.set();
	m_holder.m_target->Rva0073EE55Slot0(-1);
}

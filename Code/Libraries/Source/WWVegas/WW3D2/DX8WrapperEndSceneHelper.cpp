// cl: /DNDEBUG /MD /EHsc
// platformsdk

#include <comdef.h>

// Retail 0x00958910 is the COM dispatch helper called by
// DX8Wrapper::End_Scene after EndScene.  Its caller pushes one value and
// removes it after the call, so the helper is cdecl with one argument.

// The IID is the GUID WebBrowserComCreateInstance.cpp defines at VA 0xbd4e3c.
extern _GUID g_bfmeIidTSA;

struct Rva00958910Object;

struct Rva00958910Vtable
{
	void *slot00;
	void *slot04;
	void *slot08;
	void *slot0c;
	void *slot10;
	void *slot14;
	void *slot18;
	void *slot1c;
	void *slot20;
	void *slot24;
	void *slot28;
	void *slot2c;
	void *slot30;
	void *slot34;
	long (__stdcall *slot38)(Rva00958910Object *self, void *argument);
};

struct Rva00958910Object
{
	Rva00958910Vtable *vtable;

	long invoke(void *argument)
	{
		long result = vtable->slot38(this, argument);
		if (result < 0)
			_com_issue_errorex(result, (IUnknown *)this,
				reinterpret_cast<const GUID &>(g_bfmeIidTSA));
		return result;
	}
};

struct Rva00959410Ptr
{
	Rva00958910Object *m_p;

	operator bool() const;

	Rva00958910Object *operator->() const
	{
		return m_p;
	}
};

// The dispatch object: the data ledger's g_bfmeObjECF at 0x009F7040
// (BfmeConv804.cpp), read through this unit's smart-pointer view.
struct BfmeObjECF;
extern BfmeObjECF *g_bfmeObjECF;

static inline Rva00959410Ptr &dispatch()
{
	return *reinterpret_cast<Rva00959410Ptr *>(&g_bfmeObjECF);
}

// ?bfmeEndSceneTouch00958910@@YAXPAX@Z
void bfmeEndSceneTouch00958910(void *argument)
{
	if (dispatch().m_p != 0)
		dispatch()->invoke(argument);
}

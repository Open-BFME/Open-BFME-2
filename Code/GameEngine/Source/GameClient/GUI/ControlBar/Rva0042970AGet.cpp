// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// Retail 0x0042970A (RVA 0x0042970A) size 103: find command button by override id 0x1c.
// Evidence: TheInGameUI vtable+0x12c then +0xfc Object then rva00290E67 AsciiString then g_bfmeWorldRV Rva0031D5F8 lookup to CommandSet then getCommandButton loop 0x20 with +0x14==0x18 and Overridable +0x44 +0x1c vs arg.
#include "ascii_string.h"

class Object
{
public:
	const AsciiString *rva00290E67() const;
};

class BfmeWorldRV;
extern class ControlBar *TheControlBar;

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *key);
};

class CommandButton;
class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	char m_pad[0x1c];
	int m_id1c;
};

class CommandButton
{
public:
	char m_pad00[0x14];
	int m_type14;
	char m_pad18[0x44 - 0x18];
	Overridable *m_over44;
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int i) const;
};

class InGameUI
{
public:
	virtual void *v00(); virtual void *v01(); virtual void *v02(); virtual void *v03();
	virtual void *v04(); virtual void *v05(); virtual void *v06(); virtual void *v07();
	virtual void *v08(); virtual void *v09(); virtual void *v10(); virtual void *v11();
	virtual void *v12(); virtual void *v13(); virtual void *v14(); virtual void *v15();
	virtual void *v16(); virtual void *v17(); virtual void *v18(); virtual void *v19();
	virtual void *v20(); virtual void *v21(); virtual void *v22(); virtual void *v23();
	virtual void *v24(); virtual void *v25(); virtual void *v26(); virtual void *v27();
	virtual void *v28(); virtual void *v29(); virtual void *v30(); virtual void *v31();
	virtual void *v32(); virtual void *v33(); virtual void *v34(); virtual void *v35();
	virtual void *v36(); virtual void *v37(); virtual void *v38(); virtual void *v39();
	virtual void *v40(); virtual void *v41(); virtual void *v42(); virtual void *v43();
	virtual void *v44(); virtual void *v45(); virtual void *v46(); virtual void *v47();
	virtual void *v48(); virtual void *v49(); virtual void *v50(); virtual void *v51();
	virtual void *v52(); virtual void *v53(); virtual void *v54(); virtual void *v55();
	virtual void *v56(); virtual void *v57(); virtual void *v58(); virtual void *v59();
	virtual void *v60(); virtual void *v61(); virtual void *v62(); virtual void *v63();
	virtual void *v64(); virtual void *v65(); virtual void *v66(); virtual void *v67();
	virtual void *v68(); virtual void *v69(); virtual void *v70(); virtual void *v71();
	virtual void *v72(); virtual void *v73(); virtual void *v74(); virtual void *v75();
};
extern InGameUI *TheInGameUI;

struct InGameRet
{
	char m_pad[0xfc];
	Object *m_obj;
};

const CommandButton *__stdcall Rva0042970AGet(int id)
{
	int i;
	const CommandButton *btn;
	CommandSet *set;
	InGameRet *r = (InGameRet *)((InGameUI *)TheInGameUI)->v75();
	Object *obj = r->m_obj;
	const AsciiString *name = obj->rva00290E67();
	set = (CommandSet *)((Rva0031D5F8 *)(*(BfmeWorldRV **)&TheControlBar))->rva0031D5F8(name);
	if (set != 0) {
		for (i = 0; i < 0x20; i++) {
			btn = set->getCommandButton(i);
			if (btn == 0) {
				continue;
			}
			if (btn->m_type14 != 0x18) {
				continue;
			}
			const Overridable *ov = btn->m_over44->friend_getFinalOverride();
			if (ov->m_id1c == id) {
				return btn;
			}
		}
	}
	return 0;
}

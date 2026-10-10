// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD
//
// ?rva004958AE@Rva004958AE@@QAEHXZ, retail 0x004958AE, 104 bytes (secondary-base update).
// Pending-command pump: when the owning object (this-8) has its AI (+0x258) and a command is
// held at +0x14, an AI state of 2 (virtual slot 143) dispatches on the command's type (+0x14):
// types 0x17 and 0x1B go to the rowed hunt predicate 0x00495801, types 0x18 and 0x26 to the
// rowed command-button gate 0x00495840 (both on the primary base at this-0x10, argument the AI);
// any other state drops the command and releases the name string at +0x10. Everything else
// sleeps forever (0x3FFFFFFF). Evidence: target bytes and the rowed callees; names are neutral.

template <class T> class StringBase
{
	void releaseBuffer();
	void *m_data;
	friend class Rva004958AE;
};

class Rva00495801Arg;
class Arg;
class Rva00495801 { public: int rva00495801(Rva00495801Arg *arg); };
class Rva00495840 { public: int rva00495840(Arg *arg); };

class Rva004958AEAI
{
public:
	virtual void v000() = 0;
	virtual void v001() = 0;
	virtual void v002() = 0;
	virtual void v003() = 0;
	virtual void v004() = 0;
	virtual void v005() = 0;
	virtual void v006() = 0;
	virtual void v007() = 0;
	virtual void v008() = 0;
	virtual void v009() = 0;
	virtual void v010() = 0;
	virtual void v011() = 0;
	virtual void v012() = 0;
	virtual void v013() = 0;
	virtual void v014() = 0;
	virtual void v015() = 0;
	virtual void v016() = 0;
	virtual void v017() = 0;
	virtual void v018() = 0;
	virtual void v019() = 0;
	virtual void v020() = 0;
	virtual void v021() = 0;
	virtual void v022() = 0;
	virtual void v023() = 0;
	virtual void v024() = 0;
	virtual void v025() = 0;
	virtual void v026() = 0;
	virtual void v027() = 0;
	virtual void v028() = 0;
	virtual void v029() = 0;
	virtual void v030() = 0;
	virtual void v031() = 0;
	virtual void v032() = 0;
	virtual void v033() = 0;
	virtual void v034() = 0;
	virtual void v035() = 0;
	virtual void v036() = 0;
	virtual void v037() = 0;
	virtual void v038() = 0;
	virtual void v039() = 0;
	virtual void v040() = 0;
	virtual void v041() = 0;
	virtual void v042() = 0;
	virtual void v043() = 0;
	virtual void v044() = 0;
	virtual void v045() = 0;
	virtual void v046() = 0;
	virtual void v047() = 0;
	virtual void v048() = 0;
	virtual void v049() = 0;
	virtual void v050() = 0;
	virtual void v051() = 0;
	virtual void v052() = 0;
	virtual void v053() = 0;
	virtual void v054() = 0;
	virtual void v055() = 0;
	virtual void v056() = 0;
	virtual void v057() = 0;
	virtual void v058() = 0;
	virtual void v059() = 0;
	virtual void v060() = 0;
	virtual void v061() = 0;
	virtual void v062() = 0;
	virtual void v063() = 0;
	virtual void v064() = 0;
	virtual void v065() = 0;
	virtual void v066() = 0;
	virtual void v067() = 0;
	virtual void v068() = 0;
	virtual void v069() = 0;
	virtual void v070() = 0;
	virtual void v071() = 0;
	virtual void v072() = 0;
	virtual void v073() = 0;
	virtual void v074() = 0;
	virtual void v075() = 0;
	virtual void v076() = 0;
	virtual void v077() = 0;
	virtual void v078() = 0;
	virtual void v079() = 0;
	virtual void v080() = 0;
	virtual void v081() = 0;
	virtual void v082() = 0;
	virtual void v083() = 0;
	virtual void v084() = 0;
	virtual void v085() = 0;
	virtual void v086() = 0;
	virtual void v087() = 0;
	virtual void v088() = 0;
	virtual void v089() = 0;
	virtual void v090() = 0;
	virtual void v091() = 0;
	virtual void v092() = 0;
	virtual void v093() = 0;
	virtual void v094() = 0;
	virtual void v095() = 0;
	virtual void v096() = 0;
	virtual void v097() = 0;
	virtual void v098() = 0;
	virtual void v099() = 0;
	virtual void v100() = 0;
	virtual void v101() = 0;
	virtual void v102() = 0;
	virtual void v103() = 0;
	virtual void v104() = 0;
	virtual void v105() = 0;
	virtual void v106() = 0;
	virtual void v107() = 0;
	virtual void v108() = 0;
	virtual void v109() = 0;
	virtual void v110() = 0;
	virtual void v111() = 0;
	virtual void v112() = 0;
	virtual void v113() = 0;
	virtual void v114() = 0;
	virtual void v115() = 0;
	virtual void v116() = 0;
	virtual void v117() = 0;
	virtual void v118() = 0;
	virtual void v119() = 0;
	virtual void v120() = 0;
	virtual void v121() = 0;
	virtual void v122() = 0;
	virtual void v123() = 0;
	virtual void v124() = 0;
	virtual void v125() = 0;
	virtual void v126() = 0;
	virtual void v127() = 0;
	virtual void v128() = 0;
	virtual void v129() = 0;
	virtual void v130() = 0;
	virtual void v131() = 0;
	virtual void v132() = 0;
	virtual void v133() = 0;
	virtual void v134() = 0;
	virtual void v135() = 0;
	virtual void v136() = 0;
	virtual void v137() = 0;
	virtual void v138() = 0;
	virtual void v139() = 0;
	virtual void v140() = 0;
	virtual void v141() = 0;
	virtual void v142() = 0;
	virtual int state();
};

class Rva004958AEObject
{
public:
	char m_pad[0x258];
	Rva004958AEAI *m_ai258;
};

struct Rva004958AECommand
{
	char m_pad[0x14];
	int m_type14;
};

class Rva004958AE
{
public:
	int rva004958AE();
private:
	char m_pad[0x10];
	StringBase<char> m_name10;
	Rva004958AECommand *m_command14;
};

int Rva004958AE::rva004958AE()
{
	Rva004958AEObject *object = *(Rva004958AEObject **)((char *)this - 8);
	Rva004958AEAI *ai = object->m_ai258;
	if (ai && m_command14)
	{
		if (ai->state() != 2)
		{
			m_command14 = 0;
			m_name10.releaseBuffer();
		}
		else
		{
			switch (m_command14->m_type14)
			{
			case 0x17:
			case 0x1B:
				return ((Rva00495801 *)((char *)this - 0x10))->rva00495801((Rva00495801Arg *)ai);
			case 0x18:
			case 0x26:
				return ((Rva00495840 *)((char *)this - 0x10))->rva00495840((Arg *)ai);
			}
		}
	}
	return 0x3FFFFFFF;
}

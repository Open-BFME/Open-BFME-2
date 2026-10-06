// cl: /DNDEBUG /MD
//
// ?Rva0023C7F5Get@@YGHHH@Z @0x0023C7F5, 70B.
// Returns 1 or 3 based on GameLogic mode (+0x110 ==1/5 triggers Network check)
// and GameLogic field (+0x40 >=6). Network null means true, else virtual +0xd0.
// Evidence: callers show ret 8 stdcall; TheGameLogic/TheNetwork names in use;
// retail shape xor/inc and push 3/pop indicates /O1.

class GameLogic
{
public:
	char _pad0[0x40];
	unsigned int m_0040;
	char _pad1[0x110 - 0x40 - 4];
	int m_0110;
};

extern GameLogic *TheGameLogic;

class NetworkInterface
{
public:
	virtual void _v00();
	virtual void _v01();
	virtual void _v02();
	virtual void _v03();
	virtual void _v04();
	virtual void _v05();
	virtual void _v06();
	virtual void _v07();
	virtual void _v08();
	virtual void _v09();
	virtual void _v10();
	virtual void _v11();
	virtual void _v12();
	virtual void _v13();
	virtual void _v14();
	virtual void _v15();
	virtual void _v16();
	virtual void _v17();
	virtual void _v18();
	virtual void _v19();
	virtual void _v20();
	virtual void _v21();
	virtual void _v22();
	virtual void _v23();
	virtual void _v24();
	virtual void _v25();
	virtual void _v26();
	virtual void _v27();
	virtual void _v28();
	virtual void _v29();
	virtual void _v30();
	virtual void _v31();
	virtual void _v32();
	virtual void _v33();
	virtual void _v34();
	virtual void _v35();
	virtual void _v36();
	virtual void _v37();
	virtual void _v38();
	virtual void _v39();
	virtual void _v40();
	virtual void _v41();
	virtual void _v42();
	virtual void _v43();
	virtual void _v44();
	virtual void _v45();
	virtual void _v46();
	virtual void _v47();
	virtual void _v48();
	virtual void _v49();
	virtual void _v50();
	virtual void _v51();
	virtual bool isReady();
};

extern NetworkInterface *TheNetwork;

int __stdcall Rva0023C7F5Get(int a, int b)
{
	int result = 1;
	int mode = TheGameLogic->m_0110;
	if ((mode == 1 || mode == 5) && (TheNetwork ? TheNetwork->isReady() : true)) {
		result = 3;
	} else if (TheGameLogic->m_0040 >= 6) {
		result = 3;
	}
	return result;
}

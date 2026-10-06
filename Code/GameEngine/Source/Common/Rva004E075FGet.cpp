// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva004E075FGet@@YAHPAVRva004E075FObj@@H@Z @0x004E075F 24B
// Free __cdecl wrapper: returns obj->v37("LivingWorldBuildingID", arg, 4) where
// v37 is virtual slot 37 (offset 0x94). Retail is mov ecx,[esp+4] /
// mov eax,[ecx] / push 4 / push [esp+0x0C] / push "LivingWorldBuildingID" /
// call [eax+0x94] / ret (24B). /Os keeps the second push late (defaults hoist
// it to edx: mov edx,[esp+8] plus push edx, 25B).
// Evidence: unlock lane; string LivingWorldBuildingID only referenced here;
// callers at 0x002980AB 0x002BC6AD 0x002D9E36 0x003F3DC0; virtual slot 37.
class Rva004E075FObj
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual int v37(const char *, int, int);
};
int Rva004E075FGet(Rva004E075FObj *o, int a)
{
	return o->v37("LivingWorldBuildingID", a, 4);
}

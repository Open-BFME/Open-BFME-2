// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva000685E2Reset@@YAXXZ @0x000685E2 272B
// Bulk DX8 texture-stage + render-state reset. Retail is 4x
// Set_DX8_Texture_Stage_State, 2x direct SetTextureStageState slot
// 0x114 with counter bumps, 6x wrapper, 2x direct, 2x wrapper, 3x
// Set_DX8_Render_State. Evidence: unlock lane; callees rowed
// 0x000661DD 0x0006615F; data VAs 0x009EDA34 0x009EDA98 0x009EDA68
// with extern names in use; neighbours Disp32DwordClearers2.cpp and
// Rva000687B8.cpp share // cl: /O1; no args ret (free func).
typedef long HRESULT;
struct IDirect3DDevice8
{
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
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void v68();
	virtual HRESULT __stdcall SetTextureStageState(unsigned stage, unsigned long state, unsigned value);
};
class DX8Wrapper
{
public:
	static void Set_DX8_Texture_Stage_State(unsigned stage, unsigned long state, unsigned value);
	static void Set_DX8_Render_State(unsigned long state, unsigned value);
	static IDirect3DDevice8 *D3DDevice;
};
extern unsigned int number_of_DX8_calls;
extern unsigned int g_d3dCallCount;
void __cdecl Rva000685E2Reset()
{
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 2, 2);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 3, 0);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 1, 4);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 4, 1);
	DX8Wrapper::D3DDevice->SetTextureStageState(0, 1, 1);
	number_of_DX8_calls++;
	g_d3dCallCount++;
	DX8Wrapper::D3DDevice->SetTextureStageState(0, 2, 1);
	number_of_DX8_calls++;
	g_d3dCallCount++;
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 11, 0);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 24, 0);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 2, 2);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 3, 0);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 1, 4);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 4, 1);
	DX8Wrapper::D3DDevice->SetTextureStageState(1, 1, 1);
	number_of_DX8_calls++;
	g_d3dCallCount++;
	DX8Wrapper::D3DDevice->SetTextureStageState(1, 2, 1);
	number_of_DX8_calls++;
	g_d3dCallCount++;
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 11, 1);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 24, 0);
	DX8Wrapper::Set_DX8_Render_State(27, 0);
	DX8Wrapper::Set_DX8_Render_State(19, 5);
	DX8Wrapper::Set_DX8_Render_State(20, 6);
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_d3dCallCount@@3IA=?texture_stage_state_changes@DX8Wrapper@@1IA")

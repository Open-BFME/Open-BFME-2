// cl: /O2 /DNDEBUG /MD
//
// statistics.cpp: Debug_Statistics bodies retail links from this TU (tu_map
// approved), folded from five split units with these exact flags, in retail
// order: texture mode, last-frame texture getters, texture string, then
// Begin_Statistics and End_Statistics.
//
//
// Debug_Statistics::Record_Texture_Mode / Get_Record_Texture_Mode,
// retail 0x00129470 (10B) and 0x00129480 (6B).

namespace Debug_Statistics
{
	enum RecordTextureMode
	{
		RECORD_TEXTURE_NONE,
		RECORD_TEXTURE_SIMPLE,
		RECORD_TEXTURE_DETAILS
	};

	void Record_Texture_Mode(RecordTextureMode mode);
	RecordTextureMode Get_Record_Texture_Mode();
}

Debug_Statistics::RecordTextureMode record_texture_mode;

void Debug_Statistics::Record_Texture_Mode(RecordTextureMode mode)
{
	record_texture_mode = mode;
}

Debug_Statistics::RecordTextureMode Debug_Statistics::Get_Record_Texture_Mode()
{
	return record_texture_mode;
}

//
// Debug_Statistics last-frame texture getters. Each is `mov eax, [last]; ret`.

int last_frame_texture_memory;
int last_frame_texture_count;
int last_frame_texture_change_count;
int last_frame_lightmap_texture_memory;
int last_frame_lightmap_texture_count;
int last_frame_procedural_texture_memory;
int last_frame_procedural_texture_count;

namespace Debug_Statistics
{
	int Get_Record_Texture_Size();
	int Get_Record_Texture_Count();
	int Get_Record_Texture_Change_Count();
	int Get_Record_Lightmap_Texture_Size();
	int Get_Record_Lightmap_Texture_Count();
	int Get_Record_Procedural_Texture_Size();
	int Get_Record_Procedural_Texture_Count();
}

int Debug_Statistics::Get_Record_Texture_Size()
{
	return last_frame_texture_memory;
}

int Debug_Statistics::Get_Record_Texture_Count()
{
	return last_frame_texture_count;
}

int Debug_Statistics::Get_Record_Texture_Change_Count()
{
	return last_frame_texture_change_count;
}

int Debug_Statistics::Get_Record_Lightmap_Texture_Size()
{
	return last_frame_lightmap_texture_memory;
}

int Debug_Statistics::Get_Record_Lightmap_Texture_Count()
{
	return last_frame_lightmap_texture_count;
}

int Debug_Statistics::Get_Record_Procedural_Texture_Size()
{
	return last_frame_procedural_texture_memory;
}

int Debug_Statistics::Get_Record_Procedural_Texture_Count()
{
	return last_frame_procedural_texture_count;
}

//
// Debug_Statistics::Get_Record_Texture_String, retail 0x00129500, 6 bytes.
// Returns the address of the statistics string object.

class StringClass
{
};

StringClass texture_statistics_string;

namespace Debug_Statistics
{
	const StringClass &Get_Record_Texture_String();
}

const StringClass &Debug_Statistics::Get_Record_Texture_String()
{
	return texture_statistics_string;
}

//
// Debug_Statistics::Begin_Statistics, retail 0x0012A400, 67 bytes. Eleven
// dword counters zeroed, then two helpers. /O2 tail-jumps the second.

int g_stat0;
int g_stat1;
int g_stat2;
int g_stat3;
int g_stat4;
int g_stat5;
int g_stat6;
int g_stat7;
int g_stat8;
int g_stat9;
int g_stat10;

void Record_Texture_Begin();

class DX8Wrapper
{
public:
	static void Begin_Statistics();
	static void End_Statistics();
};

namespace Debug_Statistics
{
	void Begin_Statistics();
}

void Debug_Statistics::Begin_Statistics()
{
	g_stat0 = 0;
	g_stat1 = 0;
	g_stat2 = 0;
	g_stat3 = 0;
	g_stat4 = 0;
	g_stat5 = 0;
	g_stat6 = 0;
	g_stat7 = 0;
	g_stat8 = 0;
	g_stat9 = 0;
	g_stat10 = 0;
	Record_Texture_Begin();
	DX8Wrapper::Begin_Statistics();
}

//
// Debug_Statistics::End_Statistics, retail 0x0012A450, 122 bytes. Snapshot
// last-frame counters then tail-jump DX8Wrapper::End_Statistics.


int g_last0;
int g_last1;
int g_last2;
int g_last3;
int g_last4;
int g_last5;
int g_last6;
int g_last7;
int g_last8;
int g_last9;

void Record_Texture_End();

namespace Debug_Statistics
{
	void End_Statistics();
}

void Debug_Statistics::End_Statistics()
{
	Record_Texture_End();
	g_last2 = g_stat2;
	g_last3 = g_stat3;
	g_last5 = g_stat5;
	g_last4 = g_stat4;
	g_last0 = g_stat0;
	g_last1 = g_stat1;
	g_last6 = g_stat6;
	g_last7 = g_stat7;
	g_last8 = g_stat8;
	g_last9 = g_stat9;
	DX8Wrapper::End_Statistics();
}

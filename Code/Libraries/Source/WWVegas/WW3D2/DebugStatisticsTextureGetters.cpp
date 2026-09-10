// cl: /O2 /DNDEBUG /MD
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

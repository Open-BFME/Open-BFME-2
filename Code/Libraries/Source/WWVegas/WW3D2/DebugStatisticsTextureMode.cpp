// cl: /O2 /DNDEBUG /MD
//
// Debug_Statistics::Record_Texture_Mode / Get_Record_Texture_Mode,
// retail 0x00129474 (10B) and 0x00129480 (6B).

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

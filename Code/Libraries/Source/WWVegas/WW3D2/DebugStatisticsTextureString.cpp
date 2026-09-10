// cl: /O2 /DNDEBUG /MD
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

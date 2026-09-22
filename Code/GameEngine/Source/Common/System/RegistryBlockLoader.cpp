// cl: /DNDEBUG /MD

// ?LoadRegistryValues@@YAXXZ, retail 0x0002F840, 300 bytes.
//
// Registry-block file loader behind the ten lazy getters in
// RegistryValueDispatch.cpp. It builds the "<dir>\gi.dat" path from the
// directory global below, reads the whole block, checks the "GI  " magic,
// and feeds each key/value pair to the dispatcher at 0x0002F720. The block
// stays allocated: the dispatcher's globals point into it, so even the
// short-read path keeps it and only closes the file.
//
// The directory global has no owning TU yet (nothing else references it);
// its address is DIR32-masked like the other retail globals here.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Directory prefix the gi.dat path is built from. Written at runtime by
// startup code nobody has converted yet; read here and in no other TU.
extern char g_registryBlockDir[];

void __cdecl Rva0002F720(const char *key, const char *value);

void LoadRegistryValues()
{
	char fileName[512];
	fileName[0] = 0;
	// Hand index-copy, not strcpy: the intrinsic expands to a pointer loop
	// and falls through, while retail is an index loop placed out of line.
	// The backslash append rides inside the guard: when the directory is
	// empty the path is just "gi.dat", which is why retail's je skips the
	// copy, the strlen and the word store together.
	if (g_registryBlockDir[0] != 0)
	{
		int i = 0;
		char c;
		do
		{
			c = g_registryBlockDir[i];
			fileName[i] = c;
			i++;
		} while (c != 0);
		strcat(fileName, "\\");
	}
	strcat(fileName, "gi.dat");
	FILE *file = fopen(fileName, "rt");
	if (file != NULL)
	{
		if (fseek(file, 0, SEEK_END) == 0)
		{
			long size = ftell(file);
			fseek(file, 0, SEEK_SET);
			char *data = (char *)malloc(size);
			if (fread(data, 1, size, file) == (unsigned long)size && *(int *)data == 0x20204947)
			{
				char *ptr = data + 8;
				for (int i = 0; i < *(int *)(data + 4); i++)
				{
					const char *key = ptr;
					while (*ptr != 0)
						ptr++;
					ptr++;
					const char *value = ptr;
					while (*ptr != 0)
						ptr++;
					Rva0002F720(key, value);
					ptr++;
				}
			}
		}
		fclose(file);
	}
}

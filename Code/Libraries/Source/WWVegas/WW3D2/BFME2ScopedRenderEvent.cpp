// cl: /EHsc /MD /arch:SSE /G7

#include <string.h>

void bfmeRva0011F340(const char *text, void *context);

class BFME2ScopedRenderEvent
{
	char Label[256];
	char Group[64];

public:
	BFME2ScopedRenderEvent(const char *label, const char *group, unsigned color);
};

BFME2ScopedRenderEvent::BFME2ScopedRenderEvent(
	const char *label, const char *group, unsigned color)
{
	if (label != 0) {
		strncpy(Label, label, sizeof(Label));
		Label[sizeof(Label) - 1] = 0;

		if (group != 0) {
			strcpy(Group, "SceneAnalyst");
			unsigned length = strlen(Group);
			strncpy(Group + length, group, sizeof(Group) - length);
			Group[sizeof(Group) - 1] = 0;
		} else {
			Group[0] = 0;
		}

		bfmeRva0011F340(Label, (void *)color);
	}
}

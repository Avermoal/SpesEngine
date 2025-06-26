#ifndef INCLUDES_SPES_ENGINE_CORE_EVENTS_DATA_H
#define INCLUDES_SPES_ENGINE_CORE_EVENTS_DATA_H

#include <stdbool.h>

struct EventsData {
	bool* keys;
	unsigned short* frames;
	unsigned short current;
	float deltaX;
	float deltaY;
	float x;
	float y;
	bool cursor_locked;
	bool cursor_started;
};

static struct EventsData eventsData;

#endif//INCLUDES_SPES_ENGINE_CORE_EVENTS_DATA_H

#ifndef INCLUDES_SPES_ENGINE_CORE_EVENTS_DATA_H
#define INCLUDES_SPES_ENGINE_CORE_EVENTS_DATA_H

#include <stdbool.h>

struct EventsData {
	bool* keys_;
	unsigned short* frames_;
	unsigned short current_;
	float deltaX_;
	float deltaY_;
	float x_;
	float y_;
	bool cursor_locked_;
	bool cursor_started_;
};

static struct EventsData eventsData;

#endif//INCLUDES_SPES_ENGINE_CORE_EVENTS_DATA_H
#ifndef INCLUDES_TEST_H
#define INCLUDES_TEST_H

#include <stdio.h>

#ifdef NDEBUG
#define LOG_INFO(...) 
#else
#define LOG_INFO(...) printf(__VA_ARGS__)
#endif



#endif//INCLUDES_TEST_H
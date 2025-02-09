#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#define DEBUG_PRINT(x) do { printf x; } while (0)
#else
#define DEBUG_PRINT(x) do {} while (0)
#endif

#endif
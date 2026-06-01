#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
	const char *name;
	const char *character;
	const char *colour;
} ConfigParam;


extern ConfigParam ilc_parameters[];
extern const size_t ilc_parameters_count;
#endif

char* ilc_hello_world();

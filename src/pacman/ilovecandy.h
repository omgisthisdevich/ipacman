#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
	const char *character;
	const char *colour;
} ProgressBar;

typedef struct {
	ProgressBar todo;
	ProgressBar done;
	ProgressBar pacman_C;
	ProgressBar pacman_c;
} ilc_Config;

extern ilc_Config ilc_parameters;
#endif

int read_config_file();

#include <stdio.h>
#include <pwd.h>

#include "yyjson.h"

#include "ilovecandy.h"

ilc_Config ilc_parameters = {
	.todo = {},
	.done = {},
	.pacman_C = {},
	.pacman_c = {}
};
//const size_t ilc_parameters_count =sizeof(ilc_pailc_parameters)/sizeof(ilc_pailc_parameters[0]);


int read_config_file(){
	char config_path[256];

	struct passwd *pw = getpwnam(getenv("SUDO_USER")); /* Need a check */

	snprintf(config_path, sizeof(config_path), "%s/.config/ipacman/ipacman.jsonc", pw->pw_dir);

	yyjson_read_err err;
    yyjson_read_flag flags = YYJSON_READ_ALLOW_COMMENTS | YYJSON_READ_ALLOW_TRAILING_COMMAS;

	yyjson_doc *doc = yyjson_read_file(config_path, flags, NULL, &err);

	if (!doc){
		fprintf(stderr, "ipacman config read error: %s, code %u", err.msg, err.code);
	return(-1);
	}
	yyjson_val *root= yyjson_doc_get_root(doc);

	/*
	for (int i=0 ; i < 4 ; i++){
		yyjson_val *param_name = yyjson_obj_get(root, ilc_parameters[i].name);
		ilc_parameters[i].character = yyjson_get_str(yyjson_obj_get(param_name,"character"));
		ilc_parameters[i].colour = yyjson_get_str(yyjson_obj_get(param_name, "color"));
	//	printf("%s, %s \n", ilc_parameters[i].character, pailc_parameters[i].colour);
	}
	*/
	yyjson_val *todo = yyjson_obj_get(root, "PROGRESS_BAR_TODO") ;
	ilc_parameters.todo.character = yyjson_get_str(yyjson_obj_get(todo, "character"));

	yyjson_doc_free(doc);

	return 1;
}

//int main(void){
//	read_config_file();
//	return 0;
//}


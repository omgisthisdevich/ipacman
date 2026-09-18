#include <stdio.h>
#include <pwd.h>

#include "yyjson.h"

#include "ilovecandy.h"

ilc_Config ilc_parameters = {
	.todo = 		{ .key = "PROGRESS_BAR_TODO" },
	.done = 		{ .key = "PROGRESS_BAR_DONE" },
	.pacman_C =		{ .key = "PACMAN_C" },
	.pacman_c = 		{ .key = "PACMAN_NOM" }
};


int read_config_file(){
	char config_path[256];

	const char *sudo_user = getenv("SUDO_USER");
	if (!sudo_user) return(-1);

	struct passwd *pw = getpwnam(sudo_user);
	if (!pw) return(-1);

	snprintf(config_path, sizeof(config_path), "%s/.config/ipacman/ipacman.jsonc", pw->pw_dir);

	yyjson_read_err err;
	yyjson_read_flag flags = YYJSON_READ_ALLOW_COMMENTS | YYJSON_READ_ALLOW_TRAILING_COMMAS;

	yyjson_doc *doc = yyjson_read_file(config_path, flags, NULL, &err);

	if (!doc){
		return(-1);
	}
	yyjson_val *root= yyjson_doc_get_root(doc);

	yyjson_val *todo = yyjson_obj_get(root, ilc_parameters.todo.key) ;
	ilc_parameters.todo.character = yyjson_get_str(yyjson_obj_get(todo, "character"));
	ilc_parameters.todo.colour = yyjson_get_str(yyjson_obj_get(todo, "color"));

	yyjson_val *done = yyjson_obj_get(root, ilc_parameters.done.key) ;
	ilc_parameters.done.character = yyjson_get_str(yyjson_obj_get(done, "character"));
	ilc_parameters.done.colour = yyjson_get_str(yyjson_obj_get(done, "color"));

	yyjson_val *pacman_C = yyjson_obj_get(root, ilc_parameters.pacman_C.key) ;
	ilc_parameters.pacman_C.character = yyjson_get_str(yyjson_obj_get(pacman_C, "character"));
	ilc_parameters.pacman_C.colour = yyjson_get_str(yyjson_obj_get(pacman_C, "color"));

	yyjson_val *pacman_c = yyjson_obj_get(root, ilc_parameters.pacman_c.key) ;
	ilc_parameters.pacman_c.character = yyjson_get_str(yyjson_obj_get(pacman_c, "character"));
	ilc_parameters.pacman_c.colour = yyjson_get_str(yyjson_obj_get(pacman_c, "color"));


	yyjson_doc_free(doc);

	return 1;
}


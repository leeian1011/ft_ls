#include "../../include/ft_ls.h"

static struct option long_opts[] = {
	{"help", no_argument, NULL, 255},
	{NULL, 0, NULL, 0}
};

uint8_t ident_to_optbit(char ident) {
	switch (ident) {
		case OPT_RECURSIVE_IDENT:
			return OPT_RECURSIVE;
		case OPT_REVERSE_IDENT:
			return OPT_REVERSE;
		case OPT_ALL_INFO_IDENT:
			return OPT_ALL_INFO;
		case OPT_LISTING_IDENT:
			return OPT_LISTING;
		case OPT_G_LISTING:
			return OPT_G_LISTING;
		case OPT_O_LISTING:
			return OPT_O_LISTING;
		case OPT_TIME_ORDERED_IDENT:
			return OPT_TIME_ORDERED;
		case OPT_DIRECTORIES_ONLY_IDENT:
			return OPT_DIRECTORIES_ONLY;
		default:
			// this control flow path should not be reachable.
			return 0;
	}
}

t_arguments parse_arguments(int argc, char *const *argv) {
	t_arguments args = {
		0,
		NULL,
		true
	};
	
	if (argc == 1) return args;

	t_opt opts = 0;
	while ((opts = getopt_long(argc, argv, OPT_IDENTS, long_opts, NULL)) != -1) {
		output_opterr(opts);
		args.options |= ident_to_optbit(opts);
	}

	char cwd[PATH_MAX];
	void *_ = getcwd(cwd, PATH_MAX); (void)_;
	size_t cwd_len = strlen(cwd);
	t_llist *non_dir = NULL;

	for (int i = optind; i < argc; i++) {
		if (args.options & OPT_PASSED_PATH) {
			args.options |= OPT_MULTI_PP;
		}
		
		BUILD_RESET(!strncmp(argv[i], "/", 1), cwd, argv[i], cwd_len, {
			DIR* dir = opendir(cwd);
			if (!dir) {
				if (handle_errno_parsing(argv[i], &non_dir)) {
					llist_append(&args.dirs, argv[i]);
				}
			} else {
				llist_append(&args.dirs, argv[i]);
				args.options |= OPT_PASSED_PATH;
				closedir(dir);
			}
		});
	}

	output_nondir(non_dir, &args, argc);

	return args;
}

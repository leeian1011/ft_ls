#include "../../include/ft_ls.h"
#include <bits/getopt_core.h>
#include <getopt.h>

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
		NULL
	};
	
	if (argc == 1) return args;
	int opts = 0;
	while ((opts = getopt_long(argc, argv, OPT_IDENTS, long_opts, NULL)) != -1) {
		if (opts == '?') {
			fprintf(stderr, "Try ft_ls --help for more information.\n");
			exit(2);
		} else if (opts == 255) {
			//print help
			printf("Usage: ft_ls [OPTION]... [FILE]...\n"
					"List information about the FILEs (the current directory by default).\n"
					"Sort entries alphabetically if none of -cftuvSUX nor --sort is specified.\n"
					"\nMandatory arguments to long options are mandatory for short options too.\n"
				  );
			exit(0);
		}
		args.options |= ident_to_optbit(opts);
	}

	for (int i = optind; i < argc; i++) {
		llist_append(&args.dirs, argv[i]);
	}

	return args;
}

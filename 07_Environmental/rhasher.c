#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>

#include <rhash.h>

#ifdef USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

size_t general_getline(char** cmd) {
#ifdef USE_READLINE
    free(*cmd);

    char* hint;
    if (isatty(STDIN_FILENO)) {
    	hint = "$ ";
    	rl_outstream = stdout;
    } else {
    	hint = NULL;
    	rl_outstream = stderr;
    }

    *cmd = readline(hint);
	if (*cmd == NULL) return 0;

    add_history(*cmd);
    return strlen(*cmd);
#else
	size_t n;
	return getline(cmd, &n, stdin);
#endif
}

int calculate_hash(const char* message, char* output, int algo, int base) {
	char digest[64];

	int res;
	if (message[0] == '"') {
        message += 1;  /* Ignore first character */
		res = rhash_msg(algo, message, strlen(message), digest);
		if (res < 0) {
			fprintf(stderr, "Error: cannot calculate hash\n");
			return res;
		}

	} else { /* Treat message as file path */
		res = rhash_file(algo, message, digest);
		if (res < 0) {
			fprintf(stderr, "Error: %s\n", strerror(errno));
			return res;
		}
	}

	rhash_print_bytes(output, digest, rhash_get_digest_size(algo), base);
	return 0;
}

int main() {
	rhash_library_init();

	char* cmd = NULL;
	ssize_t cmd_len;
	char output[130];	
	while ((cmd_len = general_getline(&cmd)) > 1) {
		const char* algo_name = strtok(cmd, " ");
		
		/* Get algo id */
		int algo;
		if (strcasecmp(algo_name, "md5") == 0) {
			algo = RHASH_MD5;
		} else if (strcasecmp(algo_name, "sha1") == 0) {
			algo = RHASH_SHA1;
		} else if (strcasecmp(algo_name, "tth") == 0) {
			algo = RHASH_TTH;
		} else {
			printf("Error: Unsupported hash algorithm.\n");
			continue;
		}
		
		/* Get output base 0x or Base */
		int output_base;	
		if (isupper(algo_name[0])) {
			output_base = RHPR_HEX;
		} else {
	 		output_base = RHPR_BASE64;
		}

		char* message = strtok(NULL, " ");
		size_t message_len = strlen(message);
		if (message[message_len - 1] == '\n') {
			message[message_len - 1] = '\0';
		}
		int hash_res = calculate_hash(message, output, algo, output_base);
		if (hash_res < 0) {
			continue;
		} else {
			printf("%s\n", output);
		}
	}
	free(cmd);
}

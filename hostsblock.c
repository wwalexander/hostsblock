#include <ctype.h>
#include <stdio.h>
#include <string.h>

/* Length limit for domain names is 253 characters */
#define MAX_DOMAIN_LENGTH 254
#define MAX_DOMAIN_RULE_LENGTH MAX_DOMAIN_LENGTH + 3

enum state {
	INIT,
	FIRST_BAR,
	SECOND_BAR,
	DOMAIN_ALNUM,
	DOMAIN_HYPHEN,
	DOMAIN_PERIOD,
	DELIM
};

int get_domain(char *rule, char *domain)
{
	enum state state = INIT;
	int i = 0;

	do {
		switch (state) {
		case INIT:
			if (*rule == '|') {
				state = FIRST_BAR;
			} else {
				return 1;
			}
			break;
		case FIRST_BAR:
			if (*rule == '|') {
				state = SECOND_BAR;
			} else {
				return 1;
			}
			break;
		case SECOND_BAR:
			if (isalnum(*rule)) {
				domain[i] = *rule;
				++i;
				state = DOMAIN_ALNUM;
			} else {
				return 1;
			}
			break;
		case DOMAIN_ALNUM:
			if (isalnum(*rule)) {
				domain[i] = *rule;	
				i++;
				state = DOMAIN_ALNUM;
				break;
			}
			switch (*rule) {
			case '-':
				domain[i] = *rule;
				i++;
				state = DOMAIN_HYPHEN;
				break;
			case '.':
				domain[i] = *rule;
				i++;
				state = DOMAIN_PERIOD;
				break;
			case '|':
			case '^':
				state = DELIM;
				break;
			default:
				return 1;
			}
			break;
		case DOMAIN_HYPHEN:
			if (isalnum(*rule)) {
				domain[i] = *rule;
				++i;
				state = DOMAIN_ALNUM;
				break;
			}
			if (*rule == '-') {
				domain[i] = *rule;
				i++;
				state = DOMAIN_HYPHEN;
			} else {
				return 1;
			}
			break;
		case DOMAIN_PERIOD:
			if (isalnum(*rule)) {
				domain[i] = *rule;
				i++;
				state = DOMAIN_ALNUM;
			} else {
				return 1;
			}
			break;
		case DELIM:
			if (*rule == '\n') {
				domain[i] = '\0';
				return 0;
			} else {
				return 1;
			}
		}
	} while (++rule && i < MAX_DOMAIN_LENGTH);

	return 1;
}

int main(int argc, char **argv)
{
	FILE *list;
	char rule[MAX_DOMAIN_RULE_LENGTH];
	char domain[MAX_DOMAIN_LENGTH] = { 0 };

	if (argc > 2) {
		fputs("usage: hostsblock file\n", stderr);
		return 1;
	}
	
	if (argc < 2 || !strncmp(argv[1], "-", 2)) list = stdin;
	else list = fopen(argv[1], "r");

	if (list == NULL) {
		perror("error opening filter list");
		return 1;
	}

	while (1) {
		char *c = fgets(rule, MAX_DOMAIN_RULE_LENGTH, list);
		if (c == NULL || feof(list) || ferror(list)) break;

		if (!get_domain(rule, domain)) {
			printf("0\t%s\n", domain);
		}
	}

	if (ferror(list)) {
		perror("error reading filter list");
		return 1;
	}

	return 0;
}

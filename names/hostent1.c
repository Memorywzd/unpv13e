#include	"unp.h"

int
main(int argc, char **argv)
{
	char			*ptr, **pptr;
	char			str[INET_ADDRSTRLEN];
	struct hostent	*hptr;
	struct hostent	*hptr0;

	while (--argc > 0) {
		ptr = *++argv;
		if ( (hptr = gethostbyname(ptr)) == NULL) {
			err_msg("gethostbyname error for host: %s: %s",
					ptr, hstrerror(h_errno));
			continue;
		}
		printf("official hostname: %s\n", hptr->h_name);

		for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
			printf("\talias: %s\n", *pptr);

		switch (hptr->h_addrtype) {
		case AF_INET:
			pptr = hptr->h_addr_list;
			for ( ; *pptr != NULL; pptr++) {
				printf("\taddress: %s\n",
					Inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
				if ( ((hptr0 = gethostbyaddr(*pptr, hptr->h_length, hptr->h_addrtype)) != NULL))
					printf("\t\tgethostbyaddr: %s\n", hptr0->h_name);
				else if (h_errno == HOST_NOT_FOUND)
					printf("\t\t(no hostname returned by gethostbyaddr)\n");
				else
					printf("\t\terror: %s\n", hstrerror(h_errno));
			}
				
			break;

		default:
			err_ret("unknown address type");
			break;
		}
	}
	exit(0);
}

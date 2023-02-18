/*
 * Pico NetLink Link Message Test
 *
 * Copyright (c) 2016-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdio.h>

#include <pnl/message/addr.h>
#include <pnl/message/link.h>
#include <pnl/socket.h>

#define NLM_F_UPDATE  (NLM_F_REQUEST | NLM_F_CREATE | NLM_F_REPLACE)

int main (int argc, char *argv[])
{
	int s;
	uint32_t buf[32], max = sizeof (buf);
	struct nlm *o;
	char addr[] = {10, 0, 128, 1,  10, 0, 128, 255,
		       10, 0, 129, 1,  10, 0, 129, 254};

	if ((s = nls_open (NETLINK_ROUTE)) == -1)
		goto no_sock;

	o = nlm_start (buf, max, RTM_SETLINK, NLM_F_REQUEST, 0, 0);

	nlm_add_link       (o, max, 0, 2);
	nlm_add_link_mtu   (o, max, 8008);
	nlm_add_link_alias (o, max, "Test Link #2");

	if (!nlm_fit (o, max)) {
		errno = EOVERFLOW;
		goto no_act;
	}

	if (nls_send (s, o, 0) == -1)
		goto no_act;

	o = nlm_start (buf, max, RTM_NEWADDR, NLM_F_UPDATE, 0, 0);

	nlm_add_addr		(o, max, AF_INET, 24, 200, 2);
	nlm_add_addr_local	(o, max, addr + 0, 4);
	nlm_add_addr_broadcast	(o, max, addr + 4, 4);

	if (nls_send (s, o, 0) == -1)
		goto no_act;

	o = nlm_start (buf, max, RTM_NEWADDR, NLM_F_UPDATE, 0, 0);

	nlm_add_addr		(o, max, AF_INET, 24, 200, 2);
	nlm_add_addr_local	(o, max, addr +  8, 4);
	nlm_add_addr_broadcast	(o, max, addr + 12, 4);

	if (nls_send (s, o, 0) == -1)
		goto no_act;

	nls_close (s);
	return 0;
no_act:
	nls_close (s);
no_sock:
	perror ("nlm-link");
	return 1;
}

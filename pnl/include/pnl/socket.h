/*
 * Pico NetLink Socket
 *
 * Copyright (c) 2016-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef PNL_SOCKET_H
#define PNL_SOCKET_H  1

#include <sys/socket.h>
#include <unistd.h>

#include <pnl/message.h>

static inline int nls_open (int proto)
{
	return socket (AF_NETLINK, SOCK_DGRAM, proto);
}

static inline int nls_close (int s)
{
	return close (s);
}

static inline ssize_t nls_send (int s, const struct nlm *o, int flags)
{
	return send (s, o, o->len, flags);
}

#endif  /* PNL_SOCKET_H */

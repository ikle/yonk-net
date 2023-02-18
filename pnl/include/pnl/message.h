/*
 * Pico NetLink Message
 *
 * Copyright (c) 2016-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef PNL_MESSAGE_H
#define PNL_MESSAGE_H  1

#include <stdint.h>

struct nlm {
	uint32_t len;
	uint16_t type;
	uint16_t flags;
	uint32_t seq;
	uint32_t pid;
};

#define nlm_align(len)	(((len) + 3u) & ~3u)
#define nlm_hdrlen	((uint32_t) nlm_align (sizeof (struct nlm)))

static inline uint32_t nlm_len (uint32_t len)
{
	return nlm_hdrlen + len;
}

static inline void *nlm_data (struct nlm *o)
{
	return (void *)(o) + nlm_hdrlen;
}

static inline uint32_t nlm_payload (struct nlm *o, uint32_t prefix)
{
	return o->len - nlm_align (nlm_len (prefix));
}

static inline void *nlm_tail (struct nlm *o)
{
	return (void *)(o) + nlm_align (o->len);
}

static inline int nlm_fit (struct nlm *o, uint32_t max)
{
	return o->len <= max;
}

#endif  /* PNL_MESSAGE_H */

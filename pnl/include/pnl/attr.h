/*
 * Pico NetLink Attribute
 *
 * Copyright (c) 2016-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef PNL_ATTR_H
#define PNL_ATTR_H  1

#include <stdint.h>

struct nla {
	uint16_t len;
	uint16_t type;
};

#define nla_align(len)	(((len) + 3u) & ~3u)
#define nla_hdrlen	((uint16_t) nla_align (sizeof (struct nla)))

static inline uint16_t nla_len (uint16_t len)
{
	return nla_hdrlen + len;
}

static inline void *nla_data (struct nla *o)
{
	return (void *)(o) + nla_hdrlen;
}

static inline uint16_t nla_payload (struct nla *o)
{
	return o->len - nla_hdrlen;
}

#endif  /* PNL_ATTR_H */

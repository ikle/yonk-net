/*
 * Pico NetLink Message Generator
 *
 * Copyright (c) 2016-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef PNL_MESSAGE_GEN_H
#define PNL_MESSAGE_GEN_H  1

#include <string.h>

#include <pnl/attr.h>
#include <pnl/message.h>

static inline struct nlm *
nlm_start (uint32_t *buf, uint32_t max, int type, int flags, int seq, int pid)
{
	struct nlm *o = (void *) buf;

	if (max < nlm_hdrlen)
		return NULL;

	o->len   = nlm_hdrlen;
	o->type  = type;
	o->flags = flags;
	o->seq   = seq;
	o->pid   = pid;
	return o;
}

void *nlm_add (struct nlm *o, uint32_t max, uint32_t len);

void nlm_add_attr (struct nlm *o, uint32_t max, int type,
		   const void *data, uint16_t size);

static inline void nlm_add_flag (struct nlm *o, uint32_t max, int type)
{
	nlm_add_attr (o, max, type, NULL, 0);
}

static inline
void nlm_add_u8 (struct nlm *o, uint32_t max, int type, uint8_t v)
{
	nlm_add_attr (o, max, type, &v, sizeof (v));
}

static inline
void nlm_add_u16 (struct nlm *o, uint32_t max, int type, uint16_t v)
{
	nlm_add_attr (o, max, type, &v, sizeof (v));
}

static inline
void nlm_add_u32 (struct nlm *o, uint32_t max, int type, uint32_t v)
{
	nlm_add_attr (o, max, type, &v, sizeof (v));
}

static inline
void nlm_add_u64 (struct nlm *o, uint32_t max, int type, uint64_t v)
{
	nlm_add_attr (o, max, type, &v, sizeof (v));
}

static inline
void nlm_add_string (struct nlm *o, uint32_t max, int type, const char *s)
{
	nlm_add_attr (o, max, type, s, strlen (s) + 1);
}

static inline struct nla *nlm_open_group (struct nlm *o, uint32_t max, int type)
{
	struct nla *group = nlm_tail (o);

	nlm_add_attr (o, max, type, NULL, 0);
	return group;
}

static inline
void nlm_close_group (struct nlm *o, uint32_t max, struct nla *group)
{
	const size_t head = (void *) group - (void *) o;

	if (nlm_fit (o, max))
		group->len = o->len - head;
}

#endif  /* PNL_MESSAGE_GEN_H */

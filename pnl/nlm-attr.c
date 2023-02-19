/*
 * Pico NetLink Message Attributes
 *
 * Copyright (c) 2016-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdint.h>

#include <pnl/writer.h>

void nlm_add_attr (struct nlm *o, uint32_t max, int type,
		   const void *data, uint16_t size)
{
	const uint32_t len   = nla_len (size);
	const uint32_t space = nlm_align (len);
	const uint32_t end   = nlm_align (o->len) + space;
	struct nla *a = nlm_tail (o);

	if (end <= max) {
		a->len  = len;
		a->type = type;

		memcpy (nla_data (a), data, size);
		memset (nlm_tail (o) + len, 0, space - len);
	}

	o->len = end;
}

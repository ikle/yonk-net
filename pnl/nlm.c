/*
 * Pico NetLink Message
 *
 * Copyright (c) 2016-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdint.h>
#include <string.h>

#include <pnl/message.h>

void *nlm_add (struct nlm *o, uint32_t max, uint32_t len)
{
	const uint32_t space = nlm_align (len);
	const uint32_t end   = nlm_align (o->len) + space;
	void *item = nlm_tail (o);

	if (end <= max)
		memset (nlm_tail (o), 0, space);

	o->len = end;
	return item;
}

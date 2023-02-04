/*
 * AVL Tree: Find High Bound
 *
 * Copyright (c) 2010-2022 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "avl-int.h"

struct avl *avl_find_hi (struct avl **root, const void *key, avl_cmp_cb *cmp)
{
	struct avl *o, *hi;
	int c;

	for (hi = NULL, o = *root; o != NULL; o = o->child[c > 0])
		if ((c = cmp (key, o)) == 0)
			return o;
		else
		if (c < 0)
			hi = o;

	return hi;
}

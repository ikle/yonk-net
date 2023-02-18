/*
 * Pico NetLink Address Message
 *
 * Copyright (c) 2016-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef PNL_NLM_ADDR_H
#define PNL_NLM_ADDR_H  1

#include <linux/if_addr.h>

#include <pnl/message-gen.h>

static inline struct ifaddrmsg *
nlm_add_addr (struct nlm *o, uint32_t max, int family, int prefix, int scope,
	      int link)
{
	struct ifaddrmsg *m = nlm_add (o, max, sizeof (*m));

	if (nlm_fit (o, max)) {
		m->ifa_family    = family;
		m->ifa_prefixlen = prefix;
		m->ifa_scope     = scope;
		m->ifa_index     = link;
	}

	return m;
}

static inline void nlm_add_addr_remote (struct nlm *o, uint32_t max,
					const void *address, uint16_t len)
{
	nlm_add_attr (o, max, IFA_ADDRESS, address, len);
}

static inline void nlm_add_addr_local (struct nlm *o, uint32_t max,
				       const void *address, uint16_t len)
{
	nlm_add_attr (o, max, IFA_LOCAL, address, len);
}

static inline
void nlm_add_addr_label (struct nlm *o, uint32_t max, const char *label)
{
	nlm_add_string (o, max, IFA_LABEL, label);
}

static inline void nlm_add_addr_broadcast (struct nlm *o, uint32_t max,
					   const void *address, uint16_t len)
{
	nlm_add_attr (o, max, IFA_BROADCAST, address, len);
}

static inline void nlm_add_addr_anycast (struct nlm *o, uint32_t max,
					 const void *address, uint16_t len)
{
	nlm_add_attr (o, max, IFA_ANYCAST, address, len);
}

static inline void nlm_add_addr_multicast (struct nlm *o, uint32_t max,
					   const void *address, uint16_t len)
{
	nlm_add_attr (o, max, IFA_MULTICAST, address, len);
}

static inline
void nlm_add_addr_flags (struct nlm *o, uint32_t max, int flags)
{
	nlm_add_u32 (o, max, IFA_FLAGS, flags);
}

#endif  /* PNL_NLM_ADDR_H */

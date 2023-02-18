/*
 * Pico NetLink Link Message
 *
 * Copyright (c) 2016-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef PNL_NLM_LINK_H
#define PNL_NLM_LINK_H  1

#include <linux/if_link.h>
#include <linux/rtnetlink.h>

#include <pnl/message-gen.h>

static inline struct ifinfomsg *
nlm_add_link (struct nlm *o, uint32_t max, int type, int index)
{
	struct ifinfomsg *m = nlm_add (o, max, sizeof (*m));

	if (nlm_fit (o, max)) {
		m->ifi_type  = type;
		m->ifi_index = index;
	}

	return m;
}

static inline void nlm_add_link_address (struct nlm *o, uint32_t max,
					 const void *address, uint16_t len)
{
	nlm_add_attr (o, max, IFLA_ADDRESS, address, len);
}

static inline void nlm_add_link_broadcast (struct nlm *o, uint32_t max,
					   const void *address, uint16_t len)
{
	nlm_add_attr (o, max, IFLA_BROADCAST, address, len);
}

static inline
void nlm_add_link_name (struct nlm *o, uint32_t max, const char *name)
{
	nlm_add_string (o, max, IFLA_IFNAME, name);
}

static inline void nlm_add_link_mtu (struct nlm *o, uint32_t max, int mtu)
{
	nlm_add_u32 (o, max, IFLA_MTU, mtu);
}

static inline void nlm_add_link_ref (struct nlm *o, uint32_t max, int link)
{
	nlm_add_u32 (o, max, IFLA_LINK, link);
}

static inline void nlm_add_link_master (struct nlm *o, uint32_t max, int master)
{
	nlm_add_u32 (o, max, IFLA_MASTER, master);
}

static inline struct nla *nlm_open_proto (struct nlm *o, uint32_t max)
{
	return nlm_open_group (o, max, IFLA_PROTINFO | NLA_F_NESTED);
}

static inline void nlm_add_link_qlen (struct nlm *o, uint32_t max, int qlen)
{
	nlm_add_u32 (o, max, IFLA_TXQLEN, qlen);
}

static inline
void nlm_add_link_alias (struct nlm *o, uint32_t max, const char *alias)
{
	if (alias == NULL)
		nlm_add_flag (o, max, IFLA_IFALIAS);
	else
		nlm_add_string (o, max, IFLA_IFALIAS, alias);
}

static inline void nlm_add_link_group (struct nlm *o, uint32_t max, int group)
{
	nlm_add_u32 (o, max, IFLA_GROUP, group);
}

#endif  /* PNL_NLM_LINK_H */

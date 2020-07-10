/* iksemel (XML parser for Jabber)
** Copyright (C) 2009 Gurer Ozen
** This code is free software; you can redistribute it and/or
** modify it under the terms of GNU Lesser General Public License.
*/

#include "common.h"
#include "iksemel.h"

#ifdef HAVE_GNUTLS

#include <gnutls/gnutls.h>

/* issues here:
** 1. handle GNUTLS_E_AGAIN in handshake
** 2. eol condition in tls_recv needs examination
** 5. access to gnutls settings? how to do that portably?
*/

struct ikstls_data {
	gnutls_session sess;
	gnutls_certificate_credentials cred;
	ikstransport *trans;
	void *sock;
	int timeout;
};

static size_t
tls_push (struct ikstls_data *data, const char *buffer, size_t len)
{
	int ret;

	ret = data->trans->send (data->sock, buffer, len);
	if (ret) return (size_t) -1;
	return len;
}

static size_t
tls_pull (struct ikstls_data *data, char *buffer, size_t len)
{
	int ret;

	ret = data->trans->recv (data->sock, buffer, len, data->timeout);
	if (ret == -1) return (size_t) -1;
	return ret;
}

static int
tls_handshake (struct ikstls_data **datap, ikstransport *trans, void *sock)
{

	/* Section Upgrading to 3.4.x from 3.3.x from https://www.gnutls.org/manual/html_node/Upgrading-from-previous-versions.html */
	#if defined(GNUTLS_VERSION_NUMBER) && \
	    GNUTLS_VERSION_NUMBER >= 0x020200 /* 2.2.0 */
		/* This type of priority setting scheme comes with 2.2.0 version. */
		char *priority="NORMAL:+VERS-SSL3.0:+VERS-TLS1.0:+VERS-TLS1.1:+VERS-TLS1.2:+VERS-TLS1.3RSA:+MD5:+SHA1:+COMP-NULL:+COMP-ZLIB:+3DES-CBC:+ARCFOUR-128";
		/*
			Available SSL versions:
				* VERS-SSL3.0,
			Available TLS versions:
				* VERS-TLS1.0,
				* VERS-TLS1.1,
				* VERS-TLS1.2,
				* VERS-TLS1.3,
			Availability For Key eXchange:
				* RSA
			Availability For MAC:
				* MD5
				* SHA1
			Availability For compression:
				* COMP-NULL
				* COMP-ZLIB
			Availability For cipher:
			https://gnutls.org/manual/html_node/Encryption-algorithms-used-in-the-record-layer.html#tab_003aciphers
				* 3DES-CBC,
				* ARCFOUR-128,
			*/
	#else
	  /* This type of priority setting scheme become legacy with 3.4.0 version. */
		const int protocol_priority[] = { GNUTLS_TLS1, GNUTLS_SSL3, 0 };
		const int kx_priority[] = { GNUTLS_KX_RSA, 0 };
		const int cipher_priority[] = { GNUTLS_CIPHER_3DES_CBC, GNUTLS_CIPHER_ARCFOUR, 0};
		const int comp_priority[] = { GNUTLS_COMP_ZLIB, GNUTLS_COMP_NULL, 0 };
		const int mac_priority[] = { GNUTLS_MAC_SHA, GNUTLS_MAC_MD5, 0 };
	#endif
	struct ikstls_data *data;
	int ret;

	*datap = NULL;

	data = iks_malloc (sizeof(*data));
	if (!data) return IKS_NOMEM;
	memset (data, 0, sizeof(*data));
	data->trans = trans;
	data->sock = sock;
	data->timeout = -1;

	if (gnutls_global_init () != 0) {
		iks_free (data);
		return IKS_NOMEM;
	}

	if (gnutls_certificate_allocate_credentials (&data->cred) < 0) {
		iks_free (data);
		return IKS_NOMEM;
	}

	if (gnutls_init (&data->sess, GNUTLS_CLIENT) != 0) {
		gnutls_certificate_free_credentials (data->cred);
		iks_free (data);
		return IKS_NOMEM;
	}

#if defined(GNUTLS_VERSION_NUMBER) && \
    GNUTLS_VERSION_NUMBER >= 0x020200 /* 2.2.0 */
	gnutls_priority_set_direct(data->sess, priority, NULL);

#else
	gnutls_protocol_set_priority (data->sess, protocol_priority);
	gnutls_cipher_set_priority(data->sess, cipher_priority);
	gnutls_compression_set_priority(data->sess, comp_priority);
	gnutls_kx_set_priority(data->sess, kx_priority);
	gnutls_mac_set_priority(data->sess, mac_priority);
#endif

	gnutls_credentials_set (data->sess, GNUTLS_CRD_CERTIFICATE, data->cred);

	gnutls_transport_set_push_function (data->sess, (gnutls_push_func) tls_push);
	gnutls_transport_set_pull_function (data->sess, (gnutls_pull_func) tls_pull);
	gnutls_transport_set_ptr (data->sess, data);

	ret = gnutls_handshake (data->sess);
	if (ret != 0) {
		gnutls_deinit (data->sess);
		gnutls_certificate_free_credentials (data->cred);
		iks_free (data);
		return IKS_NET_TLSFAIL;
	}

	*datap = data;
	return IKS_OK;
}

static int
tls_send (struct ikstls_data *data, const char *buf, size_t size)
{
	if (gnutls_record_send (data->sess, buf, size) < 0)
		return IKS_NET_RWERR;
	return IKS_OK;
}

static int
tls_recv (struct ikstls_data *data, char *buf, size_t size, int timeout)
{
	data->timeout = timeout;
	return gnutls_record_recv (data->sess, buf, size);
}

static void
tls_terminate(struct ikstls_data *data)
{
	gnutls_bye (data->sess, GNUTLS_SHUT_WR);
	gnutls_deinit (data->sess);
	gnutls_certificate_free_credentials (data->cred);
	iks_free (data);
}

ikstls iks_default_tls = {
	tls_handshake,
	tls_send,
	tls_recv,
	tls_terminate
};

#else /* HAVE_GNUTLS */

#ifndef HAVE_OPENSSL
ikstls iks_default_tls = {
	NULL,
	NULL,
	NULL,
	NULL
};
#endif /* HAVE_OPENSSL */

#endif /* HAVE_GNUTLS */

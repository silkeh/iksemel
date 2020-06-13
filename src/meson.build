sources = [
            'ikstack.c',
            'utility.c',
            'iks.c',
            'sax.c',
            'dom.c',
            'io-posix.c',
            'sha.c',
            'md5.c',
            'base64.c',
           ]

gnutls_sources = ['tls-gnutls.c']
openssl_sources = ['tls-openssl.c']

jabber_sources = [
                  'filter.c',
                  'stream.c',
                  'jabber.c',
                 ]

libiksemel = shared_library('iksemel',
                        sources,
                        include_directories : include_dir,
                        install : true)

libiksemel_gnutls = shared_library('iksemel_gnutls',
                        [gnutls_sources],
                        include_directories : include_dir,
                        link_with: libiksemel,
                        dependencies : gnutls_dep,
                        install : true,
                        required: get_option('gnutls'))

libiksemel_openssl = shared_library('iksemel_openssl',
                        openssl_sources,
                        include_directories : include_dir,
                        link_with: libiksemel,
                        dependencies : openssl_dep,
                        install : true,
                        required: get_option('openssl'))



link_jabber = []
dep_jabber = []
src_jabber = [jabber_sources]
if get_option('gnutls').enabled()
  link_jabber += libiksemel_gnutls
  dep_jabber += gnutls_dep
  src_jabber += gnutls_sources
endif
if get_option('openssl').enabled()
  link_jabber += libiksemel_openssl
  dep_jabber += openssl_dep
  src_jabber += openssl_sources
endif

if backends.length() != 0
  libjabber = shared_library('jabber',
                          src_jabber,
                          include_directories : include_dir,
                          dependencies : dep_jabber,
                          link_with : [libiksemel, link_jabber],
                          install : true)
endif

cc = meson.get_compiler('c')

cdata = configuration_data()
cdata.set('version', version)
cdata.set('package_name', package_name)
cdata.set('package_url', package_url)

check_headers = [
  ['HAVE_DLFCN_H', 'dlfcn.h'],
  ['HAVE_ERRNO_H', 'errno.h'],
  ['HAVE_INTTYPES_H', 'inttypes.h'],
  ['HAVE_MEMORY_H', 'memory.h'],
  ['HAVE_STDINT_H', 'stdint.h'],
  ['HAVE_STDLIB_H', 'stdlib.h'],
  ['HAVE_STRINGS_H', 'strings.h'],
  ['HAVE_STRING_H', 'string.h'],
  ['HAVE_SYS_STAT_H', 'sys/stat.h'],
  ['HAVE_SYS_TYPES_H', 'sys/types.h'],
  ['HAVE_UNISTD_H', 'unistd.h'],
]

foreach h : check_headers
  if cc.has_header(h.get(1))
    cdata.set(h.get(0), 1)
  endif
endforeach

check_functions = [
  ['HAVE_GETADDRINFO', 'getaddrinfo', '#include<netdb.h>'],
  ['HAVE_GETOPT_LONG', 'getopt_long', '#include<getopt.h>'],
# check token ['HAVE_GNUTLS']
# check token ['HAVE_LIBWSOCK32']
# check token ['HAVE_OPENSSL']
# check token ['HAVE_STRUCT_STAT_ST_BLKSIZE']
]

foreach f : check_functions
  if cc.has_function(f.get(1), prefix : f.get(2))
    cdata.set(f.get(0), 1)
  endif
endforeach

if cc.has_link_argument('-DHAVE_CONFIG_H')
  cdata.set('HAVE_CONFIG_H', 1)
endif

if cc.has_link_argument('-DSTDC_HEADERS')
  cdata.set('STDC_HEADERS', 1)
endif

backends = []

# *** Checks for GnuTLS     ***
gnutls_dep = dependency('gnutls', version: '>= 3.6.5', required: get_option('gnutls'))

if get_option('gnutls').enabled()
  if gnutls_dep.found()
    backends = ['gnutls']
    cdata.set('HAVE_GNUTLS', 1)
  else
    error('\"gnutls\" feature enabled but not \"gnutls\" installation found on your installation.')
  endif
endif

# *** Checks for OpenSSL    ***
openssl_option = get_option('openssl')
if openssl_option.disabled()
  openssl_dep = []
else
  # XXX: https://github.com/mesonbuild/meson/issues/2945
  openssl_dep = dependency('openssl', required: false)
  if openssl_dep.found()
    backends += ['openssl']
    cdata.set('HAVE_OPENSSL', 1)

  else
    # MSVC builds of OpenSSL does not generate pkg-config files,
    # so we check for it manually here in this case, if we can't find those files
    # Based on the CMake check for OpenSSL in CURL's CMakeLists.txt,
    # on which headers we should check for
    openssl_headers = []
    foreach h : ['crypto.h', 'engine.h', 'err.h', 'pem.h',
                 'rsa.h', 'ssl.h', 'x509.h', 'rand.h', 'tls1.h']
      openssl_headers += 'openssl/' + h
    endforeach

    # OpenSSL 1.1.x and 1.0.x (or earlier) have different .lib names,
    # so we need to look for the correct pair

    # Find either libcrypto.lib (1.1.x) or libeay32.lib (1.0.x or earlier) first
    libcrypto_dep = cc.find_library('crypto', required: false)
    if libcrypto_dep.found()
      libssl = 'ssl'
    else
      libcrypto_dep = cc.find_library('eay32', required: openssl_option)
      libssl = 'ssleay32'
    endif

    if libcrypto_dep.found()
      # Find the corresponding SSL library depending on which crypto .lib we found
      libssl_dep = cc.find_library(libssl, required: openssl_option, has_headers: openssl_headers)
    endif

    if libcrypto_dep.found() and libssl_dep.found()
      openssl_dep = [libcrypto_dep, libssl_dep]
      backends += ['openssl']
      cdata.set('HAVE_OPENSSL', 1)
    endif
  endif
endif

if backends.length() == 0
  warning('No TLS backends enabled. Please enable at least one TLS backend [GnuTLS or OpenSSL] to use Jabber.')
endif

configure_file(input : 'config.h.meson',
  output : 'config.h',
  configuration : cdata)


install_headers([
                 'common.h',
                 'finetune.h',
                 'iksemel.h',
                ]
)

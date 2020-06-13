ikslint_sources = ['ikslint.c', 'hash.c']
iksroster_sources = ['iksroster.c']
iksperf_sources = ['iksperf.c', 'perf.c']

executable('ikslint',
           sources : ikslint_sources,
           include_directories : include_dir,
           link_with : libiksemel)

if backends.length() != 0

  executable('iksroster',
            sources : iksroster_sources,
            include_directories : include_dir,
            dependencies : dep_jabber,
            link_with : [libiksemel, libjabber, link_jabber],
            )
endif


executable('iksperf',
          sources : iksperf_sources,
          include_directories : [include_dir,'.'],
          link_with : libiksemel)

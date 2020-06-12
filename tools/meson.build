ikslint_sources = ['ikslint.c', 'hash.c']
executable('ikslint',
           sources : ikslint_sources,
           include_directories : include_dir,
           link_with : libiksemel)

iksroster_sources = ['iksroster.c']

executable('iksroster',
          sources : iksroster_sources,
          include_directories : include_dir,
          link_with : libiksemel)

iksperf_sources = ['iksperf.c', 'perf.c']

executable('iksperf',
          sources : iksperf_sources,
          include_directories : [include_dir,'.'],
          link_with : libiksemel)

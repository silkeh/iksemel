dom_test = executable('test-dom', 'tst-dom.c',
                     include_directories : include_dir,
                     link_with : libiksemel)

iks_test = executable('test-iks', 'tst-iks.c',
                    include_directories : include_dir,
                    link_with : libiksemel)

ikstack_test = executable('test-ikstack', 'tst-ikstack.c',
                    include_directories : include_dir,
                    link_with : libiksemel)

md5_test = executable('test-md5', 'tst-md5.c',
                    include_directories : include_dir,
                    link_with : libiksemel)

sax_test = executable('test-sax', 'tst-sax.c',
                    include_directories : include_dir,
                    link_with : libiksemel)

sha_test = executable('test-sha', 'tst-sha.c',
                    include_directories : include_dir,
                    link_with : libiksemel)

test('Iksemel Test Suite - DOM Test', dom_test, is_parallel : true)
test('Iksemel Test Suite - IKS Test', iks_test, is_parallel : true)
test('Iksemel Test Suite - IkStack Test', ikstack_test, is_parallel : true)
test('Iksemel Test Suite - MD5 Test', md5_test, is_parallel : true)
test('Iksemel Test Suite - SAX Test', sax_test, is_parallel : true)
test('Iksemel Test Suite - SHA Test', sha_test, is_parallel : true)


if backends.length() != 0
  filter_test = executable('test-filter', 'tst-filter.c',
                      include_directories : include_dir,
                      link_with : [libiksemel, libjabber],)

  jid_test = executable('test-jid', 'tst-jid.c',
                      include_directories : include_dir,
                      link_with : [libiksemel, libjabber],)

  test('Iksemel Test Suite - Filter Test', filter_test, is_parallel : true)

  test('Iksemel Test Suite - JiD Test', jid_test, is_parallel : true)
endif

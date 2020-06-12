envdata = environment()
python_paths = [
                'attributes.py',
                'generate.py',
                'iteration.py',
                'root.py',
                'traverse.py',
                ]

envdata.append('PYTHONPATH', pypathdir)
envdata.append('TESTS_BUILDDIR', meson.current_build_dir())

test('Iksemel Test Suite - Python Tests [attibutes]', python,
  args : [join_paths(meson.current_source_dir(), 'attibutes.py')],
  env : envdata,
  dep : pyiksemel,
  timeout : 90)

test('Iksemel Test Suite - Python Tests [generate]', python,
  args : [join_paths(meson.current_source_dir(), 'generate.py')],
  env : envdata,
  dep : pyiksemel,
  timeout : 90)

test('Iksemel Test Suite - Python Tests [iteration]', python,
  args : [join_paths(meson.current_source_dir(), 'iteration.py')],
  env : envdata,
  dep : pyiksemel,
  timeout : 90)

test('Iksemel Test Suite - Python Tests [root]', python,
  args : [join_paths(meson.current_source_dir(), 'root.py')],
  env : envdata,
  dep : pyiksemel,
  timeout : 90)

test('Iksemel Test Suite - Python Tests [traverse]', python,
  args : [join_paths(meson.current_source_dir(), 'traverse.py')],
  env : envdata,
  dep : pyiksemel,
  timeout : 90)

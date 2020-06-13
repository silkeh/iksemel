project('iksemel','c',
  default_options : ['warning_level=3'])

# Iksemel specific declarations

version = get_option('version')
package_name = get_option('package_name')
package_url = get_option('package_url')
package_bugreport_url =  get_option('package_bugreport_url')

# Add indispensable  subdirectories
include_dir = include_directories('include')

subdir('include')
subdir('src')

# Add Tests
if get_option('tests')
  subdir('test')
endif

# Add Python Bindings
if get_option('with_python')
  py_include_dir = include_directories('python')
  subdir('python')
endif

# Add Tools
if get_option('with_tools')
  subdir('tools')
endif



# Write pkgconfig
pkgconf = configuration_data()

pkgconf.set('prefix', join_paths(get_option('prefix')))
pkgconf.set('exec_prefix', '${prefix}')
pkgconf.set('includedir', join_paths('${prefix}', get_option('includedir')))
pkgconf.set('libdir', join_paths('${prefix}', get_option('libdir')))
pkgconf.set('datarootdir', join_paths('${prefix}', get_option('datadir')))
pkgconf.set('datadir', '${datarootdir}')
pkgconf.set('VERSION', version)

pkg_install_dir = '@0@/pkgconfig'.format(get_option('libdir'))

configure_file(input : 'iksemel.pc.in'.format(version),
  output : 'iksemel-@0@.pc'.format(version),
  configuration : pkgconf,
  install_dir : pkg_install_dir)

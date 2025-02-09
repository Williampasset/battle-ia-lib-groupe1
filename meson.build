project('battle_c_bot', ['c', 'cpp'],
  version: '0.1.0',
)

# Dependencies
battle_c_subproject = subproject('battle_c')
battle_c_dep = battle_c_subproject.get_variable('battle_c_dep')

# Create the executable
executable_sources = ['./src/main.c', './src/radar.c', './src/shoot.c', './src/utils.c', './src/move.c']

include_dir = include_directories('./include')

# Check if debug mode is enabled
debug_mode = get_option('debug')

# Set compiler flags based on debug mode
if debug_mode
  add_project_arguments('-DDEBUG', language: 'c')
  add_project_arguments('-g', language: 'c')
else
  add_project_arguments('-O2', language: 'c')
endif

executable(
  'battle_c_bot',
  executable_sources,
  include_directories: [include_dir],
  dependencies: [battle_c_dep],
)
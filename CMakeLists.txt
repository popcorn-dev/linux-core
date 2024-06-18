add_subdirectory(src)

set(POPCORN_LINUX ON PARENT_SCOPE)
set(POPCORN_LINUX ON)

if   (PRESET_BUILD_EXAMPLE)
    add_subdirectory(example)
endif()
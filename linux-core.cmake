lib_from_repo(klever  popcorn-dev main)
lib_from_repo(popcorn popcorn-dev main)
dep(popcorn)

include_directories(/lib/modules/${CMAKE_HOST_SYSTEM_VERSION}/build/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
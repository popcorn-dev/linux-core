lib_from_repo(klever  gunnerDgd v1-dev)
lib_from_repo(popcorn gunnerDgd v1-dev)
dep(popcorn)

include_directories(/lib/modules/${CMAKE_HOST_SYSTEM_VERSION}/build/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
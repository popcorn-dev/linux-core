if   (NOT DEFINED POPCORN)
    repo (popcorn gunnerDgd v1-dev)
    setup(popcorn)
endif()

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
kernel_feature_source(popcorn example popcorn-linux-core)

add_kernel_source (wqe wqe.c)
add_kernel_feature(wqe example wqe)

kernel_feature_include(popcorn example ${CMAKE_CURRENT_SOURCE_DIR}/../include)
kernel_feature_include(wqe     example ${CMAKE_CURRENT_SOURCE_DIR}/../include)
kernel_feature_include(popcorn example ${ROOT_LIB}/popcorn/include)
kernel_feature_include(wqe     example ${ROOT_LIB}/popcorn/include)
kernel_feature_source (wqe example wqe)
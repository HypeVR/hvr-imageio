include(vcpkg_common_functions)

set(VCPKG_LIBRARY_LINKAGE dynamic)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO HypeVR/hvr-imageio
    REF 0.0.0.2
    SHA512 f3afa62d905a36a5f1d59a0e064a607faaaea062cf3ca8737716e7dbff0841c4b1567ebc4ce69aa566401cf011cf4d4d5e76069859efe38682f2f9fecf853395
    HEAD_REF master
)

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
)

vcpkg_install_cmake()

vcpkg_fixup_cmake_targets(CONFIG_PATH "lib/cmake/hvr-imageio")

vcpkg_copy_pdbs()

file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/include)
file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/share)
file(GLOB EXE ${CURRENT_PACKAGES_DIR}/bin/*.exe)
file(GLOB DEBUG_EXE ${CURRENT_PACKAGES_DIR}/debug/bin/*.exe)
file(COPY ${EXE} DESTINATION ${CURRENT_PACKAGES_DIR}/tools/hvr-imageio/)
file(REMOVE ${EXE})
file(REMOVE ${DEBUG_EXE})

file(COPY ${SOURCE_PATH}/README.md DESTINATION ${CURRENT_PACKAGES_DIR}/share/hvr-imageio/)
file(RENAME ${CURRENT_PACKAGES_DIR}/share/hvr-imageio/README.md ${CURRENT_PACKAGES_DIR}/share/hvr-imageio/copyright)

# build and link the targets
add_library(
    ${PROJECT_NAME}
    SHARED
    "${CMAKE_CURRENT_LIST_DIR}/action.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/driver.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/race_context.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/state.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/lib.cpp"
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    PREFIX ""
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}"
        "${TORCS_BASE}"
        "${TORCS_EXPORTS_INCLUDE_DIR}"
        "${TORCS_LIBS_INCLUDE_DIR}"
        "${TORCS_INTERFACES_INCLUDE_DIR}"
)

target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
    "USE_RANDR_EXT"
    "GL_GLEXT_PROTOTYPES"
    "_DEFAULT_SOURCE"
    "_SVID_SOURCE"
    "_BSD_SOURCE"
    "SHM"
    "HAVE_CONFIG_H"
)

target_link_directories(
    ${PROJECT_NAME}
    PUBLIC
        "${TORCS_EXPORTS_LIB_DIR}"
)

target_link_libraries(
    ${PROJECT_NAME}
    "${OPEN_AL_LIBRARY}"
    "${AL_UTILITY_TOOLKIT_LIBRARY}"
    "${VORBIS_FILE_LIBRARY}"
)


# install the targets
cmake_path(APPEND PROJECT_DRIVER_XML "${CMAKE_CURRENT_LIST_DIR}" "${PROJECT_NAME}.xml")
cmake_path(APPEND PROJECT_DRIVER_LOGO "${TORCS_TEXTURES_DATA_DIR}" "logo.rgb")
cmake_path(APPEND PROJECT_CAR_LOGO "${TORCS_CARS_DATA_DIR}" "acura-nsx-sz" "acura-nsx-sz.rgb")

install(DIRECTORY DESTINATION ${TORCS_DRIVER_LIB_DIR})
install(DIRECTORY DESTINATION ${TORCS_DRIVER_LIB_DIR})

install(TARGETS ${PROJECT_NAME} DESTINATION ${TORCS_DRIVER_LIB_DIR})
install(FILES ${PROJECT_DRIVER_XML} DESTINATION ${TORCS_DRIVER_DATA_DIR})
install(FILES ${PROJECT_DRIVER_LOGO} DESTINATION ${TORCS_DRIVER_DATA_DIR})
install(FILES ${PROJECT_CAR_LOGO} DESTINATION ${TORCS_DRIVER_DATA_DIR})

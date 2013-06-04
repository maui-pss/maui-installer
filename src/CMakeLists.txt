include_directories(
    ${Solid_INCLUDE_DIRS}
)

set(SOURCES
    main.cpp
    installer.cpp
    engine.cpp
    languagesmodel.cpp
    volumemodel.cpp
    volumeitem.cpp
)

set(QM_SOURCES
)

#qt5_add_translation(QM_FILES ${QM_SOURCES})
qt5_add_resources(RC_FILES installer.qrc)

add_executable(maui-installer ${SOURCES} ${RC_FILES})
target_link_libraries(maui-installer ${Solid_LIBRARIES})
qt5_use_modules(maui-installer Qml Quick)

install(TARGETS maui-installer
    DESTINATION ${CMAKE_INSTALL_BINDIR})
#install(FILES ${QM_FILES}
#    DESTINATION ${CMAKE_INSTALL_DATADIR}/maui-installer/translations)

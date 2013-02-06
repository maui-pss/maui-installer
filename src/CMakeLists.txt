include_directories(
    ${solid_INCLUDE_DIRS}
)

set(SOURCES
    main.cpp
    installer.cpp
    volumemodel.cpp
    volumeitem.cpp
    volumedelegate.cpp
    pages/welcomepage.cpp
    pages/partitionpage.cpp
    pages/installpage.cpp
    pages/thankspage.cpp
)

set(UI_SOURCES
    pages/welcomepage.ui
    pages/partitionpage.ui
    pages/installpage.ui
    pages/thankspage.ui
)

set(QM_SOURCES
)

qt5_wrap_ui(UI_FILES ${UI_SOURCES})
#qt5_add_translation(QM_FILES ${QM_SOURCES})
#qt5_add_resources(RC_FILES installer.qrc)

#add_executable(installer ${SOURCES} ${UI_FILES} ${RC_FILES} ${QM_FILES})
add_executable(maui-installer ${SOURCES} ${UI_FILES})
target_link_libraries(maui-installer ${solid_LIBRARIES})
qt5_use_modules(maui-installer Widgets)

install(TARGETS maui-installer
    DESTINATION ${CMAKE_INSTALL_BINDIR})
#install(FILES ${QM_FILES}
#    DESTINATION ${CMAKE_INSTALL_DATADIR}/maui-installer/translations)

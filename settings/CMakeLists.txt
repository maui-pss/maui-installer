configure_file(
    settings.conf.in
    ${CMAKE_CURRENT_BINARY_DIR}/settings.conf
    @ONLY
)

set(FILES
    displaymanager.conf
    extlinuxcfg.conf
    locale.conf
    prepare.conf
    unpackfs.conf
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/settings.conf
        DESTINATION ${CMAKE_INSTALL_FULL_SYSCONFDIR}/calamares)

install(FILES ${FILES}
        DESTINATION ${CMAKE_INSTALL_FULL_SYSCONFDIR}/calamares/modules)

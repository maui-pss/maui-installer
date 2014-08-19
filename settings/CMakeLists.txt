set(FILES
    locale.conf
    unpackfs.conf
)

install(FILES settings.conf
        DESTINATION ${CMAKE_INSTALL_FULL_SYSCONFDIR}/calamares)

install(FILES ${FILES}
        DESTINATION ${CMAKE_INSTALL_FULL_SYSCONFDIR}/calamares/modules)

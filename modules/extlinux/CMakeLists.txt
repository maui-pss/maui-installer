install(FILES main.py module.desc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/calamares/modules/extlinux)
install(FILES extlinux.conf
        DESTINATION ${CMAKE_INSTALL_DATADIR}/calamares/modules)

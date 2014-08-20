install(FILES main.py module.desc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/calamares/modules/preunpackfs)
install(FILES preunpackfs.conf
        DESTINATION ${CMAKE_INSTALL_DATADIR}/calamares/modules)

install(FILES main.py module.desc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/calamares/modules/extlinuxcfg)
install(FILES extlinuxcfg.conf
        DESTINATION ${CMAKE_INSTALL_DATADIR}/calamares/modules)

set(hdrs SerialPort.h Thread.h TimeSpec.h Timer.h type.h)

install(FILES ${hdrs} DESTINATION ${INC_INSTALL_DIR}
    COMPONENT library)


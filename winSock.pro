QMAKE_CXXFLAGS+=-std=c++11
#ifdef Q_WS_WIN
#INCLUDEPATH +=D:/tools/PComm/Lib
#LIBS        +=-LD:/tools/PComm/Lib -lPcomm
LIBS        += -lws2_32
LIBS        += -lwsock32
#endif



SOURCES += \
    main.cpp \
    sockets/sockserver.cpp \
    sockets/socketservfct.cpp \
    sockets/winsoksserver.cpp

HEADERS += \
    globals.h \
    sockets/sockserver.hpp \
    sockets/socketservfct.hpp \
    sockets/winsoksserver.hpp



QT += quick sql \
      quickcontrols2 \


SOURCES += \
        assingmentlistmodel.cpp \
        backend.cpp \
        filterproxymodel.cpp \
        main.cpp \
        sqlcommand.cpp

resources.files = main.qml
resources.prefix = /$${TARGET}
RESOURCES += \
    Database.qrc \
    QML_Files.qrc \
    cPlusPlus.qrc \
    images.qrc \
    resources

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES    += \
    Settings.qml \
    main.qml

HEADERS += \
    assingmentlistmodel.h \
    backend.h \
    filterproxymodel.h \
    sqlcommand.h

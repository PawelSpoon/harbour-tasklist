# The name of your app.
# NOTICE: name defined in TARGET has a corresponding QML filename.
#         If name defined in TARGET is changed, following needs to be
#         done to match new name:
#         - corresponding QML filename must be changed
#         - desktop icon filename must be changed
#         - desktop filename must be changed
#         - icon definition filename in desktop file must be changed
TARGET = harbour-tasklist

CONFIG += sailfishapp c++11
#QT += dbus

SOURCES += src/harbour-tasklist.cpp \
    src/tasksexport.cpp

OTHER_FILES += qml/harbour-tasklist.qml \
    qml/pages/CoverPage.qml \
    rpm/harbour-tasklist.yaml \
    harbour-tasklist.desktop \
    qml/localdb.js \
    qml/pages/AboutPage.qml \
    qml/pages/EditPage.qml \
    qml/pages/TaskPage.qml \
    qml/pages/ListPage.qml \
    qml/pages/SettingsPage.qml \
    qml/pages/TaskListItem.qml \
    qml/pages/ExportPage.qml \
    qml/pages/TagPage.qml \
    qml/pages/TagDialog.qml \
    qml/pages/sync/DropboxAuth.qml \
    qml/pages/sync/DropboxSync.qml \
    qml/pages/HelpPage.qml

# without _idbased app did not load the files properly
CONFIG += sailfishapp_i18n
CONFIG += sailfishapp_i18n_idbased

# TRANSLATIONS += other-folder-then-translation/harbour-tasklist_ca.ts will not trigger qm generation
TRANSLATIONS += translations/harbour-tasklist_ca.ts  \
                translations/harbour-tasklist_cs_CZ.ts \
                translations/harbour-tasklist_da_DK.ts \
                translations/harbour-tasklist_de_DE.ts \
                translations/harbour-tasklist_en_US.ts \
                translations/harbour-tasklist_es_ES.ts \
                translations/harbour-tasklist_fi_FI.ts \
                translations/harbour-tasklist_fr_FR.ts \
                translations/harbour-tasklist_hu.ts \
                translations/harbour-tasklist_it_IT.ts \
                translations/harbour-tasklist_ku_IQ.ts \
                translations/harbour-tasklist_nl_NL.ts \
                translations/harbour-tasklist_pl_PL.ts \
                translations/harbour-tasklist_ru_RU.ts \
                translations/harbour-tasklist_sv_SE.ts \
                translations/harbour-tasklist_tr_TR.ts \
                translations/harbour-tasklist_zh_CN.ts


# this would trigger a manuall lupdate
#"/home/pawel/SailfishOS/bin/sfdk build-shell lupdate /home/pawel/Documents/SailfishProjects/harbour-tasklist/harbour-tasklist.pro"

#lupdate_only {
#    SOURCES = qml/*.qml \
#              qml/*.js \
#              qml/pages/*.qml \
#              qml/pages/sync/*.qml
#    TRANSLATIONS = translations/*.ts
#}

HEADERS += \
    src/tasksexport.h

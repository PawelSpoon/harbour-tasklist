#include "tasksexport.h"
#include <QDesktopServices>
#include <QDirIterator>
#include <QFile>
#include <QTextStream>
#include <QSettings>

// FIXME
#include <QDebug>

TasksExport::TasksExport(QObject *parent) :
    QObject(parent), dropboxPath("/sandbox/harbour-tasklist.json")
{
}

TasksExport::~TasksExport()
{
    exitDropbox();
}

QString TasksExport::load(const QString &path) const
{
    QString result;
    if (path.isEmpty())
        return result;
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return result;

    QTextStream in(&file);
    in.setCodec("UTF-8");
    result = in.readAll();

    file.close();
    return result;
}

QStringList TasksExport::getFilesList(const QString &directory) const
{
    QStringList result;
    QDirIterator iter(directory);
    while (iter.hasNext()) {
        iter.next();
        QFileInfo info(iter.filePath());
        if (info.isFile() && info.suffix() == "json")
            result.append(info.completeBaseName());
    }
    return result;
}

bool TasksExport::save(const QString &tasks) const
{
    if (mFileName.isEmpty())
        return false;
    // check that directory is present
    int slash = mFileName.lastIndexOf("/");
    if (slash >= 0) {
        QString directoryName = mFileName.left(slash);
        QDir dir(directoryName);
        if (!dir.exists())
            dir.mkpath(".");
    }
    QFile file(mFileName);
    if (!file.open(QFile::WriteOnly | QFile::Truncate))
        return false;

    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << tasks;

    file.close();
    return true;
}

bool TasksExport::remove(const QString &path) const
{
    if (path.isEmpty())
        return false;

    QFile file(path);
    file.remove(path);
    return true;
}

// modified version of https://github.com/karip/harbour-file-browser/blob/master/src/engine.cpp#L122
QStringList TasksExport::mountPoints() const
{
    // read /proc/mounts and return all mount points for the filesystem
    QFile file("/proc/mounts");
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return QStringList();

    QTextStream in(&file);
    QString result = in.readAll();

    // split result to lines
    QStringList lines = result.split(QRegExp("[\n\r]"));

    // get columns
    QStringList dirs;
    foreach (QString line, lines) {
        QStringList columns = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        if (columns.count() < 6) // sanity check
            continue;

        QString dir = columns.at(1);
        dirs.append(dir);
    }

    return dirs;
}

QStringList TasksExport::sdcardPath(const QString &path) const
{
    // get sdcard dir candidates
    QDir dir(path);
    if (!dir.exists())
        return QStringList();
    dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    QStringList sdcards = dir.entryList();
    if (sdcards.isEmpty())
        return QStringList();

    // remove all directories which are not mount points
    QStringList mps = mountPoints();
    QMutableStringListIterator i(sdcards);
    while (i.hasNext()) {
        QString dirname = i.next();
        QString abspath = dir.absoluteFilePath(dirname);
        if (!mps.contains(abspath))
            i.remove();
    }

    // none found, return empty string
    if (sdcards.isEmpty())
        return QStringList();

    // always return all cards
    return sdcards;
}

QString TasksExport::dropboxAuthorizeLink()
{
}

QStringList TasksExport::getDropboxCredentials()
{
    QStringList result;
    return result;
}

void TasksExport::setDropboxCredentials(const QString &token, const QString &tokenSecret)
{
}

QString TasksExport::uploadToDropbox(const QString &tasks)
{
}

QStringList TasksExport::downloadFromDropbox()
{
    return {};
}

QString TasksExport::getRevision()
{
    return "";
}

void TasksExport::initDropbox()
{
}

void TasksExport::exitDropbox()
{
}

QString TasksExport::language()
{
    QSettings settings;
    return settings.value("language", "").toString();
}

void TasksExport::setLanguage(const QString &lang)
{
    QSettings settings;
    settings.setValue("language", lang);
}

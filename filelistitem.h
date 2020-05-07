#ifndef FILELISTITEM_H
#define FILELISTITEM_H
#include <QAbstractListModel>

class FileListItem
{
public:
    FileListItem() {}
    FileListItem(QString filePath, QString fileName, int index ):m_filePath(filePath),m_fileName(fileName),m_index(index)
    {
    }
    QString filePath() const;
    QString fileName() const;
    int index() const;
    //bool available() const;
    //int result() const;
    //void setAvailable(bool able);
    //void setResult(int value);
    void setfilePath(QString filePath);
    void setfileName(QString fileName);

private:
    QString m_filePath;
    QString m_fileName;
    int m_index;
    //bool m_available;
    // int m_result;
};

class FileListItemModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit FileListItemModel(QObject *parent = 0):QAbstractListModel(parent)
    {
    }

    enum FileListItemRoles {//////////////////////////////listview机制////////////////////////////////
        FilePathRole = Qt::UserRole + 1,
        IndexRole,
        FileName,
        //Available,
        //ResultRole
    };


    void removeItem(int index);

    int getIndexbyFilePath(QString FilePath);

    //Q_INVOKABLE void setAvailableStateByIndex(int index, bool state);

    //Q_INVOKABLE void updateAvailableStateByIndex(int index);

    void insertItem(int index, const FileListItem &item);

    void addFileListItem(const FileListItem &item);

    Q_INVOKABLE QString getFilePathByIndex(int index);

    QString getFileNameByIndex(int index);

    //Q_INVOKABLE bool getAvailableStateByIndex(int index);

    //Q_INVOKABLE void updateAllAvailableState(bool status);

    //Q_INVOKABLE void setResultValueByIndex(int index, int value);

    //Q_INVOKABLE void updateAllResultState(int value);

    Q_INVOKABLE void setFileNamebyIndex(int index, QString fileName);

    Q_INVOKABLE void setFilePathbyIndex(int index, QString filePath);

    Q_INVOKABLE void setFileNamebyFilePath(QString filePath, QString fileName);

    Q_INVOKABLE void clear();

    Q_INVOKABLE QVariant get(int index, QString role);
    
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role) const;

    QHash<int, QByteArray> roleNames() const;

private:
    QList<FileListItem> m_FileListItem;

};

#endif // FILELISTITEM_H

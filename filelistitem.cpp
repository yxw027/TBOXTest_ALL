#include "filelistitem.h"

/*****************************************************************************
 函 数 名  : filePath
 功能描述  : 返回文件路径
 输入参数  : 无
 输出参数  : 无
 返 回 值  : QString
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2018年1月18日 星期四
    作    者   : Huang
    修改内容   : 新生成函数

*****************************************************************************/
QString FileListItem::filePath() const
{
    return m_filePath;
}

void FileListItem::setfilePath(QString filePath)
{
    m_filePath =  filePath;
}

QString FileListItem::fileName() const
{
    return m_fileName;
}

/*****************************************************************************
 函 数 名  : fileName
 功能描述  : 返回文件名
 输入参数  : 无
 输出参数  : 无
 返 回 值  : QString
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2018年1月18日 星期四
    作    者   : Huang
    修改内容   : 新生成函数

*****************************************************************************/
//QString FileListItem::fileName() const
//{
//    return m_fileName;
//}

/*****************************************************************************
 函 数 名  : index
 功能描述  : 返回列表索引
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2018年1月18日 星期四
    作    者   : Huang
    修改内容   : 新生成函数

*****************************************************************************/
int FileListItem::index() const
{
    return m_index;
}

/*void FileListItem::setResult(int value)
{
   m_result = value;
}*/

void FileListItem::setfileName(QString fileName)
{
    printf("setfileName \n");
//    printf("sss %s \n", m_fileName.toLocal8Bit().data());
//    printf("sss %s \n", this->fileName());
//    printf("sss %s \n", m_fileName.toLocal8Bit().data());
//    printf("sss %s \n", fileName.toLocal8Bit().data());

    this->m_fileName = fileName;

    printf(" after setfileName \n");

}

/*****************************************************************************
 函 数 名  : available
 功能描述  : 当前Item是否可用
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2018年1月18日 星期四
    作    者   : Huang
    修改内容   : 新生成函数

*****************************************************************************/
/*bool FileListItem::available() const
{
    return m_available;
}


void FileListItem::setAvailable(bool able)
{
   m_available = able;
}

*/

/*****************************************************************************
 函 数 名  : addFileListItem
 功能描述  : 加载Item到列表中
 输入参数  : const FileListItem &item
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2018年1月18日 星期四
    作    者   : Huang
    修改内容   : 新生成函数

*****************************************************************************/
void FileListItemModel::addFileListItem(const FileListItem &item)
{
    printf("addFileListItem \n");
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_FileListItem << item;
    endInsertRows();
}

void FileListItemModel::removeItem(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    m_FileListItem.removeAt(index);
    endRemoveRows();
}

/*void FileListItemModel::setAvailableStateByIndex(int index, bool state)
{
    m_FileListItem[index].setAvailable(state);
     emit dataChanged(this->index(index), this->index(index));//update qml listview
}*/

/*void FileListItemModel::updateAllResultState(int value)
{
    int i = 0;
    for(i=0; i<m_FileListItem.count(); i++)
    {
        if(m_FileListItem[i].filePath() != "undef")
            m_FileListItem[i].setResult(value);
    }
    emit dataChanged(this->index(0), this->index(rowCount()-1));//update qml listview
}*/

/*void FileListItemModel::updateAvailableStateByIndex(int index)
{
    bool state;
    state = m_FileListItem[index].available();
    m_FileListItem[index].setAvailable(!state);
    emit dataChanged(this->index(index), this->index(index));//update qml listview
}*/

/*void FileListItemModel::updateAllAvailableState(bool status)
{
    int i = 0;
    for(i=0; i<m_FileListItem.count(); i++)
    {
        if(m_FileListItem[i].filePath() != "undef")
            m_FileListItem[i].setAvailable(status);
    }
    emit dataChanged(this->index(0), this->index(rowCount()-1));
}*/

/*void FileListItemModel::setResultValueByIndex(int index, int value)
{
    m_FileListItem[index].setResult(value);
    emit dataChanged(this->index(index), this->index(index));//update qml listview
}*/

void FileListItemModel::insertItem(int index, const FileListItem &item)
{
    beginInsertRows(QModelIndex(), index, index);
    m_FileListItem.insert(index, item);
    endInsertRows();
}

void FileListItemModel::setFileNamebyIndex(int index, QString fileName) {
    printf("RUN setFileNamebyIndex %d %s \n" ,index,fileName.toLocal8Bit().data());

//    printf("==== this fileName ==== %s \n", m_FileListItem[index].fileName().toLocal8Bit().data());

    //    m_FileListItem.at(index).setfileName(fileName);
    m_FileListItem[index].setfileName(fileName);
    //    this->m_FileListItem.setfileName(fileName);
//    m_FileListItem[index].setfilePath(fileName);


    printf("after set filename \n");
    //    m_FileListItem[index].fileName() = fileName;
    emit dataChanged(this->index(index), this->index(index));//update qml listview
}

void FileListItemModel::setFilePathbyIndex(int index, QString filePath) {
    m_FileListItem[index].filePath() = filePath;
    emit dataChanged(this->index(index), this->index(index));//update qml listview
}

int FileListItemModel::getIndexbyFilePath(QString FilePath) {
    int i;
    for(i=0; i<m_FileListItem.count(); i++) {
        if(m_FileListItem[i].filePath() == FilePath) {
            break;
        }
    }
    return i;
}

void FileListItemModel::setFileNamebyFilePath(QString filePath, QString fileName) {
    int i;
    for(i=0; i<m_FileListItem.count(); i++) {
        if(m_FileListItem[i].filePath() == filePath) {
            m_FileListItem[i].setfileName(fileName);
            emit dataChanged(this->index(i), this->index(i));
            break;
        }
    }
}


/*****************************************************************************
 函 数 名  : getFilePathByIndex
 功能描述  : 根据列表索引获取对应文件路径
 输入参数  : int index
 输出参数  : 无
 返 回 值  : QString
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2018年1月18日 星期四
    作    者   : Huang
    修改内容   : 新生成函数

*****************************************************************************/
QString FileListItemModel::getFilePathByIndex(int index)
{
    return m_FileListItem.at(index).filePath();
}
QString FileListItemModel::getFileNameByIndex(int index)
{
    return m_FileListItem.at(index).fileName();
}

/*bool FileListItemModel::getAvailableStateByIndex(int index)
{
    return m_FileListItem.at(index).available();
}*/

/*****************************************************************************
 函 数 名  : clear
 功能描述  : 清空list
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2018年1月18日 星期四
    作    者   : Huang
    修改内容   : 新生成函数

*****************************************************************************/
void FileListItemModel::clear()
{
    beginResetModel();
    m_FileListItem.clear();
    endResetModel();
}

/*****************************************************************************
 函 数 名  : get
 功能描述  : 根据索引和关键字返回列表中对应的值
 输入参数  : int index, QString role
 输出参数  : 无
 返 回 值  : QVariant
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2018年1月18日 星期四
    作    者   : Huang
    修改内容   : 新生成函数

*****************************************************************************/
QVariant FileListItemModel :: get(int index, QString role)
{
    if (index < 0 || index >= m_FileListItem.count())
        return QVariant();

    const FileListItem &item = m_FileListItem[index];
    if (role == "FilePath")
        return item.filePath();
    else if (role == "Index")
        return item.index();
    else if (role == "FileName")
        return item.fileName();
    //    else if (role == "Available")
    //        return item.available();
    else
        return QVariant();
}

/*****************************************************************************
 函 数 名  : rowCount
 功能描述  : 返回list中item的总数量
 输入参数  : const QModelIndex & parent
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2018年1月18日 星期四
    作    者   : Huang
    修改内容   : 新生成函数

*****************************************************************************/
int FileListItemModel :: rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return m_FileListItem.count();
}

/*****************************************************************************
 函 数 名  : data
 功能描述  : 根据索引和枚举值返回list中对应的数据
 输入参数  : const QModelIndex & index, int role
 输出参数  : 无
 返 回 值  : QVariant
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2018年1月18日 星期四
    作    者   : Huang
    修改内容   : 新生成函数

*****************************************************************************/
QVariant  FileListItemModel :: data(const QModelIndex & index, int role) const//////////////////////////////listview机制////////////////////////////////
{
    if (index.row() < 0 || index.row() >= m_FileListItem.count())
        return QVariant();

    const FileListItem &item = m_FileListItem[index.row()];
    if (role == FilePathRole)
        return item.filePath();
    else if (role == IndexRole)
        return item.index();
    else if (role == FileName)
        return item.fileName();
    //    else if (role == Available)
    //        return item.available();
    //    else if (role == ResultRole)
    //        return item.result();
    else
        return QVariant();
}

/*****************************************************************************
 函 数 名  : roleNames
 功能描述  : 显示窗口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2018年1月18日 星期四
    作    者   : Huang
    修改内容   : 新生成函数

*****************************************************************************/
QHash<int, QByteArray>  FileListItemModel :: roleNames() const//////////////////////////////listview机制////////////////////////////////
{
    QHash<int, QByteArray> roles;
    roles[FilePathRole] = "FilePath";
    roles[IndexRole] = "Index";
    roles[FileName] = "FileName";
    //    roles[Available] = "Available";
    //    roles[ResultRole] = "Result";

    return roles;
}

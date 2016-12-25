#include "localfilemanager.h"
#include <QFileInfo>

#define log(s) TMY::logger.log(s)

TMY::LocalFileWriter::LocalFileWriter(QString syncPath_)
{
    syncPath = syncpath_;
}

TMY::LocalFileReader::LocalFileReader(QString syncPath_)
{
    syncPath = syncpath_;
}

TMY::LocalFileWriter::setFilePath(const FilePath filepath_)
{
    filePath = filepath_;
    path = syncPath;
    path += TMY::convert(filePath);
    metaPath = path;
    metaPath += METATAIL;
}

TMY::LocalFileReader::setFilePath(const FilePath filepath_)
{
    filePath = filepath_;
    path = syncPath;
    path += TMY::convert(filePath);
}

PullReq TMY::LocalFileWriter::generatePullReqEntry()
{
    std::ifstream metafile(metaPath.toStdString());
    if (metafile.fail())
    {
        log("ERR: metafile not found");
        return ;
    }
    json j;
    metafile >> j;
    chunks.fromJSON(j);

    file.setFileName(path);
    file.open(QIODevice::ReadOnly);

    PullReq pullReq;

    pullReq.clear();
    PullReqEntry p;
    p.filePath = filePath;
    p.offset = 0;
    int tail = 0;
    for (int i = 0; i < chunks.size(); ++i)
    {
        tail = chunks[i].offset;
        if (p.offset != tail)
        {
            p.len = tail - p.offset;
            pullReq.push_back(p);
        }
        tail += chunks[i].len;
        p.offset = tail;
    }
    p.len = dirinfoentry.len - p.offset;
    pullReq.push_back(p);

    return pullReq;
}

void TMY::LocalFileWriter::writePush(PushReqEntry &pushReq)
{
    file.setFileName(path);
    file.open(QIODevice::ReadOnly);
    file.seek(pushReq.offset);
    file.write(pushReq.buffer, pushReq.len);

    delete[] pushReq.buffer;

    int i;
    for (i = 0; i < chunks.size(); ++i)
        if (chunks[i].offset > pushReq.offset)
            break;
    --i;
    chunks.insert(chunks.begin() + i, { pushReq.offset, pushReq.len });
    updateChunks();
}


void TMY::LocalFileWriter::updateChunks()
{
	for (int i = 0; i < chunks.size() - 1; ++i)
	{
		int tail = chunks[i].offset + chunks[i].len;
		int head = chunks[i + 1].offset;
		if (tail == head)
		{
			chunks[i].len += chunks[i+1].len;
			chunks.erase(chunks.begin() + i + 1);
			--i;
		}
	}
	if (chunks[0].len == dirinfoentry.len)
	{
		finished = true;
		std::string metapath = filepath;
		metapath += METATAIL;
		remove(metapath.c_str());
	}

}

TMY::PushReq TMY::LocalFileReader::generatePushReqEntry(PullReq pull)
{
    PushReq pushes;
    file.setFileName(path);
    file.open(QIODevice::ReadOnly);
    for (PullReqEntry &entry : pull)
    {
        while (entry.len != 0)
        {
            PushReqEntry push;
            push.offset = entry.offset;
            int len = entry.len > 1024 * 1024 ? 1024 * 1024 : entry.len;
            push.len = len;
            push.buffer = new char[len];
            file.seek(entry.offset);
            file.read(push.buffer, len);
            pushes.push_back(push);

            entry.offset += len;
            entry.len -= len;
        }
    }
    return pushes;
}

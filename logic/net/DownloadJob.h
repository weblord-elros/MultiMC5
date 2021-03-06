#pragma once
#include <QtNetwork>
#include "Download.h"
#include "ByteArrayDownload.h"
#include "FileDownload.h"
#include "CacheDownload.h"
#include "HttpMetaCache.h"
#include "ForgeXzDownload.h"
#include "logic/tasks/ProgressProvider.h"

class DownloadJob;
typedef std::shared_ptr<DownloadJob> DownloadJobPtr;

/**
 * A single file for the downloader/cache to process.
 */
class DownloadJob : public ProgressProvider
{
	Q_OBJECT
public:
	explicit DownloadJob(QString job_name)
		:ProgressProvider(), m_job_name(job_name){};
	
	ByteArrayDownloadPtr addByteArrayDownload(QUrl url);
	FileDownloadPtr      addFileDownload(QUrl url, QString rel_target_path);
	CacheDownloadPtr     addCacheDownload(QUrl url, MetaEntryPtr entry);
	ForgeXzDownloadPtr   addForgeXzDownload(QUrl url, MetaEntryPtr entry);
	
	DownloadPtr operator[](int index)
	{
		return downloads[index];
	};
	DownloadPtr first()
	{
		if(downloads.size())
			return downloads[0];
		return DownloadPtr();
	}
	int size() const
	{
		return downloads.size();
	}
	virtual void getProgress(qint64& current, qint64& total)
	{
		current = current_progress;
		total = total_progress;
	};
	virtual QString getStatus() const
	{
		return m_job_name;
	};
	virtual bool isRunning() const
	{
		return m_running;
	};
	QStringList getFailedFiles();
signals:
	void started();
	void progress(qint64 current, qint64 total);
	void succeeded();
	void failed();
public slots:
	virtual void start();
private slots:
	void partProgress(int index, qint64 bytesReceived, qint64 bytesTotal);;
	void partSucceeded(int index);
	void partFailed(int index);
private:
	struct part_info
	{
		qint64 current_progress = 0;
		qint64 total_progress = 1;
		int failures = 0;
	};
	QString m_job_name;
	QList<DownloadPtr> downloads;
	QList<part_info> parts_progress;
	qint64 current_progress = 0;
	qint64 total_progress = 0;
	int num_succeeded = 0;
	int num_failed = 0;
	bool m_running = false;
};


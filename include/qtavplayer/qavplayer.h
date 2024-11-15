/*********************************************************
 * Copyright (C) 2020, Val Doroshchuk <valbok@gmail.com> *
 *                                                       *
 * This file is part of QtAVPlayer.                      *
 * Free Qt Media Player based on FFmpeg.                 *
 *********************************************************/

#ifndef QAVPLAYER_H
#define QAVPLAYER_H

#include <qtavplayer/qavvideoframe.h>
#include <qtavplayer/qavaudioframe.h>
#include <qtavplayer/qavsubtitleframe.h>
#include <qtavplayer/qavstream.h>
#include <qtavplayer/qtavplayer_global.h>
#include <QString>
#include <memory>

QT_BEGIN_NAMESPACE

class QAVIODevice;
class QAVPlayerPrivate;
class QTAVPLAYER_EXPORT QAVPlayer : public QObject
{
    Q_OBJECT

public:
    enum State
    {
        StoppedState,
        PlayingState,
        PausedState
    };
    Q_ENUM(State)

    enum MediaStatus
    {
        NoMedia,
        LoadedMedia,
        EndOfMedia,
        InvalidMedia
    };
    Q_ENUM(MediaStatus)

    enum Error
    {
        NoError,
        ResourceError,
        FilterError
    };
    Q_ENUM(Error)

public:
    QAVPlayer(QObject *parent = nullptr);
    ~QAVPlayer();

public:
    void setSource(const QString &url, const QSharedPointer<QAVIODevice> &dev = {});
    QString source() const;

    QList<QAVStream> availableVideoStreams() const;
    QList<QAVStream> currentVideoStreams() const;
    void setVideoStream(const QAVStream &stream);
    void setVideoStreams(const QList<QAVStream> &streams);

    QList<QAVStream> availableAudioStreams() const;
    QList<QAVStream> currentAudioStreams() const;
    void setAudioStream(const QAVStream &stream);
    void setAudioStreams(const QList<QAVStream> &streams);

    QList<QAVStream> availableSubtitleStreams() const;
    QList<QAVStream> currentSubtitleStreams() const;
    void setSubtitleStream(const QAVStream &stream);
    void setSubtitleStreams(const QList<QAVStream> &streams);

    State state() const;
    MediaStatus mediaStatus() const;
    qint64 duration() const;
    qint64 position() const;
    qreal speed() const;
    double videoFrameRate() const;

    void setFilter(const QString &desc);
    void setFilters(const QList<QString> &filters);
    QList<QString> filters() const;

    void setBitstreamFilter(const QString &desc);
    QString bitstreamFilter() const;

    bool isSeekable() const;

    bool isSynced() const;
    void setSynced(bool sync);

    QString inputFormat() const;
    void setInputFormat(const QString &format);

    QString inputVideoCodec() const;
    void setInputVideoCodec(const QString &codec);
    static QStringList supportedVideoCodecs();

    QMap<QString, QString> inputOptions() const;
    void setInputOptions(const QMap<QString, QString> &opts);

    QAVStream::Progress progress(const QAVStream &stream) const;

public Q_SLOTS:
    void play();
    void pause();
    void stop();
    void seek(qint64 position);
    void setSpeed(qreal rate);
    void stepForward();
    void stepBackward();

Q_SIGNALS:
    void sourceChanged(const QString &url);
    void stateChanged(QAVPlayer::State newState);
    void mediaStatusChanged(QAVPlayer::MediaStatus status);
    void errorOccurred(QAVPlayer::Error, const QString &str);
    void durationChanged(qint64 duration);
    void seekableChanged(bool seekable);
    void speedChanged(qreal rate);
    void videoFrameRateChanged(double rate);
    void videoStreamsChanged(const QList<QAVStream> &streams);
    void audioStreamsChanged(const QList<QAVStream> &streams);
    void subtitleStreamsChanged(const QList<QAVStream> &streams);
    void played(qint64 pos);
    void paused(qint64 pos);
    void stopped(qint64 pos);
    void stepped(qint64 pos);
    void seeked(qint64 pos);
    void filtersChanged(const QList<QString> &filters);
    void bitstreamFilterChanged(const QString &desc);
    void syncedChanged(bool sync);
    void inputFormatChanged(const QString &format);
    void inputVideoCodecChanged(const QString &codec);
    void inputOptionsChanged(const QMap<QString, QString> &opts);

    void videoFrame(const QAVVideoFrame &frame);
    void audioFrame(const QAVAudioFrame &frame);
    void subtitleFrame(const QAVSubtitleFrame &frame);

public:
    static void setLogsLevelBackend(int level);

protected:
    std::unique_ptr<QAVPlayerPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QAVPlayer)
    Q_DECLARE_PRIVATE(QAVPlayer)
};

QT_END_NAMESPACE

#endif

/*********************************************************
 * Copyright (C) 2020, Val Doroshchuk <valbok@gmail.com> *
 *                                                       *
 * This file is part of QtAVPlayer.                      *
 * Free Qt Media Player based on FFmpeg.                 *
 *********************************************************/

#ifndef QAVAUDIOOUTPUT_H
#define QAVAUDIOOUTPUT_H

#include <QtAVPlayer/qavaudioframe.h>
#include <QtAVPlayer/qtavplayerglobal.h>
#include <QAudioFormat>
#include <QObject>
#include <memory>

QT_BEGIN_NAMESPACE

class QAVAudioOutputPrivate;
class QAVAudioOutput : public QObject
{
    Q_OBJECT
public:
    QAVAudioOutput(QObject *parent = nullptr);
    ~QAVAudioOutput();

    void setVolume(qreal v);
    qreal volume() const;
    void setBufferSize(int bytes);
    int bufferSize() const;
#if QT_VERSION >= QT_VERSION_CHECK(6, 4, 0)
    void setChannelConfig(QAudioFormat::ChannelConfig);
    QAudioFormat::ChannelConfig channelConfig() const;
#endif

    bool play(const QAVAudioFrame &frame);

public Q_SLOTS:
    // No audio should be rendered if stopped even if play() is called
    void stop();

private:
    Q_DISABLE_COPY(QAVAudioOutput)
    Q_DECLARE_PRIVATE(QAVAudioOutput)
    std::unique_ptr<QAVAudioOutputPrivate> d_ptr;
};

QT_END_NAMESPACE

#endif

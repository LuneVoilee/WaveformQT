#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
#include <QAudioOutput>
#include <sndfile.h>
#include <QTimer>

class AudioPlayer : public QObject
{
    Q_OBJECT

public:
    explicit AudioPlayer(QObject *parent = nullptr);
    ~AudioPlayer();
    bool loadFile(const QString &filePath);
    void start();

signals:
    void audioDataReady(QVector<float> FBuffer); // Signal to notify when waveform data is ready for update

private slots:
    void readNextChunk();

private:

    const int bufferSize = 2048;
    QVector<float> FBuffer;

    int bitsPerSample;
    SNDFILE *file;
    SF_INFO sfinfo;
    QAudioOutput *audioOutput;

    QByteArray audioBuffer;
    QIODevice *audioDevice;
    QTimer *timer;

    void updateWaveform();
};

#endif // AUDIOPLAYER_H

#include "AudioPlayer.h"
#include <QFile>
#include <QDebug>

AudioPlayer::AudioPlayer(QObject *parent)
    : QObject(parent), file(nullptr), audioOutput(nullptr), audioDevice(nullptr),timer(new QTimer(this))
{
    connect(timer, &QTimer::timeout, this, &AudioPlayer::readNextChunk);
}

AudioPlayer::~AudioPlayer()
{
    if (file) {
        sf_close(file);
    }
    if(audioOutput) {
        delete audioOutput;
        audioOutput = nullptr;
    }
    if(audioDevice) {
        delete audioDevice;
        audioDevice = nullptr;
    }
    if(timer) {
        delete timer;
        timer = nullptr;
    }
}

bool AudioPlayer::loadFile(const QString &filePath)
{
    sfinfo = {};
    file = sf_open(filePath.toUtf8().constData(), SFM_READ, &sfinfo);
    if (!file) {
        qWarning() << "Failed to open file:" << filePath;
        return false;
    }
    switch (sfinfo.format & SF_FORMAT_SUBMASK) {
        case SF_FORMAT_PCM_16:
            bitsPerSample = 16; // 16-bit
            break;
        case SF_FORMAT_PCM_24:
            bitsPerSample = 24; // 24-bit
            break;
        case SF_FORMAT_PCM_32:
            bitsPerSample = 32; // 32-bit
            break;
        case SF_FORMAT_FLOAT:
            bitsPerSample = 32; // 32-bit float
            break;
        default:
            qWarning() << "Unsupported format!";
            sf_close(file);
            return false;
    }
    qDebug() << "Sample rate:" << sfinfo.samplerate;
    qDebug() << "bitsPerSample:" << bitsPerSample;
    qDebug() << "Channels:" << sfinfo.channels;
    qDebug() << "Frames:" << sfinfo.frames;
    qDebug() << "Format:" << sfinfo.format;

    QAudioFormat format;
    format.setSampleRate(sfinfo.samplerate);
    format.setChannelCount(sfinfo.channels);
    format.setSampleSize(bitsPerSample);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    audioOutput = new QAudioOutput(format, this);
    audioDevice = audioOutput->start();

    return true;
}

void AudioPlayer::start()
{
    timer->start(45); // Set to read every 100 ms, adjust as needed

    //audioDevice = audioOutput->start(); // Start audio output
}

void AudioPlayer::readNextChunk()
{
    //(framesRead * channel) may less than bufferSize
    audioBuffer.resize(bufferSize * sfinfo.channels * sizeof(short));
    sf_count_t framesRead = sf_readf_short(file, reinterpret_cast<short*>(audioBuffer.data()), bufferSize);

    if (framesRead > 0) {

        audioDevice->write(audioBuffer);
        QVector<float> FBuffer;
        for (int i = 0; i < framesRead * sfinfo.channels; ++i) {
            short sample = *reinterpret_cast<const short *>(audioBuffer.constData() + i * 2);
            FBuffer.append(static_cast<float>(sample) / 32768.0f); // Normalize
        }
        emit audioDataReady(FBuffer);  // Notify waveform update
    }
    else {
        audioOutput->stop();
        timer->stop();
    }
}

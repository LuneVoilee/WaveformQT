#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qstring.h>
#include "AudioPlayer.h"
#include "WaveformWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString path , QWidget *parent = nullptr);
    ~MainWindow();

private:
    AudioPlayer *audioPlayer;
    WaveformWidget *waveformWidget;
    QString filePath;

private slots:
    void updateWaveform(QVector<float> FBuffer);
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "AudioPlayer.h"
#include "WaveformWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    AudioPlayer *audioPlayer;
    WaveformWidget *waveformWidget;

private slots:
    void updateWaveform(QVector<float> FBuffer);
};

#endif // MAINWINDOW_H

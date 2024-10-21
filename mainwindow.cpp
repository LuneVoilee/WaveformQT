#include "mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    audioPlayer = new AudioPlayer(this);
    waveformWidget = new WaveformWidget(this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(waveformWidget);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Load and play the file
    audioPlayer->loadFile("/home/qywy/qt/1.wav");
    audioPlayer->start();

    // Connect signal and slot for real-time waveform update
    connect(audioPlayer, &AudioPlayer::audioDataReady, this, &MainWindow::updateWaveform);
}

MainWindow::~MainWindow()
{
}

void MainWindow::updateWaveform(QVector<float> FBuffer)
{
    waveformWidget->setSamples(FBuffer);
}

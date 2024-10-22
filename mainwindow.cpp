#include "mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QString path , QWidget *parent)
    : QMainWindow(parent) , filePath(path)
{
    audioPlayer = new AudioPlayer(this);
    waveformWidget = new WaveformWidget(this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(waveformWidget);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Load and play the file
    audioPlayer->loadFile(filePath);
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

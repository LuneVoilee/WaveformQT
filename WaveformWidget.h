#ifndef WAVEFORMWIDGET_H
#define WAVEFORMWIDGET_H

#include <QWidget>

class WaveformWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WaveformWidget(QWidget *parent = nullptr);
    void setSamples(const QVector<float> &samples);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<float> currentSamples;
};

#endif // WAVEFORMWIDGET_H

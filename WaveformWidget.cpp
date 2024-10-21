#include "WaveformWidget.h"
#include <QPainter>
#include <QDebug>

WaveformWidget::WaveformWidget(QWidget *parent)
    : QWidget(parent)
{
}

void WaveformWidget::setSamples(const QVector<float> &samples)
{
    currentSamples = samples;
    update();  // Request a repaint of the widget
}

void WaveformWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);  // Fill background with black

    if (currentSamples.isEmpty())
        return;

    // Calculate the position of each sample point in the widget
    float step = static_cast<float>(width()) / currentSamples.size();
    int midY = height() / 2;

    painter.setPen(Qt::green);  // Set the color of the waveform
    for (int i = 0; i < currentSamples.size() - 1; ++i) {
        int x1 = i * step;
        int x2 = (i + 1) * step;
        int y1 = midY - (currentSamples[i] * midY);  // Scale samples to widget height
        int y2 = midY - (currentSamples[i + 1] * midY);
        painter.drawLine(x1, y1, x2, y2);  // Draw waveform line between two points
    }
}

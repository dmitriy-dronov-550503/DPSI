#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Vizualizer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_sampleSizeText_returnPressed();

    void on_equationText_returnPressed();

    void on_horizontalSlider_valueChanged(int value);

    void on_frequencyText_returnPressed();

    void on_checkBox_stateChanged(int arg1);


    void on_tabWidget_currentChanged(int index);

    void on_equationText_2_returnPressed();

    void on_horizontalSlider_2_valueChanged(int value);

    void on_frequencyText_2_returnPressed();

    void on_bwLineEdit_returnPressed();

    void on_sampleSizeText_2_returnPressed();

    void on_equationText_2_textEdited(const QString &arg1);

    void on_equationText_2_selectionChanged();

    void on_equationText_2_textChanged(const QString &arg1);

    void on_equationText_textEdited(const QString &arg1);

public slots:
    void FrequencyGraphClicked(QMouseEvent* event);


private:
    Ui::MainWindow *ui;
    Vizualizer vizualizer;
    void RedrawGraphs(bool doRedrawSource = false);
    void RedrawFIRGraphs(bool doRedrawSource);
    void RedrawIIRGraphs(bool doRedrawSource);
};

#endif // MAINWINDOW_H

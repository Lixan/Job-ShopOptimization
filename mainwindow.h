#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>

#include "heuristicmethod.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QWidget *mainWidget;
    QHBoxLayout *H_layout;
    QVBoxLayout *V_layout;

    QPushButton *btn;
    QLabel *nomFichier;
    QScrollArea *scrollArea;
    QLabel *console;

    QComboBox * comboBox;
    QPushButton *btnOk;

public:
    explicit MainWindow(QWidget *parent = 0);
    int afficherGraphe(QString fichier);
    bool fileExists(QString path);

signals:

public slots:
    void openDialog();
    void lancement();
};

Q_DECLARE_METATYPE(HeuristicMethod *)

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QComboBox>

#include "heuristicmethod.h"
#include "graphewindow.h"

#include "Bierwirth.h"
#include "Data.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QWidget *mainWidget;
    QHBoxLayout *H_layout_top;
    QHBoxLayout *H_layout_bottom;
    QVBoxLayout *V_layout;

    QPushButton *btn;
    QLabel *nomFichier;
    QScrollArea *scrollAreaConsole;
    QLabel *console;
    QScrollArea *scrollAreaGraphe;
    GrapheWindow *graphe;

    QComboBox * comboBox;
    QPushButton *btnOk;

    Bierwirth *b;
    Data *d;
public:
    explicit MainWindow(QWidget *parent = 0);
    void afficherGraphe(QString fichier);
    bool fileExists(QString path);

signals:

public slots:
    void openDialog();
    void lancement();
};

Q_DECLARE_METATYPE(HeuristicMethod *)

#endif // MAINWINDOW_H

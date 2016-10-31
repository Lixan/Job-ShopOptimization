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

public:
    explicit MainWindow(QWidget *parent = 0);
    int afficherGraphe(QString fichier);
    bool fileExists(QString path);

signals:

public slots:
    void openDialog();
};

#endif // MAINWINDOW_H

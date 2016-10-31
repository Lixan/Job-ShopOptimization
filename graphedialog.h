#ifndef GRAPHEDIALOG_H
#define GRAPHEDIALOG_H

#include <QDialog>
#include <QScrollArea>
#include <QVBoxLayout>
#include "Bierwirth.h"
#include "Data.h"
#include "graphewindow.h"

class GrapheDialog : public QDialog
{
    Q_OBJECT
    QScrollArea *scrollArea;
    GrapheWindow *graphe;
    QVBoxLayout *layout;
public:
    explicit GrapheDialog(Data &d, Bierwirth &b, QDialog *parent = 0);

signals:

public slots:
};

#endif // GRAPHEDIALOG_H

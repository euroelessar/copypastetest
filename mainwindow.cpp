#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plainTextEdit->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj != ui->plainTextEdit) {
        return QMainWindow::eventFilter(obj, ev);
    }

    if (ev->type() == QEvent::KeyRelease) {
        ui->hotkeysEdit->clear();
    }

    if (ev->type() != QEvent::KeyPress)
        return false;

    onKeyPress(static_cast<QKeyEvent *>(ev));

    return false;
}

void MainWindow::onKeyPress(QKeyEvent *ev)
{
    //The keypad and group switch modifier should not make a difference
    const uint searchkey = (ev->modifiers() | ev->key()) & ~(Qt::KeypadModifier | Qt::GroupSwitchModifier);

//    const QList<QKeySequence> bindings = QKeySequence::keyBindings(QKeySequence::Copy);
//    const bool match = bindings.contains(QKeySequence(searchkey));

    QList<ushort> text;
    for (QChar ch : ev->text())
        text << ch.unicode();

    qDebug()
            << "searchKey:" << QString::number(searchkey, 16).toLatin1() << QKeySequence(searchkey)
//             << "bindings:" << bindings
//             << "match:" << match
            << "text:" << text
            << "native:" << ev->nativeScanCode();

    ui->hotkeysEdit->setPlainText(QKeySequence(searchkey).toString());
}

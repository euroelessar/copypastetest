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

    if (ev->type() == QEvent::KeyRelease)
        ui->hotkeysEdit->clear();
    else if (ev->type() == QEvent::KeyPress)
        onKeyPress(static_cast<QKeyEvent *>(ev));
    else if (ev->type() == QEvent::Shortcut)
        onShortcut(static_cast<QShortcutEvent *>(ev));

    return false;
}

void MainWindow::onKeyPress(QKeyEvent *ev)
{
    //The keypad and group switch modifier should not make a difference
    const uint searchkey = (ev->modifiers() | ev->key()) & ~(Qt::KeypadModifier | Qt::GroupSwitchModifier);

    const QList<QKeySequence> bindings = QKeySequence::keyBindings(QKeySequence::Quit);
    const bool match = bindings.contains(QKeySequence(searchkey));

    QList<ushort> text;
    for (int i = 0; i < ev->text().size(); ++i)
        text << ev->text().at(i).unicode();

//    QList<QKeySequence> sequences = QKeySequence::listFromString("Ctrl+Shift+C");

    qDebug()
            << "searchKey:" << QString::number(searchkey, 16).toLatin1() << QKeySequence(searchkey)
             << "bindings:" << bindings
             << "match:" << match
            << "text:" << text
            << "native:" << ev->nativeScanCode();
//            << "sequence:" << sequences
//            << "match:" << sequences.contains(QKeySequence(searchkey));

    ui->hotkeysEdit->setPlainText(QKeySequence(searchkey).toString());
}

void MainWindow::onShortcut(QShortcutEvent *ev)
{
    qDebug() << "shortcut:" << ev->key()
             << "ambiguous:" << ev->isAmbiguous()
             << "id:" << ev->shortcutId();
}

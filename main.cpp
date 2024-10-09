#include <QApplication>
#include <QDir>
#include <QFileSystemModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QHeaderView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::homePath());
    model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);

    QTreeView *treeView = new QTreeView;
    treeView->setModel(model);
    treeView->setRootIndex(model->index(QDir::homePath()));
    treeView->setSortingEnabled(true);
    treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    QLineEdit *filterEdit = new QLineEdit;
    filterEdit->setPlaceholderText("Enter the name of a file or a folder");
    QObject::connect(filterEdit, &QLineEdit::textChanged, [=](const QString &text) {
        model->setNameFilters({ "*" + text + "*" });
        model->setNameFilterDisables(false);
    });

    QWidget window;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(filterEdit);
    layout->addWidget(treeView);

    window.setLayout(layout);
    window.setWindowTitle(QObject::tr("File Explorer with Filtering"));
    window.setMinimumSize(800, 600);
    window.show();

    return app.exec();
}

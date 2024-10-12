#include <QApplication>
#include <QDir>
#include <QFileSystemModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QHeaderView>
#include <memory>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto model = std::make_unique<QFileSystemModel>();
    model->setRootPath(QDir::homePath());
    model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);

    auto treeView = std::make_unique<QTreeView>();
    treeView->setModel(model.get());
    treeView->setRootIndex(model->index(QDir::homePath()));
    treeView->setSortingEnabled(true);
    treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    auto filterEdit = std::make_unique<QLineEdit>();
    filterEdit->setPlaceholderText("Enter the name of a file or a folder");
    QObject::connect(filterEdit.get(), &QLineEdit::textChanged, [model = model.get()](const QString &text) {
        model->setNameFilters({ "*" + text + "*" });
        model->setNameFilterDisables(false);
    });

    QWidget window;
    QVBoxLayout layout;
    layout.addWidget(filterEdit.release());
    layout.addWidget(treeView.release());

    window.setLayout(&layout);
    window.setWindowTitle(QObject::tr("File Explorer with Filtering"));
    window.setMinimumSize(800, 600);
    window.show();

    return app.exec();
}
#ifndef EVENTTEMPLATE_H
#define EVENTTEMPLATE_H

#include <QWidget>
#include <QListWidgetItem>
#include <QStringList>
#include <QDateTime>

namespace Ui {
class EventTemplate;
}

class EventTemplate : public QWidget
{
    Q_OBJECT
    
public:
    explicit EventTemplate(QStringList, QListWidgetItem * = 0, QWidget *parent = 0);
    ~EventTemplate();

private:
    Ui::EventTemplate *ui;
    QListWidgetItem * holder;

};

#endif // EVENTTEMPLATE_H

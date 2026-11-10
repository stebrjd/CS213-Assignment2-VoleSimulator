#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>

class assignmentData;

class assignment
{
    Q_OBJECT
    QML_ELEMENT
public:
    assignment();
    assignment(const assignment &);
    assignment(assignment &&);
    assignment &operator=(const assignment &);
    assignment &operator=(assignment &&);
    ~assignment();

private:
    QSharedDataPointer<assignmentData> data;
};

#endif // ASSIGNMENT_H

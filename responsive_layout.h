//
// Created by Archie Gerry for UI CWK1 on 24/11/2022
//

#ifndef RESPONSIVELAYOUT_H
#define RESPONSIVELAYOUT_H

#include <QtGui>
#include <QList>
#include <QLayout>

class ResponsiveLayout : public QLayout {
public:
    ResponsiveLayout(): QLayout() {}
    ~ResponsiveLayout();

    // standard functions for a QLayout
    void setGeometry(const QRect &rect);
    int checkStandardDimensions(const QRect &rect, int labelCount);
    int checkCompactDimensions(const QRect &rect, int labelCount);
    void compactLayout(const QRect &r);
    void horizontalLayout(const QRect &r);
    void verticalLayout(const QRect &r);
    void standardLayout(const QRect &r);

    void addItem(QLayoutItem *item);
    QSize sizeHint() const;
    QSize minimumSize() const;
    int count() const;
    QLayoutItem *itemAt(int) const;
    QLayoutItem *takeAt(int);

private:
    QList<QLayoutItem*> list_;
};
#endif // RESPONSIVELAYOUT_H

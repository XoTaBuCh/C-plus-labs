#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtGui>
#include <QDialog>
#include <QPainter>
#include <QtCore>
#include <QDebug>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget      *ui;
protected:
    void paintEvent(QPaintEvent *event);
};
class Trie {
    struct node {
        node* next[256];
        double k;

        node() {
            k= 0;
            for (int i = 0; i < 123; i++) {   //изначально заполняем next нулевыми указателями,
                next[i] = nullptr;           //так как следующие вершины ещё не созданы
            }
        }
    };
    node* root = new node();   //корневая вершина бора, соответствующая пустой строке.

    void Clear(node* cur) {
        if (cur == nullptr) {
            return;
        }
        for (int i = 0; i < 123; i++) {
            Clear(cur->next[i]);
        }
        delete cur;
    }
public:
    ~Trie() {
        Clear(root);
    }

    void add(const QString& s, double k) {
        node* cur_v = root;     //текущая вершина

        for (int i = 0; i < s.length(); i++) {
            int c = s[i].unicode();
            if (cur_v->next[c] == nullptr) {
                cur_v->next[c] = new node();
            }
            cur_v = cur_v->next[c];
        }
        cur_v->k = k;
    }

    double has(const QString& s) {
        node* cur_v = root;

        for (int i = 0; i < s.length(); i++) {
            cur_v = cur_v->next[s[i].unicode()];
            if (cur_v == nullptr) {
                return 0;
            }
        }

        return cur_v->k;
    }
};
#endif // WIDGET_H

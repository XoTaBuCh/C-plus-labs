#include "widget.h"
#include "./ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: cyan;");
}

Widget::~Widget()
{
    delete ui;
}

void get_states(QMap<QString , QVector<QPolygon>>* states, QStringList& listWithKeys) {
    QFile file("D:\\7\\states.json");
    QJsonDocument document;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        document = QJsonDocument::fromJson(file.readAll());
    }
    file.close();

    QJsonObject json = document.object();
    listWithKeys = json.keys();

    for(int i = 0; i < listWithKeys.size(); i++){
        QJsonArray jsonArray = json[listWithKeys[i]].toArray();
        QVector<QPolygon> polygons;

        QJsonArray newArray = jsonArray[0].toArray();
        QJsonArray newArray2 = newArray[0].toArray();
        if (newArray2[0].isArray()){
            for(int j = 0; j < jsonArray.size(); j++) {
                QJsonArray first = jsonArray[j].toArray();
                QJsonArray second = first[0].toArray();
                QPolygon poly;
                for(int k =0; k<second.size(); k++){
                    QJsonArray third = second[k].toArray();
                    double x = (10) *(third[0].toDouble()+100) + 800;
                    double y = third[1].toDouble()*(-10) + 800;
                    poly << QPoint(x,y);
                }
                polygons.push_back(poly);
            }
        }
        else {
            QPolygon poly;
            QJsonArray first = jsonArray[0].toArray();
            for(int k =0; k<first.size(); k++){
                QJsonArray second = first[k].toArray();
                double x = (10) *(second[0].toDouble()+100) + 800;
                double y = second[1].toDouble()*(-10) + 800;

                poly<< QPoint(x,y);
            }
            polygons.push_back(poly);
        }
        states->insert(listWithKeys[i], polygons);
    }
}

void get_dictionary(Trie* dictionary) {
    QFile in("D:\\7\\sentiments.csv");
    in.open(QIODevice::ReadOnly | QIODevice::Text);
    QString str, word;
    QString num;
    while (!in.atEnd()) {
        str = in.readLine();
        word = ""; num = "";
        qsizetype i = 0;
        while (str[i] != ',') {
            word += str[i];
            i++;
        }
        i++;
        while (i < str.size()) {
            num += str[i];
            i++;
        }
        dictionary->add(word, num.toDouble());
    }
    in.close();
}

void get_logs(Trie& dictionary, QMap<QString , QVector<QPolygon>>& states, QStringList& listWithKeys, QMap<QString , double>& values){
    QFile logs("D:\\7\\tweets2014.txt");
    logs.open(QIODevice::ReadOnly | QIODevice::Text);
    QString input;
    while (!logs.atEnd()) {
        input = logs.readLine();
        size_t size = input.size();
        if (size == 0 || input[0] != '[') {
            continue;
        }
        size_t i = 1;
        QString x = "", y = "";
        while (i < size && input[i] != ',') {
            x += input[i];
            i++;
        }
        i++; i++;
        while (i < size && input[i] != ']') {
            y += input[i];
            i++;
        }
        char count = 0;
        while (i < size && count != 2) {
            while (i < size && input[i] != ':') {
                i++;
            }
            count++;
            i++;
        }
        i++; i++; i++;
        QString word = "";
        bool flag = 1;
        double sum = 0;
        while (i < size) {
            int in = input[i].unicode();
            if (!((in > 64 && in < 91) || (in > 96 && in < 123))) {
                if (flag == 1) {
                    sum += dictionary.has(word.toLower());
                }
                word = "";
                flag = 0;
            }
            else {
                flag = 1;
                word += input[i];
            }
            i++;
        }
        if(sum != 0){
            double intX = (10) *(y.toDouble() + 100) + 800;
            double intY = x.toDouble() * (-10) + 800;
            for(int j = 0; j<states.size();j++){
                for(int k = 0; k <states[listWithKeys[j]].size(); k++){

                    if(states[listWithKeys[j]][k].containsPoint(QPoint(intX, intY), Qt::OddEvenFill)){
                        values[listWithKeys[j]]+=sum;
                        j = states.size();
                        break;
                    }
                }

            }
        }
    }
    logs.close();
}

long double map(long double x, long double in_min, long double in_max, long double out_min, long double out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Draw(QPainter& painter, QMap<QString , QVector<QPolygon>>& states, QStringList& listWithKeys, QMap<QString , double>& values){
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::black);
    painter.setPen(pen);

    double min = 0;
    double max = 0;
    for(int j = 0; j<states.size();j++){
        if(values[listWithKeys[j]]>max){
            max = values[listWithKeys[j]];
        }
        if(values[listWithKeys[j]]<min){
            min = values[listWithKeys[j]];
        }
    }

    for(int j = 0; j<states.size();j++){
        for(int k = 0; k <states[listWithKeys[j]].size(); k++){
            QBrush brush;
            int r = map(values[listWithKeys[j]], max, min, 0, 255);;
            int g = map(values[listWithKeys[j]], min, max, 0, 255);
            int b = 0;
            brush.setColor(QColor(r,  g , b, 255));
            brush.setStyle(Qt::SolidPattern);
            painter.setBrush(brush);
            painter.drawPolygon(states[listWithKeys[j]][k]);
        }
    }
}

void Widget::paintEvent(QPaintEvent *event){

    QPainter painter(this);

    Trie dictionary;
    get_dictionary(&dictionary);

    QMap<QString , QVector<QPolygon>> states;

    QMap<QString , double> values;
    QStringList listWithKeys;
    get_states(&states, listWithKeys);

    for (int i = 0; i<listWithKeys.size(); i++){
        values.insert(listWithKeys[i], 0);
    }

    get_logs(dictionary, states, listWithKeys, values);

    Draw(painter, states, listWithKeys, values);


}




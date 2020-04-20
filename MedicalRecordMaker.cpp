#include "MedicalRecordMaker.h"
#include "QPainter"
#pragma execution_character_set("utf-8")
MedicalRecordMaker::MedicalRecordMaker()
{

}


QImage MedicalRecordMaker::getPaper(){

    int scale = 4;
    m_width = 210;
    m_height = 297;
    m_width *= scale;
    m_height *= scale;
    QImage A4Paper(m_width, m_height, QImage::Format_RGBA8888);
    QPainter painter(&A4Paper);
    painter.setPen(Qt::NoPen);
    drawBackground(&painter);
    int nowY = 0;
    nowY = drawTitle(&painter);
    nowY = drawInfomation(&painter, nowY);
    drawTable(&painter, nowY);
    drawImage(&painter, "");
    return A4Paper;
}

void MedicalRecordMaker::drawBackground(QPainter *painter)
{
    painter->save();
    painter->setBrush(QColor("#ffffff"));
    painter->drawRect(0, 0, m_width, m_height);
    painter->restore();
}

int MedicalRecordMaker::drawTitle(QPainter *painter)
{
    painter->save();
    int w = 480;
    int h = 30;
    int x = (m_width - w)/2;
    int y = 20;
    QFont font;
    font.setFamily("Microsoft Yahei");
    font.setPixelSize(h-2);
    painter->setFont(font);
    painter->setPen(QColor("#39C5BB"));
    painter->drawText(x, y, w, h, Qt::AlignCenter, "NAVIGATION · CERTIFICATE");
    painter->restore();

    return y+h;
}

int MedicalRecordMaker::drawInfomation(QPainter *painter, int nowY)
{

    int h = 20;
    int w1 = 180;
    int textLP1 = 20;
    int x1 = m_leftPadding + textLP1;
    int x2 = x1 +w1 + 10;
    int w2 = w1*2;
    int topPadding = nowY + 20;
    int yspacing = 8;


    QStringList infoName {"NAME", "ID", "BITRH DAY", "TREATMENT DATE", "TREATMENT SIDE", "IMPLANT"} ;
    QStringList data{"张三","20191234","20200202","20200203", "left", "DEFUALT"};
    int W = m_width - 2*m_leftPadding;
    int H = (h+yspacing)*infoName.size() + yspacing;
    painter->setBrush(QColor(m_areaColor));
    painter->drawRect(m_leftPadding, topPadding, W, H);

    QFont font;
    font.setFamily("Microsoft Yahei");
    font.setPixelSize(h-3);
    painter->setFont(font);
    painter->setPen(QColor("#333333"));
    int curY = topPadding + yspacing;
    for(auto&& t: infoName){
        painter->drawText(x1, curY, w1, h, Qt::AlignVCenter | Qt::AlignLeft, t);
        curY += yspacing + h;
    }
    curY = topPadding + yspacing;
    for(auto&& t: data){
        painter->drawText(x2, curY, w2, h, Qt::AlignVCenter | Qt::AlignLeft, t.prepend(":                       "));
        curY += yspacing + h;
    }
    return topPadding + H;
}

void MedicalRecordMaker::drawTable(QPainter *painter, int nowY)
{
    int centerSpacing = 10;
    int tableW = (m_width - m_leftPadding*2 - centerSpacing)/2;
    int tableH = 300;
    int topPadding = nowY + 20;

    auto&& table1 = getTableBackground("LEG ALIGNMENT", QSize(tableW, tableH));
    painter->drawImage(QRect(m_leftPadding, topPadding, tableW, tableH), table1);

    auto&& table2 = getTableBackground("JOINT STABILITY", QSize(tableW, tableH*2 + 10));
    painter->drawImage(QRect(m_leftPadding + tableW + centerSpacing,
                             topPadding, tableW, tableH*2 + 10), table2);

    topPadding += tableH + 10;

    auto&& table3 = getTableBackground("Range of Motion", QSize(tableW, tableH));
    painter->drawImage(QRect(m_leftPadding, topPadding , tableW, tableH), table3);

}

void MedicalRecordMaker::drawImage(QPainter *painter, QString url)
{

}

QImage MedicalRecordMaker::getTableBackground(QString title, QSize sz)
{
    QImage img(sz, QImage::Format_RGBA8888);
    QPainter pt(&img);
    int leftPadding = 0;

    int w = sz.width() - leftPadding*2-1;
    int h = 40;
    pt.setPen(QColor(m_areaColor));
    pt.setBrush(QColor("#FFFFFF"));
    pt.drawRect(0, 0, sz.width()-1, sz.height()-1);
    pt.setBrush(QColor(m_areaColor));
    pt.drawRect(leftPadding, 0, w, h);
    pt.setPen(QColor("#333333"));
    QFont font;
    font.setFamily("Microsoft Yahei");
    font.setPixelSize(h/2);
    pt.setFont(font);

    pt.drawText(leftPadding, 0, w, h, Qt::AlignVCenter | Qt::AlignHCenter , title);
    return img;
}
#include "QPrinter"
void MedicalRecordMaker::print()
{
    QPrinter pdf(QPrinter::HighResolution);
    pdf.setPageSize(QPrinter::A4);  //设置纸张大小为A4
    pdf.setOutputFormat(QPrinter::PdfFormat);  //设置输出格式为pdf
    pdf.setOutputFileName("testMedicalRecordMaker.pdf");   //设置输出路径

    QPixmap mp;
    mp.convertFromImage(this->getPaper());

    QPainter painter;
    painter.begin(&pdf);
    QRect rect = painter.viewport();
    float multiple = rect.width()/mp.width();
    painter.scale(multiple, multiple); //将图像(所有要画的东西)在pdf上放大multiple-1倍
    painter.drawPixmap(0, 0, mp);  //画图
    painter.end();
}

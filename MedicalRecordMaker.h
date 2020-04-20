#ifndef MEDICALRECORDMAKER_H
#define MEDICALRECORDMAKER_H

#include "QImage"
#include "memory"
class QPainter;

class MedicalRecordMaker
{
public:
    MedicalRecordMaker();
    typedef std::shared_ptr<MedicalRecordMaker>     Ptr;
    typedef std::weak_ptr<MedicalRecordMaker>       WPtr;

public:
    auto getPaper()->QImage;
    void print();
private:
    void drawBackground     (QPainter* painter);
    int  drawTitle          (QPainter* painter);
    int  drawInfomation     (QPainter* painter, int nowY);
    void drawTable          (QPainter* painter, int nowY);
    void drawImage          (QPainter* painter, QString url);
    auto getTableBackground (QString title, QSize sz)->QImage;
private:
    int m_width;
    int m_height;
    int m_leftPadding = 20;
    QString m_areaColor = "#dddddd";
};
//{
//	"title":
//	{
//		"color":"an apple",
//		"text":"appleIcon"
//	},
//	"data":
//	{
//		"name":"text1",
//		"id"  :"text2",
//		"birthday":"text3",
//      "treatmentdate":"text4",
//      "side":"text5",
//      "I
//	},
//	"three fruit array":
//	[
//		"eat 0",
//		"eat 1",
//		"eat 2",
//		"eat 3",
//		"eat 4"
//	]
//}
#endif // MEDICALRECORDMAKER_H

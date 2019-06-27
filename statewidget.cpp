#include "statewidget.h"

stateWidget::stateWidget(QWidget *parent)
	: QWidget(parent), m_on(false) {}

bool stateWidget::isOn() const
{
	return m_on;
}

void stateWidget::setOn(bool on)
{
	if (on == m_on)
		return;
	m_on = on;
	update();
}

void stateWidget::turnOff()
{
	setOn(false);
}

void stateWidget::turnOn()
{
	setOn(true);
}

void stateWidget::paintEvent(QPaintEvent *)
{

	if (!m_on)
		return;
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(m_color);
	painter.drawEllipse(0, 0, this->width(), this->height());

	// �������������ַ�ʽ������� -- ��֪Ϊ�λ��������
	QFont font;
	font.setFamily("����");
	// ��С
	font.setPointSize(16);
	// б��
	//font.setItalic(true);
	// �����»���
	//font.setUnderline(true);
	// �����ϻ���
	//font.setOverline(true);
	// ������ĸ��Сд
	//font.setCapitalization(QFont::SmallCaps);
	// �����ַ����
	font.setLetterSpacing(QFont::AbsoluteSpacing, 10);
	painter.setFont(font);
	painter.setPen(Qt::white);
	//lightTextStr = QString::fromLocal8Bit(lightText);
	// qDebug() << lightTextStr<< endl;
	painter.drawText(0, 0, this->width(), this->height(), Qt::AlignCenter, lightTextStr);
}
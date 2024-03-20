#pragma once
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <QTimer>
#include <QColor>
#include <QPainter>


/*
* Written by shzy.
* Happy for using.
*/


class ZToggleButton : public QWidget
{
	Q_OBJECT
	//Q_PROPERTY(int m_space READ space WRITE setSpace)
	//Q_PROPERTY(bool m_checked READ checked WRITE setChecked)

	//Q_PROPERTY(QColor m_bgColorOn READ bgColorOn WRITE setBgColorOn)
	//Q_PROPERTY(QColor m_bgColorOff READ bgColorOff WRITE setBgColorOff)
	//Q_PROPERTY(QColor m_sliderColorOn READ sliderColorOn WRITE setSliderColorOn)
	//Q_PROPERTY(QColor m_sliderColorOff READ sliderColorOff WRITE setSliderColorOff)

	//Q_PROPERTY(int m_step READ step WRITE setStep)
	//Q_PROPERTY(int m_startX READ startX WRITE setStartX)
	//Q_PROPERTY(int m_endX READ endX WRITE setEndX)

public:
	explicit ZToggleButton(QWidget *parent = 0);

	~ZToggleButton() { }

signals:
	void toggled(bool checked);

public:
	bool isChecked();
	void setChecked(bool checked);

	void setCheckedWithoutSignal(bool checked);

	void setBgColorOn(const QColor &color);
	void setBgColorOff(const QColor &color);
	void setSliderColorOn(const QColor &color);
	void setSliderColorOff(const QColor &color);


private slots:
	void updateValue();

private:
	void drawBackGround(QPainter *painter);
	void drawSlider(QPainter *painter);

protected:
	void paintEvent(QPaintEvent *ev) override;
	void mousePressEvent(QMouseEvent *ev) override;

private:
	int m_space;

	bool m_checked;

	QColor m_bgColorOn;
	QColor m_bgColorOff;
	QColor m_sliderColorOn;
	QColor m_sliderColorOff;

	QTimer *m_timer;
	int m_step;
	int m_startX;
	int m_endX;

};


inline ZToggleButton::ZToggleButton(QWidget *parent) : QWidget(parent)
{
	m_space = 2;
	m_checked = false;

	m_bgColorOn = QColor(73, 194, 100);
	m_bgColorOff = QColor(233, 233, 235);

	m_sliderColorOn = QColor(255, 255, 255);
	m_sliderColorOff = QColor(255, 255, 255);

	m_step = 0;
	m_startX = m_space;
	m_endX = 0;

	m_timer = new QTimer(this);
	m_timer->setInterval(16);
	connect(m_timer, &QTimer::timeout, this, &ZToggleButton::updateValue);

}

//inline void ZToggleButton::setSpace(int space)
//{
//	if (m_space != space)
//	{
//		m_space = space;
//		update();
//	}
//}

inline void ZToggleButton::setChecked(bool checked)
{
	if (m_checked != checked)
	{
		m_checked = checked;

		m_step = (width() - m_space / 2) / 16;

		if (m_checked)
		{
			m_startX = m_space;
		}
		else
		{
			m_startX = width() - height() + m_space;
		}

		m_timer->start();
	}

	emit toggled(checked);
}

inline void ZToggleButton::setCheckedWithoutSignal(bool checked)
{
	if (m_checked != checked)
	{
		m_checked = checked;

		m_step = (width() - m_space / 2) / 16;

		if (m_checked)
		{
			m_startX = m_space;
		}
		else
		{
			m_startX = width() - height() + m_space;
		}

		m_timer->start();
	}
}

inline bool ZToggleButton::isChecked()
{
	return m_checked;
}


inline void ZToggleButton::setBgColorOn(const QColor &color)
{
	if (m_bgColorOn != color)
	{
		m_bgColorOn = color;
		update();
	}
}

inline void ZToggleButton::setBgColorOff(const QColor &color)
{
	if (m_bgColorOff != color)
	{
		m_bgColorOff = color;
		update();
	}
}

inline void ZToggleButton::setSliderColorOn(const QColor &color)
{
	if (m_sliderColorOn != color)
	{
		m_sliderColorOn = color;
		update();
	}
}

inline void ZToggleButton::setSliderColorOff(const QColor &color)
{
	if (m_sliderColorOff != color)
	{
		m_sliderColorOff = color;
		update();
	}
}

inline void ZToggleButton::updateValue()
{
	if (m_checked)
	{
		m_endX = width() - height() + m_space;

		if (m_startX < m_endX)
		{
			m_startX += m_step;

			if (m_startX > m_endX)
			{
				m_startX = m_endX;
			}
		}
		else
		{
			m_startX = m_endX;
			m_timer->stop();
		}
	}
	else
	{
		m_endX = m_space;

		if (m_startX > m_endX)
		{
			m_startX -= m_step;

			if (m_startX < m_endX)
			{
				m_startX = m_endX;
			}
		}
		else
		{
			m_startX = m_endX;
			m_timer->stop();
		}
	}

	update();
}

inline void ZToggleButton::drawBackGround(QPainter *painter)
{
	painter->save();
	painter->setPen(Qt::NoPen);

	QColor bgColor = m_checked ? m_bgColorOn : m_bgColorOff;

	painter->setBrush(bgColor);

	QRect rect(0, 0, width(), height());
	int side = qMin(width(), height());

	QPainterPath path1;
	path1.addEllipse(rect.x(), rect.y(), side, side);

	QPainterPath path2;
	path2.addEllipse(rect.width() - side, rect.y(), side, side);

	QPainterPath path3;
	path3.addRect(rect.x() + side / 2, rect.y(), rect.width() - side, height());

	QPainterPath path = path1 + path2 + path3;
	painter->drawPath(path);

	/* draw text */
	/*int sliderWidth = qMin(height(), width()) - m_space * 2 - 5;
	if (m_checked)
	{
	QRect textRect(0, 0, width() - sliderWidth, height());
	painter->setPen(QPen(m_textColor));
	painter->drawText(textRect, Qt::AlignCenter, m_textOn);
	}
	else
	{
	QRect textRect(sliderWidth, 0, width() - sliderWidth, height());
	painter->setPen(QPen(m_textColor));
	painter->drawText(textRect, Qt::AlignCenter, m_textOff);
	}*/

	painter->restore();
}

inline void ZToggleButton::drawSlider(QPainter *painter)
{
	painter->save();
	painter->setPen(Qt::NoPen);

	QColor color = m_checked ? m_sliderColorOn : m_sliderColorOff;

	painter->setBrush(QBrush(color));

	int sliderWidth = qMin(width(), height()) - m_space * 2;
	QRect rect(m_startX, m_space, sliderWidth, sliderWidth);
	painter->drawEllipse(rect);

	painter->restore();
}

inline void ZToggleButton::paintEvent(QPaintEvent *ev)
{
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

	drawBackGround(&painter);

	drawSlider(&painter);
}

inline void ZToggleButton::mousePressEvent(QMouseEvent *ev)
{
	m_checked = !m_checked;

	m_step = (width() - m_space / 2) / 16;

	if (m_checked)
	{
		m_startX = m_space;
	}
	else
	{
		m_startX = width() - height() + m_space;
	}

	m_timer->start();

	emit toggled(m_checked);
}



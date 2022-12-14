/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "ui/widgets/buttons.h"

namespace Ui {

class SendButton final : public RippleButton {
public:
	explicit SendButton(QWidget *parent);

	static constexpr auto kSlowmodeDelayLimit = 100 * 60;

	enum class Type {
		Send,
		Schedule,
		Save,
		Record,
		Cancel,
		Slowmode,
	};
	[[nodiscard]] Type type() const {
		return _type;
	}
	void setType(Type state);
	void setSlowmodeDelay(int seconds);
	void finishAnimating();

protected:
	void paintEvent(QPaintEvent *e) override;

	QImage prepareRippleMask() const override;
	QPoint prepareRippleStartPosition() const override;

private:
	[[nodiscard]] QPixmap grabContent();
	[[nodiscard]] bool isSlowmode() const;

	void paintRecord(QPainter &p, bool over);
	void paintSave(QPainter &p, bool over);
	void paintCancel(QPainter &p, bool over);
	void paintSend(QPainter &p, bool over);
	void paintSchedule(QPainter &p, bool over);
	void paintSlowmode(QPainter &p);

	Type _type = Type::Send;
	Type _afterSlowmodeType = Type::Send;
	QPixmap _contentFrom, _contentTo;

	Ui::Animations::Simple _a_typeChanged;

	int _slowmodeDelay = 0;
	QString _slowmodeDelayText;

};

} // namespace Ui

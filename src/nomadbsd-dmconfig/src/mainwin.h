/*-
 * Copyright (c) 2019 The NomadBSD Project. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QMainWindow>
#include <QLineEdit>
#include <QCheckBox>
#include <QStatusBar>
#include <QStringList>
#include <QStyle>
#include <QComboBox>
#include <QCloseEvent>
#include <QMessageBox>

class MainWin : public QMainWindow {
	Q_OBJECT
public:
	MainWin(QWidget *paren = 0);

private:
	void closeEvent(QCloseEvent *event);

	static void errAndOut(QString message)
	{
		QMessageBox msgBox;
		msgBox.setWindowModality(Qt::WindowModal);
		msgBox.setText(tr("Fatal error"));
		msgBox.setWindowTitle(tr("Error"));
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setWindowIcon(msgBox.iconPixmap());
		message.append(tr("\n\nPlease send a bug report to the "    \
				  "NomadBSD mailing list.\n\nWe are sorry " \
				  "for the inconvenience\n"));
		msgBox.setInformativeText(message);
		msgBox.addButton(tr("Exit"), QMessageBox::ActionRole);
		msgBox.exec();
		std::exit(1);
	}

	static void cancelMenu()
	{
		QMessageBox msgBox;
		msgBox.setWindowModality(Qt::WindowModal);
		msgBox.setText(tr("Sure you want to quit?"));
		msgBox.setWindowTitle(tr("Cancel"));
		msgBox.setIcon(QMessageBox::Question);
		msgBox.setWindowIcon(msgBox.iconPixmap());
		QPushButton *leave = msgBox.addButton(tr("Quit"),
		    QMessageBox::ActionRole);
		msgBox.setStandardButtons(QMessageBox::Cancel);
		msgBox.setButtonText(QMessageBox::Cancel, tr("Cancel"));
		msgBox.exec();
		if (msgBox.clickedButton() == leave)
			std::exit(0);
	}

	void init(void);
	void querySettings(void);
	void showPreviewImage(QString &);
	QFrame *mkLine(void);
private slots:
	void save(void);
	void quit(void);
	void autologinCBClicked(int);
	void defaultUserCBClicked(int);
	void usernameChanged(int);
	void themeChanged(int);
private:
	QString		cfg_username;
	QString		cfg_theme;
	QString		cfg_autologin;
	QString		saved_username;
	QString		saved_theme;
	QString		saved_autologin;
	QWidget		*defaultUserContainer;
	QComboBox	*themeCbB;
	QComboBox	*usernameCbB;
	QLabel		*previewImage;
	QCheckBox	*autologinCB;
	QCheckBox	*defaultUserCB;
	QStringList	usernames;
	QStringList	themes;
};

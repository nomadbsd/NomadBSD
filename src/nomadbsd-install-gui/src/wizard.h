//-
// Copyright (c) 2019 The NomadBSD Project. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
 
#pragma once
#include <QDebug>
#include <QWizard>
#include <QWizardPage>
#include <QString>
#include <QProcess>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QCheckBox>
#include <QComboBox>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QProgressBar>
#include <QCoreApplication>
#include <sys/types.h>
#include <signal.h>

#define PATH_ETC_PASSWD "/etc/passwd"
#define SHUTDOWN_CMD	"shutdown -p now"
#define REBOOT_CMD	"shutdown -r now"

extern pid_t pid;

class InstallWizard : public QWizard
{
	Q_OBJECT

public:
	InstallWizard(QWidget *parent = 0);
	void accept() override;
	void reject() override;

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
		msgBox.exec();
		std::exit(1);
	}

	static void cancelMenu()
	{
		QMessageBox msgBox;
		msgBox.setWindowModality(Qt::WindowModal);
		msgBox.setText(tr("Are you sure you want to quit?"));
		msgBox.setWindowTitle(tr("Quit installation"));
		msgBox.setIcon(QMessageBox::Question);
		msgBox.setWindowIcon(msgBox.iconPixmap());
		QPushButton *leave = msgBox.addButton(tr("Quit"),
		    QMessageBox::ActionRole);
		msgBox.setStandardButtons(QMessageBox::Cancel);
		msgBox.setButtonText(QMessageBox::Cancel, tr("Cancel"));
		msgBox.exec();
		if (msgBox.clickedButton() == leave) {
			if (pid > (pid_t)-1)
				kill(0, SIGKILL);
			QCoreApplication::exit(0);
		}
	}
};

//////////////////////////////////////////////////////////////////////////////
//
// Welcome page
//
//////////////////////////////////////////////////////////////////////////////
class WelcomePage : public QWizardPage
{
	Q_OBJECT

public:
	WelcomePage(QWidget *parent = 0);
private:
	QLabel *title;
	QLabel *intro;
};

//////////////////////////////////////////////////////////////////////////////
//
// Main window
//
//////////////////////////////////////////////////////////////////////////////
class SettingsPage : public QWizardPage
{
	Q_OBJECT

public:
	SettingsPage(QWidget *parent = 0);
	bool isComplete() const;
public slots:
	void diskSelected(int row);
	void usernameChanged(const QString &username);
	void swapChanged(int mb);
	void lenovofixChanged(int state);
	void autologinChanged(int state);
	void ufsClicked(bool);
	void zfsClicked(bool);
	bool validateUsername(const QString &username) const;
	void readUsernames(void);
private:
	QLabel	    *status;
	QSpinBox    *swapsb;
	QLineEdit   *usernamele;
	QCheckBox   *lenovofixCb;
	QCheckBox   *autologinCb;
	QListWidget *diskls;
	QList<QString> usernames;
};

//////////////////////////////////////////////////////////////////////////////
//
// Summary page
//
//////////////////////////////////////////////////////////////////////////////
class SummaryPage : public QWizardPage
{
	Q_OBJECT
public:
	SummaryPage(QWidget *parent = 0);
protected:
	void initializePage();
private:
	static const int nkeys = 6;
	QLabel *val[nkeys];
	QLabel *key[nkeys];
	QLabel *text;
};

class CommitPage : public QWizardPage
{
	Q_OBJECT
public:
	CommitPage(QWidget *parent = 0);
	bool isComplete() const;
public slots:
	void readCmdOutput();
	void readError();
	void catchError(QProcess::ProcessError);
	void cleanup(int, QProcess::ExitStatus);
protected:
	void initializePage();
private:
	QLabel	     *commandMsg;
	QLabel	     *statusMsg;
	QString	     commandMsgBuf;
	QString	     errorMsgBuf;
	QProcess     proc;
	QProgressBar *progBar;
};

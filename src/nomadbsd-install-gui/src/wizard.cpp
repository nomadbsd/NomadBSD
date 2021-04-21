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

#include <QVariant>
#include <QStyle>
#include <QProcess>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QCoreApplication>
#include <QScrollArea>
#include <QFormLayout>
#include <QStatusBar>
#include <QFile>

#include "wizard.h"
#include "backend.h"
#include "qt-helper/qt-helper.h"
//////////////////////////////////////////////////////////////////////////////
//
// Global variables to hold the configuration
//
//////////////////////////////////////////////////////////////////////////////
static QString cfg_swap	     = "2048";
static QString cfg_username  = "settler";
static QString cfg_lenovofix = "0";
static QString cfg_autologin = "0";
static QString cfg_fs	     = "UFS";
static QString cfg_disk;
static QString cfg_disk_descr;

//////////////////////////////////////////////////////////////////////////////
pid_t pid = (pid_t)-1;

InstallWizard::InstallWizard(QWidget *parent) : QWizard(parent)
{
	QIcon winIcon = qh_loadIcon("drive-harddisk", 0);
	setWindowTitle(tr("NomadBSD Installation Wizard"));
	setWindowIcon(winIcon);

	setButtonText(QWizard::NextButton,   tr("Next"));
	setButtonText(QWizard::BackButton,   tr("Back"));
	setButtonText(QWizard::CommitButton, tr("Commit"));
	setButtonText(QWizard::FinishButton, tr("Finish"));
	setButtonText(QWizard::CancelButton, tr("Cancel"));

	addPage(new WelcomePage);
	addPage(new SettingsPage);
	addPage(new SummaryPage);
	addPage(new CommitPage);
}

void InstallWizard::accept()
{
	QDialog::accept();
}

void InstallWizard::reject()
{
	cancelMenu();
}

//////////////////////////////////////////////////////////////////////////////
//
// Welcome page
//
//////////////////////////////////////////////////////////////////////////////
WelcomePage::WelcomePage(QWidget *parent) : QWizardPage(parent)
{
	QLabel	    *intro  = new QLabel;
	QLabel	    *title  = new QLabel;
	QVBoxLayout *layout = new QVBoxLayout;

	title->setText(tr("<b>Welcome to the NomadBSD installation wizard." \
			  "</b><br/><br/>"));
	intro->setText(tr("This program will install your NomadBSD with its " \
			  "current configuration on a hard disk.\n\n"));
	setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/logo.png"));
	setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo.png"));
	intro->setWordWrap(true);
	layout->addWidget(title);
	layout->addWidget(intro);
	setLayout(layout);
}

//////////////////////////////////////////////////////////////////////////////
//
// Main page - Select target disk, set swap and username. 
//
//////////////////////////////////////////////////////////////////////////////
SettingsPage::SettingsPage(QWidget *parent) : QWizardPage(parent)
{
	status		    = new QLabel;
	swapsb		    = new QSpinBox;
	diskls		    = new QListWidget(this);
	usernamele	    = new QLineEdit;
	lenovofixCb	    = new QCheckBox;
	autologinCb	    = new QCheckBox;
	QVBoxLayout *vbox   = new QVBoxLayout;
	QLabel	    *dlabel = new QLabel;
	QLabel	    *slabel = new QLabel;
	QLabel	    *ulabel = new QLabel;
	QLabel	    *info   = new QLabel;
	QRegExp	    chars   = QRegExp("[a-z]+");
	QProcess    proc;
        QByteArray  line;
	QStringList args;
	args << "devlist";

	readUsernames();
  	proc.setReadChannel(QProcess::StandardOutput);
	proc.start(PATH_NOMADBSD_INSTALL, args);
	(void)proc.waitForStarted(-1);

	//
	// According to the Qt docs, we can not rely on the return value.
	// We have to check state().
	//
	if (proc.state() == QProcess::NotRunning) {
		InstallWizard::errAndOut(tr("Couldn't start backend '%1': %2")
		    .arg(BACKEND_GET_DISKS).arg(proc.errorString()));
	}
	while (proc.waitForReadyRead(-1)) {
		while (!(line = proc.readLine()).isEmpty()) {
			// Remove trailing newline
			line.truncate(line.size() - 1);
			QList<QByteArray>fields = line.split('|');
			if (fields.count() < 2)
				continue;
			QString descr = fields.at(1);
			QString disk  = fields.at(0);
			QString label = QString("%1 - %2").arg(disk).arg(descr);
			QListWidgetItem *item = new QListWidgetItem(label);
			item->setData(Qt::UserRole, QVariant(disk));
			diskls->addItem(item);
		}
        }
	proc.waitForFinished(-1);
	if (proc.exitCode() != 0) {
		InstallWizard::errAndOut(
		    QString("Command '%1' returned with an error.")
			.arg(BACKEND_GET_DISKS));
	}
	dlabel->setText(tr("<b>Please select the device you want to install " \
			   "NomadBSD on</b>"));
	vbox->addWidget(dlabel);
	vbox->addWidget(diskls);

	//
	// Filesystem selection
	//
	QGroupBox *groupBox = new QGroupBox(tr("Target filesystem type"));
	QRadioButton *rbUFS = new QRadioButton(tr("&UFS"));
	QRadioButton *rbZFS = new QRadioButton(tr("&ZFS"));
	rbUFS->setChecked(true);

	QVBoxLayout *rbVbox = new QVBoxLayout;
	rbVbox->addWidget(rbUFS);
	rbVbox->addWidget(rbZFS);
	rbVbox->addStretch(1);
	groupBox->setLayout(rbVbox);
	vbox->addWidget(groupBox);

	//
	// Lenovofix
	//
	lenovofixCb->setCheckState(Qt::Unchecked);
	lenovofixCb->setTristate(false);
	lenovofixCb->setText(tr("Enable lenovofix"));
	lenovofixCb->setToolTip(tr("Setting this allows Lenovo systems with " \
				   "a buggy BIOS to boot from GPT partitions"));
	vbox->addWidget(lenovofixCb);

	//
	// Swap setting
	//
	slabel->setText(tr("<b>Desired size of the swap partition</b>"));

	swapsb->setMinimum(0);
	swapsb->setMaximum(100000);
	swapsb->setSuffix(" MB");
	swapsb->setValue(cfg_swap.toInt(0, 10));

	vbox->addWidget(slabel);
	vbox->addWidget(swapsb);
	
	//
	// Username
	//
	ulabel->setText(tr("<b>Username*</b>"));
	usernamele->setMaxLength(8);
	usernamele->setValidator(new QRegExpValidator(chars));
	usernamele->setPlaceholderText(cfg_username);
	autologinCb->setText(tr("Auto-login user"));
	status->setStyleSheet("font-weight: bold; color: red");	
	info->setText(tr("<i>* The installation script will adopt nomad's " \
			  "complete account. Only the username changes.</i>"));
	info->setWordWrap(true);

	vbox->addWidget(ulabel);
	vbox->addWidget(usernamele);
	vbox->addWidget(autologinCb);
	vbox->addWidget(status);
	vbox->addWidget(info);
	setLayout(vbox);
	if (diskls->count() > 0) {
		diskls->setCurrentRow(0);
		diskSelected(0);
	}
	connect(diskls, SIGNAL(currentRowChanged(int)), this,
	    SLOT(diskSelected(int)));
	connect(swapsb, SIGNAL(valueChanged(int)), this,
            SLOT(swapChanged(int)));
	connect(usernamele, SIGNAL(textChanged(const QString &)), this,
	    SLOT(usernameChanged(const QString &)));
	connect(lenovofixCb, SIGNAL(stateChanged(int)), this,
		SLOT(lenovofixChanged(int)));
	connect(autologinCb, SIGNAL(stateChanged(int)), this,
		SLOT(autologinChanged(int)));
	connect(rbUFS, SIGNAL(clicked(bool)), this,
		SLOT(ufsClicked(bool)));
	connect(rbZFS, SIGNAL(clicked(bool)), this,
		SLOT(zfsClicked(bool)));
}

void SettingsPage::diskSelected(int row)
{
	cfg_disk = diskls->item(row)->data(Qt::UserRole).toString();
	cfg_disk_descr = diskls->item(row)->text();
}

bool SettingsPage::validateUsername(const QString &username) const
{
	if (cfg_username.length() < 1) {
		status->setText(tr("Username must not be empty"));
		return (false);
	}
	for (int i = 0; i < usernames.count(); i++) {
		if (username == usernames.at(i)) {
			status->setText(tr("Username already in use"));
			return (false);
		}
	}
	status->setText("");
	return (true);
}

void SettingsPage::readUsernames()
{
	QFile file(PATH_ETC_PASSWD);

	if (!file.open(QIODevice::ReadOnly)) {
		InstallWizard::errAndOut(tr("Couldn't read '%1': %2")
		    .arg(PATH_ETC_PASSWD).arg(file.error()));
		return;
	}
	while (!file.atEnd()) {
		QByteArray line = file.readLine();
		QList<QByteArray>fields = line.split(':');
		usernames.append(fields[0]);
	}
	file.close();
}

void SettingsPage::autologinChanged(int state)
{
	cfg_autologin.setNum(state);
}

void SettingsPage::usernameChanged(const QString &username)
{
	cfg_username = username;
	emit completeChanged();
}

bool SettingsPage::isComplete() const
{
	return (validateUsername(cfg_username));
}

void SettingsPage::lenovofixChanged(int state)
{
	cfg_lenovofix.setNum(state);
}

void SettingsPage::swapChanged(int mb)
{
	cfg_swap.setNum(mb);
}

void SettingsPage::ufsClicked(bool active)
{
	if (active)
		cfg_fs = "UFS";
}

void SettingsPage::zfsClicked(bool active)
{
	if (active)
		cfg_fs = "ZFS";
}


//////////////////////////////////////////////////////////////////////////////
//
// Summary page
//
//////////////////////////////////////////////////////////////////////////////
SummaryPage::SummaryPage(QWidget *parent) : QWizardPage(parent)
{
	text		  = new QLabel;
	QFormLayout *form = new QFormLayout;
	QVBoxLayout *vbox = new QVBoxLayout;

	for (int n = 0; n < nkeys; n++) {
		key[n]		  = new QLabel;
		val[n]		  = new QLabel;
		key[n]->setStyleSheet("font-weight: bold;");
		form->addRow(key[n], val[n]);
	}
	vbox->addWidget(new QLabel(tr("<b>Summary:</b><br/><br/>")));
	vbox->addLayout(form);
	vbox->addWidget(text);
	setLayout(vbox);
	setCommitPage(true);
}

void SummaryPage::initializePage()
{
	QString lfstate =
		(cfg_lenovofix.toInt(0, 10) == 0 ? tr("No") : tr("Yes"));
	QString alstate =
		(cfg_autologin.toInt(0, 10) == 0 ? tr("No") : tr("Yes"));
	struct summary_s {
		QString key;
		QString val;
	} summary[] = {
		{ tr("Target disk:"),  cfg_disk_descr },
		{ tr("Swap (in MB):"), cfg_swap       },
		{ tr("Username:"),     cfg_username   },
		{ tr("Auto-login:"),   alstate	      },
		{ tr("Filesystem:"),   cfg_fs	      },
		{ tr("Lenovofix:"),    lfstate	      }
	};
	for (int n = 0; n < nkeys; n++) {
		key[n]->setText(summary[n].key);
		val[n]->setText(summary[n].val);
	}
	text->setText(tr("<br/><br/><b>Warning:<br/><br/></b>\nIf you click " \
			 "<i>commit</i>, the system will be written to " \
			 "<i>%1</i>. All data on <i>%1</i> will be lost!")
			 .arg(cfg_disk));
	text->setWordWrap(true);
}

CommitPage::CommitPage(QWidget *parent) : QWizardPage(parent)
{
	statusMsg	       = new QLabel;
	commandMsg	       = new QLabel;
	progBar		       = new QProgressBar;
	QWidget	    *container = new QWidget;
	QVBoxLayout *vbox      = new QVBoxLayout(container);
	QVBoxLayout *layout    = new QVBoxLayout;
	QScrollArea *sa	       = new QScrollArea(this);

	sa->setWidget(container);
	sa->setWidgetResizable(true);

	progBar->setRange(0, 0);
	progBar->setValue(0);
	progBar->setVisible(false);

	layout->addWidget(statusMsg, 0, Qt::AlignCenter);
	layout->addWidget(sa);

	statusMsg->setStyleSheet("font-weight: bold;");
	commandMsg->setStyleSheet("font-family: monospace;");

	vbox->addWidget(commandMsg, 1, Qt::AlignLeft);
	vbox->addWidget(progBar, 1, Qt::AlignCenter);
	setLayout(layout);
}

void CommitPage::initializePage()
{
	QMessageBox msgBox;
	msgBox.setWindowModality(Qt::WindowModal);
	msgBox.setText(tr("Last chance to quit installation."));
	msgBox.setWindowTitle(tr("Last chance"));
	msgBox.setIcon(QMessageBox::Warning);
	msgBox.setWindowIcon(msgBox.iconPixmap());
	QPushButton *leave = msgBox.addButton(tr("Quit"),
	QMessageBox::ActionRole);
	msgBox.setStandardButtons(QMessageBox::Apply);
	msgBox.setButtonText(QMessageBox::Apply, tr("Install"));
	msgBox.exec();
	if (msgBox.clickedButton() == leave) {
		std::exit(0);
	}
	QStringList args;
	args << "commit" <<
		"-u" << cfg_username <<
		"-d" << cfg_disk <<
		"-s" << cfg_swap <<
		"-f" << cfg_fs;
	if (cfg_lenovofix.toInt(0, 10) != 0)
		args.append("-l");
	if (cfg_autologin.toInt(0, 10) != 0)
		args.append("-a");
	proc.setReadChannel(QProcess::StandardOutput);
	proc.start(PATH_NOMADBSD_INSTALL, args);
	pid = (pid_t)proc.processId();
	(void)proc.waitForStarted(-1);
	//
	// According to the Qt docs, we can not rely on the return value.
	// We have to check state().
	//
	if (proc.state() == QProcess::NotRunning) {
		InstallWizard::errAndOut(tr("Couldn't start backend '%1': %2")
		    .arg(BACKEND_COMMIT).arg(proc.errorString()));
	}
	proc.closeWriteChannel();
	connect(&proc, SIGNAL(readyReadStandardOutput()), this,
	    SLOT(readCmdOutput()));
	connect(&proc, SIGNAL(readyReadStandardError()), this,
	    SLOT(readError()));
	connect(&proc, SIGNAL(finished(int, QProcess::ExitStatus)), this,
	    SLOT(cleanup(int, QProcess::ExitStatus)));
	connect(&proc, SIGNAL(errorOccurred(QProcess::ProcessError)), this,
	    SLOT(catchError(QProcess::ProcessError)));
}

void CommitPage::catchError(QProcess::ProcessError /* perr */)
{
	InstallWizard::errAndOut(
	    QString(tr("An unexpected error occured while executing %1: %2")
	        .arg(PATH_NOMADBSD_INSTALL).arg(proc.errorString())));
}

void CommitPage::readCmdOutput()
{
	QByteArray line;
	QFontMetrics fm(commandMsg->font());
	const int maxc = fm.horizontalAdvance("m") * 50;

	proc.setReadChannel(QProcess::StandardOutput);
	while (!(line = proc.readLine()).isEmpty()) {
		if (line[0] == '%') {
			// Progress
			line.remove(0, 1);
			int n = line.toInt(0, 10);
			if (!progBar->isVisible())
				progBar->setVisible(true);
			progBar->setRange(0, n < 0 ? 0 : 100);
			progBar->setValue(n < 0 ? 0 : n);
		} else if (line[0] == '!') {
			// Status message
			line.remove(0, 1);
			errorMsgBuf = "";
			commandMsgBuf = "";
			commandMsg->setText("");
			statusMsg->setText(line);
			progBar->setValue(0);
			progBar->setVisible(false);
		} else if (line[0] == '>') {
			// Single line output
			line.remove(0, 1);
			//
			// Use elided version of the string with "..." in the
			// middle if the string is too long.
			//
			QString s = fm.elidedText(line, Qt::ElideMiddle, maxc);
			commandMsg->setText(s);
		} else {
			// Command output
			commandMsgBuf.append(line);
			commandMsg->setText(commandMsgBuf);
		}
	}
}

void CommitPage::readError()
{
	QByteArray line;	

	proc.setReadChannel(QProcess::StandardError);
	while (!(line = proc.readLine()).isEmpty())
		errorMsgBuf.append(line);
}

void CommitPage::cleanup(int exitCode, QProcess::ExitStatus /* exitStatus */)
{
	if (exitCode != 0) {
		InstallWizard::errAndOut(
		    QString("%1 returned with error code %2:\n\"%3\"")
			.arg(BACKEND_COMMIT).arg(exitCode).arg(errorMsgBuf));
	}
	emit completeChanged();
}

bool CommitPage::isComplete() const
{
	if (proc.state() == QProcess::NotRunning)
		return (true);
	return (false);
}

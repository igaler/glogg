/*
 * Copyright (C) 2014 Nicolas Bonnefon and other contributors
 *
 * This file is part of glogg.
 *
 * glogg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * glogg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with glogg.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "log.h"

#include <cassert>

#include <QProcess>
#include <QComboBox>
#include <QHBoxLayout>

#include "decodedockwidget.h"
#include "persistentinfo.h"
#include "configuration.h"


DecodeDockWidget::DecodeDockWidget() : QDockWidget(),
    decodedTextBox_(),
    comboBox_()
{    
    QString  command("python");
    QStringList params = QStringList()<<"-c"<<"import g_script; g_script.comboBox()";

    QProcess *process = new QProcess();
    process->start(command, params);
    process->waitForFinished();
    QString p_stdout = process->readAll();
    process->close();

    comboBox_.addItems(p_stdout.split(" "));

    decodedTextBox_.setReadOnly(true);
    decodedTextBox_.setLineWrapMode( QTextEdit::NoWrap );

    QPalette pallet = decodedTextBox_.palette();
    pallet.setColor(QPalette::Base,Qt::darkBlue);
    decodedTextBox_.setPalette(pallet);
    decodedTextBox_.setTextColor(Qt::yellow);
    decodedTextBox_.setAutoFillBackground(true);

    connect( &comboBox_, SIGNAL(currentTextChanged( const QString& ) ) ,
             this, SLOT( updateProjectHandler( const QString& ) ) );

    QWidget* view = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();

    layout->addWidget(&comboBox_);
    layout->addWidget(&decodedTextBox_);
    layout->setContentsMargins(1,1,1,1);
    view->setLayout(layout);

    setWidget(view);
    setFeatures(DockWidgetMovable|DockWidgetFloatable|DockWidgetClosable);
    setWindowTitle(tr("Decoded Line"));

}


void DecodeDockWidget::updateTextHandler( const QString& text )
{
    currStr_ = text;
    parseLine();
}

void DecodeDockWidget::updateProjectHandler(const QString& proj )
{
    parseLine();
}


void DecodeDockWidget::applyOptions()
{
    std::shared_ptr<Configuration> config =
        Persistent<Configuration>( "settings" );
    QFont font = config->mainFont();

    LOG(logDEBUG) << "DecodeDockWidget::applyOptions";

    // Whatever font we use, we should NOT use kerning
    font.setKerning( false );
    font.setFixedPitch( true );
#if QT_VERSION > 0x040700
    // Necessary on systems doing subpixel positionning (e.g. Ubuntu 12.04)
    font.setStyleStrategy( QFont::ForceIntegerMetrics );
#endif


    decodedTextBox_.setFont(font);
    comboBox_.setFont(font);
}


void DecodeDockWidget::parseLine()
{
    QString  command("python");
    QStringList params = QStringList()<<"g_script.py" << currStr_ << comboBox_.currentText();

    QProcess *process = new QProcess();
    process->start(command, params);
    process->waitForFinished();
    QString p_stdout = process->readAll();
    decodedTextBox_.setText(p_stdout);
    //decodedTextBox_.setPlainText(p_stdout);
    process->close();
}

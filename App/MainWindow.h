/***************************************************************************
 *                                                                         *
 *   This file is part of the Fotowall project,                            *
 *       http://www.enricoros.com/opensource/fotowall                      *
 *                                                                         *
 *   Copyright (C) 2007-2009 by Enrico Ros <enrico.ros@gmail.com>          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef __MainWindow_h__
#define __MainWindow_h__

#include "Shared/ApplianceContainer.h"
#include "Shared/ApplianceManager.h"
class Canvas;
class LikeBack;
class QMenu;
class QNetworkReply;
namespace Ui { class MainWindow; }
namespace WordCloud { class Cloud; }

class MainWindow : public Appliance::Container
{
    Q_OBJECT
    public:
        MainWindow(const QStringList & loadUrls = QStringList(), QWidget * parent = 0);
        ~MainWindow();

        // content editing
        void editCanvas(Canvas * newCanvas);
        void editWordcloud(WordCloud::Cloud * cloud);

    protected:
        // ::Appliance::Container
        void applianceSetScene(AbstractScene * scene);
        void applianceSetTopbar(const QList<QWidget *> & widgets);
        void applianceSetSidebar(QWidget * widget);
        void applianceSetCentralwidget(QWidget * widget);
        void applianceSetValue(quint32 id, const QVariant & value);

        // ::QWidget
        void closeEvent(QCloseEvent * event);

    private:
        void hideInLayout(QLayout * layout) const;
        Canvas * currentCanvas() const;
        QMenu * createOnlineHelpMenu();
        void checkForTutorial();
        void checkForUpdates();
        void createLikeBack();

        Ui::MainWindow *        ui;
        Appliance::Manager *    m_appManager;
        LikeBack *              m_likeBack;
        QAction *               m_aHelpTutorial;
        QString                 m_website;

    private Q_SLOTS:
        // notifications
        void slotApplianceClicked(quint32);
        void slotApplianceStructureChanged();

        // file box
        bool on_loadButton_clicked();
        bool on_saveButton_clicked();
        void on_exportButton_clicked();

        // help box
        void on_introButton_clicked();
        void on_lbBug_clicked();
        void on_lbFeature_clicked();
        void on_lbDislike_clicked();
        void on_lbLike_clicked();
        void slotHelpWebsite();
        void slotHelpWebsiteFetched();
        void slotHelpWebsiteFetchError();
        void slotHelpTutorial();
        void slotHelpUpdates();
        void slotVerifyTutorial(QNetworkReply * reply);

        // setup box
        void on_accelBox_toggled(bool checked);
        void on_transpBox_toggled(bool checked);
};

#endif
# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'mainwindow.ui'
#
# Created: Mon Jul 24 11:28:34 2017
#      by: pyside-uic 0.2.15 running on PySide 1.2.2
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1135, 811)
        MainWindow.setWindowTitle("")
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap("../../img/icon.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        MainWindow.setWindowIcon(icon)
        self.centralwidget = QtGui.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.verticalLayout = QtGui.QVBoxLayout(self.centralwidget)
        self.verticalLayout.setObjectName("verticalLayout")
        self.Toolbar = QtGui.QWidget(self.centralwidget)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred, QtGui.QSizePolicy.Maximum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.Toolbar.sizePolicy().hasHeightForWidth())
        self.Toolbar.setSizePolicy(sizePolicy)
        self.Toolbar.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.Toolbar.setObjectName("Toolbar")
        self.horizontalLayout = QtGui.QHBoxLayout(self.Toolbar)
        self.horizontalLayout.setSpacing(6)
        self.horizontalLayout.setSizeConstraint(QtGui.QLayout.SetNoConstraint)
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.Lsdrdvc = QtGui.QLabel(self.Toolbar)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Maximum, QtGui.QSizePolicy.Maximum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.Lsdrdvc.sizePolicy().hasHeightForWidth())
        self.Lsdrdvc.setSizePolicy(sizePolicy)
        self.Lsdrdvc.setMinimumSize(QtCore.QSize(86, 0))
        self.Lsdrdvc.setMaximumSize(QtCore.QSize(86, 16777215))
        self.Lsdrdvc.setObjectName("Lsdrdvc")
        self.horizontalLayout.addWidget(self.Lsdrdvc)
        self.CBsdr = QtGui.QComboBox(self.Toolbar)
        self.CBsdr.setMinimumSize(QtCore.QSize(85, 0))
        self.CBsdr.setMaximumSize(QtCore.QSize(125, 16777215))
        self.CBsdr.setObjectName("CBsdr")
        self.horizontalLayout.addWidget(self.CBsdr)
        self.Lsdrrate = QtGui.QLabel(self.Toolbar)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Fixed, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.Lsdrrate.sizePolicy().hasHeightForWidth())
        self.Lsdrrate.setSizePolicy(sizePolicy)
        self.Lsdrrate.setMinimumSize(QtCore.QSize(86, 0))
        self.Lsdrrate.setMaximumSize(QtCore.QSize(86, 16777215))
        self.Lsdrrate.setObjectName("Lsdrrate")
        self.horizontalLayout.addWidget(self.Lsdrrate)
        self.CBsdrrate = QtGui.QComboBox(self.Toolbar)
        self.CBsdrrate.setMinimumSize(QtCore.QSize(75, 0))
        self.CBsdrrate.setMaximumSize(QtCore.QSize(90, 16777215))
        self.CBsdrrate.setObjectName("CBsdrrate")
        self.horizontalLayout.addWidget(self.CBsdrrate)
        self.TBstartsdr = QtGui.QToolButton(self.Toolbar)
        self.TBstartsdr.setIconSize(QtCore.QSize(32, 32))
        self.TBstartsdr.setPopupMode(QtGui.QToolButton.DelayedPopup)
        self.TBstartsdr.setAutoRaise(True)
        self.TBstartsdr.setObjectName("TBstartsdr")
        self.horizontalLayout.addWidget(self.TBstartsdr)
        self.TBsenddataread = QtGui.QToolButton(self.Toolbar)
        self.TBsenddataread.setIconSize(QtCore.QSize(32, 32))
        self.TBsenddataread.setAutoRaise(True)
        self.TBsenddataread.setObjectName("TBsenddataread")
        self.horizontalLayout.addWidget(self.TBsenddataread)
        self.TBconfig = QtGui.QToolButton(self.Toolbar)
        self.TBconfig.setIconSize(QtCore.QSize(32, 32))
        self.TBconfig.setAutoRaise(True)
        self.TBconfig.setObjectName("TBconfig")
        self.horizontalLayout.addWidget(self.TBconfig)
        self.TBping = QtGui.QToolButton(self.Toolbar)
        self.TBping.setIconSize(QtCore.QSize(32, 32))
        self.TBping.setAutoRaise(True)
        self.TBping.setObjectName("TBping")
        self.horizontalLayout.addWidget(self.TBping)
        self.TBsendreq = QtGui.QToolButton(self.Toolbar)
        self.TBsendreq.setIconSize(QtCore.QSize(32, 32))
        self.TBsendreq.setCheckable(False)
        self.TBsendreq.setAutoRaise(True)
        self.TBsendreq.setObjectName("TBsendreq")
        self.horizontalLayout.addWidget(self.TBsendreq)
        self.space2 = QtGui.QLabel(self.Toolbar)
        self.space2.setText("")
        self.space2.setObjectName("space2")
        self.horizontalLayout.addWidget(self.space2)
        self.Wfreqconf = QtGui.QWidget(self.Toolbar)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Maximum, QtGui.QSizePolicy.Maximum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.Wfreqconf.sizePolicy().hasHeightForWidth())
        self.Wfreqconf.setSizePolicy(sizePolicy)
        self.Wfreqconf.setObjectName("Wfreqconf")
        self.verticalLayout_4 = QtGui.QVBoxLayout(self.Wfreqconf)
        self.verticalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.Wfreqconfbeacon = QtGui.QWidget(self.Wfreqconf)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Maximum, QtGui.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.Wfreqconfbeacon.sizePolicy().hasHeightForWidth())
        self.Wfreqconfbeacon.setSizePolicy(sizePolicy)
        self.Wfreqconfbeacon.setObjectName("Wfreqconfbeacon")
        self.horizontalLayout_6 = QtGui.QHBoxLayout(self.Wfreqconfbeacon)
        self.horizontalLayout_6.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_6.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_6.setObjectName("horizontalLayout_6")
        self.Lbeaconfreq = QtGui.QLabel(self.Wfreqconfbeacon)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Maximum, QtGui.QSizePolicy.Maximum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.Lbeaconfreq.sizePolicy().hasHeightForWidth())
        self.Lbeaconfreq.setSizePolicy(sizePolicy)
        self.Lbeaconfreq.setObjectName("Lbeaconfreq")
        self.horizontalLayout_6.addWidget(self.Lbeaconfreq)
        self.SBbeaconfreq = QtGui.QDoubleSpinBox(self.Wfreqconfbeacon)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Maximum, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.SBbeaconfreq.sizePolicy().hasHeightForWidth())
        self.SBbeaconfreq.setSizePolicy(sizePolicy)
        self.SBbeaconfreq.setDecimals(3)
        self.SBbeaconfreq.setMinimum(1.0)
        self.SBbeaconfreq.setMaximum(999.999)
        self.SBbeaconfreq.setProperty("value", 1.0)
        self.SBbeaconfreq.setObjectName("SBbeaconfreq")
        self.horizontalLayout_6.addWidget(self.SBbeaconfreq)
        self.verticalLayout_4.addWidget(self.Wfreqconfbeacon)
        self.Wfreqconftltc = QtGui.QWidget(self.Wfreqconf)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Maximum, QtGui.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.Wfreqconftltc.sizePolicy().hasHeightForWidth())
        self.Wfreqconftltc.setSizePolicy(sizePolicy)
        self.Wfreqconftltc.setObjectName("Wfreqconftltc")
        self.horizontalLayout_3 = QtGui.QHBoxLayout(self.Wfreqconftltc)
        self.horizontalLayout_3.setSpacing(0)
        self.horizontalLayout_3.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_3.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.Ltltc = QtGui.QLabel(self.Wfreqconftltc)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Maximum, QtGui.QSizePolicy.Maximum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.Ltltc.sizePolicy().hasHeightForWidth())
        self.Ltltc.setSizePolicy(sizePolicy)
        self.Ltltc.setObjectName("Ltltc")
        self.horizontalLayout_3.addWidget(self.Ltltc)
        self.SBtltcfreq = QtGui.QDoubleSpinBox(self.Wfreqconftltc)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Maximum, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.SBtltcfreq.sizePolicy().hasHeightForWidth())
        self.SBtltcfreq.setSizePolicy(sizePolicy)
        self.SBtltcfreq.setDecimals(3)
        self.SBtltcfreq.setMinimum(1.0)
        self.SBtltcfreq.setMaximum(999.99)
        self.SBtltcfreq.setProperty("value", 1.0)
        self.SBtltcfreq.setObjectName("SBtltcfreq")
        self.horizontalLayout_3.addWidget(self.SBtltcfreq)
        self.verticalLayout_4.addWidget(self.Wfreqconftltc)
        self.horizontalLayout.addWidget(self.Wfreqconf)
        self.verticalLayout.addWidget(self.Toolbar)
        self.TWmain = QtGui.QTabWidget(self.centralwidget)
        self.TWmain.setTabPosition(QtGui.QTabWidget.North)
        self.TWmain.setTabShape(QtGui.QTabWidget.Rounded)
        self.TWmain.setObjectName("TWmain")
        self.tabFlight = QtGui.QWidget()
        self.tabFlight.setObjectName("tabFlight")
        self.verticalLayout_3 = QtGui.QVBoxLayout(self.tabFlight)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.Lworldmap = QtGui.QLabel(self.tabFlight)
        self.Lworldmap.setMinimumSize(QtCore.QSize(640, 360))
        self.Lworldmap.setText("")
        self.Lworldmap.setScaledContents(True)
        self.Lworldmap.setObjectName("Lworldmap")
        self.verticalLayout_3.addWidget(self.Lworldmap)
        self.line = QtGui.QFrame(self.tabFlight)
        self.line.setWindowModality(QtCore.Qt.WindowModal)
        self.line.setFrameShape(QtGui.QFrame.HLine)
        self.line.setFrameShadow(QtGui.QFrame.Sunken)
        self.line.setObjectName("line")
        self.verticalLayout_3.addWidget(self.line)
        self.Wflightunder = QtGui.QWidget(self.tabFlight)
        self.Wflightunder.setMaximumSize(QtCore.QSize(16777215, 250))
        self.Wflightunder.setObjectName("Wflightunder")
        self.horizontalLayout_2 = QtGui.QHBoxLayout(self.Wflightunder)
        self.horizontalLayout_2.setSpacing(10)
        self.horizontalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.Lradar = QtGui.QLabel(self.Wflightunder)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.MinimumExpanding, QtGui.QSizePolicy.MinimumExpanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.Lradar.sizePolicy().hasHeightForWidth())
        self.Lradar.setSizePolicy(sizePolicy)
        self.Lradar.setMinimumSize(QtCore.QSize(200, 200))
        self.Lradar.setMaximumSize(QtCore.QSize(400, 400))
        self.Lradar.setText("")
        self.Lradar.setObjectName("Lradar")
        self.horizontalLayout_2.addWidget(self.Lradar)
        self.VLsatinfo = QtGui.QVBoxLayout()
        self.VLsatinfo.setSpacing(1)
        self.VLsatinfo.setObjectName("VLsatinfo")
        self.Lsalelliteinfo = QtGui.QLabel(self.Wflightunder)
        self.Lsalelliteinfo.setObjectName("Lsalelliteinfo")
        self.VLsatinfo.addWidget(self.Lsalelliteinfo)
        self.TEsatelliteinfo = QtGui.QTextEdit(self.Wflightunder)
        self.TEsatelliteinfo.setMaximumSize(QtCore.QSize(10000000, 300))
        self.TEsatelliteinfo.setReadOnly(True)
        self.TEsatelliteinfo.setObjectName("TEsatelliteinfo")
        self.VLsatinfo.addWidget(self.TEsatelliteinfo)
        self.horizontalLayout_2.addLayout(self.VLsatinfo)
        self.verticalLayout_3.addWidget(self.Wflightunder)
        self.TWmain.addTab(self.tabFlight, "")
        self.tabRequest = QtGui.QWidget()
        self.tabRequest.setObjectName("tabRequest")
        self.verticalLayout_2 = QtGui.QVBoxLayout(self.tabRequest)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.Wrequestbar = QtGui.QWidget(self.tabRequest)
        self.Wrequestbar.setMaximumSize(QtCore.QSize(16777215, 27))
        self.Wrequestbar.setObjectName("Wrequestbar")
        self.horizontalLayout_4 = QtGui.QHBoxLayout(self.Wrequestbar)
        self.horizontalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_4.setObjectName("horizontalLayout_4")
        self.Lcfgfile = QtGui.QLabel(self.Wrequestbar)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Maximum, QtGui.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.Lcfgfile.sizePolicy().hasHeightForWidth())
        self.Lcfgfile.setSizePolicy(sizePolicy)
        self.Lcfgfile.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.Lcfgfile.setObjectName("Lcfgfile")
        self.horizontalLayout_4.addWidget(self.Lcfgfile)
        self.Bcfgopen = QtGui.QPushButton(self.Wrequestbar)
        self.Bcfgopen.setMaximumSize(QtCore.QSize(80, 16777215))
        self.Bcfgopen.setObjectName("Bcfgopen")
        self.horizontalLayout_4.addWidget(self.Bcfgopen)
        self.Bcfgsaveas = QtGui.QPushButton(self.Wrequestbar)
        self.Bcfgsaveas.setMaximumSize(QtCore.QSize(80, 16777215))
        self.Bcfgsaveas.setObjectName("Bcfgsaveas")
        self.horizontalLayout_4.addWidget(self.Bcfgsaveas)
        self.Bcheckall = QtGui.QPushButton(self.Wrequestbar)
        self.Bcheckall.setMaximumSize(QtCore.QSize(80, 16777215))
        self.Bcheckall.setObjectName("Bcheckall")
        self.horizontalLayout_4.addWidget(self.Bcheckall)
        self.Buncheckall = QtGui.QPushButton(self.Wrequestbar)
        self.Buncheckall.setMaximumSize(QtCore.QSize(90, 16777215))
        self.Buncheckall.setObjectName("Buncheckall")
        self.horizontalLayout_4.addWidget(self.Buncheckall)
        self.space3 = QtGui.QLabel(self.Wrequestbar)
        self.space3.setText("")
        self.space3.setObjectName("space3")
        self.horizontalLayout_4.addWidget(self.space3)
        self.Lreqsattype = QtGui.QLabel(self.Wrequestbar)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Maximum, QtGui.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.Lreqsattype.sizePolicy().hasHeightForWidth())
        self.Lreqsattype.setSizePolicy(sizePolicy)
        self.Lreqsattype.setObjectName("Lreqsattype")
        self.horizontalLayout_4.addWidget(self.Lreqsattype)
        self.CBreqtype = QtGui.QComboBox(self.Wrequestbar)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Maximum, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.CBreqtype.sizePolicy().hasHeightForWidth())
        self.CBreqtype.setSizePolicy(sizePolicy)
        self.CBreqtype.setObjectName("CBreqtype")
        self.horizontalLayout_4.addWidget(self.CBreqtype)
        self.verticalLayout_2.addWidget(self.Wrequestbar)
        self.Wrequestdata = QtGui.QWidget(self.tabRequest)
        self.Wrequestdata.setObjectName("Wrequestdata")
        self.verticalLayout_2.addWidget(self.Wrequestdata)
        self.TWmain.addTab(self.tabRequest, "")
        self.tabReceived = QtGui.QWidget()
        self.tabReceived.setObjectName("tabReceived")
        self.verticalLayout_8 = QtGui.QVBoxLayout(self.tabReceived)
        self.verticalLayout_8.setObjectName("verticalLayout_8")
        self.Wreceivedbar = QtGui.QWidget(self.tabReceived)
        self.Wreceivedbar.setMaximumSize(QtCore.QSize(16777215, 27))
        self.Wreceivedbar.setObjectName("Wreceivedbar")
        self.horizontalLayout_5 = QtGui.QHBoxLayout(self.Wreceivedbar)
        self.horizontalLayout_5.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_5.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_5.setObjectName("horizontalLayout_5")
        self.Ldatashow = QtGui.QLabel(self.Wreceivedbar)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Maximum, QtGui.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.Ldatashow.sizePolicy().hasHeightForWidth())
        self.Ldatashow.setSizePolicy(sizePolicy)
        self.Ldatashow.setText("")
        self.Ldatashow.setObjectName("Ldatashow")
        self.horizontalLayout_5.addWidget(self.Ldatashow)
        self.CBdatashow = QtGui.QComboBox(self.Wreceivedbar)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Maximum, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.CBdatashow.sizePolicy().hasHeightForWidth())
        self.CBdatashow.setSizePolicy(sizePolicy)
        self.CBdatashow.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.CBdatashow.setObjectName("CBdatashow")
        self.horizontalLayout_5.addWidget(self.CBdatashow)
        self.Ldatashowfile = QtGui.QLabel(self.Wreceivedbar)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Maximum, QtGui.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.Ldatashowfile.sizePolicy().hasHeightForWidth())
        self.Ldatashowfile.setSizePolicy(sizePolicy)
        self.Ldatashowfile.setText("")
        self.Ldatashowfile.setObjectName("Ldatashowfile")
        self.horizontalLayout_5.addWidget(self.Ldatashowfile)
        self.Bdataopen = QtGui.QPushButton(self.Wreceivedbar)
        self.Bdataopen.setMaximumSize(QtCore.QSize(80, 16777215))
        self.Bdataopen.setObjectName("Bdataopen")
        self.horizontalLayout_5.addWidget(self.Bdataopen)
        self.space4 = QtGui.QLabel(self.Wreceivedbar)
        self.space4.setText("")
        self.space4.setObjectName("space4")
        self.horizontalLayout_5.addWidget(self.space4)
        self.Lrecsattype = QtGui.QLabel(self.Wreceivedbar)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Maximum, QtGui.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.Lrecsattype.sizePolicy().hasHeightForWidth())
        self.Lrecsattype.setSizePolicy(sizePolicy)
        self.Lrecsattype.setObjectName("Lrecsattype")
        self.horizontalLayout_5.addWidget(self.Lrecsattype)
        self.CBrectype = QtGui.QComboBox(self.Wreceivedbar)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Maximum, QtGui.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.CBrectype.sizePolicy().hasHeightForWidth())
        self.CBrectype.setSizePolicy(sizePolicy)
        self.CBrectype.setObjectName("CBrectype")
        self.horizontalLayout_5.addWidget(self.CBrectype)
        self.verticalLayout_8.addWidget(self.Wreceivedbar)
        self.Wreceiveddata = QtGui.QWidget(self.tabReceived)
        self.Wreceiveddata.setObjectName("Wreceiveddata")
        self.verticalLayout_8.addWidget(self.Wreceiveddata)
        self.TWmain.addTab(self.tabReceived, "")
        self.tabSignal = QtGui.QWidget()
        self.tabSignal.setObjectName("tabSignal")
        self.horizontalLayout_7 = QtGui.QHBoxLayout(self.tabSignal)
        self.horizontalLayout_7.setObjectName("horizontalLayout_7")
        self.TWsignal = QtGui.QTabWidget(self.tabSignal)
        self.TWsignal.setTabPosition(QtGui.QTabWidget.West)
        self.TWsignal.setObjectName("TWsignal")
        self.tabBeacon = QtGui.QWidget()
        self.tabBeacon.setObjectName("tabBeacon")
        self.TWsignal.addTab(self.tabBeacon, "")
        self.tabTLTC = QtGui.QWidget()
        self.tabTLTC.setObjectName("tabTLTC")
        self.TWsignal.addTab(self.tabTLTC, "")
        self.horizontalLayout_7.addWidget(self.TWsignal)
        self.GBsignalconfig = QtGui.QGroupBox(self.tabSignal)
        self.GBsignalconfig.setMaximumSize(QtCore.QSize(300, 16777215))
        self.GBsignalconfig.setObjectName("GBsignalconfig")
        self.horizontalLayout_7.addWidget(self.GBsignalconfig)
        self.TWmain.addTab(self.tabSignal, "")
        self.tabAntenna = QtGui.QWidget()
        self.tabAntenna.setObjectName("tabAntenna")
        self.TWmain.addTab(self.tabAntenna, "")
        self.verticalLayout.addWidget(self.TWmain)
        self.TEeventlog = QtGui.QTextEdit(self.centralwidget)
        self.TEeventlog.setMinimumSize(QtCore.QSize(0, 80))
        self.TEeventlog.setMaximumSize(QtCore.QSize(16777215, 80))
        self.TEeventlog.setReadOnly(True)
        self.TEeventlog.setObjectName("TEeventlog")
        self.verticalLayout.addWidget(self.TEeventlog)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtGui.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1135, 25))
        self.menubar.setObjectName("menubar")
        self.menuFile = QtGui.QMenu(self.menubar)
        self.menuFile.setObjectName("menuFile")
        self.menuOptions = QtGui.QMenu(self.menubar)
        self.menuOptions.setObjectName("menuOptions")
        self.menuHelp = QtGui.QMenu(self.menubar)
        self.menuHelp.setObjectName("menuHelp")
        self.menuView = QtGui.QMenu(self.menubar)
        self.menuView.setObjectName("menuView")
        self.menuEvent_log = QtGui.QMenu(self.menuView)
        self.menuEvent_log.setObjectName("menuEvent_log")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtGui.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.actionToolbar = QtGui.QAction(MainWindow)
        self.actionToolbar.setObjectName("actionToolbar")
        self.actionSettings = QtGui.QAction(MainWindow)
        self.actionSettings.setObjectName("actionSettings")
        self.actionExit = QtGui.QAction(MainWindow)
        self.actionExit.setObjectName("actionExit")
        self.actionAbout = QtGui.QAction(MainWindow)
        self.actionAbout.setObjectName("actionAbout")
        self.actionLower_side = QtGui.QAction(MainWindow)
        self.actionLower_side.setObjectName("actionLower_side")
        self.actionRight_side = QtGui.QAction(MainWindow)
        self.actionRight_side.setObjectName("actionRight_side")
        self.actionLeft_side = QtGui.QAction(MainWindow)
        self.actionLeft_side.setObjectName("actionLeft_side")
        self.actionUnshow = QtGui.QAction(MainWindow)
        self.actionUnshow.setObjectName("actionUnshow")
        self.actionFullscreen = QtGui.QAction(MainWindow)
        self.actionFullscreen.setObjectName("actionFullscreen")
        self.menuFile.addAction(self.actionExit)
        self.menuOptions.addAction(self.actionSettings)
        self.menuHelp.addAction(self.actionAbout)
        self.menuEvent_log.addAction(self.actionLower_side)
        self.menuEvent_log.addAction(self.actionRight_side)
        self.menuEvent_log.addAction(self.actionLeft_side)
        self.menuEvent_log.addAction(self.actionUnshow)
        self.menuView.addAction(self.actionToolbar)
        self.menuView.addAction(self.menuEvent_log.menuAction())
        self.menuView.addAction(self.actionFullscreen)
        self.menubar.addAction(self.menuFile.menuAction())
        self.menubar.addAction(self.menuOptions.menuAction())
        self.menubar.addAction(self.menuView.menuAction())
        self.menubar.addAction(self.menuHelp.menuAction())

        self.retranslateUi(MainWindow)
        self.TWmain.setCurrentIndex(0)
        self.TWsignal.setCurrentIndex(1)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        self.Lsdrdvc.setText(QtGui.QApplication.translate("MainWindow", "SDR Device:", None, QtGui.QApplication.UnicodeUTF8))
        self.Lsdrrate.setText(QtGui.QApplication.translate("MainWindow", "Sample rate:", None, QtGui.QApplication.UnicodeUTF8))
        self.TBstartsdr.setToolTip(QtGui.QApplication.translate("MainWindow", "Start/Stop SDR", None, QtGui.QApplication.UnicodeUTF8))
        self.TBstartsdr.setText(QtGui.QApplication.translate("MainWindow", "Start SDR", None, QtGui.QApplication.UnicodeUTF8))
        self.TBsenddataread.setToolTip(QtGui.QApplication.translate("MainWindow", "Send data read to server", None, QtGui.QApplication.UnicodeUTF8))
        self.TBsenddataread.setText(QtGui.QApplication.translate("MainWindow", "Send dataread", None, QtGui.QApplication.UnicodeUTF8))
        self.TBconfig.setToolTip(QtGui.QApplication.translate("MainWindow", "Configurations", None, QtGui.QApplication.UnicodeUTF8))
        self.TBconfig.setText(QtGui.QApplication.translate("MainWindow", "Config", None, QtGui.QApplication.UnicodeUTF8))
        self.TBping.setToolTip(QtGui.QApplication.translate("MainWindow", "Ping", None, QtGui.QApplication.UnicodeUTF8))
        self.TBping.setText(QtGui.QApplication.translate("MainWindow", "Ping", None, QtGui.QApplication.UnicodeUTF8))
        self.TBsendreq.setToolTip(QtGui.QApplication.translate("MainWindow", "Send request", None, QtGui.QApplication.UnicodeUTF8))
        self.TBsendreq.setText(QtGui.QApplication.translate("MainWindow", "Send request", None, QtGui.QApplication.UnicodeUTF8))
        self.Lbeaconfreq.setText(QtGui.QApplication.translate("MainWindow", "Beacon:", None, QtGui.QApplication.UnicodeUTF8))
        self.SBbeaconfreq.setSuffix(QtGui.QApplication.translate("MainWindow", " MHz", None, QtGui.QApplication.UnicodeUTF8))
        self.Ltltc.setText(QtGui.QApplication.translate("MainWindow", "TLTC:   ", None, QtGui.QApplication.UnicodeUTF8))
        self.SBtltcfreq.setSuffix(QtGui.QApplication.translate("MainWindow", " MHz", None, QtGui.QApplication.UnicodeUTF8))
        self.Lsalelliteinfo.setText(QtGui.QApplication.translate("MainWindow", "Satellite flight info", None, QtGui.QApplication.UnicodeUTF8))
        self.TWmain.setTabText(self.TWmain.indexOf(self.tabFlight), QtGui.QApplication.translate("MainWindow", "Flight Data", None, QtGui.QApplication.UnicodeUTF8))
        self.Lcfgfile.setText(QtGui.QApplication.translate("MainWindow", "Config. file:", None, QtGui.QApplication.UnicodeUTF8))
        self.Bcfgopen.setText(QtGui.QApplication.translate("MainWindow", "Open", None, QtGui.QApplication.UnicodeUTF8))
        self.Bcfgsaveas.setText(QtGui.QApplication.translate("MainWindow", "Save As", None, QtGui.QApplication.UnicodeUTF8))
        self.Bcheckall.setText(QtGui.QApplication.translate("MainWindow", "Check All", None, QtGui.QApplication.UnicodeUTF8))
        self.Buncheckall.setText(QtGui.QApplication.translate("MainWindow", "Uncheck All", None, QtGui.QApplication.UnicodeUTF8))
        self.Lreqsattype.setText(QtGui.QApplication.translate("MainWindow", "Satellite:", None, QtGui.QApplication.UnicodeUTF8))
        self.TWmain.setTabText(self.TWmain.indexOf(self.tabRequest), QtGui.QApplication.translate("MainWindow", "Request Data", None, QtGui.QApplication.UnicodeUTF8))
        self.Bdataopen.setText(QtGui.QApplication.translate("MainWindow", "Open", None, QtGui.QApplication.UnicodeUTF8))
        self.Lrecsattype.setText(QtGui.QApplication.translate("MainWindow", "Satellite:", None, QtGui.QApplication.UnicodeUTF8))
        self.TWmain.setTabText(self.TWmain.indexOf(self.tabReceived), QtGui.QApplication.translate("MainWindow", "Received Data", None, QtGui.QApplication.UnicodeUTF8))
        self.TWsignal.setTabText(self.TWsignal.indexOf(self.tabBeacon), QtGui.QApplication.translate("MainWindow", "Beacon", None, QtGui.QApplication.UnicodeUTF8))
        self.TWsignal.setTabText(self.TWsignal.indexOf(self.tabTLTC), QtGui.QApplication.translate("MainWindow", "TLTC", None, QtGui.QApplication.UnicodeUTF8))
        self.GBsignalconfig.setTitle(QtGui.QApplication.translate("MainWindow", "Signal Configuration", None, QtGui.QApplication.UnicodeUTF8))
        self.TWmain.setTabText(self.TWmain.indexOf(self.tabSignal), QtGui.QApplication.translate("MainWindow", "Signal Data", None, QtGui.QApplication.UnicodeUTF8))
        self.TWmain.setTabText(self.TWmain.indexOf(self.tabAntenna), QtGui.QApplication.translate("MainWindow", "Antenna", None, QtGui.QApplication.UnicodeUTF8))
        self.TEeventlog.setHtml(QtGui.QApplication.translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'Ubuntu\'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.menuFile.setTitle(QtGui.QApplication.translate("MainWindow", "File", None, QtGui.QApplication.UnicodeUTF8))
        self.menuOptions.setTitle(QtGui.QApplication.translate("MainWindow", "Options", None, QtGui.QApplication.UnicodeUTF8))
        self.menuHelp.setTitle(QtGui.QApplication.translate("MainWindow", "Help", None, QtGui.QApplication.UnicodeUTF8))
        self.menuView.setTitle(QtGui.QApplication.translate("MainWindow", "View", None, QtGui.QApplication.UnicodeUTF8))
        self.menuEvent_log.setTitle(QtGui.QApplication.translate("MainWindow", "Event log", None, QtGui.QApplication.UnicodeUTF8))
        self.actionToolbar.setText(QtGui.QApplication.translate("MainWindow", "Toolbar", None, QtGui.QApplication.UnicodeUTF8))
        self.actionSettings.setText(QtGui.QApplication.translate("MainWindow", "Settings", None, QtGui.QApplication.UnicodeUTF8))
        self.actionExit.setText(QtGui.QApplication.translate("MainWindow", "Exit", None, QtGui.QApplication.UnicodeUTF8))
        self.actionAbout.setText(QtGui.QApplication.translate("MainWindow", "About", None, QtGui.QApplication.UnicodeUTF8))
        self.actionLower_side.setText(QtGui.QApplication.translate("MainWindow", "Lower side", None, QtGui.QApplication.UnicodeUTF8))
        self.actionRight_side.setText(QtGui.QApplication.translate("MainWindow", "Right side", None, QtGui.QApplication.UnicodeUTF8))
        self.actionLeft_side.setText(QtGui.QApplication.translate("MainWindow", "Left side", None, QtGui.QApplication.UnicodeUTF8))
        self.actionUnshow.setText(QtGui.QApplication.translate("MainWindow", "Unshow", None, QtGui.QApplication.UnicodeUTF8))
        self.actionFullscreen.setText(QtGui.QApplication.translate("MainWindow", "Fullscreen", None, QtGui.QApplication.UnicodeUTF8))

